/* Copyright 2021 tadakado
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    LOWER = BMP_SAFE_RANGE,
    RAISE,
    ADJUST,
    GT_DEL,
    GT_BSPC,
    IME,
    MAC,
    WIN,
    CLR,
    FST,
    DUMMY
};

const key_string_map_t custom_keys_user =
{
    .start_kc = LOWER,
    .end_kc = DUMMY,
     .key_strings = "LOWER\0RAISE\0ADJUST\0GT_DEL\0GT_BSPC\0IME\0MAC\0WIN\0CLR\0FST\0DUMMY\0"
};

enum layers {
    _BASE, _LOWER, _RAISE, _ADJUST
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{
    // Do NOT use LAYOUT() macro and multi-dimesnional array
    //
    // Layer 0
    KC_A,  KC_1,  KC_H,

    // Layer 1
    KC_TAB,  KC_SPC,
    }}
};

uint32_t keymaps_len() {
  return sizeof(keymaps)/sizeof(uint16_t);
}

/*
#define AT_ESC  ALT_T(KC_ESC)
#define AT_ENT  ALT_T(KC_ENT)
#define ST_SPC  LSFT_T(KC_SPC)

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT( \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_AT,   \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_COLN, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UNDS, \
                          AT_ESC,  GT_DEL,  ST_SPC,  LOWER,   RAISE,   ST_SPC,  GT_BSPC, AT_ENT \
    ),
    [_LOWER] = LAYOUT( \
        KC_EXLM, KC_DQUO, KC_HASH, KC_DLR,  KC_PERC, KC_AMPR, KC_QUOT, KC_LPRN, KC_RPRN, S(KC_0), KC_EQL,  KC_TILD, \
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_CIRC, \
        _______, KC_ZKHK, KC_TAB,  _______, _______, _______, KC_JYEN, KC_LBRC, KC_RBRC, _______, _______, _______, \
                          KC_ENT,  KC_DEL,  _______, _______, _______, _______, KC_BSPC, _______ \
    ),
    [_RAISE] = LAYOUT( \
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_CIRC, \
        _______, _______, KC_CAPS, KC_HOME, KC_END,  KC_INS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP, _______, \
        _______, _______, _______, _______, _______, _______, KC_PIPE, KC_LCBR, KC_RCBR, _______, KC_PGDN, _______, \
                          _______, KC_DEL,  _______, _______, _______, _______, KC_BSPC, _______ \
    ),
    [_ADJUST] = LAYOUT( \
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
        XXXXXXX, XXXXXXX, WIN,     MAC,     IME,     XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, \
        TG(_NUM),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                          RESET,   EEP_RST, _______, _______, _______, _______, EEP_RST, RESET \
    ),
    [_NUM] = LAYOUT( \
        KC_EXLM, KC_DQUO, KC_HASH, KC_DLR,  KC_PERC, KC_AMPR, KC_MINS, KC_7,    KC_8,    KC_9,    KC_BSPC, KC_SLSH,  \
        KC_QUOT, KC_LPRN, KC_RPRN, KC_LABK, KC_RABK, KC_GRV,  KC_PLUS, KC_4,    KC_5,    KC_6,    KC_TAB,  KC_ASTR, \
        TG(_NUM),KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_QUES, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_ENT,  KC_COMM, \
                          KC_TILD, KC_CIRC, KC_JYEN, _______, _______, KC_0,    KC_DOT,  KC_SPC \
    )
};

uint32_t keymaps_len() {
  return 220;
}
*/

enum win_mac_keys { HENK, MHEN };
static bool mac_mode = true;
static bool ime_disabled = false;

void win_mac(enum win_mac_keys key) {
    switch (key) {
        case HENK:
            if (ime_disabled) { break; };
            if (mac_mode) {
                tap_code(KC_LANG1);
            } else {
                tap_code(KC_HENK);
            };
            break;
        case MHEN:
            if (ime_disabled) { break; };
            if (mac_mode) {
                tap_code(KC_LANG2);
            } else {
                tap_code(KC_MHEN);
            };
            break;
    }
}

/*
void keyboard_post_init_user(void) {
  setPinOutput(LED_NUM_LOCK_PIN);
  setPinOutput(LED_CAPS_LOCK_PIN);
  setPinOutput(LED_SCROLL_LOCK_PIN);
}
*/

void update_leds(uint8_t num, uint8_t caps, uint8_t scroll) {
        writePin(LED_NUM_LOCK_PIN, num);
        writePin(LED_CAPS_LOCK_PIN, caps);
        writePin(LED_SCROLL_LOCK_PIN, scroll);
}

void status_on_led() {
    static uint8_t old_status = 0xff;
    uint8_t new_status;
    uint8_t ble_enabled = get_ble_enabled();
    // uint8_t ble_status = *(uint16_t *)BLE_STATUS;
    uint8_t ble_device = *(uint16_t *)BLE_DEVICE;
    new_status = (ble_enabled & 0x01) << 2 | (ble_device & 0x03);
    if (old_status != new_status) {
        update_leds((new_status >> 2) & 1, (new_status >> 1) & 1, new_status & 1);
        uprintf("LED status change: %02x => %02x\r", old_status, new_status);
        old_status = new_status;
    }
}

void matrix_scan_user(void) {
    status_on_led();
}

static bool lower_pressed = false;
static bool raise_pressed = false;
static bool lgui_pressed = false;
static bool lgui_registered = false;
static bool rgui_pressed = false;
static bool rgui_registered = false;
static uint16_t lower_pressed_time = 0;
static uint16_t raise_pressed_time = 0;
static uint16_t lgui_pressed_time = 0;
static uint16_t rgui_pressed_time = 0;

void flag_status() {
    uprint("##### status #####\r");
    uprintf("mac_mode: %d\r", mac_mode);
    uprintf("ime_disabled: %d\r", ime_disabled);
    uprintf("lower_pressed: %d\r", lower_pressed);
    uprintf("raise_pressed: %d\r", raise_pressed);
    uprintf("lgui_pressed: %d\r", lgui_pressed);
    uprintf("lgui_registered: %d\r", lgui_registered);
    uprintf("rgui_pressed: %d\r", rgui_pressed);
    uprintf("rgui_registere: %d\r", rgui_registered);
    uprintf("usb_enabled: %d\r", get_usb_enabled());
    uprintf("ble_enabled: %d\r", get_ble_enabled());
    uprintf("ble_status: %04x\r", *(uint16_t *)BLE_STATUS);
    uprintf("ble_device: %04x\r", *(uint16_t *)BLE_DEVICE);
}

void clear_modifiers(void) {
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    unregister_code(KC_LALT);
    unregister_code(KC_LGUI);
    unregister_code(KC_RSFT);
    unregister_code(KC_RCTL);
    unregister_code(KC_RALT);
    unregister_code(KC_RGUI);
    lower_pressed = false;
    raise_pressed = false;
    lgui_pressed = false;
    lgui_registered = false;
    rgui_pressed = false;
    rgui_registered = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool continue_process = process_record_user_bmp(keycode, record);
    if (continue_process == false) {
        return false;
    }

    switch (keycode) {
        case LOWER:
            dprint("LOWER\r");
            if (record->event.pressed) {
                lower_pressed = true;
                lower_pressed_time = record->event.time;
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
                    win_mac(MHEN);
                }
                lower_pressed = false;
            }
            return false;
        case RAISE:
            dprint("RAISE\r");
            if (record->event.pressed) {
                raise_pressed = true;
                raise_pressed_time = record->event.time;
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
                    win_mac(HENK);
                }
                raise_pressed = false;
            }
            return false;
        case GT_DEL:
            dprint("GT_DEL\r");
            if (record->event.pressed) {
                lgui_pressed = true;
                lgui_pressed_time = record->event.time;
            } else {
                if (lgui_pressed && (TIMER_DIFF_16(record->event.time, lgui_pressed_time) < TAPPING_TERM)) {
                    tap_code(KC_DEL);
                }
                lgui_pressed = false;
                if (lgui_registered) {
                    unregister_code(KC_LGUI);
                }
                lgui_registered = false;
            }
            return false;
        case KC_LGUI:
            if (! record->event.pressed) {
                lgui_pressed = false;
                lgui_registered = false;
            }
            return true;
            break;
        case GT_BSPC:
            dprint("GT_BSPC\r");
            if (record->event.pressed) {
                rgui_pressed = true;
                rgui_pressed_time = record->event.time;
            } else {
                if (rgui_pressed && (TIMER_DIFF_16(record->event.time, rgui_pressed_time) < TAPPING_TERM)) {
                    tap_code(KC_BSPC);
                }
                rgui_pressed = false;
                if (lgui_registered) {
                    unregister_code(KC_RGUI);
                }
                rgui_registered = false;
            }
            return false;
        case KC_RGUI:
            if (! record->event.pressed) {
                rgui_pressed = false;
                rgui_registered = false;
            }
            return true;
        case IME:
            dprint("IME\r");
            if (record->event.pressed) {
      	        ime_disabled = !ime_disabled;
            }
            return false;
        case MAC:
            dprint("MAC\r");
            if (record->event.pressed) {
      	        mac_mode = true;
            }
            return false;
        case WIN:
            dprint("WIN\r");
            if (record->event.pressed) {
      	        mac_mode = false;
            }
            return false;
        case CLR:
            dprint("CLR\r");
            if (record->event.pressed) {
                uprint("##### clear keyboard #####\r");
                layer_clear();
                clear_modifiers();
                clear_keyboard();
            }
            return false;
        case FST:
            dprint("FST\r");
            if (record->event.pressed) {
                flag_status();
            }
            return false;
        default:
            if (record->event.pressed) {
                // reset the flags
                lower_pressed = false;
                raise_pressed = false;
                if (lgui_pressed && (TIMER_DIFF_16(record->event.time, lgui_pressed_time) > GUI_COMBO_TAPPING_TERM)) {
                    register_code(KC_LGUI);
                    lgui_registered = true;
                }
                if (rgui_pressed && (TIMER_DIFF_16(record->event.time, rgui_pressed_time) > GUI_COMBO_TAPPING_TERM)) {
                    register_code(KC_RGUI);
                    rgui_registered = true;
                }
            }
            break;
    }
    return true;
}
