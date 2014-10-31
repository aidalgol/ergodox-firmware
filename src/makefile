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

FORMAT := ihex        # The program binary's format
MCU    := atmega32u4  # Processor type (for teensy 2.0)
BOARD  := teensy-2-0  # See the libraries you're using for what's available
F_CPU  := 16000000    # Processor speed in Hz; must match initialization in source

SRC := $(wildcard *.c)
KEYBOARD := $(strip $(KEYBOARD))
LAYOUT   := $(strip $(LAYOUT))

SRC += $(wildcard keyboard/$(KEYBOARD)*.c)
SRC += $(wildcard keyboard/$(KEYBOARD)/*.c)
SRC += $(wildcard keyboard/$(KEYBOARD)/controller/*.c)
SRC += $(wildcard keyboard/$(KEYBOARD)/layout/$(LAYOUT)*.c)
# Library files
# - should be last in the list of files to compile, in case there are default
#   macros that have to be overridden in other source files
SRC += $(wildcard lib/*.c)
SRC += $(wildcard lib/*/*.c)
SRC += $(wildcard lib/*/*/*.c)
SRC += $(wildcard lib-other/*.c)
SRC += $(wildcard lib-other/*/*.c)
SRC += $(wildcard lib-other/*/*/*.c)

OBJ = $(SRC:%.c=%.o)

CFLAGS_CPU := -mmcu=$(MCU)      # processor type of the Teensy 2.0
CFLAGS_CPU += -DF_CPU=$(F_CPU)  # processor frequency; must match initialization in source

CFLAGS_MAKEFILE_DEFINES := -DMAKEFILE_BOARD='$(strip $(BOARD))'
CFLAGS_MAKEFILE_DEFINES += -DMAKEFILE_KEYBOARD='$(strip $(KEYBOARD))'
CFLAGS_MAKEFILE_DEFINES += -DMAKEFILE_KEYBOARD_LAYOUT='$(strip $(LAYOUT))'
CFLAGS_MAKEFILE_DEFINES += -DMAKEFILE_DEBOUNCE_TIME='$(strip $(DEBOUNCE_TIME))'
CFLAGS_MAKEFILE_DEFINES += -DMAKEFILE_LED_BRIGHTNESS='$(strip $(LED_BRIGHTNESS))'

CFLAGS_WARNINGS := -Wall -Wstrict-prototypes
CFLAGS_OPTIMISATIONS := -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections
CFLAGS := -std=gnu99 $(CFLAGS_CPU) $(CFLAGS_MAKEFILE_DEFINES) $(CFLAGS_WARNINGS) $(CFLAGS_OPTIMISATIONS)

# generate a link map with a cross reference table.
LDFLAGS := -Wl,-Map=$(strip $(TARGET)).map,--cref
# Enables some platform-specific linker optimizations.
LDFLAGS += -Wl,--relax
# Discard unused functions and data.
LDFLAGS += -Wl,--gc-sections

GEN_DEP_FLAGS += -MMD -MP -MF $@.dep  # generate dependency files


CC      := avr-gcc
OBJCOPY := avr-objcopy
SIZE    := avr-size


.PHONY: all clean

all: $(TARGET).hex $(TARGET).eep
	$(SIZE) --target=$(FORMAT) $(TARGET).hex
	$(SIZE) --target=$(FORMAT) $(TARGET).eep
	@echo 'you can load "$(TARGET).hex" and "$(TARGET).eep" onto the'
	@echo 'Teensy using the Teensy loader'

clean:
	@echo --- cleaning ---
	rm -f $(TARGET).*
	find -name \*.o -delete -or -name \*.o.dep -delete

%.hex: %.elf
	@echo --- making $@ ---
	$(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature $< $@

%.eep: %.elf
	@echo --- making $@ ---
	$(OBJCOPY) -O $(FORMAT) \
		-j .eeprom \
		--set-section-flags=.eeprom="alloc,load" \
		--change-section-lma .eeprom=0 \
		--no-change-warnings \
		$< $@ || exit 0

%.elf: $(OBJ)
	@echo --- making $@ ---
	$(CC) $(CFLAGS) $(LDFLAGS) $^ --output $@

%.o: %.c
	@echo --- making $@ ---
	$(CC) -c $(CFLAGS) $(GEN_DEP_FLAGS) $< -o $@


-include $(OBJ:%=%.dep)
