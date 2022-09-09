//
// Created by David Zhi LuoZhang on 9/4/22.
//

#include "AState.h"
using namespace std;

AState::AState(int timestep) {
    this->timestep = timestep;
}

string AState::toString() {
    return "Time: " + to_string(timestep) + ", Power: " + to_string(power) + ", RL_MPH: " +
    to_string(rearLeftMPH) + ", RR_MPH: " + to_string(rearRightMPH) + ", FL_MPH:" +
    to_string(frontLeftMPH) + ", FR_MPH: " + to_string(frontRightMPH);
}

//void AState::setPower(float power) {
//    this->power = power;
//}
//
//void AState::setRearLeftMPH(float rearLeftMPH) {
//    this->rearLeftMPH = rearLeftMPH;
//}
//
//void AState::setRearRightMPH(float rearRightMPH) {
//    this->rearRightMPH = rearRightMPH;
//}
//
//void AState::setFrontLeftMPH(float frontLeftMPH) {
//    this->frontLeftMPH = frontLeftMPH;
//}
//
//void AState::setFrontRightMPH(float frontRightMPH) {
//    this->frontRightMPH = frontRightMPH
//}
