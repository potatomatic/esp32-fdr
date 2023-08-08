#pragma once

#include <HardwareSerial.h>


///
/// @brief Initialize telemetry receiving via a serial port.
///
/// The function does not configure, start, or stop the serial port.
/// It should be done externally.
///
/// @param telemetry_port serial port object used to receive telemetry. 
///
void initTelemetryReceiver(HardwareSerial& telemetry_port);