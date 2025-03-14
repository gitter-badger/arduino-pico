/*
 * pinMode and digitalRead/Write for the Raspberry Pi Pico RP2040
 *
 * Copyright (c) 2021 Earle F. Philhower, III <earlephilhower@yahoo.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "Arduino.h"
#include <hardware/gpio.h>

extern "C" void pinMode( pin_size_t ulPin, PinMode ulMode ) {
    switch (ulMode) {
        case INPUT:
            gpio_init(ulPin);
            gpio_set_dir(ulPin, false);
            break;
        case INPUT_PULLUP:
            gpio_init(ulPin);
            gpio_set_dir(ulPin, false);
            gpio_pull_up(ulPin);
            break;
        case INPUT_PULLDOWN:
            gpio_init(ulPin);
            gpio_set_dir(ulPin, false);
            gpio_pull_down(ulPin);
            break;
        case OUTPUT:
            gpio_init(ulPin);
            gpio_set_dir(ulPin, true);
            break;
        default:
            // Error
            break;
    }
}

extern "C" void digitalWrite( pin_size_t ulPin, PinStatus ulVal ) {
    if (!gpio_is_dir_out(ulPin)) {
        if (ulVal == LOW) {
            gpio_pull_down(ulPin);
        } else {
            gpio_pull_up(ulPin);
        }
    } else {
        gpio_put(ulPin, ulVal == LOW ? 0 : 1);
    }
}

extern "C" PinStatus digitalRead( pin_size_t ulPin )
{
    return gpio_get(ulPin) ? HIGH : LOW;
}

