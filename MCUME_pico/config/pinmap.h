#pragma once

/* Central pin mapping for RP2040 ILI9341 + GPIO gamepad + USB OTG
   Edit here to change pins used by the build. */

#ifndef MCUME_PICO_PINMAP_H
#define MCUME_PICO_PINMAP_H

// ILI9341 SPI pins (user-provided)
#define ILI9341_CS_PIN    17 // GP17
#define ILI9341_DC_PIN    20 // GP20
#define ILI9341_MISO_PIN  16 // GP16
#define ILI9341_MOSI_PIN  19 // GP19
#define ILI9341_RST_PIN   21 // GP21
#define ILI9341_SCK_PIN   18 // GP18

// Audio (PWM) - can keep existing default or override here
#ifndef AUDIO_PIN
#define AUDIO_PIN 10
#endif

// GPIO gamepad default pins (digital inputs)
#define GPAD_UP_PIN      27
#define GPAD_DOWN_PIN    26
#define GPAD_LEFT_PIN    22
#define GPAD_RIGHT_PIN   28

#define GPAD_BTN_A_PIN    1
#define GPAD_BTN_B_PIN    2
#define GPAD_BTN_START_PIN 3
#define GPAD_BTN_SELECT_PIN 4

// User keys
#define GPAD_USER1_PIN   14
#define GPAD_USER2_PIN   15

#endif // MCUME_PICO_PINMAP_H
