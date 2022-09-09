//
// Created by David Zhi LuoZhang on 9/4/22.
//

#ifndef PERSOFTWARECHALLENGE22_23_ASTATE_H
#define PERSOFTWARECHALLENGE22_23_ASTATE_H

#include <string>

// Was originally going to use a data object to keep records for each time step, but realized this imposed significant
// overhead and (more importantly) made it difficult to save time steps with incomplete readings

class AState {

    public:

    AState(int timestep);

    int timestep;
    float power;
    float rearLeftMPH;
    float rearRightMPH;
    float frontLeftMPH;
    float frontRightMPH;

//    Unnecessary setters and stack usage if the fields were going to be public anyway
//    void setPower(float power);
//
//    void setRearLeftMPH(float rearLeftMPH);
//
//    void setRearRightMPH(float rearRightMPH);
//
//    void setFrontLeftMPH(float frontLeftMPH);
//
//    void setFrontRightMPH(float frontRightMPH);
    std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> toString();
};


#endif //PERSOFTWARECHALLENGE22_23_ASTATE_H
