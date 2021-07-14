/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
#include <keymap_french.h>

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

enum unicode_names {
    COIN,
    SHRUG
};

const uint32_t PROGMEM unicode_map[] = {
    [COIN] = 0x1F986,   // 🦆
    [SHRUG]  = 0x1F937, // 🤷
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up | Knob 2: Media Prev/Next | Knob 3: TBD        |
        | Press: Mute       | Press: Play/Pause       | Press: TBD         |
        | TBD               | Layer 1                 | RGB On/Off         |
        | 🤷               | RIP                     | 🦆                 |
     */
    [0] = LAYOUT(
        LCA(KC_F11), XXXXXXX, KC_MEDIA_PLAY_PAUSE,
        XXXXXXX, MO(1), RGB_TOG,
        X(SHRUG), XXXXXXX, X(COIN)),
    /*
        | Knob 1: Transparent | Knob 2: Arrow left/right | Knob 3: Transparent |
        | Press: Mute         | Transparent              | Transparent         |
        | Transparent         | Transparent              | Transparent         |
        | Transparent         | RIP                      | alt+0 (Coin.mp3)    |
     */
    [1] = LAYOUT(
        KC_MUTE, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, LALT(KC_KP_0)),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case _LEFT:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case _MIDDLE:
            break;
        case _RIGHT:
            if (layer_state_is(1))
            {
                if (clockwise)
                {
                    tap_code(KC_RIGHT);
                }
                else
                {
                    tap_code(KC_LEFT);
                }
            }
            else
            {
                if (clockwise)
                {
                    tap_code(KC_MEDIA_NEXT_TRACK);
                }
                else
                {
                    tap_code(KC_MEDIA_PREV_TRACK);
                }
            }
            break;
    }
    return true;
}

void rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case 0:
            rgb_matrix_set_color_all(30, 30, 30);
            break;
        case 1:
            rgb_matrix_set_color_all(40, 40, 40);
            rgb_matrix_set_color(4, 0, 0, 255);
            rgb_matrix_set_color(9, 0, 0, 255);
            rgb_matrix_set_color(10, 0, 0, 255);
            break;
    }
    led_t led_state = host_keyboard_led_state();
    if (led_state.caps_lock) {
        rgb_matrix_set_color(10, 255, 0, 0);
    }
}