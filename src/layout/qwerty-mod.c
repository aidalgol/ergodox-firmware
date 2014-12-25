/* ----------------------------------------------------------------------------
 * ergoDOX layout : QWERTY (modified from the Kinesis layout)
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include "../lib/data-types/misc.h"
#include "../lib/usb/usage-page/keyboard--short-names.h"
#include "../lib/key-functions/public.h"
#include "../matrix.h"

const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

	KB_MATRIX_LAYER(  // layout: layer 0: default
// left hand
_grave,   _1,      _2,     _3,        _4,         _5, 1,
_equal,   _Q,      _W,     _E,        _R,         _T, 3,
_tab,     _A,      _S,     _D,        _F,         _G,
_shiftL,  _Z,      _X,     _C,        _V,         _B, 1,
_guiL,  _esc, _insert, _ctrlL,     _altL,
                                            _home, _end,
                                                   _F21,
                                        _bs, _del, _F22,
// right hand
     3, _6,      _7,     _8,        _9,         _0,   _backslash,
  _esc, _Y,      _U,     _I,        _O,         _P,        _dash,
        _H,      _J,     _K,        _L, _semicolon,       _quote,
     1, _N,      _M, _comma,   _period,     _slash,      _shiftR,
             _ctrlR,  _altR, _bracketL,  _bracketR, _application,
_pageU, _pageD,
  _F23,
  _F24, _enter, _space ),


	KB_MATRIX_LAYER(  // layout: layer 1: function and infrequently-used keys
// left hand
          0, _F1, _F2, _F3, _F4, _F5, _F11,
_scrollLock,   0,   0,   0,   0,   0,    1,
     _print,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,    2,
          0,   0,   0,   0,   0,
                                     0,  0,
                                         0,
                                 0,  0,  0,
// right hand
_F12, _F6,     _F7,     _F8,     _F9,    _F10,        0,
   0,   0,       0,       0,       0,       0, _volumeU,
        0,       0,       0,       0,       0, _volumeD,
   2,   0, _arrowL, _arrowD, _arrowU, _arrowR,    _mute,
                 0,       0,       0,       0,        0,
   0,  0,
   0,
   0,  0,  0 ),


	KB_MATRIX_LAYER(  // layout: layer 2: keyboard functions
// left hand
0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
               0, 0,
                  0,
            0, 0, 0,
// right hand
0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
0, 0,
0,
0, 0, 0 ),


	KB_MATRIX_LAYER(  // layout: layer 3: numpad
// left hand
0,       0, 0, 0, 0, 0, 0,
0,       0, 0, 0, 0, 0, 0,
0,       0, 0, 0, 0, 0,
0,       0, 0, 0, 0, 0, 0,
0, _insert, 0, 0, 0,
                     0, 0,
                        0,
                  0, 0, 0,
// right hand
3, 0,     3, _equal_kp, _div_kp,   _mul_kp, _numLock_kp,
0, 0, _7_kp,     _8_kp,   _9_kp,   _sub_kp, 0,
   0, _4_kp,     _5_kp,   _6_kp,   _add_kp, 0,
0, 0, _1_kp,     _2_kp,   _3_kp, _enter_kp, 0,
          0,         0, _period, _enter_kp, 0,
0, 0,
0,
0, 0, _0_kp ),

};


const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

	KB_MATRIX_LAYER(  // press: layer 0: default
// left hand
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,  lpush1,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, slpunum,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 s2kcap, kprrel, kprrel, kprrel, kprrel, kprrel,  lpush1,
 kprrel, kprrel, kprrel, kprrel, kprrel,
                                          kprrel, kprrel,
                                                  kprrel,
                                  kprrel, kprrel, kprrel,
// right hand
 slpunum, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
  kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
          kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
  lpush1, kprrel, kprrel, kprrel, kprrel, kprrel, s2kcap,
                  kprrel, kprrel, kprrel, kprrel, kprrel,
  kprrel, kprrel,
  kprrel,
  kprrel, kprrel, kprrel ),


	KB_MATRIX_LAYER(  // press: layer 1: function and symbol keys
// left hand
 ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, ktrans, ktrans, ktrans, ktrans, ktrans,  lpop1,
 kprrel, ktrans, ktrans, ktrans, ktrans, ktrans,
 ktrans, ktrans, ktrans, ktrans, ktrans, ktrans, lpush2,
 ktrans, ktrans, ktrans, ktrans, ktrans,
                                         ktrans, ktrans,
                                                 ktrans,
                                 ktrans, ktrans, ktrans,
// right hand
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, ktrans,
 ktrans, ktrans, ktrans, ktrans, ktrans, ktrans, kprrel,
         ktrans, ktrans, ktrans, ktrans, ktrans, kprrel,
 lpush2, ktrans, kprrel, kprrel, kprrel, kprrel, kprrel,
                 ktrans, ktrans, ktrans, ktrans, ktrans,
 ktrans, ktrans,
 ktrans,
 ktrans, ktrans, ktrans ),


	KB_MATRIX_LAYER(  // press: layer 2: keyboard functions
// left hand
 dbtldr, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL,
                                       NULL,
                           NULL, NULL, NULL,
// right hand
   NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL,
   NULL, NULL,
         NULL,
   NULL, NULL, NULL ),


	KB_MATRIX_LAYER(  // press: layer 3: numpad
// left hand
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
  ktrans, kprrel, ktrans, ktrans, ktrans,
                                         ktrans, ktrans,
                                                 ktrans,
                                 ktrans, ktrans, ktrans,
// right hand
 slponum, ktrans,slponum, kprrel, kprrel, kprrel, kprrel,
  ktrans, ktrans, kprrel, kprrel, kprrel, kprrel, ktrans,
          ktrans, kprrel, kprrel, kprrel, kprrel, ktrans,
  ktrans, ktrans, kprrel, kprrel, kprrel, kprrel, ktrans,
                  ktrans, ktrans, kprrel, kprrel, ktrans,
 ktrans, ktrans,
 ktrans,
 ktrans, ktrans, kprrel ),
};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

	KB_MATRIX_LAYER(  // release: layer 0: default
// left hand
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,    NULL,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, slponum,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 s2kcap, kprrel, kprrel, kprrel, kprrel, kprrel,   lpop1,
 kprrel, kprrel, kprrel, kprrel, kprrel,
                                         kprrel,  kprrel,
                                                  kprrel,
                                  kprrel, kprrel, kprrel,
// right hand
 NULL,   kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
         kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
  lpop1, kprrel, kprrel, kprrel, kprrel, kprrel, s2kcap,
                 kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel,
 kprrel,
 kprrel, kprrel, kprrel ),


	KB_MATRIX_LAYER(  // release: layer 1: function and symbol keys
// left hand
   NULL,  kprrel,  kprrel, kprrel, kprrel,  kprrel, kprrel,
 ktrans, sshprre, sshprre, kprrel, kprrel,    NULL,   NULL,
 ktrans,  kprrel,  kprrel, kprrel, kprrel, sshprre,
 ktrans,  kprrel,  kprrel, kprrel, kprrel, sshprre,  lpop2,
 ktrans,  ktrans,  ktrans, ktrans, ktrans,
                                            ktrans, ktrans,
                                                    ktrans,
                                    ktrans, ktrans, ktrans,
// right hand
 kprrel,  kprrel, kprrel,  kprrel,  kprrel,  kprrel, kprrel,
 ktrans,    NULL, kprrel, sshprre, sshprre,  kprrel, kprrel,
          kprrel, kprrel, sshprre, sshprre, sshprre, kprrel,
  lpop2, sshprre, kprrel,  kprrel,  kprrel,  kprrel, kprrel,
                  ktrans,  ktrans,  ktrans,  ktrans, ktrans,
 ktrans,  ktrans,
 ktrans,
 ktrans,  ktrans, ktrans ),


	KB_MATRIX_LAYER(  // release: layer 2: keyboard functions
// left hand
 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 NULL, NULL, NULL, NULL, NULL, NULL,
 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL,
                                     NULL,
                         NULL, NULL, NULL,
// right hand
 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
       NULL, NULL, NULL, NULL, NULL, NULL,
 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 NULL, NULL, NULL, NULL, NULL,
 NULL, NULL,
 NULL,
 NULL, NULL, NULL ),


	KB_MATRIX_LAYER(  // release: layer 3: numpad
// left hand
 ktrans, ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
 ktrans, ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
 ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
 ktrans, ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
 ktrans, kprrel, ktrans, ktrans, ktrans,
                                         ktrans, ktrans,
                                                 ktrans,
                                 ktrans, ktrans, ktrans,
// right hand
   NULL, ktrans,   NULL, kprrel, kprrel, kprrel, kprrel,
 ktrans, ktrans, kprrel, kprrel, kprrel, kprrel, ktrans,
         ktrans, kprrel, kprrel, kprrel, kprrel, ktrans,
 ktrans, ktrans, kprrel, kprrel, kprrel, kprrel, ktrans,
                 ktrans, ktrans, kprrel, kprrel, ktrans,
 ktrans, ktrans,
 ktrans,
 ktrans, ktrans, kprrel ),


	KB_MATRIX_LAYER(  // release: layer 3: nothing (just making sure unused
			  // functions don't get compiled out)
// other
 kprrel, lpush8,  lpop8,   NULL,   NULL,   NULL,   NULL,   NULL,
   ktog, lpush9,  lpop9,   NULL,   NULL,   NULL,   NULL,   NULL,
 ktrans,lpush10, lpop10,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush1,  lpop1,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush2,  lpop2, dbtldr,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush3,  lpop3,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush4,  lpop4, s2kcap,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush5,  lpop5,slpunum,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush6,  lpop6,slponum,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush7,  lpop7,   NULL,   NULL )
};
