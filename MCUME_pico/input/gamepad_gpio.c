#include "pinmap.h"
#include "emuapi.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Simple GPIO gamepad implementation
// Poll pins and map to emulator input bitmask

static inline uint16_t read_gamepad(void) {
    uint16_t mask = 0;
    // D-pad
    if (gpio_get(GPAD_UP_PIN) == 0)    mask |= (1<<2); // map to UP bit (emu expects specific bits)
    if (gpio_get(GPAD_DOWN_PIN) == 0)  mask |= (1<<3);
    if (gpio_get(GPAD_LEFT_PIN) == 0)  mask |= (1<<1);
    if (gpio_get(GPAD_RIGHT_PIN) == 0) mask |= (1<<0);
    // Buttons
    if (gpio_get(GPAD_BTN_A_PIN) == 0) mask |= (1<<4); // FIRE/A
    if (gpio_get(GPAD_BTN_B_PIN) == 0) mask |= (1<<5); // B
    if (gpio_get(GPAD_BTN_START_PIN) == 0) mask |= (1<<6);
    if (gpio_get(GPAD_BTN_SELECT_PIN) == 0) mask |= (1<<7);
    // User keys
    if (gpio_get(GPAD_USER1_PIN) == 0) mask |= (1<<8);
    if (gpio_get(GPAD_USER2_PIN) == 0) mask |= (1<<9);
    return mask;
}

void gpad_init(void) {
    // configure pins as inputs with pull-ups
    gpio_init(GPAD_UP_PIN);    gpio_set_dir(GPAD_UP_PIN, GPIO_IN); gpio_pull_up(GPAD_UP_PIN);
    gpio_init(GPAD_DOWN_PIN);  gpio_set_dir(GPAD_DOWN_PIN, GPIO_IN); gpio_pull_up(GPAD_DOWN_PIN);
    gpio_init(GPAD_LEFT_PIN);  gpio_set_dir(GPAD_LEFT_PIN, GPIO_IN); gpio_pull_up(GPAD_LEFT_PIN);
    gpio_init(GPAD_RIGHT_PIN); gpio_set_dir(GPAD_RIGHT_PIN, GPIO_IN); gpio_pull_up(GPAD_RIGHT_PIN);

    gpio_init(GPAD_BTN_A_PIN); gpio_set_dir(GPAD_BTN_A_PIN, GPIO_IN); gpio_pull_up(GPAD_BTN_A_PIN);
    gpio_init(GPAD_BTN_B_PIN); gpio_set_dir(GPAD_BTN_B_PIN, GPIO_IN); gpio_pull_up(GPAD_BTN_B_PIN);
    gpio_init(GPAD_BTN_START_PIN); gpio_set_dir(GPAD_BTN_START_PIN, GPIO_IN); gpio_pull_up(GPAD_BTN_START_PIN);
    gpio_init(GPAD_BTN_SELECT_PIN); gpio_set_dir(GPAD_BTN_SELECT_PIN, GPIO_IN); gpio_pull_up(GPAD_BTN_SELECT_PIN);

    gpio_init(GPAD_USER1_PIN); gpio_set_dir(GPAD_USER1_PIN, GPIO_IN); gpio_pull_up(GPAD_USER1_PIN);
    gpio_init(GPAD_USER2_PIN); gpio_set_dir(GPAD_USER2_PIN, GPIO_IN); gpio_pull_up(GPAD_USER2_PIN);
}

void gpad_poll_and_feed(void) {
    static uint16_t last = 0;
    uint16_t cur = read_gamepad();
    if (cur != last) {
        // translate to emulator bClick format — this mapping mirrors picospeccy usage of emu_Input
        // NOTE: emu_Input expects a bitmask produced by emu_DebounceLocalKeys in original code. We will feed this mask directly.
        emu_Input(cur);
        last = cur;
    }
}
