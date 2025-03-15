#include <iostream>

#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
#include <sstream>

#define BYTE 8

// Question 3: This is an extension task that requires you to decode sensor data from a CAN log file.
// CAN (Controller Area Network) is a communication standard used in automotive applications (including Redback cars)
// to allow communication between sensors and controllers.
//
// Your Task: Using the definition in the Sensors.dbc file, extract the "WheelSpeedRR" values
// from the candump.log file. Parse these values correctly and store them in an output.txt file with the following format:
// (<UNIX_TIME>): <DECODED_VALUE>
// eg:
// (1705638753.913408): 1234.5
// (1705638754.915609): 6789.0
// ...
// The above values are not real numbers; they are only there to show the expected data output format.
// You do not need to use any external libraries. Use the resources below to understand how to extract sensor data.
// Hint: Think about manual bit masking and shifting, data types required,
// what formats are used to represent values, etc.
// Resources:
// https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial
// https://www.csselectronics.com/pages/can-dbc-file-database-intro

int main()
{

    // can ID: 1797
    //  SG_ WheelSpeedRR : 32|16@0+ (0.1,0) [0|0] "km/h" Vector__XXX
    // starting bit is 32, 4th byte
    // 16 bits in length, 2 bytes
    // @0+ for big-endian/Motorola
    // (0.1,0) scale, offset
    // [min | max] optional meta information can be set to 0|0
    // km/h unit

    // read the file
    std::ifstream fin;
    fin.open("candump.log");

    ofstream outputFile;
    outputFile.open("output.txt");

    // get line is used because the data is stored in each line
    std::string currrent_line;
    while (std::getline(fin, currrent_line))
    {
        // get the correct info out

        std::istringstream ss(currrent_line);
        std::string unixtimestamp, vcan0, can_id, rest_of_the_string;
        std::vector<std::string> vec;

        ss >> unixtimestamp >> vcan0 >> can_id >> rest_of_the_string;
        // vector of string instead of fix array

        // 1. go past UNIX TIMESTAMP

        // 2. use standard identifier of 1797 or 0x705 in hex
        //
        int identifier = 0x705;

        if (identifier = can_id)
        {
            // go to the 4th byte

            // get raw_value_decimal ( 2 bytes )
            uint16_t raw_value_decimal;
            // Bif endian convertion

            uint16_t converted = 0;
            // converted = first byte << 8
            // converted |= second byte

            uint32_t physical_value;

            // physical_value = offset + scale * raw_value_decimal
            physical_value = 0 + 0.1 * converted;

            // store info
            outputFile << unixtimestamp << ': ' << physical_value;
        };
    };

    fin.close();

    outputFile.close();

    return;
}
