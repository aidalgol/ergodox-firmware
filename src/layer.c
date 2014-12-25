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

#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include "lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "lib/key-functions.h"
#include "controller.h"
#include "matrix.h"
#include "led.h"
#include "layer.h"

#define  MAX_ACTIVE_LAYERS  20

static kb_matrix _layer_kb_is_pressed;
static kb_matrix _layer_kb_was_pressed;
kb_matrix *layer_kb_is_pressed = &_layer_kb_is_pressed;
kb_matrix *layer_kb_was_pressed = &_layer_kb_was_pressed;

uint8_t layer_pressed[KB_ROWS][KB_COLUMNS];

uint8_t current_layer = 0;
uint8_t current_layer_offset = 0;
uint8_t current_row = 0;
uint8_t current_col = 0;
bool    layer_is_pressed = false;
bool    layer_was_pressed = false;
bool    layer_any_non_trans_key_pressed = false;
bool    layer_trans_key_pressed = false;

struct layers {
  uint8_t layer;
  uint8_t id;
  uint8_t sticky;
};

struct layers layers[MAX_ACTIVE_LAYERS];
uint8_t       layers_head = 0;
uint8_t       layers_ids_in_use[MAX_ACTIVE_LAYERS] = {true};

/*
 * Exec key
 * - Execute the keypress or keyrelease function (if it exists) of the key at
 *   the current possition.
 */
void layer_exec_key(void)
{
  void (*key_function)(void) =
    ( (layer_is_pressed)
      ? kb_layout_press_get(current_layer, current_row, current_col)
      : kb_layout_release_get(current_layer, current_row, current_col) );

  if (key_function)
    (*key_function)();

  // If the current layer is in the sticky once up state and a key defined
  //  for this layer (a non-transparent key) was pressed, pop the layer
  if (layers[layers_head].sticky == eStickyOnceUp && layer_any_non_trans_key_pressed)
    layer_pop_id(layers_head);
}

/*
 * peek()
 *
 * Arguments
 * - 'offset': the offset (down the stack) from the head element
 *
 * Returns
 * - success: the layer-number of the requested element (which may be 0)
 * - failure: 0 (default) (out of bounds)
 */
uint8_t layer_peek(uint8_t offset)
{
  if (offset <= layers_head)
    return layers[layers_head - offset].layer;

  return 0;  // default, or error
}

uint8_t layer_peek_sticky(uint8_t offset)
{
  if (offset <= layers_head)
    return layers[layers_head - offset].sticky;

  return 0;  // default, or error
}

/*
 * push()
 *
 * Arguments
 * - 'layer': the layer-number to push to the top of the stack
 *
 * Returns
 * - success: the id assigned to the newly added element
 * - failure: 0 (the stack was already full)
 */
uint8_t layer_push(uint8_t layer, uint8_t sticky)
{
  // look for an available id
  for (uint8_t id=1; id<MAX_ACTIVE_LAYERS; id++) {
    // if one is found
    if (layers_ids_in_use[id] == false) {
      layers_ids_in_use[id] = true;
      layers_head++;
      layers[layers_head].layer = layer;
      layers[layers_head].id = id;
      layers[layers_head].sticky = sticky;
      return id;
    }
  }

  return 0;  // default, or error
}

/*
 * pop_id()
 *
 * Arguments
 * - 'id': the id of the element to pop from the stack
 */
void layer_pop_id(uint8_t id)
{
  // look for the element with the id we want to pop
  for (uint8_t element=1; element<=layers_head; element++)
    // if we find it
    if (layers[element].id == id) {
      // move all layers above it down one
      for (; element<layers_head; element++) {
        layers[element].layer = layers[element+1].layer;
        layers[element].id = layers[element+1].id;
      }
      // reinitialize the topmost (now unused) slot
      layers[layers_head].layer = 0;
      layers[layers_head].id = 0;
      // record keeping
      layers_ids_in_use[id] = false;
      layers_head--;
    }
}
