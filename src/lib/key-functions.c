/* ----------------------------------------------------------------------------
 * key functions
 * ----------------------------------------------------------------------------
 * These functions may do... pretty much anything rational that they like.  If
 * they want keycodes to be sent to the host in an aggregate report, they're
 * responsible for modifying the appropriate report variables.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#include <avr/interrupt.h>
#include <util/delay.h>
#include "../layer.h"
#include "../lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "../lib/usb/usage-page/keyboard.h"

#define MAX_LAYER_PUSH_POP_FUNCTIONS 10

/* MediaCodeLookupTable is used to translate from enumeration in keyboard.h to
 * consumer key scan code in usb_keyboard.h
 */
static const uint16_t _media_code_lookup_table[] = {
  TRANSPORT_PLAY_PAUSE, /* MEDIAKEY_PLAY_PAUSE */
  TRANSPORT_STOP, /* MEDIAKEY_STOP */
  TRANSPORT_PREV_TRACK, /* MEDIAKEY_PREV_TRACK */
  TRANSPORT_NEXT_TRACK, /* MEDIAKEY_NEXT_TRACK */
  AUDIO_MUTE, /* MEDIAKEY_AUDIO_MUTE */
  AUDIO_VOL_UP, /* MEDIAKEY_AUDIO_VOL_UP */
  AUDIO_VOL_DOWN, /* MEDIAKEY_AUDIO_VOL_DOWN */
};

/* Generate a normal keypress or keyrelease
 *
 * Arguments
 * - press: whether to generate a keypress (true) or keyrelease (false)
 * - keycode: the keycode to use
 *
 * Because of the way USB does things, what this actually does is either add or
 * remove 'keycode' from the list of currently pressed keys, to be sent at the
 * end of the current cycle (see main.c)
 */
static void _kbfun_press_release(bool press, uint8_t keycode)
{
  // no-op
  if (keycode == 0)
    return;

  // modifier keys
  switch (keycode) {
    case KEY_LeftControl:  (press)
               ? (keyboard_modifier_keys |=  (1<<0))
               : (keyboard_modifier_keys &= ~(1<<0));
               return;
    case KEY_LeftShift:    (press)
               ? (keyboard_modifier_keys |=  (1<<1))
               : (keyboard_modifier_keys &= ~(1<<1));
               return;
    case KEY_LeftAlt:      (press)
               ? (keyboard_modifier_keys |=  (1<<2))
               : (keyboard_modifier_keys &= ~(1<<2));
               return;
    case KEY_LeftGUI:      (press)
               ? (keyboard_modifier_keys |=  (1<<3))
               : (keyboard_modifier_keys &= ~(1<<3));
               return;
    case KEY_RightControl: (press)
               ? (keyboard_modifier_keys |=  (1<<4))
               : (keyboard_modifier_keys &= ~(1<<4));
               return;
    case KEY_RightShift:   (press)
               ? (keyboard_modifier_keys |=  (1<<5))
               : (keyboard_modifier_keys &= ~(1<<5));
               return;
    case KEY_RightAlt:     (press)
               ? (keyboard_modifier_keys |=  (1<<6))
               : (keyboard_modifier_keys &= ~(1<<6));
               return;
    case KEY_RightGUI:     (press)
               ? (keyboard_modifier_keys |=  (1<<7))
               : (keyboard_modifier_keys &= ~(1<<7));
               return;
  }

  // all others
  for (uint8_t i=0; i<6; i++) {
    if (press) {
      if (keyboard_keys[i] == 0) {
        keyboard_keys[i] = keycode;
        return;
      }
    } else {
      if (keyboard_keys[i] == keycode) {
        keyboard_keys[i] = 0;
        return;
      }
    }
  }
}

/* Is the given keycode pressed? */
static bool _kbfun_is_pressed(uint8_t keycode)
{
  // modifier keys
  switch (keycode) {
    case KEY_LeftControl:  if (keyboard_modifier_keys & (1<<0))
                 return true;
    case KEY_LeftShift:    if (keyboard_modifier_keys & (1<<1))
                 return true;
    case KEY_LeftAlt:      if (keyboard_modifier_keys & (1<<2))
                 return true;
    case KEY_LeftGUI:      if (keyboard_modifier_keys & (1<<3))
                 return true;
    case KEY_RightControl: if (keyboard_modifier_keys & (1<<4))
                 return true;
    case KEY_RightShift:   if (keyboard_modifier_keys & (1<<5))
                 return true;
    case KEY_RightAlt:     if (keyboard_modifier_keys & (1<<6))
                 return true;
    case KEY_RightGUI:     if (keyboard_modifier_keys & (1<<7))
                 return true;
  }

  // all others
  for (uint8_t i=0; i<6; i++)
    if (keyboard_keys[i] == keycode)
      return true;

  return false;
}

static void _kbfun_mediakey_press_release(bool press, uint8_t keycode)
{
  uint16_t mediakey_code = _media_code_lookup_table[keycode];
  if (press) {
    consumer_key = mediakey_code;
  } else {
    // Only one key can be pressed at a time so only clear the keypress for
    //  active key (most recently pressed)
    if (mediakey_code == consumer_key) {
      consumer_key = 0;
    }
  }
}

/* For reflashing the controller
 *
 * From PJRC (slightly modified):
 * <http://www.pjrc.com/teensy/jump_to_bootloader.html>
 */
void kbfun_jump_to_bootloader(void)
{
	// --- for all Teensy boards ---

	cli();

	// disable watchdog, if enabled
	// disable all peripherals
	UDCON = 1;
	USBCON = (1<<FRZCLK);  // disable USB
	UCSR1B = 0;
	_delay_ms(5);

	// --- Teensy 2.0 specific ---

	EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
	TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
	DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
	PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
	asm volatile("jmp 0x7E00");
}

/* Generate a normal keypress or keyrelease */
void kbfun_press_release(void)
{
	if (!layer_trans_key_pressed)
		layer_any_non_trans_key_pressed = true;
	kbfun_press_release_preserve_sticky();
}

/* Press|Release and preserve top layer sticky key state.  Generate a normal
 * keypress or keyrelease while basing the sticky key state transition on
 * whether kbfun_press_release() was called after kbfun_transparent() generally
 * works in practice, it is not always the desired behavior.  One of the
 * benefits of sticky keys is avoiding key chording, so we want to make sure
 * that standard modifiers do not interrupt the sticky key cycle.  Use
 * kbfun_press_release_preserve_sticky() if you want to define a standard
 * modifier key (shift, control, alt, gui) on the sticky layer instead of
 * defining the key to be transparent for the layer.
 */
void kbfun_press_release_preserve_sticky(void)
{
	uint8_t keycode = kb_layout_get(current_layer, current_row, current_col);
	_kbfun_press_release(layer_is_pressed, keycode);
}

/* Toggle the key pressed or unpressed */
void kbfun_toggle(void)
{
	uint8_t keycode = kb_layout_get(current_layer, current_row, current_col);

	if (_kbfun_is_pressed(keycode))
		_kbfun_press_release(false, keycode);
	else
		_kbfun_press_release(true, keycode);
}

/*  Execute the key that would have been executed if the current layer was not
 *  active.
 */
void kbfun_transparent(void)
{
	layer_trans_key_pressed = true;
	current_layer_offset++;
	current_layer = layer_peek(current_layer_offset);
	layer_pressed[current_row][current_col] = current_layer;
	layer_exec_key();
}

/* ----------------------------------------------------------------------------
 * layer push/pop functions
 * ------------------------------------------------------------------------- */

/* While there are only MAX_LAYER_PUSH_POP_FUNCTIONS number of layer functions,
 * there are MAX_LAYER_PUSH_POP_FUNCTIONS + 1 layer ids because we still have
 * layer 0 even if we will never have a push or pop function for it
 */
static uint8_t layer_ids[MAX_LAYER_PUSH_POP_FUNCTIONS + 1];

/* Push a layer element containing the layer value specified in the keymap to
 * the top of the stack, and record the id of that layer element
 */
static void basic_layer_push(uint8_t local_id)
{
	uint8_t keycode = kb_layout_get(current_layer, current_row, current_col);
	layer_pop_id(layer_ids[local_id]);
	// Only the topmost layer on the stack should be in sticky once state, pop
	//  the top layer if it is in sticky once state
	uint8_t topSticky = layer_peek_sticky(0);
	if (topSticky == eStickyOnceDown || topSticky == eStickyOnceUp) {
		layer_pop_id(layer_peek(0));
	}
	layer_ids[local_id] = layer_push(keycode, eStickyNone);
}

/* Pop the layer element created by the corresponding "layer push" function out
 * of the layer stack (no matter where it is in the stack, without touching any
 * other elements)
 */
static void layer_pop(uint8_t local_id)
{
	layer_pop_id(layer_ids[local_id]);
	layer_ids[local_id] = 0;
}

/* This function gives similar behavior to sticky keys for modifiers available
 * on most operating systems. It is considered an accessibility feature because
 * it alleviates the user from having to hold down modifiers while pressing a
 * key to produce the modified key function. It is useful for fast touch typing
 * because you can avoid chording motions which both strain your hands and take
 * your hands out of home-row position while pressing normal alpha keys.

 * This function emulates the 3-state behavior which is default on OS X and
 * optional in Windows where the modifier cycles between Off->Once->Locked
 * states. This is particularly handy for symbol layers where you typically only
 * type one symbol before you want to return to unmodified typing (layer 0),
 * e.g. 'if (condition) { a = "b" + "c"; }'. If you assign a symbol layer to a
 * thumb key as a layer sticky cycle, you can type the entire line of code
 * without taking your hands out of home row position and you do not need to
 * toggle off the layer after each symbol is pressed, only immediately before
 * keying the symbol.
 *
 * The exact behavior of the layer sticky cycle function is defined as follows
 * for each state:
 *
 *  1) One time down (set on key press) - The layer was not active and the key
 *     has been pressed but not yet released. The layer is pushed in the one
 *     time down state.
 *
 *  2) One time up (set on key release) - The layer was active when the layer
 *     sticky key was released. If a key on this layer (not set to transparent)
 *     was pressed before the key was released, the layer will be popped. If a
 *     non-transparent key was not pressed, the layer is popped and pushed again
 *     in the one time up state.
 *
 *  3) Locked (set on key press) - The layer was active and in the one time up
 *     state when the layer sticky key was pressed again. The layer will be
 *     popped if the function is invoked on a subsequent keypress.
 */
static void layer_sticky(uint8_t local_id)
{
	uint8_t keycode = kb_layout_get(current_layer, current_row, current_col);
	if (layer_is_pressed) {
		uint8_t topLayer = layer_peek(0);
		uint8_t topSticky = layer_peek_sticky(0);
		layer_pop_id(layer_ids[local_id]);
		if (topLayer == local_id) {
			if (topSticky == eStickyOnceUp)
				layer_ids[local_id] = layer_push(keycode, eStickyLock);
		}
		else
		{
			// only the topmost layer on the stack should be in sticky once state
			if (topSticky == eStickyOnceDown || topSticky == eStickyOnceUp) {
				layer_pop_id(layer_ids[topLayer]);
			}
			layer_ids[local_id] = layer_push(keycode, eStickyOnceDown);
			// this should be the only place we care about this flag being cleared
			layer_any_non_trans_key_pressed = false;
		}
	}
	else
	{
		uint8_t topLayer = layer_peek(0);
		uint8_t topSticky = layer_peek_sticky(0);
		if (topLayer == local_id) {
			if (topSticky == eStickyOnceDown) {
				// When releasing this sticky key, pop the layer always
				layer_pop_id(layer_ids[local_id]);
				if (!layer_any_non_trans_key_pressed) {
					// If no key defined for this layer (a non-transparent key)
					//  was pressed, push the layer again, but in the
					//  StickyOnceUp state
					layer_ids[local_id] = layer_push(keycode, eStickyOnceUp);
				}
			}
		}
	}
}

/* Generate a 'shift' press or release before the normal keypress or
 * keyrelease */
void kbfun_shift_press_release(void) {
	_kbfun_press_release(layer_is_pressed, KEY_LeftShift);
	kbfun_press_release();
}

/* When assigned to two keys (e.g. the physical left and right shift keys) (in
 * both the press and release matrices), pressing and holding down one of the
 * keys will make the second key toggle capslock
 *
 * If either of the shifts are pressed when the second key is pressed, they wil
 * be released so that capslock will register properly when pressed.  Capslock
 * will then be pressed and released, and the original state of the shifts will
 * be restored
 */
void kbfun_2_keys_capslock_press_release(void) {
	static uint8_t keys_pressed;
	static bool lshift_pressed;
	static bool rshift_pressed;

	uint8_t keycode = kb_layout_get(current_layer, current_row, current_col);

	if (!layer_is_pressed) keys_pressed--;

	// take care of the key that was actually pressed
	_kbfun_press_release(layer_is_pressed, keycode);

	// take care of capslock (only on the press of the 2nd key)
	if (keys_pressed == 1 && layer_is_pressed) {
		// save the state of left and right shift
		lshift_pressed = _kbfun_is_pressed(KEY_LeftShift);
		rshift_pressed = _kbfun_is_pressed(KEY_RightShift);
		// disable both
		_kbfun_press_release(false, KEY_LeftShift);
		_kbfun_press_release(false, KEY_RightShift);

		// press capslock, then release it
		_kbfun_press_release(true, KEY_CapsLock);
		usb_keyboard_send();
		_kbfun_press_release(false, KEY_CapsLock);
		usb_keyboard_send();

		// restore the state of left and right shift
		if (lshift_pressed)
			_kbfun_press_release(true, KEY_LeftShift);
		if (rshift_pressed)
			_kbfun_press_release(true, KEY_RightShift);
	}

	if (layer_is_pressed) keys_pressed++;
}

/* ----------------------------------------------------------------------------
 * numpad functions
 * ------------------------------------------------------------------------- */

static uint8_t numpad_layer_id;

static inline void numpad_toggle_numlock(void)
{
	_kbfun_press_release(true, KEY_LockingNumLock);
	usb_keyboard_send();
	_kbfun_press_release(false, KEY_LockingNumLock);
	usb_keyboard_send();
}

/* Set the numpad to on (put the numpad layer, specified in the keymap, in an
 * element at the top of the layer stack, and record that element's id) and
 * toggle numlock (regardless of whether or not numlock is currently on)
 *
 * Meant to be assigned (along with "numpad off") instead of a normal numlock
 * key
 */
void kbfun_layer_push_numpad(void)
{
	uint8_t keycode = kb_layout_get(current_layer, current_row, current_col);
	layer_pop_id(numpad_layer_id);
	numpad_layer_id = layer_push(keycode, eStickyNone);
	numpad_toggle_numlock();
}

/* Set the numpad to off (pop the layer element created by "numpad on" out of
 * the stack) and toggle numlock (regardless of whether or not numlock is
 * currently on)
 *
 * Meant to be assigned (along with "numpad on") instead of a normal numlock key
 */
void kbfun_layer_pop_numpad(void)
{
	layer_pop_id(numpad_layer_id);
	numpad_layer_id = 0;
	numpad_toggle_numlock();
}

/* Generate a keypress for a media key, such as play/pause, next track, or
 * previous track
 */
void kbfun_mediakey_press_release(void)
{
	uint8_t keycode = kb_layout_get(current_layer, current_row, current_col);
	_kbfun_mediakey_press_release(layer_is_pressed, keycode);
}

/* These argumentless wrapper-functions are necessary because the key-function
 * matrices only take function pointers for zero-argument functions. */
void kbfun_layer_push_1(void)
{
	basic_layer_push(1);
}
void kbfun_layer_push_2(void)
{
	basic_layer_push(2);
}
void kbfun_layer_push_3(void)
{
	basic_layer_push(3);
}
void kbfun_layer_push_4(void)
{
	basic_layer_push(4);
}
void kbfun_layer_push_5(void)
{
	basic_layer_push(5);
}
void kbfun_layer_push_6(void)
{
	basic_layer_push(6);
}
void kbfun_layer_push_7(void)
{
	basic_layer_push(7);
}
void kbfun_layer_push_8(void)
{
	basic_layer_push(8);
}
void kbfun_layer_push_9(void)
{
	basic_layer_push(9);
}
void kbfun_layer_push_10(void)
{
	basic_layer_push(10);
}
void kbfun_layer_pop_1(void)
{
	layer_pop(1);
}
void kbfun_layer_pop_2(void)
{
	layer_pop(2);
}
void kbfun_layer_pop_3(void)
{
	layer_pop(3);
}
void kbfun_layer_pop_4(void)
{
	layer_pop(4);
}
void kbfun_layer_pop_5(void)
{
	layer_pop(5);
}
void kbfun_layer_pop_6(void)
{
	layer_pop(6);
}
void kbfun_layer_pop_7(void)
{
	layer_pop(7);
}
void kbfun_layer_pop_8(void)
{
	layer_pop(8);
}
void kbfun_layer_pop_9(void)
{
	layer_pop(9);
}
void kbfun_layer_pop_10(void)
{
	layer_pop(10);
}
void kbfun_layer_sticky_1(void)
{
	layer_sticky(1);
}
void kbfun_layer_sticky_2(void)
{
	layer_sticky(2);
}
void kbfun_layer_sticky_3(void)
{
	layer_sticky(3);
}
void kbfun_layer_sticky_4(void)
{
	layer_sticky(4);
}
void kbfun_layer_sticky_5(void)
{
	layer_sticky(5);
}
void kbfun_layer_sticky_6(void)
{
	layer_sticky(6);
}
void kbfun_layer_sticky_7(void)
{
	layer_sticky(7);
}
void kbfun_layer_sticky_8(void)
{
	layer_sticky(8);
}
void kbfun_layer_sticky_9(void)
{
	layer_sticky(9);
}
void kbfun_layer_sticky_10(void)
{
	layer_sticky(10);
}
