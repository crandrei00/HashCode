#pragma once

//-----------------------------------

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include "Reader.hpp"
#include "Car.hpp"

//-----------------------------------

void execute_closestToStart(const Reader& reader, Rides& rides);
void execute_closestToStartAndEarliestStart(const Reader& reader, Rides& rides);
void execute_closestToCar(const Reader& reader, Cars& cars, Rides& rides);
void execute_bestRoutePriority(const Reader& reader, Cars& cars, Rides& rides);
void execute_bestCarForRide(const Reader& reader, Cars& cars, Rides& rides);

//-----------------------------------
