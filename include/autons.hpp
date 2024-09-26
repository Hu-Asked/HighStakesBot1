#pragma once

#include "EZ-Template/drive/drive.hpp"

#ifndef AUTONS_HPP
#define AUTONS_HPP

extern const int DRIVE_SPEED;
extern const int TURN_SPEED;
extern const int SWING_SPEED;

extern Drive chassis;

void RedLeft();
void RedRight();
void RedRight2();
void BlueLeft();
void BlueRight();
void BlueRight2();
void AutonomousSkills();

void drive_example();
void turn_example();
void swing_example();
void interfered_example();

void default_constants();

#endif  // AUTONS_HPP