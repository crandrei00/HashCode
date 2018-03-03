#pragma once

#include <vector>
#include <algorithm>
#include "Reader.hpp"
#include "Car.hpp"

void execute_closestToStart(const Reader& reader, Rides& rides);
void execute_closestToStartAndEarliestStart(const Reader& reader, Rides& rides);
void execute_closestToCar(const Reader& reader, Cars& cars, Rides& rides);