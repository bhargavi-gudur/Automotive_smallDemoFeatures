/**
 * @file ev_can_signal_decoder.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an Electric Vehicle CAN Message Signal Decoder.
 *
 *   The system receives raw CAN frames and decodes important
 *   EV signals such as:
 *   - Battery State of Charge (SoC)
 *   - Vehicle Speed
 *   - Motor Temperature
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL array
 *   - STL vector
 *   - STL map
 *   - STL bitset
 *   - Bitwise operations
 *
 * @date 02-09-2026
 */

#include <array>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

/**
 * @class CANDevice
 * @brief Abstract base class for a CAN-enabled ECU.
 */
class CANDevice
{
public:

    /**
     * @brief Receive and process CAN data.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~CANDevice() = default;
};

/**
 * @class EV_CAN_Decoder
 * @brief Decodes EV CAN frame signals.
 */
class EV_CAN_Decoder : public CANDevice
{
private:

    /**
     * @brief Represents an 8-byte CAN data frame.
     */
    using CANFrame = array<uint8_t, 8>;

    /**
     * @brief Stores received CAN frames.
     */
    vector<CANFrame> frames;

    /**
     * @brief Maps CAN IDs to message names.
     */
    map<uint32_t, string> messageNames
    {
        {0x100, "Battery Status"},
        {0x200, "Motor Status"},
        {0x300, "Vehicle Status"}
    };

    /**
     * @brief Extracts bits from a CAN byte.
     */
    uint8_t extractBits(
        uint8_t data,
        int startBit,
        int length) const
    {
        const uint8_t mask =
            static_cast<uint8_t>(
                (1U << length) - 1U
            );

        return
            (data >> startBit) & mask;
    }

    /**
     * @brief Decode Battery State of Charge.
     *
     * Byte 0:
     * Bits 0-6 -> SoC
     */
    double decodeSoC(
        const CANFrame& frame) const
    {
        const uint8_t rawSoC =
            extractBits(frame[0], 0, 7);

        return static_cast<double>(rawSoC);
    }

    /**
     * @brief Decode vehicle speed.
     *
     * Byte 1 and Byte 2 form a 16-bit value.
     *
     * Resolution = 0.1 km/h
     */
    double decodeSpeed(
        const CANFrame& frame) const
    {
        const uint16_t rawSpeed =
            static_cast<uint16_t>(frame[1])
            |
            (static_cast<uint16_t>(frame[2]) << 8);

        return rawSpeed * 0.1;
    }

    /**
     * @brief Decode motor temperature.
     *
     * Byte 3 contains temperature.
     * Offset = -40°C
     */
    double decodeMotorTemperature(
        const CANFrame& frame) const
    {
        return static_cast<double>(frame[3]) - 40.0;
    }

public:

    /**
     * @brief Create sample CAN frames.
     */
    void createFrames()
    {
        frames.push_back(
            {75, 220, 5, 105, 0, 0, 0, 0}
        );

        frames.push_back(
            {55, 144, 7, 115, 0, 0, 0, 0}
        );

        frames.push_back(
            {30, 100, 4, 130, 0, 0, 0, 0}
        );
    }

    /**
     * @brief Process and decode CAN frames.
     */
    void processData() override
    {
        cout << "===== EV CAN Signal Decoder =====\n";

        createFrames();

        vector<uint32_t> canIDs
        {
            0x100,
            0x200,
            0x300
        };

        for(size_t i = 0;
            i < frames.size();
            ++i)
        {
            const CANFrame& frame =
                frames[i];

            const uint32_t canID =
                canIDs[i];

            cout << "\nCAN ID: 0x"
                 << hex
                 << canID
                 << dec
                 << endl;

            cout << "Message: "
                 << messageNames[canID]
                 << endl;

            cout << "Raw Data: ";

            for(uint8_t byte : frame)
            {
                cout << bitset<8>(byte)
                     << " ";
            }

            cout << endl;

            cout << fixed
                 << setprecision(1);

            cout << "Battery SoC       : "
                 << decodeSoC(frame)
                 << " %"
                 << endl;

            cout << "Vehicle Speed     : "
                 << decodeSpeed(frame)
                 << " km/h"
                 << endl;

            cout << "Motor Temperature : "
                 << decodeMotorTemperature(frame)
                 << " °C"
                 << endl;

            /*
             * Telematics warning logic.
             */
            if(decodeSoC(frame) < 20)
            {
                cout << "Warning: LOW BATTERY SoC ⚠️"
                     << endl;
            }

            if(decodeMotorTemperature(frame) > 80)
            {
                cout << "Warning: MOTOR OVERHEATING ⚠️"
                     << endl;
            }
        }
    }
};

/**
 * @brief Main function.
 *
 * Demonstrates runtime polymorphism using
 * a base-class pointer.
 */
int main()
{
    CANDevice* device =
        new EV_CAN_Decoder();

    device->processData();

    delete device;

    return 0;
}