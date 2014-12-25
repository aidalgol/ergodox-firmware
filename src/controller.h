/* ----------------------------------------------------------------------------
 * ergoDOX : controller specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#ifndef KEYBOARD__ERGODOX__CONTROLLER_h
#define KEYBOARD__ERGODOX__CONTROLLER_h

#include <stdint.h>
#include "matrix.h"

uint8_t kb_init(void);
uint8_t kb_update_matrix(kb_matrix matrix);

#endif
