COMMON_OBJECTS 	=
CPU 		= msp430g2553
CFLAGS 		= -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

CC		= msp430-elf-gcc
AS		= msp430-elf-as -mcpu=msp430 --traditional-format -mP

all: blinkyBuzzy.elf

blinkyBuzzy.elf: ${COMMON_OBJECTS} buzzer.o wdInterruptHandler.o p2_interrupt_handler.o assembly.o stateMachines.o led.o switches.o blinkyBuzzyMain.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: blinkyBuzzy.elf
	msp430loader.sh blinkyBuzzy.elf

clean:
	rm -f *.o *.elf
