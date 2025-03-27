
PHONY: build
PHONY: deploy
PHONY: clean

# Sources & Outputs

SOURCES := 	main.c \
			startup.c

LINKER_FILE := stm32_U585A_linker_script.ld

OUTPUT := blinker.elf

# Set those to appropriate paths if the GNU suite tools or OpenOCD are not in PATH

CC := arm-none-eabi-gcc

OPEN_OCD_PATH := 
INTERFACE_SCRIPT_PATH := interface/stlink.cfg
TARGET_SCRIPT_PATH := target/stm32u5x.cfg

# Flags

CC_FLAGS := -mthumb -mcpu=cortex-m33
LINKER_FLAGS := -T $(LINKER_FILE) -nostdlib

build:
	$(CC) $(SOURCES) -o $(OUTPUT) $(CC_FLAGS) $(LINKER_FLAGS)

deploy:
	$(OPEN_OCD_PATH)openocd -f $(INTERFACE_SCRIPT_PATH) -f $(TARGET_SCRIPT_PATH) -c "program $(OUTPUT) verify reset exit"

clean:
	del $(OUTPUT)