// vim: ts=4 sw=4 sts=4
/* ----------------------------------------------------------------------------
 * main()
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
#include "layer.h"
#include "matrix.h"
#include "led.h"

static kb_matrix kb_was_transparent;

/*
 * main()
 */
void main(void)
{
  kb_init();  // does controller initialization too

  kb_led_state_power_on();

  usb_init();
  while (!usb_configured());
  kb_led_delay_usb_init();  // give the OS time to load drivers, etc.

  kb_led_state_ready();

  for (;;) {
    // swap layer_kb_is_pressed and layer_kb_was_pressed, then update
    kb_matrix *temp = layer_kb_was_pressed;
    layer_kb_was_pressed = layer_kb_is_pressed;
    layer_kb_is_pressed = temp;

    kb_update_matrix(*layer_kb_is_pressed);

    // this loop is responsible to
    // - "execute" keys when they change state
    // - keep track of which layers the keys were on when they were pressed
    //   (so they can be released using the function from that layer)
    //
    // note
    // - everything else is the key function's responsibility
    //   - see the keyboard layout file ("keyboard/ergodox/layout/*.c") for
    //     which key is assigned which function (per layer)
    //   - see "lib/key-functions/public/*.c" for the function definitions
    for (uint8_t row = 0; row < KB_ROWS; row++) {
      for (uint8_t col = 0; col < KB_COLUMNS; col++) {
        layer_is_pressed = (*layer_kb_is_pressed)[row][col];
        layer_was_pressed = (*layer_kb_was_pressed)[row][col];

        if (layer_is_pressed != layer_was_pressed) {
          if (layer_is_pressed) {
            current_layer = layer_peek(0);
            layer_pressed[row][col] = current_layer;
            layer_trans_key_pressed = false;
          } else {
            current_layer = layer_pressed[row][col];
            layer_trans_key_pressed = kb_was_transparent[row][col];
          }

          // set remaining vars, and "execute" key
          current_row          = row;
          current_col          = col;
          current_layer_offset = 0;
          layer_exec_key();
          kb_was_transparent[row][col] = layer_trans_key_pressed;
        }
      }
    }

    // send the USB report (even if nothing's changed)
    usb_keyboard_send();
    usb_extra_consumer_send();
    _delay_ms(DEBOUNCE_TIME);
  }
}
