SOURCE		= interrupt.c
ADDITIONAL	= 
NAME		= $(basename $(SOURCE))
CPU		= msp430g2553
OPTIMIZATION	= -O0
CFLAGS		= -mmcu=$(CPU) $(OPTIMIZATION) -Wall -g
LIBEMB		= -lshell -lconio -lserial

$(NAME).elf: $(SOURCE) $(ADDITIONAL)
ifeq (,$(findstring libemb,$(shell cat $(SOURCE))))
	msp430-gcc $(CFLAGS) -o $@ $(SOURCE) $(ADDITIONAL)
else
	msp430-gcc $(CFLAGS) -o $@ $(SOURCE) $(ADDITIONAL) $(LIBEMB)
endif

flash: $(NAME).elf
	mspdebug rf2500 "prog $(NAME).elf"

erase:
	mspdebug rf2500 erase

clean:
	rm -f *.elf

debug: $(NAME).elf
	( mspdebug rf2500 "gdb" 1>/dev/null & ); msp430-gdb $(NAME).elf -ex "target remote :2000"

#msp430-gcc -S -mmcu=msp430g2553 $(source)
asm: $(SOURCE) $(SOURCE)
	msp430-gcc -S -o complex_$(NAME).s $(CFLAGS) $(SOURCE) $(ADDITIONAL)
	msp430-gcc -S -mmcu=msp430g2553 $(SOURCE)