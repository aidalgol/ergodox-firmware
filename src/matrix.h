/* ----------------------------------------------------------------------------
 * ergoDOX : key matrix
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#ifndef KEYBOARD__ERGODOX__MATRIX_h
#define KEYBOARD__ERGODOX__MATRIX_h

// ROWS and COLUMNS must match that of the PCB
#define KB_ROWS      6
#define KB_COLUMNS  14
#define KB_LAYERS   10

#include <stdbool.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include "lib/data-types/misc.h"
#include "layout.h"

typedef bool kb_matrix[KB_ROWS][KB_COLUMNS];

/* mapping from spatial position to matrix position
 * - spatial position: where the key is spatially, relative to other
 *   keys both on the keyboard and in the layout
 * - matrix position: the coordinate in the matrix to which a key is
 *   scanned by the update functions
 *
 * - location numbers are in the format `row##column`, where both 'row'
 *   and 'column' are single digit hex numbers corresponding to the
 *   matrix position (which also corresponds to the row and column pin
 *   labels used in the teensy and mcp23018 files)
 *
 * - coordinates
 *   - optional keys
 *     k15, k16 (left hand thumb group)
 *     k17, k18 (right hand thumb group)
 *   - unused keys
 *     k36, k00 (left hand)
 *     k37, k0D (right hand)
 *
 * --- other info -----------------------------------------------------
 *           rows x columns = positions;  used,  unused
 * per hand:    6 x  7      = 42;         40,    2
 *    total:    6 x 14      = 84;         80,    4
 *
 * left hand  : rows 0..5, cols 0..6
 * right hand : rows 0..5, cols 7..D
 * --------------------------------------------------------------------
 */
#define KB_MATRIX_LAYER(\
    /* left hand, spatial positions */ \
    k50,k51,k52,k53,k54,k55,k56,\
    k40,k41,k42,k43,k44,k45,k46,\
    k30,k31,k32,k33,k34,k35,\
    k20,k21,k22,k23,k24,k25,k26,\
    k10,k11,k12,k13,k14,\
                        k05,k06,\
                            k04,\
                    k03,k02,k01,\
    /* right hand, spatial positions */ \
    k57,k58,k59,k5A,k5B,k5C,k5D,\
    k47,k48,k49,k4A,k4B,k4C,k4D,\
        k38,k39,k3A,k3B,k3C,k3D,\
    k27,k28,k29,k2A,k2B,k2C,k2D,\
            k19,k1A,k1B,k1C,k1D,\
    k07,k08,\
    k09,\
    k0C,k0B,k0A) \
 \
/* matrix positions */ \
{{  0,k01,k02,k03,k04,k05,k06, k07,k08,k09,k0A,k0B,k0C,  0},\
 {k10,k11,k12,k13,k14,  0,  0,   0,  0,k19,k1A,k1B,k1C,k1D},\
 {k20,k21,k22,k23,k24,k25,k26, k27,k28,k29,k2A,k2B,k2C,k2D},\
 {k30,k31,k32,k33,k34,k35,  0,   0,k38,k39,k3A,k3B,k3C,k3D},\
 {k40,k41,k42,k43,k44,k45,k46, k47,k48,k49,k4A,k4B,k4C,k4D},\
 {k50,k51,k52,k53,k54,k55,k56, k57,k58,k59,k5A,k5B,k5C,k5D}}


/* matrix 'get' macros, and `extern` matrix declarations
 *
 * These are written for when the matrices are stored solely in Flash.
 * Layouts may redefine them if they wish and use Flash, RAM, EEPROM,
 * or any combination of the three, as long as they maintain the same
 * interface.
 *
 * - If the macro is overridden, the matrix declaration must be too,
 *   and vice versa.
 *
 * - 'set' functions are optional, and should be defined in the layout
 *   specific '.h'.  They'll require the use of the EEPROM, possibly in
 *   clever conjunction with one of the other two memories (since the
 *   EEPROM is small).  Custom key functions will also need to be
 *   written.
 *
 * - To override these macros with real functions, set the macro equal
 *   to itself (e.g. `#define kb_layout_get kb_layout_get`) and provide
 *   function prototypes, in the layout specific '.h'
 */

// layout
#define kb_layout_get(layer,row,column) \
  ((uint8_t) pgm_read_byte(&(_kb_layout[layer][row][column])))

// layout_press
#define kb_layout_press_get(layer,row,column) \
			((void_funptr_t) pgm_read_word(&(_kb_layout_press[layer][row][column])))

// layout_release
#define kb_layout_release_get(layer,row,column) \
  ((void_funptr_t) pgm_read_word(&(_kb_layout_release[layer][row][column])))

#endif
