TARGET = firmware
MCU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = $(MCU) -Wall -O0 -g3 -std=c11
CFLAGS += -Iinclude
LDFLAGS = $(MCU) -T linker.ld -nostartfiles -specs=nosys.specs -Wl,-Map=$(TARGET).map

SRCS = src/main.c src/sevenseg.c src/rtc.c startup_stm32f446xx.s

all: $(TARGET).elf

$(TARGET).elf: $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $@
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

flash: $(TARGET).elf
	st-flash --reset write $(TARGET).bin 0x8000000

clean:
	rm -f $(TARGET).elf $(TARGET).bin $(TARGET).map