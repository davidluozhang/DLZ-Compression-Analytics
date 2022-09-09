//
// Created by David Zhi LuoZhang on 9/7/22.
//

#include "taskC.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <iostream>
using namespace std;

void encode(const string& path, const string& outName, fstream* fileOut){
    fstream file;
    file.open(path.c_str(), ios::in);
    if (!file.is_open()) throw runtime_error("Error loading file for task C encoding");

    (*fileOut).open(outName.c_str(), ios::out | ios::binary);
    int prevTime = -1;
    unordered_map<int, float> canValueMap;
    while (file.good()) {
        string inputLine;
        getline(file, inputLine);
        vector<string> tokens;
        if (inputLine.substr(0, inputLine.find(' ')) == "Value") {
            string label = inputLine.substr(0, inputLine.find(':'));
        } else {
            stringstream line(inputLine);
            string item;
            while (getline(line, item, ',')) {
                tokens.push_back(item);
            }
            if (tokens.size() < 3) continue;
            int timestep = stoi(tokens.at(0));
            if (timestep != prevTime) {
                prevTime = timestep;
                int n = canValueMap.size();
                canValueMap.clear();
            }
            try {
                canValueMap[stoi(tokens.at(1))] = stof(tokens[2]);
            } catch (const invalid_argument &e) {
                cout << "NaN value" << endl;
            }
            try {
                timestep = stoi(tokens.at(0));
            } catch (const invalid_argument &e) {
                continue;
            }
        }

    }
}