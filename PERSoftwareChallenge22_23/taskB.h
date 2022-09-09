//
// Created by David Zhi LuoZhang on 9/6/22.
//

#include <string>

#ifndef PERSOFTWARECHALLENGE22_23_TASKB_H
#define PERSOFTWARECHALLENGE22_23_TASKB_H

#endif //PERSOFTWARECHALLENGE22_23_TASKB_H

void parseB(const std::string &path, std::unordered_map<std::string, std::unordered_map<int, float>*>* powerAndSpeedMap);

int timeElapsed(std::string start, std::string now);

float littleEndianBinaryToFloat(std::vector<int>* bytes);

void multiLittleEndianBinaryToFloat(std::vector<int>* bytes, float outputs[], int n);

float RPMtoMPH(float RPM);


namespace bConstants{

    const std::string TASK_B_FILE_PATH = "/Users/dluozhang/Downloads/DATA_TASK_B";

    const int B_CURRENT_ID = 0x311;
    const int B_VOLTAGE_ID = 0x313;
    const int FW_SPEED_ID = 0x222;

    const float diameterInch = 19.5;
    const int minInHour = 60;
    const int inchInMile = 63360;
    const float pi = 3.14159265358979323846;
}