if ! ps o command= $$ | grep -q 'bash'; then echo "Please run with bash, not sh"; exit 1; fi; if grep -r $'\r' "$0" > /dev/null; then echo "Incorrect file endings detected. Fixing..."; tr -d '\r' < "$0" > "$0~"; mv "$0~" "$0"; chmod +x "$0"; echo "Please re-run this file"; exit 0; fi;
# NOTE: Use $HOME instead of tilde (~) when in quotes
set -e  # Abort if any command fails
set -o verbose # Show commands being run

# Do NOT run as sudo, it will ask for passwords when needed
# Edit this line to desired, or leave to use .local in HOME directory.
# Path can't have spaces or energia can't compile
INSTALL_PATH_LINUX="$HOME/.local"
INSTALL_PATH_MAC="$HOME/Applications"
# Here was the default before
#INSTALL_PATH_LINUX="/opt"

# Change this to where you downloaded the tgz file
if [ "$(uname)" == "Darwin" ]; then
    DOWNLOADED_PATH="$HOME/Downloads/energia.dmg"
else
    DOWNLOADED_PATH="$HOME/Downloads/energia.tgz"
fi

# Check for needed commands
if ! which unzip > /dev/null; then
    printf "\033[0;31m   unzip command not found, please install it\033[0m\n"
    exit 1
fi

# Handle if file not found
if [ ! -f "$DOWNLOADED_PATH" ]; then
    echo "Unable to find energia at '$DOWNLOADED_PATH'"
    echo "Either move it there or update this script"
    echo

    read -p "Do you want to download it? (y/N) " -n 1 -r
    echo

    if [[ $REPLY =~ ^[Yy]$ ]]; then
        # Download Appropriate Version for Architecture
        printf "\033[0;32m>> Downloading Energia ...\033[0m\n"
        mkdir -p ~/Downloads
        if [ "$(uname)" == "Darwin" ]; then
            curl -# -o ~/Downloads/energia.dmg -kL https://yakko.cs.wmich.edu/~sphinx/energia/energia-0101E0017-macosx-signed.dmg
            DOWNLOADED_PATH="$HOME/Downloads/energia.dmg"
        else
            if [ `getconf LONG_BIT` = "64" ]
            then
                # 64-bit Download
                wget -O ~/Downloads/energia.tgz https://yakko.cs.wmich.edu/~sphinx/energia/energia-0101E0017-linux64.tgz
            else
                # 32-bit Download
                wget -O ~/Downloads/energia.tgz https://yakko.cs.wmich.edu/~sphinx/energia/energia-0101E0017-linux.tgz
            fi
            DOWNLOADED_PATH="$HOME/Downloads/energia.tgz"
        fi
    fi
fi

if [ ! -f "$INSTALL_PATH_LINUX/energia" ]; then
    printf "\033[0;32m>> Removing old installation ...\033[0m\n"
    rm -rf "$INSTALL_PATH_LINUX/energia"
fi

mkdir -p "$INSTALL_PATH_LINUX"
printf "\033[0;32m>> Unpacking ...\033[0m\n"
if [ "$(uname)" == "Darwin" ]; then
    hdiutil attach "$DOWNLOADED_PATH" -quiet
    cp -R "/Volumes/energia-0101E0017-macosx-signed/Energia.app" "$INSTALL_PATH_MAC"
    hdiutil unmount "/Volumes/energia-0101E0017-macosx-signed"
else
    tar -xf "$DOWNLOADED_PATH" -C "$INSTALL_PATH_LINUX" && mv "$INSTALL_PATH_LINUX"/energia* "$INSTALL_PATH_LINUX/energia"
fi

# Append /bin to PATH
printf "\033[0;32m>> Appending PATH ...\033[0m\n"
if [ "$(uname)" == "Darwin" ]; then
    sed -i '' -e '$a\' ~/.bash_profile
    echo 'export PATH='"$INSTALL_PATH_LINUX"'/Energia.app/Contents/Resources/Java/hardware/tools/msp430/bin:$PATH' >> ~/.bash_profile
    echo 'export PATH='"$INSTALL_PATH_LINUX"'/Energia.app/Contents/Resources/Java/hardware/tools/msp430/mspdebug:$PATH' >> ~/.bash_profile
    export PATH="$INSTALL_PATH_LINUX/Energia.app/Contents/Resources/Java/hardware/tools/msp430/bin:$PATH"
    export PATH="$INSTALL_PATH_LINUX/Energia.app/Contents/Resources/Java/hardware/tools/msp430/mspdebug:$PATH"
else
    sed -i -e '$a\' ~/.bashrc
    echo 'export PATH='"$INSTALL_PATH_LINUX"'/energia/hardware/tools/msp430/bin:$PATH' >> ~/.bashrc
    export PATH="$INSTALL_PATH_LINUX/energia/hardware/tools/msp430/bin:$PATH"

    printf "\033[0;32m>> Please enter your password to update udev and groups ...\033[0m\n"

    # Add Rule to udev
    printf "\033[0;32m>> Adding Rule to udev ...\033[0m\n"
    echo 'ATTRS{idVendor}=="0451", ATTRS{idProduct}=="f432", MODE="0660", GROUP="plugdev"' | sudo tee /etc/udev/rules.d/46-TI_launchpad.rules > /dev/null
    if sudo restart udev &> /dev/null; then
        echo
    else
        # Use service instead of restart command, if above failed
        sudo service udev restart
    fi

    # Add User to dialout
    printf "\033[0;32m>> Adding you to dialout group ...\033[0m\n"
    # Ignore errors (caused by already in group)
    if sudo adduser $SUDO_USER dialout &> /dev/null; then
        echo
    fi

fi

# Download Libemb
printf "\033[0;32m>> Downloading Libemb ...\033[0m\n"
if [ "$(uname)" == "Darwin" ]; then
    curl -# -o ~/Downloads/libemb.zip -kL https://github.com/chrissphinx/libemb/archive/master.zip
else
    wget -O ~/Downloads/libemb.zip https://github.com/chrissphinx/libemb/archive/master.zip
fi

# Make & Install Libemb
printf "\033[0;32m>> Installing Libemb ...\033[0m\n"
cd ~/Downloads
unzip -q -u libemb.zip
cd libemb-master
if [ "$(uname)" == "Darwin" ]; then
    INSTDIR="$INSTALL_PATH_MAC/Energia.app/Contents/Resources/Java/hardware/tools/msp430/msp430" TARCH=MSP430 make install --silent
else
    INSTDIR="$INSTALL_PATH_LINUX/energia/hardware/tools/msp430/msp430" TARCH=MSP430 make install --silent
fi
cd

# Cleanup
# Uncomment if you want to remove old files
#rm -rf "$DOWNLOADED_PATH" ~/Downloads/libemb-master ~/Downloads/libemb.zip

# Finished
printf "\033[0;32m>> Done!\033[0m\n"
printf "\033[0;31m   Please logout or restart your computer\n   to access the msp430 toolchain\n   Or you could try just running: source ~/.bashrc Or: source ~/.bash_profile on a mac\033[0m\n"
