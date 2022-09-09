//
// Created by David Zhi LuoZhang on 9/4/22.
//

//#include "AState.h"
#include <string>
#include <unordered_map>


#ifndef PERSOFTWARECHALLENGE22_23_TASK_A_H
#define PERSOFTWARECHALLENGE22_23_TASK_A_H

#endif //PERSOFTWARECHALLENGE22_23_TASK_A_H

int print();

void parseA(const std::string& path, std::unordered_map<std::string, std::unordered_map<int, float>*>* powerAndSpeedMap);

void minMaxAverage(std::unordered_map<int, float>* timeLog, float calculations[4]);

float monteCarloIntegrator(std::unordered_map<int, float>* timeLog);

constexpr unsigned int myHash(const char* str, int h = 0);

namespace constants{
    const std::string TASK_A_FILE_PATH = "/Users/dluozhang/Downloads/DATA_TASK_A.csv";

    const std::string CURRENT = "Value AMS Current";
    const std::string VOLTAGE = "Value AMS Voltage";
    const std::string FL_SPEED = "Value PCM Front MPH 0";
    const std::string FR_SPEED = "Value PCM Front MPH 1";
    const std::string RL_SPEED = "Value PCM Rear MPH 0";
    const std::string RR_SPEED = "Value PCM Rear MPH 1";

//    constexpr const char* test = "Value AMS Current";

    const int CURRENT_I = 0;
    const int VOLTAGE_I = 1;
    const int FL_SPEED_I = 2;
    const int FR_SPEED_I = 3;
    const int RL_SPEED_I = 4;
    const int RR_SPEED_I = 5;

//    const int CURRENT_ID = 170;
//    const int VOLTAGE_ID = 172;
//    const int FL_SPEED_ID = 95;
//    const int FR_SPEED_ID = 96;
//    const int RL_SPEED_ID = 97;
//    const int RR_SPEED_ID = 98;

    const int IS_CURRENT_FOUND = 0;
    const int IS_VOLTAGE_FOUND = 1;
    const int IS_FL_SPEED_FOUND = 2;
    const int IS_FR_SPEED_FOUND = 3;
    const int IS_RL_SPEED_FOUND = 4;
    const int IS_RR_SPEED_FOUND = 5;

    const std::string POWER_KEY = "Power (kW)";
    const std::string FL_SPEED_KEY = "PCM Front MPH 0";
    const std::string FR_SPEED_KEY = "PCM Front MPH 1";
    const std::string RL_SPEED_KEY = "PCM Rear MPH 0";
    const std::string RR_SPEED_KEY = "PCM Rear MPH 1";

    const std::string TOTAL_ENERGY_KEY = "Total Energy";

    const std::string FL_SPEED_STATS = "PCM Front MPH 0 Min, Max, Avg:";
    const std::string FR_SPEED_STATS = "PCM Front MPH 1 Min, Max, Avg:";
    const std::string RL_SPEED_STATS = "PCM Rear MPH 0 Min, Max, Avg:";
    const std::string RR_SPEED_STATS = "PCM Rear MPH 1 Min, Max, Avg:";
//
//
//    const std::string FR_SPEED_MIN_KEY = "PCM Front Min MPH 1";
//    const std::string FR_SPEED_MAX_KEY = "PCM Front Max MPH 1";
//    const std::string FR_SPEED_AVG_KEY = "PCM Front Avg MPH 1";
//
//    const std::string RL_SPEED_MIN_KEY = "PCM Rear Min MPH 0";
//    const std::string RL_SPEED_MAX_KEY = "PCM Rear Max MPH 0";
//    const std::string RL_SPEED_AVG_KEY = "PCM Rear Avg MPH 0";
//
//    const std::string RR_SPEED_MIN_KEY = "PCM Rear Min MPH 1";
//    const std::string RR_SPEED_MAX_KEY = "PCM Rear Max MPH 1";
//    const std::string RR_SPEED_AVG_KEY = "PCM Rear Avg MPH 1";
}

