#include <iostream>
#include "taskA.h"
#include "taskB.h"
#include <unordered_map>
using namespace std;

int main() {

    cout << "-- Task A --" << endl;

    unordered_map<string, unordered_map<int, float>*> taskATimeStates;

    unordered_map<int, float> powersA;
    unordered_map<int, float> flSpeedsA;
    unordered_map<int, float> frSpeedsA;
    unordered_map<int, float> rlSpeedsA;
    unordered_map<int, float> rrSpeedsA;

    taskATimeStates[constants::POWER_KEY] = &powersA;
    taskATimeStates[constants::FL_SPEED_KEY] = &flSpeedsA;
    taskATimeStates[constants::FR_SPEED_KEY] = &frSpeedsA;
    taskATimeStates[constants::RL_SPEED_KEY] = &rlSpeedsA;
    taskATimeStates[constants::RR_SPEED_KEY] = &rrSpeedsA;

//    cout << (taskATimeStates).size() << endl;
    parseA(constants::TASK_A_FILE_PATH, &taskATimeStates);
//    cout << (taskATimeStates).size() << endl;
//    cout << (*(taskATimeStates)[constants::POWER_KEY]).size() << endl;
//    cout << (*(taskATimeStates)[constants::FL_SPEED_KEY]).size() << endl;
//    cout << (*(taskATimeStates)[constants::FR_SPEED_KEY]).size() << endl;
//    cout << (*(taskATimeStates)[constants::RL_SPEED_KEY]).size() << endl;
//    cout << (*(taskATimeStates)[constants::RR_SPEED_KEY]).size() << endl;

    unordered_map<string, float*> taskASpeedStats;
    pair<string, string> keysA[4] = {
            {constants::FL_SPEED_KEY, constants::FL_SPEED_STATS},
            {constants::FR_SPEED_KEY, constants::FR_SPEED_STATS},
            {constants::RL_SPEED_KEY, constants::RL_SPEED_STATS},
            {constants::RR_SPEED_KEY, constants::RR_SPEED_STATS}};
    float flCalcs[4] = {0, 0, 0, 0};
    float frCalcs[4] = {0, 0, 0, 0};
    float rlCalcs[4] = {0, 0, 0, 0};
    float rrCalcs[4] = {0, 0, 0, 0};

    taskASpeedStats[constants::FL_SPEED_STATS] = flCalcs;
    taskASpeedStats[constants::FR_SPEED_STATS] = frCalcs;
    taskASpeedStats[constants::RL_SPEED_STATS] = rlCalcs;
    taskASpeedStats[constants::RR_SPEED_STATS] = rrCalcs;

    for (auto& itr : keysA) {
//        cout << itr.second << endl;
        minMaxAverage(taskATimeStates[itr.first], taskASpeedStats[itr.second]);
    }

    cout << "Front Left Wheel MPH\t--\tMin: " << (taskASpeedStats[constants::FL_SPEED_STATS])[0] << ",\tMax: "
         << (taskASpeedStats[constants::FL_SPEED_STATS])[1] << ",\tAvg: "
         << (taskASpeedStats[constants::FL_SPEED_STATS])[2] << ",\tM.C. Avg: "
         << (taskASpeedStats[constants::FL_SPEED_STATS])[3] << endl;

    cout << "Front Right Wheel MPH\t--\tMin: " << (taskASpeedStats[constants::FR_SPEED_STATS])[0] << ",\tMax: "
         << (taskASpeedStats[constants::FR_SPEED_STATS])[1] << ",\tAvg: "
         << (taskASpeedStats[constants::FR_SPEED_STATS])[2] << ",\tM.C. Avg: "
         << (taskASpeedStats[constants::FR_SPEED_STATS])[3] << endl;

    cout << "Rear Left Wheel MPH\t\t--\tMin: " << (taskASpeedStats[constants::RL_SPEED_STATS])[0] << ",\tMax: "
         << (taskASpeedStats[constants::RL_SPEED_STATS])[1] << ",\tAvg: "
         << (taskASpeedStats[constants::RL_SPEED_STATS])[2] << ",\tM.C. Avg: "
         << (taskASpeedStats[constants::RL_SPEED_STATS])[3] << endl;

    cout << "Rear Right Wheel MPH\t--\tMin: " << (taskASpeedStats[constants::RR_SPEED_STATS])[0] << ",\tMax: "
         << (taskASpeedStats[constants::RR_SPEED_STATS])[1] << ",\tAvg: "
         << (taskASpeedStats[constants::RL_SPEED_STATS])[2] << ",\tM.C. Avg: "
         << (taskASpeedStats[constants::RL_SPEED_STATS])[3] << endl;

    float energyA = monteCarloIntegrator(taskATimeStates[constants::POWER_KEY]) / 3600000;
    cout << "M.C. Total Energy kWh: \t--\t" << energyA << endl;

//    for (int i = 0; i < 10; i++) {
//        float energy = monteCarloIntegrator(taskATimeStates[constants::POWER_KEY]);
//        cout << "Total Energy (Monte Carlo): " << energy << endl;
//    }

    cout << "-- Task B --" << endl;

    unordered_map<string, unordered_map<int, float>*> taskBTimeStates;

    unordered_map<int, float> powersB;
    unordered_map<int, float> flSpeedsB;
    unordered_map<int, float> frSpeedsB;
    taskBTimeStates[constants::POWER_KEY] = &powersB;
    taskBTimeStates[constants::FL_SPEED_KEY] = &flSpeedsB;
    taskBTimeStates[constants::FR_SPEED_KEY] = &frSpeedsB;

    parseB(bConstants::TASK_B_FILE_PATH, &taskBTimeStates);

    unordered_map<string, float*> taskBSpeedStats;
    pair<string, string> keysB[2] = {
            {constants::FL_SPEED_KEY, constants::FL_SPEED_STATS},
            {constants::FR_SPEED_KEY, constants::FR_SPEED_STATS}};
    float flCalcsB[4] = {0, 0, 0, 0};
    float frCalcsB[4] = {0, 0, 0, 0};

    taskBSpeedStats[constants::FL_SPEED_STATS] = flCalcsB;
    taskBSpeedStats[constants::FR_SPEED_STATS] = frCalcsB;

    for (auto& itr : keysB) {
        minMaxAverage(taskBTimeStates[itr.first], taskBSpeedStats[itr.second]);
    }

    cout << "Front Left Wheel MPH\t--\tMin: " << (taskBSpeedStats[constants::FL_SPEED_STATS])[0] << ",\tMax: "
         << (taskBSpeedStats[constants::FL_SPEED_STATS])[1] << ",\tAvg: "
         << (taskBSpeedStats[constants::FL_SPEED_STATS])[2] << ",\tM.C. Avg: "
         << (taskBSpeedStats[constants::FL_SPEED_STATS])[3] << endl;

    cout << "Front Right Wheel MPH\t--\tMin: " << (taskBSpeedStats[constants::FR_SPEED_STATS])[0] << ",\tMax: "
         << (taskBSpeedStats[constants::FR_SPEED_STATS])[1] << ",\tAvg: "
         << (taskBSpeedStats[constants::FR_SPEED_STATS])[2] << ",\tM.C. Avg: "
         << (taskBSpeedStats[constants::FR_SPEED_STATS])[3] << endl;

    float energyB = monteCarloIntegrator(taskBTimeStates[constants::POWER_KEY]) / 3600000;
    cout << "M.C. Total Energy kWh: \t--\t" << energyB << endl;


    return 0;
}
