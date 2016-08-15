#include "state_machine.h"

/*
 * EVENTS
 * Button push
 * SD Card
 *   Inserted
 *   Removed
 * (Time)
 *   LED
 *   Data collection
 *
 * STATES
 * (Initialize program)
 * No SD card inserted
 * Initialize SD Card
 * Standby
 * Data
 *   Data collection setup
 *   Data collection abort
 *   Countdown
 *   Data collection
 *     Wait
 *     Measure
 *       Temperature
 *       Ping time
 *     Compute
 *     Log
 *   Data collection conclude
 * Error
 *
 * | STATE                     | TRIGGER EVENT       | NEXT STATE                |
 * +---------------------------+---------------------+---------------------------+
 * | Initialize program        | None                | Standby                   |
 * +---------------------------+---------------------+---------------------------+
 * | Any                       | SD card removed     | No SD card                |
 * | No SD card                | None                | No SD card                |
 * | No SD card                | SD card inserted    | Initialize SD card        |
 * +---------------------------+---------------------+---------------------------+
 * | Initialize SD card        | None                | Standby                   |
 * | Initialize SD card        | Error               | Error                     |
 * +---------------------------+---------------------+---------------------------+
 * | Standby                   | None                | Standby                   |
 * | Standby                   | Button push         | Data collection setup     |
 * +---------------------------+---------------------+---------------------------+
 * | Data collection setup     | None                | Countdown                 |
 * | Data collection setup     | Error               | Error                     |
 * +---------------------------+---------------------+---------------------------+
 * | Countdown                 | None                | Data collection           |
 * | Countdown                 | Button push         | Data collection abort     |
 * +---------------------------+---------------------+---------------------------+
 * | Data collection abort     | None                | Standby                   |
 * | Data collection abort     | Error               | Error                     |
 * +---------------------------+---------------------+---------------------------+
 * | Data collection           | None                | Data collection           |
 * | Data collection           | Button push         | Data collection conclude  |
 * | Data collection           | Max data exceeded   | Standby                   |
 * | Data collection           | Error               | Error                     |
 * +---------------------------+---------------------+---------------------------+
 * | Data collection conclude  | None                | Standby                   |
 * | Data collection conclude  | Error               | Error                     |
 * +---------------------------+---------------------+---------------------------+
 * | Error                     | None                | Error                     |
 *
 * NOTES
 * Internal and external events can trigger state changes
 * Timer interrupt triggers LED changes
 * Hardware interrupt trigger "external" events (button push, SD card inserted or removed)
 *
 * DESIGN PATTERNS
 * Switch/case and enums
 * Table
 * Object-oriented design pattern
 *
 */
