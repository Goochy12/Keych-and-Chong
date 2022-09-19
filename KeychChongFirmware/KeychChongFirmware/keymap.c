#include "keymap.h"


const uint16_t keymaps_array[][MATRIX_ROWS][MATRIX_COLS] = {
	 /*
     *  A   B   C 
     *  1   2   3
     * SHF WIN CPS
     */
    
    [0] = {KC_1,    KC_2,    KC_3},
    {KC_A,    KC_B,    KC_C},
    {KC_LSFT, KC_LGUI, KC_CAPS}
    
};