/* ----------------------------------------------------------------------------
 * key functions
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#ifndef LIB__KEY_FUNCTIONS__h
#define LIB__KEY_FUNCTIONS__h

#include <stdbool.h>
#include <stdint.h>

// basic
void kbfun_press_release(void);
void kbfun_press_release_preserve_sticky(void);
void kbfun_toggle(void);
void kbfun_transparent(void);
// layer push/pop/sticky functions
void kbfun_layer_push_1(void);
void kbfun_layer_push_2(void);
void kbfun_layer_push_3(void);
void kbfun_layer_push_4(void);
void kbfun_layer_push_5(void);
void kbfun_layer_push_6(void);
void kbfun_layer_push_7(void);
void kbfun_layer_push_8(void);
void kbfun_layer_push_9(void);
void kbfun_layer_push_10(void);
void kbfun_layer_pop_1(void);
void kbfun_layer_pop_2(void);
void kbfun_layer_pop_3(void);
void kbfun_layer_pop_4(void);
void kbfun_layer_pop_5(void);
void kbfun_layer_pop_6(void);
void kbfun_layer_pop_7(void);
void kbfun_layer_pop_8(void);
void kbfun_layer_pop_9(void);
void kbfun_layer_pop_10(void);
void kbfun_layer_sticky_1(void);
void kbfun_layer_sticky_2(void);
void kbfun_layer_sticky_3(void);
void kbfun_layer_sticky_4(void);
void kbfun_layer_sticky_5(void);
void kbfun_layer_sticky_6(void);
void kbfun_layer_sticky_7(void);
void kbfun_layer_sticky_8(void);
void kbfun_layer_sticky_9(void);
void kbfun_layer_sticky_10(void);

// device
void kbfun_jump_to_bootloader(void);

// special
void kbfun_shift_press_release(void);
void kbfun_2_keys_capslock_press_release(void);
void kbfun_layer_push_numpad(void);
void kbfun_layer_pop_numpad(void);
void kbfun_mediakey_press_release(void);

/** aliases **/
// basic
#define  kprrel  &kbfun_press_release
#define  ktog    &kbfun_toggle
#define  ktrans  &kbfun_transparent
// layer push/pop functions
#define  lpush1   &kbfun_layer_push_1
#define  lpush2   &kbfun_layer_push_2
#define  lpush3   &kbfun_layer_push_3
#define  lpush4   &kbfun_layer_push_4
#define  lpush5   &kbfun_layer_push_5
#define  lpush6   &kbfun_layer_push_6
#define  lpush7   &kbfun_layer_push_7
#define  lpush8   &kbfun_layer_push_8
#define  lpush9   &kbfun_layer_push_9
#define  lpush10  &kbfun_layer_push_10
#define  lpop1    &kbfun_layer_pop_1
#define  lpop2    &kbfun_layer_pop_2
#define  lpop3    &kbfun_layer_pop_3
#define  lpop4    &kbfun_layer_pop_4
#define  lpop5    &kbfun_layer_pop_5
#define  lpop6    &kbfun_layer_pop_6
#define  lpop7    &kbfun_layer_pop_7
#define  lpop8    &kbfun_layer_pop_8
#define  lpop9    &kbfun_layer_pop_9
#define  lpop10   &kbfun_layer_pop_10

// device
#define  dbtldr  &kbfun_jump_to_bootloader

// special
#define  sshprre  &kbfun_shift_press_release
#define  s2kcap   &kbfun_2_keys_capslock_press_release
#define  slpunum  &kbfun_layer_push_numpad
#define  slponum  &kbfun_layer_pop_numpad

#endif
