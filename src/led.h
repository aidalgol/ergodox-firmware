/* ----------------------------------------------------------------------------
 * ergoDOX : high-level LED-control
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#ifndef KEYBOARD__ERGODOX__LAYOUT__DEFAULT__LED_CONTROL_h
#define KEYBOARD__ERGODOX__LAYOUT__DEFAULT__LED_CONTROL_h

// state and delay macros
#define kb_led_state_power_on() do {            \
    _kb_led_all_set_percent(LED_BRIGHTNESS/10); \
    _kb_led_all_on();                           \
  } while(0)

// note: need to delay for a total of ~1 second
#define kb_led_delay_usb_init() do {            \
    _kb_led_1_set_percent(LED_BRIGHTNESS);      \
    _delay_ms(333);                             \
    _kb_led_2_set_percent(LED_BRIGHTNESS);      \
    _delay_ms(333);                             \
    _kb_led_3_set_percent(LED_BRIGHTNESS);      \
    _delay_ms(333);                             \
  } while(0)

#define kb_led_state_ready() do {               \
    _kb_led_all_off();                          \
    _kb_led_all_set_percent(LED_BRIGHTNESS);    \
  } while(0)

#endif
