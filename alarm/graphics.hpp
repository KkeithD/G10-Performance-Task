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
 *   These are the graphics used in the serial monitor. They all
 *   exist in PROGMEM, and take up about 1-2k bytes.
 *   
 *   When draw calls are made to the serial monitor, 
 *   there are four main elements drawn to the monitor: 
 *   BASE_TOP, BANNER, BASE_MID, ALERT, BASE_BOTTOM.
 *   
 *   The "BASE" graphics represent alarm structure and non-changing
 *   graphical elements. 
 *   
 *   The "BANNER" graphics represent the first changeable graphical
 *   element at the top of the alarm graphic. It's used for 
 *   indicating whether or not the alarm is armed, disarmed etc.
 *   
 *   The "ALERT" graphics represent the large graphical elements
 *   at the bottom of the alarm graphic. It's used for indicating
 *   whether ot not there is a threat, and what type of threat there
 *   is.
 */

#pragma once

#include <avr/pgmspace.h>

static const char SYS_GRAPHIC_CALIB[] PROGMEM = 
R"(+------------------------------------------------>
|
|
|
|
|
|
|         Align arrows with Serial Monitor
|     window, then send the message "start" to
|         the Arduino to start this program.
|
|
|
|
|
|
v)";

static const char SYS_GRAPHIC_BASE_TOP[] PROGMEM = 
R"(+-+------+--------------------------------+----+-+
| |      |                                |    | |
| |      |      G10-PFT  Alarm v1.0       |    | |
| |      |        By Keith Davies         |    | |
| |      |                                |    | |
+--------+--------------------------------+------+)";


static const char SYS_GRAPHIC_BASE_MID[] PROGMEM = 
R"(+------------------------------------------------+
| |                                            | |)";

static const char SYS_GRAPHIC_BASE_BOTTOM[]  PROGMEM= 
R"(| |                                            | |
| |                                            | |
+-+--------------------------------------------+-+)";


static const char SYS_GRAPHIC_BANNER_EMPTY[] PROGMEM =
R"(| |                                            | |)";

static const char SYS_GRAPHIC_BANNER_WELCOME[] PROGMEM =
R"(| |                  WELCOME                   | |)";

static const char SYS_GRAPHIC_BANNER_INIT[] PROGMEM =
R"(| |               INITIALIZING...              | |)";

static const char SYS_GRAPHIC_BANNER_ARMING0[] PROGMEM =
R"(| |                   ARMING                   | |)";

static const char SYS_GRAPHIC_BANNER_ARMING1[] PROGMEM =
R"(| |                  ARMING.                   | |)";

static const char SYS_GRAPHIC_BANNER_ARMING2[] PROGMEM =
R"(| |                  ARMING..                  | |)";

static const char SYS_GRAPHIC_BANNER_ARMING3[] PROGMEM =
R"(| |                 ARMING...                  | |)";

static const char SYS_GRAPHIC_BANNER_CANCELLED[] PROGMEM =
R"(| |              ARMING CANCELLED              | |)"; 

static const char SYS_GRAPHIC_BANNER_ARMED[] PROGMEM =
R"(| |                ALARM ARMED                 | |)";

static const char SYS_GRAPHIC_BANNER_DISARMED[]PROGMEM =
R"(| |               DISARMED ALARM               | |)";

static const char SYS_GRAPHIC_BANNER_FLOOD_EXPIRED[] PROGMEM =
R"(| |            FLOOD THREAT EXPIRED            | |)"; 



static const char SYS_GRAPHIC_ALERT_EMPTY[] PROGMEM =
R"(| |                                            | |
| |                                            | |
| |                                            | |)";

static const char SYS_GRAPHIC_ALERT_THREAT[] PROGMEM =
R"(| |   _____  _   _ _____  ____   ____  _____   | |
| |  |_   _|| |_| || () )| ===| / () \|_   _|  | |
| |    |_|  |_| |_||_|\_\|____|/__/\__\ |_|    | |)";


static const char SYS_GRAPHIC_ALERT_FLOOD[] PROGMEM =
R"(| |        ____  _     ____  ____  ____        | |
| |       | ===|| |__ / () \/ () \| _) \       | |
| |       |__|  |____|\____/\____/|____/       | |)";

static const char SYS_GRAPHIC_ALERT_MOTION[] PROGMEM =
R"(| |    __  __   ____  _____  _  ____  __  _    | |
| |   |  \/  | / () \|_   _|| |/ () \|  \| |   | |
| |   |_|\/|_| \____/  |_|  |_|\____/|_|\__|   | |)";
