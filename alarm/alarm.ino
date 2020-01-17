/**
 * 
 *     /$$$$$$            /$$    /$$$$$$        /$$$$$$$  /$$$$$$$$ /$$$$$$$$
 *    /$$__  $$         /$$$$   /$$$_  $$      | $$__  $$| $$_____/|__  $$__/
 *   | $$  \__/        |_  $$  | $$$$\ $$      | $$  \ $$| $$         | $$   
 *   | $$ /$$$$ /$$$$$$  | $$  | $$ $$ $$      | $$$$$$$/| $$$$$      | $$   
 *   | $$|_  $$|______/  | $$  | $$\ $$$$      | $$____/ | $$__/      | $$   
 *   | $$  \ $$          | $$  | $$ \ $$$      | $$      | $$         | $$   
 *   |  $$$$$$/         /$$$$$$|  $$$$$$/      | $$      | $$         | $$   
 *   \______/         |______/ \______/       |__/      |__/         |__/   
 *   
 *   By ~ Keith Davies.
 *   
 *   This is the main Arudino ino file. It's responsible for defining base
 *   arduino functions.
 *   
 *   NOTE: Use 500 000 baud rate in the serial monitor, or whatever
 *         SETTINGS_SERIAL_BAUD_RATE is set to internally.
 */

#include <arduino.h>
#include <stdint.h>

#include "settings.hpp"
#include "system.hpp"

void setup() {
    Serial.begin(SETTINGS_SERIAL_BAUD_RATE);
    System::initialize();
};

void loop() {
    System::update();
};
