# makefile for the ergoDOX firmware
# Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
# Copyright (C) 2014  Aidan Gauland <aidalgol@amuri.net>
# Released under The MIT License (MIT) (see "license.md")
#
# - .h file dependencies are automatically generated
#
# - This makefile was originally (extensively) modified from the WinAVR makefile
#   template in <http://pjrc.com/teensy/usb_keyboard.zip>, mostly by removing
#   stuff.

include makefile-options

# The program binary's format
FORMAT := ihex
# Processor type (for teensy 2.0)
MCU    := atmega32u4
# See the libraries you're using for what's available
BOARD  := teensy-2-0
# Processor speed in Hz; must match initialization in source
F_CPU  := 16000000

SRC := $(wildcard *.c)
LAYOUT   := $(strip $(LAYOUT))

SRC += $(wildcard *.c)
SRC += $(wildcard controller/*.c)
SRC += $(wildcard layout/$(LAYOUT)*.c)
# Library files
# - should be last in the list of files to compile, in case there are default
#   macros that have to be overridden in other source files
SRC += $(wildcard lib/key-functions/private.c)
SRC += $(wildcard lib/key-functions/public/*.c)
SRC += $(wildcard lib/teensy-2-twi.c)
# SRC += $(wildcard lib/usb/*.c) # TODO
SRC += $(wildcard lib-other/pjrc/usb_keyboard/usb_keyboard.c)


OBJ = $(SRC:%.c=%.o)

# Processor type of the Teensy 2.0
CFLAGS_CPU := -mmcu=$(MCU)
# Processor frequency; must match initialization in source
CFLAGS_CPU += -DF_CPU=$(F_CPU)

CFLAGS_MAKEFILE_DEFINES := -DMAKEFILE_BOARD='$(strip $(BOARD))'
CFLAGS_MAKEFILE_DEFINES += -DMAKEFILE_KEYBOARD='$(strip $(KEYBOARD))'
CFLAGS_MAKEFILE_DEFINES += -DMAKEFILE_KEYBOARD_LAYOUT='$(strip $(LAYOUT))'
CFLAGS_MAKEFILE_DEFINES += -DMAKEFILE_DEBOUNCE_TIME='$(strip $(DEBOUNCE_TIME))'
CFLAGS_MAKEFILE_DEFINES += -DMAKEFILE_LED_BRIGHTNESS='$(strip $(LED_BRIGHTNESS))'

# Use -Wno-main because main never returns, so we want main to have a void return value.
CFLAGS_WARNINGS := -Wall -Wextra -Wstrict-prototypes -Werror -Wno-main
CFLAGS_OPTIMISATIONS := -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections
CFLAGS := -std=gnu99 $(CFLAGS_CPU) $(CFLAGS_MAKEFILE_DEFINES) $(CFLAGS_WARNINGS) $(CFLAGS_OPTIMISATIONS)

# generate a link map with a cross reference table.
LDFLAGS := -Wl,-Map=$(strip $(TARGET)).map,--cref
# Enables some platform-specific linker optimizations.
LDFLAGS += -Wl,--relax
# Discard unused functions and data.
LDFLAGS += -Wl,--gc-sections

# Generate dependency files
GEN_DEP_FLAGS += -MMD -MP -MF $@.dep


CC      := avr-gcc
OBJCOPY := avr-objcopy
SIZE    := avr-size


.PHONY: all clean

all: $(TARGET).hex $(TARGET).eep
	@echo "You can now load $(TARGET).hex and $(TARGET).eep onto the"
	@echo "Teensy using the Teensy loader."

clean:
	@echo "Cleaning build environment"
	rm -f $(TARGET).*
	find -name \*.o -delete -or -name \*.o.dep -delete

$(TARGET).hex: $(TARGET).elf
	@echo "Generating hex file from ELF"
	$(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature $< $@

$(TARGET).eep: $(TARGET).elf
	@echo "Generating EEPROM file from ELF"
	$(OBJCOPY) -O $(FORMAT) \
		-j .eeprom \
		--set-section-flags=.eeprom="alloc,load" \
		--change-section-lma .eeprom=0 \
		--no-change-warnings \
		$< $@ || exit 0

$(TARGET).elf: $(OBJ)
	@echo "Linking objects into ELF"
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ --output $@

%.o: %.c
	@echo Compiling $@
	@$(CC) -c $(CFLAGS) $(GEN_DEP_FLAGS) $< -o $@


-include $(OBJ:%=%.dep)
