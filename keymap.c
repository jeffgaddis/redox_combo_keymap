#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
uint8_t mod_state;
uint8_t oneshot_mod_state;
uint16_t last_keycode;


#define _COLEMAK 0
#define _QWERTY 1
#define _NAV 2
#define _NUM 3
#define _ADJUST 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NAV,
  NUM,
  ADJUST,
  //Remove OS Mods if they are stuck
  OS_CLR,
  KC_P000,
  KC_C000,
  O_BRACE,
  C_BRACE,
};

// Shortcut to make keymap more readable
#define KC_QWER TG(_QWERTY)

#define NUM_TAB LT(_NUM, KC_TAB)
#define NAV_ENT LT(_NAV, KC_ENT)

#define ADJUST MO(_ADJUST)

// Miscellaneous keyboard shortcuts in direct access
#define UNDO LCTL(KC_Z)
#define REDO LCTL(KC_Y)
#define C_A_DEL LCA(KC_DEL)

// One Shot Shifts
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)

// One Shot Others
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define OS_LGUI OSM(MOD_LGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRV  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,DM_PLY1 ,                          DM_PLY2 ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_G    ,KC_TAB  ,                          KC_ENT  ,KC_M    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_QUOT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     OS_LGUI ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,OS_LCTL ,OS_LALT ,        KC_DEL  ,KC_ESC  ,KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_MINS ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     UNDO    ,REDO    ,A(KC_TAB),LCA(KC_TAB), OS_LSFT ,    KC_BSPC ,OSL(_NUM),      OSL(_NAV),KC_SPC  ,    OS_RSFT ,     KC_HOME ,KC_END  ,KC_LBRC ,KC_RBRC 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,_______ ,                          _______ ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,_______ ,                          _______ ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,_______ ,_______ ,        _______ ,_______ ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_QWER ,KC_MPRV ,KC_MPLY ,KC_MSTP ,KC_MNXT ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,TG(_NAV),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     ADJUST  ,_______ ,_______ ,KC_UP   ,KC_APP  ,C_A_DEL ,DM_REC1 ,                          DM_REC2 ,O_BRACE ,KC_RPRN ,KC_LPRN ,KC_RBRC ,KC_LBRC ,KC_PSCR ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_PGUP ,_______ ,KC_LEFT ,KC_DOWN ,KC_RIGHT,_______ ,_______ ,                          _______ ,C_BRACE ,KC_RCTL ,KC_RSFT ,KC_RALT ,KC_RGUI ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_PGDN ,C(KC_A) ,C(KC_X) ,C(KC_C) ,C(KC_V) ,LCA(KC_V),_______,_______ ,        _______ ,_______ ,KC_CIRC ,KC_AMPR ,KC_HASH ,KC_AT   ,KC_EXLM ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,ADJUST  ,_______ ,_______ ,   C(KC_BSPC),    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,DM_REC1 ,DM_REC2 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_QWER ,KC_NUM  ,KC_PSCR ,KC_SCRL ,KC_PAUS ,KC_BRIU ,                                            KC_P000 ,KC_CIRC ,KC_AMPR ,KC_HASH ,KC_EXLM ,TG(_NUM),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MUTE ,O_BRACE ,C_BRACE ,KC_LCBR ,KC_RCBR ,KC_BRID ,_______ ,                          _______ ,KC_C000 ,KC_7    ,KC_8    ,KC_9    ,KC_PERC ,KC_DLR  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_VOLU ,KC_LBRC ,KC_RBRC ,KC_LPRN ,KC_RPRN ,KC_INS  ,_______ ,                          _______ ,KC_COMM ,KC_4    ,KC_5    ,KC_6    ,KC_PAST ,KC_PPLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_VOLD ,C(KC_A) ,C(KC_X) ,C(KC_C) ,C(KC_V) ,LCA(KC_V),_______,_______ ,        _______ ,_______ ,KC_EQL  ,KC_1    ,KC_2    ,KC_3    ,KC_PSLS ,KC_PMNS ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,ADJUST  ,TG(_NUM),TG(_NUM),   C(KC_BSPC),    _______ ,_______ ,        _______ ,_______ ,    KC_PENT ,     KC_P0   ,KC_PDOT ,KC_PENT ,KC_CALC 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,QK_BOOT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,QK_BOOT ,_______ ,XXXXXXX ,        XXXXXXX ,_______ ,QK_BOOT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};


// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n",
         keycode,
         record->event.key.row,
         record->event.key.col,
         get_highest_layer(layer_state),
         record->event.pressed,
         get_mods(),
         get_oneshot_mods(),
         record->tap.count
         );
#endif

    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    switch (keycode) {

    case KC_SPC:
        if (oneshot_mod_state & MOD_MASK_SHIFT) {
            if (record->event.pressed) {
                tap_code(KC_MINS); // The one-shot shift will convert it to an underscore
            }
            return false;
        }
        return true;

     case OS_CLR:
         if (record->event.pressed) {
             clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
         }
         return false;

    case KC_P000:
      if (record->event.pressed) {
          send_string("000");
          return false;
      }
      break;

    case KC_C000:
      if (record->event.pressed) {
          send_string(",000");
          return false;
      }
      break;

    case O_BRACE:
      if (record->event.pressed) {
          tap_code16(KC_LCBR);
          tap_code(KC_ENTER);
          return false;
      }
      break;

    case C_BRACE:
      if (record->event.pressed) {
          tap_code16(KC_RCBR);
          tap_code(KC_ENTER);
          return false;
      }
      break;

    }
    return true;
};
