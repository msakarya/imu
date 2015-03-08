# Sources

SRCS = main.c stm32f4xx_it.c system_stm32f4xx.c syscalls.c utils.c MPU6050.c

# Project name

PROJ_NAME=stm32f4_sample
OUTPATH=build

OCDFLAGS   = -f board/stm32f4discovery.cfg
GDBFLAGS   = 
###################################################

# Check for valid float argument
# NOTE that you have to run make clan after
# changing these as hardfloat and softfloat are not
# binary compatible
ifneq ($(FLOAT_TYPE), hard)
ifneq ($(FLOAT_TYPE), soft)
override FLOAT_TYPE = hard
#override FLOAT_TYPE = soft
endif
endif

###################################################
PREFIX     = arm-none-eabi
BINPATH=/home/mustafa/install/gcc-arm-none-eabi/bin
CC=$(BINPATH)/arm-none-eabi-gcc
OBJCOPY=$(BINPATH)/arm-none-eabi-objcopy
SIZE=$(BINPATH)/arm-none-eabi-size

GDB        = $(BINPATH)/$(PREFIX)-gdb
OCD        = openocd

CFLAGS  = -std=gnu99 -g -O2 -Wall -Tstm32_flash.ld
CFLAGS += -mlittle-endian -mthumb -mthumb-interwork -nostartfiles -mcpu=cortex-m4

ifeq ($(FLOAT_TYPE), hard)
CFLAGS += -fsingle-precision-constant -Wdouble-promotion
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
#CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
else
CFLAGS += -msoft-float
endif

###################################################

vpath %.c src
vpath %.a lib

ROOT=$(shell pwd)

CFLAGS += -Iinc -Ilib -Ilib/inc 
CFLAGS += -Ilib/inc/core -Ilib/inc/peripherals 

SRCS += lib/startup_stm32f4xx.s # add startup file to build

OBJS = $(SRCS:.c=.o)

###################################################

.PHONY: lib proj

all: lib proj
	$(SIZE) $(OUTPATH)/$(PROJ_NAME).elf

lib:
	$(MAKE) -C lib FLOAT_TYPE=$(FLOAT_TYPE)

proj: 	$(OUTPATH)/$(PROJ_NAME).elf

$(OUTPATH)/$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -Llib -lstm32f4 -lm
	$(OBJCOPY) -O ihex $(OUTPATH)/$(PROJ_NAME).elf $(OUTPATH)/$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(OUTPATH)/$(PROJ_NAME).elf $(OUTPATH)/$(PROJ_NAME).bin

pr: all
	openocd -f interface/stlink-v2.cfg -c "set WORKAREASIZE 0x2000" -f target/stm32f4x_stlink.cfg -c "program $(OUTPATH)/$(PROJ_NAME).elf verify reset"
program: all
	$(OCD) -c "program $(OUTPATH)/$(PROJ_NAME).elf verify reset" $(OCDFLAGS)

debug:
	$(GDB) $(OUTPATH)/$(PROJ_NAME).elf -ex "target remote | openocd $(OCDFLAGS) -c 'gdb_port pipe'" \
		-ex "monitor reset halt" \
		-ex "load" $(GDBFLAGS) 

clean:
	rm -f *.o
	rm -f $(OUTPATH)/$(PROJ_NAME).elf
	rm -f $(OUTPATH)/$(PROJ_NAME).hex
	rm -f $(OUTPATH)/$(PROJ_NAME).bin
	$(MAKE) clean -C lib # Remove this line if you don't want to clean the libs as well
	
