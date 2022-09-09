//
// Created by David Zhi LuoZhang on 9/4/22.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "taskA.h"
#include <random>
//#include "AState.h"

using namespace std;
int print() {
    cout << "testing!" << endl;
    return 0;
}

void parseA(const string& path, unordered_map<string, unordered_map<int, float>*>* powerAndSpeedMap) {
    fstream file;
    file.open(path.c_str(), ios::in);
    if (!file.is_open()) throw runtime_error("Error loading file for task A");

/* Preferable to use streams for modularity in C++
 * FILE* file = fopen(path.c_str(), "r");
    if (file == nullptr) {
        throw runtime_error("Error loading file for task A");
        }
*/


    bool isValFound[6] = {false}; //Encodings as follows:
    // isValFound[0] -> current
    // isValFound[1] -> voltage
    // isValFound[2] -> front left mph
    // isValFound[3] -> front right mph
    // isValFound[4] -> rear left mph
    // isValFound[5] -> rear right mph

//    Replaced inordinate amount of bools with the above bool array
//    bool current_found = false;
//    bool voltage_found = false;
//    bool RL_MPH_found = false;
//    bool RR_MPH_found = false;
//    bool FL_MPH_found = false;
//    bool FR_MPH_found = false;

    float t_current;
    float t_voltage;
//    vector<AState> states;
    int prevTime = -1;

//    Issue with below was that the below all lived in local scope and so were lost when stack was popped
//    Moved initialization into main

//    unordered_map<string, unordered_map<int, float>*> powerAndSpeedMap;
//    unordered_map<int, float> powers;
//    unordered_map<int, float> flSpeeds;
//    unordered_map<int, float> frSpeeds;
//    unordered_map<int, float> rlSpeeds;
//    unordered_map<int, float> rrSpeeds;
//
//    (*powerAndSpeedMap)["Power"] = &powers;
//    (*powerAndSpeedMap)["PCM Front MPH 0"] = &flSpeeds;
//    (*powerAndSpeedMap)["PCM Front MPH 1"] = &frSpeeds;
//    (*powerAndSpeedMap)["PCM Rear MPH 0"] = &rlSpeeds;
//    (*powerAndSpeedMap)["PCM Rear MPH 1"] = &rrSpeeds;

    unordered_map<int, float> *powers = (*powerAndSpeedMap)[constants::POWER_KEY];
    unordered_map<int, float> *flSpeeds = (*powerAndSpeedMap)[constants::FL_SPEED_KEY];
    unordered_map<int, float> *frSpeeds = (*powerAndSpeedMap)[constants::FR_SPEED_KEY];
    unordered_map<int, float> *rlSpeeds = (*powerAndSpeedMap)[constants::RL_SPEED_KEY];
    unordered_map<int, float> *rrSpeeds = (*powerAndSpeedMap)[constants::RR_SPEED_KEY];

    int IDs[6] = {};
    while (file.good()) {
        string inputLine;
        getline(file, inputLine);
        vector<string> tokens;
        if (inputLine.substr(0, inputLine.find(' ')) == "Value") {
            string label = inputLine.substr(0, inputLine.find(':'));
//            const char* labelC = label.c_str();
//            switch (myHash(labelC, 0)) {
//                case myHash(constants::test, 0):
//            }
            if (label == constants::VOLTAGE) {
                string temp = inputLine.substr(inputLine.find(':') + 2);
                IDs[constants::VOLTAGE_I] = stoi(temp);
            } else if (label == constants::CURRENT) {
                string temp = inputLine.substr(inputLine.find(':') + 2);
                IDs[constants::CURRENT_I] = stoi(temp);
            } else if (label == constants::FL_SPEED) {
                string temp = inputLine.substr(inputLine.find(':') + 2);
                IDs[constants::FL_SPEED_I] = stoi(temp);
            } else if (label == constants::FR_SPEED) {
                string temp = inputLine.substr(inputLine.find(':') + 2);
                IDs[constants::FR_SPEED_I] = stoi(temp);
            } else if (label == constants::RL_SPEED) {
                string temp = inputLine.substr(inputLine.find(':') + 2);
                IDs[constants::RL_SPEED_I] = stoi(temp);
            } else if (label == constants::RR_SPEED) {
                string temp = inputLine.substr(inputLine.find(':') + 2);
                IDs[constants::RR_SPEED_I] = stoi(temp);
            } else {
                continue;
            }
        } else {
            stringstream line(inputLine);
            string item;
            while (getline(line, item, ',')) {
                tokens.push_back(item);
            }
            if (tokens.size() < 3) continue;
            int timestep;
            try {
                timestep = stoi(tokens.at(0));
            } catch (const invalid_argument &e) {
                continue;
            }
            int id = stoi(tokens.at(1));
//        AState state = AState(timestep);
//        Note: There used to be a check here to make sure we weren't repeat adding the same time step, but I
//        accidentally deleted that
            if (timestep != prevTime
                && (id == IDs[constants::VOLTAGE_I]
                    || id == IDs[constants::CURRENT_I]
                    || id == IDs[constants::FL_SPEED_I]
                    || id == IDs[constants::FR_SPEED_I]
                    || id == IDs[constants::RL_SPEED_I]
                    || id == IDs[constants::RR_SPEED_I])){
                for (bool &i: isValFound) {
                    i = false;
                }
                prevTime = timestep;
            }
//            switch(id){
            if (id == IDs[constants::CURRENT_I]) {

//            }
//            switch (id) {
//                case constants::CURRENT_ID {
                    if (isValFound[constants::IS_CURRENT_FOUND]) continue;
                    float value = stof(tokens.at(2));
                    t_current = value;
                    isValFound[constants::IS_CURRENT_FOUND] = true;
//                current_found = true;
//                    break;
                } else if (id == IDs[constants::VOLTAGE_I])  {
//                case constants::VOLTAGE_ID: {
                    if (isValFound[constants::IS_VOLTAGE_FOUND]) continue;
                    float value = stof(tokens.at(2));
                    t_voltage = value;
                    isValFound[constants::IS_VOLTAGE_FOUND] = true;
//                voltage_found = true;
//                    break;
                } else if (id == IDs[constants::FL_SPEED_I]) {
//                case constants::FL_SPEED_ID: {
                    if (isValFound[constants::IS_FL_SPEED_FOUND]) continue;
                    float value = stof(tokens.at(2));
                    isValFound[constants::IS_FL_SPEED_FOUND] = true;
                    (*flSpeeds)[timestep] = value;
//                flSpeeds.push_back(value);
//                state.frontLeftMPH = value;
//                FL_MPH_found = true;
//                    break;
                } else if (id == IDs[constants::FR_SPEED_I]) {
//                case constants::FR_SPEED_ID: {
                    if (isValFound[constants::IS_FR_SPEED_FOUND]) continue;
                    float value = stof(tokens.at(2));
                    isValFound[constants::IS_FR_SPEED_FOUND] = true;
                    (*frSpeeds)[timestep] = value;
//                frSpeeds.push_back(value);
//                state.frontRightMPH = value;
//                FR_MPH_found = true;
//                    break;
                } else if (id == IDs[constants::RL_SPEED_I]) {
//                case constants::RL_SPEED_ID: {
                    if (isValFound[constants::IS_RL_SPEED_FOUND]) continue;
                    float value = stof(tokens.at(2));
                    isValFound[constants::IS_RL_SPEED_FOUND] = true;
                    (*rlSpeeds)[timestep] = value;
//                rlSpeeds.push_back(value);
//                state.rearLeftMPH = value;
//                RL_MPH_found = true;
//                    break;
                } else if (id == IDs[constants::RR_SPEED_I]) {
//                case constants::RR_SPEED_ID: {
                    if (isValFound[constants::IS_RR_SPEED_FOUND]) continue;
                    float value = stof(tokens.at(2));
                    isValFound[constants::IS_RR_SPEED_FOUND] = true;
                    (*rrSpeeds)[timestep] = value;
//                rrSpeeds.push_back(value);
//                cout << "adding value" << endl;
//                state.rearRightMPH = value;
//                RR_MPH_found = true;
//                    break;
                } else {
//                default:
                    continue;
            }
            if (isValFound[constants::IS_VOLTAGE_FOUND] && isValFound[constants::IS_CURRENT_FOUND]) {
                float power = t_current * t_voltage / 1000;
                (*powers)[timestep] = power;
//            powers.push_back(power);
//            state.power = power;
            }
//            for (int i = 0; i < 6; i++) {
//                cout << IDs[i] <<endl;
//            }

            //cout << to_string(num_wheels_found) << endl;
//        if (current_found && voltage_found && RL_MPH_found && RR_MPH_found && FL_MPH_found && FR_MPH_found) {
//            current_found = false;
//            voltage_found = false;
//            RL_MPH_found = false;
//            RR_MPH_found = false;
//            FL_MPH_found = false;
//            FR_MPH_found = false;
//            states.push_back(state);
//            cout << "Adding state to back of state vector" << endl;
//        }
//        if (id == 172) {
//            t_voltage = value;
//            voltage_found = true;
//        } else if (id == 170) {
//            t_current = value;
//            voltage_found = true;
//        } else if (id == 95 || id == 96 || id == 97 || id == 98) {
//
//        }
        }
    }

//    for (vector<float> * & vec : powerAndSpeedVectors) {
//        cout << (*vec).size() << endl;
//    }

    file.close();
//    cout <<  "fr size" << endl;
//    cout << (*frSpeeds).size() << endl;
//    cout << ((*powerAndSpeedMap)["PCM Front MPH 1"]).size() << endl;
}

void minMaxAverage(unordered_map<int, float>* timeLog, float calculations[4]) {
    float min = numeric_limits<float>::max();
    float max = -numeric_limits<float>::max();
    int minTime = numeric_limits<int>::max();
    int maxTime = -numeric_limits<int>::max();
    float sum = 0;
    for (auto& itr : *timeLog) {
        if (itr.second > max) {
            max = itr.second;
        }
        if (itr.second < min) {
            min = itr.second;
        }
        if (itr.first > maxTime) {
            maxTime = itr.first;
        }
        if (itr.first < minTime) {
            minTime = itr.first;
        }
        sum += itr.second;
    }
    float average = sum / (*timeLog).size();
    calculations[0] = min;
    calculations[1] = max;
    calculations[2] = average;

    float monteCarloAverage = monteCarloIntegrator(timeLog) / (maxTime - minTime);
    calculations[3] = monteCarloAverage;
}

float monteCarloIntegrator(unordered_map<int, float>* timeLog) {
    int minTime = numeric_limits<int>::max();
    int maxTime = -numeric_limits<int>::max();
    for (auto& itr : *timeLog) {
        if (itr.first > maxTime) {
            maxTime = itr.first;
        }
        if (itr.first < minTime) {
            minTime = itr.first;
        }
    }
    float sum = 0;
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    uniform_int_distribution<int> uniform_random(1, 2);
    int count = 0;
    for (auto& itr : *timeLog) {
//        int random = uniform_random(gen);
//        if (random == 1) {
            count++;
            sum += itr.second;
//        }
    }
//    cout << "Monte Carlo Fraction Sampled: " << count << "/" <<(*timeLog).size() << endl;
    return sum * (maxTime - minTime) / count;
}

// #ToDo: Try to get switch on string literals working!
constexpr unsigned int myHash(const char* str, int h) {
    return !str[h] ? 5381 : (myHash(str, h+1)*33) ^ str[h];
}