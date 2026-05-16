/* Custom RGB Matrix: blanco por defecto, F1–F12 rojo, Q–Y violeta (L3 ISO, g_led_config). */
/* !!! DO NOT add #pragma once (QMK merges this file twice). !!! */

RGB_MATRIX_EFFECT(pek_fn_row)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// F1–F12: LEDs 1–12 (matrix row 0).
#    ifndef PEK_FN_LED_FIRST
#        define PEK_FN_LED_FIRST 1
#    endif
#    ifndef PEK_FN_LED_LAST
#        define PEK_FN_LED_LAST 12
#    endif

// Q,W,E,R,T,Y: LEDs 35–40 (matrix row 2, cols correspondientes).
#    ifndef PEK_QWE_RTY_LED_FIRST
#        define PEK_QWE_RTY_LED_FIRST 35
#    endif
#    ifndef PEK_QWE_RTY_LED_LAST
#        define PEK_QWE_RTY_LED_LAST 40
#    endif

// Matiz violeta en escala QMK hue 0–255 (ajusta a gusto).
#    ifndef PEK_VIOLET_HUE
#        define PEK_VIOLET_HUE 216
#    endif

bool pek_fn_row(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    const uint8_t v = rgb_matrix_config.hsv.v;

    HSV hsv_white  = {0, 0, v};
    HSV hsv_red    = {0, 255, v};
    HSV hsv_violet = {PEK_VIOLET_HUE, 255, v};

    RGB rgb_white  = rgb_matrix_hsv_to_rgb(hsv_white);
    RGB rgb_red    = rgb_matrix_hsv_to_rgb(hsv_red);
    RGB rgb_violet = rgb_matrix_hsv_to_rgb(hsv_violet);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        RGB rgb_sel;
        if (i >= PEK_FN_LED_FIRST && i <= PEK_FN_LED_LAST) {
            rgb_sel = rgb_red;
        } else if (i >= PEK_QWE_RTY_LED_FIRST && i <= PEK_QWE_RTY_LED_LAST) {
            rgb_sel = rgb_violet;
        } else {
            rgb_sel = rgb_white;
        }
        rgb_matrix_region_set_color(params->region, i, rgb_sel.r, rgb_sel.g, rgb_sel.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
