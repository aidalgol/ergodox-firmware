/* ----------------------------------------------------------------------------
 * ergoDOX : layer handling
 * ----------------------------------------------------------------------------
 * We keep track of which layer is foremost by placing it on a stack.  Layers
 * may appear in the stack more than once.  The base layer will always be
 * layer-0.
 *
 * Implemented as a fixed size stack.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#ifndef KEYBOARD__ERGODOX__LAYER_h
#define KEYBOARD__ERGODOX__LAYER_h

#include <stdbool.h>
#include <stdint.h>
#include "matrix.h"

typedef enum StickyState {
  eStickyNone,
  eStickyOnceDown,
  eStickyOnceUp,
  eStickyLock
} StickyState;

extern kb_matrix *layer_kb_is_pressed;
extern kb_matrix *layer_kb_was_pressed;

extern uint8_t layer_pressed[KB_ROWS][KB_COLUMNS];

extern uint8_t current_layer;
extern uint8_t current_layer_offset;
extern uint8_t current_row;
extern uint8_t current_col;
extern bool    layer_is_pressed;
extern bool    layer_was_pressed;
extern bool    layer_any_non_trans_key_pressed;
extern bool    layer_trans_key_pressed;

void layer_exec_key(void);
uint8_t layer_peek(uint8_t offset);
uint8_t layer_peek_sticky(uint8_t offset);
uint8_t layer_push(uint8_t layer, uint8_t sticky);
void layer_pop_id(uint8_t id);

#endif
