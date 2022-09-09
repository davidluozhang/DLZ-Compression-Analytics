//
// Created by David Zhi LuoZhang on 9/6/22.
//

#include <unordered_map>
#include "taskB.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "taskA.h"
#include <random>
#include <regex>

using namespace std;

void parseB(const string &path, unordered_map<string, unordered_map<int, float>*>* powerAndSpeedMap) {
    fstream file;
    file.open(path.c_str(), ios::in);
    if (!file.is_open()) throw runtime_error("Error loading file for task B");
    bool isValFound[4] = {false};
    float t_current;
    float t_voltage;
    unordered_map<int, float> *powers = (*powerAndSpeedMap)[constants::POWER_KEY];
    unordered_map<int, float> *flSpeeds = (*powerAndSpeedMap)[constants::FL_SPEED_KEY];
    unordered_map<int, float> *frSpeeds = (*powerAndSpeedMap)[constants::FR_SPEED_KEY];
    string firstLine;
    try {
        getline(file, firstLine);
    } catch (const exception &e) {
        cout << "Error reading first header line" << endl;
        return;
    }
    firstLine = firstLine.substr(0, firstLine.find(" PM"));
    firstLine = firstLine.substr(0, firstLine.find(" AM"));
//    vector<string> headerTokens;
    stringstream header(firstLine);
    string initialTime;
    while (getline(header, initialTime, ' ')) {
//        headerTokens.push_back(headerItem);
    }
    string prevTime = "";
    while (file.good()) {
        string inputLine;
        getline(file, inputLine);
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), ','), inputLine.end());
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '['), inputLine.end());
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), ']'), inputLine.end());
        stringstream line(inputLine);
//        regex re("[0-9]{2}[:][0-9]{2}[:][0-9]{2}[.][0-9]{3}[ ][0-9][ ][0][x][0-9]{1,2}[ ][48][ ][\\[]")
        vector<string> tokens;
        string item;
        while (getline(line, item, ' ')) {
            tokens.push_back(item);
        }
        if (tokens.size() < 8) continue;
        string time = tokens.at(0);
        string canID1 = tokens.at(1);
        string canID2 = tokens.at(2);
        char can1[canID1.length() + 1];
        char can2[canID2.length() + 1];
        strcpy(can1, canID1.c_str());
        strcpy(can2, canID2.c_str());
        int mostSig = ((unsigned char) can1[0] - '0') << 8;
        int middleSig = ((unsigned char) can2[2] - '0') << 4;
        int leastSig = (unsigned char) can2[3] - '0';
        int canHex = mostSig + middleSig + leastSig;
        if (canHex != bConstants::B_VOLTAGE_ID
            && canHex != bConstants::B_CURRENT_ID
            && canHex != bConstants::FW_SPEED_ID) {
            continue;
        }
        if (time != prevTime) {
            prevTime = time;
            for (bool &i: isValFound) {
                i = false;
            }
        }
        int n = stoi(tokens.at(3));
        vector<int> bytes;
        tokens.erase(tokens.begin() + 4);
        for (int i = 0; i < n; i++) {
            bytes.push_back((stoi(tokens.at(4 + i))) << (8 * (i % 4)));
        }
        switch (canHex) {
            case bConstants::B_VOLTAGE_ID: {
                if (isValFound[constants::IS_VOLTAGE_FOUND]) continue;
                isValFound[constants::IS_VOLTAGE_FOUND] = true;
                t_voltage = littleEndianBinaryToFloat(&bytes);
                break;
            }
            case bConstants::B_CURRENT_ID: {
                if (isValFound[constants::IS_CURRENT_FOUND]) continue;
                isValFound[constants::IS_CURRENT_FOUND] = true;
                t_current = littleEndianBinaryToFloat(&bytes);
                break;
            }
            case bConstants::FW_SPEED_ID: {
                if (isValFound[constants::IS_FR_SPEED_FOUND] && isValFound[constants::IS_FL_SPEED_FOUND]) continue;
                isValFound[constants::IS_FR_SPEED_FOUND] = true;
                float leftRightSpeed[2] = {0};
                multiLittleEndianBinaryToFloat(&bytes, leftRightSpeed, n);
                int timestep = timeElapsed(initialTime, time);
                float flSpeed = RPMtoMPH(leftRightSpeed[0]);
                float frSpeed = RPMtoMPH(leftRightSpeed[1]);
                if (flSpeed != std::numeric_limits<double>::infinity() && flSpeed != -std::numeric_limits<double>::infinity()) {
                    (*flSpeeds)[timestep] = flSpeed;
                    isValFound[constants::IS_FL_SPEED_FOUND] = true;
//                    cout << flSpeed << endl;
                }
                if (frSpeed != std::numeric_limits<double>::infinity() && flSpeed != -std::numeric_limits<double>::infinity()) {
                    (*frSpeeds)[timestep] = frSpeed;
                    isValFound[constants::IS_FR_SPEED_FOUND] = true;
                }
                break;
            }
        }
        if (isValFound[constants::IS_VOLTAGE_FOUND] && isValFound[constants::IS_CURRENT_FOUND]) {
            int timestep = timeElapsed(initialTime, time);
            float power = t_current * t_voltage / 1000;
            (*powers)[timestep] = power;
        }
    }
}

int timeElapsed(string start, string now) {
    regex re("[:.]");

    sregex_token_iterator firstStart{start.begin(), start.end(), re, -1}, lastStart;
    vector<string> startTokens{firstStart, lastStart};
    vector<int> startTokenInts;
    for (auto & startToken : startTokens) {
        startTokenInts.push_back(stoi(startToken));
    }

    sregex_token_iterator firstNow{now.begin(), now.end(), re, -1}, lastNow;
    vector<string> nowTokens{firstNow, lastNow};
    vector<int> nowTokenInts;
    for (auto & nowToken : nowTokens) {
        nowTokenInts.push_back(stoi(nowToken));
    }
    return nowTokenInts.at(3) - startTokenInts.at(3)
        + 1000 * (nowTokenInts.at(2) - startTokenInts.at(2))
        + 60000 * (nowTokenInts.at(1) - startTokenInts.at(1))
        + 3600000 * (nowTokenInts.at(0) - startTokenInts.at(0));
}

float littleEndianBinaryToFloat(vector<int>* bytes){
    int binarySum = 0;
    for (int i = 0; i < 4; i++) {
        binarySum += (*bytes).at(i);
    }
    auto* floatPtr = (float*) &binarySum;
    return *floatPtr;
}

void multiLittleEndianBinaryToFloat(vector<int>* bytes, float outputs[], int n){
    for (int j = 0; j < n / 4; j++) {
        int binarySum = 0;
        for (int i = 0; i < 4; i++) {
            binarySum += (*bytes).at(i + j * 4);
        }
        auto* floatPtr = (float*) &binarySum;
        outputs[j] = *floatPtr;
    }
}

float RPMtoMPH(float RPM) {
    return bConstants::minInHour * RPM * bConstants::diameterInch * bConstants::pi / bConstants::inchInMile;
}