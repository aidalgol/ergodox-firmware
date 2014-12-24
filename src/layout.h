/* ----------------------------------------------------------------------------
 * ergoDOX : layout matrices
 * ----------------------------------------------------------------------------
 * Declarations for the layout const's defined in the layer module.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#ifndef KEYBOARD__ERGODOX__LAYOUT_h
#define KEYBOARD__ERGODOX__LAYOUT_h

extern const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS];
extern const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS];
extern const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS];

#endif
