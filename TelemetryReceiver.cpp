#include "TelemetryReceiver.hpp"

#include "mavlink/common/mavlink.h"


void initTelemetryReceiver(HardwareSerial& telemetry_port)
{
    Serial.println("Initializing telemetry receiver");

    static std::size_t total_bytes_received = 0;

    telemetry_port.onReceive([&telemetry_port] () {
        int const bytes_available = telemetry_port.available();
        Serial.printf("Received %d telemetry bytes\n", bytes_available);

        while (telemetry_port.available()) 
        {
            mavlink_status_t status;
            mavlink_message_t msg;
            
            if (mavlink_parse_char(MAVLINK_COMM_0, telemetry_port.read(), &msg, &status))
            {
                Serial.printf("Received MavLink message with ID %d, sequence: %d from component %d of system %d\n", 
                    msg.msgid, msg.seq, msg.compid, msg.sysid);
            };
        }

        total_bytes_received += bytes_available;
        Serial.printf("Total telemetry bytes received %d\n", static_cast<int>(total_bytes_received));
    });

    telemetry_port.onReceiveError([] (hardwareSerial_error_t error) {
        Serial.printf("Telemetry receive error: %d\n", static_cast<int>(error));
    });
}
