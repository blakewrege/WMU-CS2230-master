# Project name
SOURCE          = pwm.c
# Get base name so we can create .elf file
NAME            = $(basename $(SOURCE))
# MSP430 MCU to compile for
CPU             = msp430g2553
# Optimisation level
OPTIMIZATION    = -O0
# Extra variables
CFLAGS          = -mmcu=$(CPU) $(OPTIMIZATION) -Wall -g
# Libemb library link flags
LIBEMB          = -lshell -lconio -lserial

# Build and link executable
$(NAME).elf: $(SOURCE)
ifeq (,$(findstring libemb,$(shell cat $(SOURCE))))
	msp430-gcc $(CFLAGS) -o $@ $(SOURCE)
else
	msp430-gcc $(CFLAGS) -o $@ $(SOURCE) $(LIBEMB)
endif

# Flash to board with mspdebug
flash: $(NAME).elf
	mspdebug rf2500 "prog $(NAME).elf"

# Erase board
erase:
	mspdebug rf2500 erase

# Clean up temporary files
clean:
	rm -f *.elf

# Remote debug board
debug: $(NAME).elf
	( mspdebug rf2500 "gdb" 1>/dev/null & ); msp430-gdb $(NAME).elf -ex "target remote :2000"