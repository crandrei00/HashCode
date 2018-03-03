#include "stdafx.h"
#include "Ride.hpp"

//-----------------------------------

bool operator==(const Coord& first, const Coord& second)
{
   return first.first == second.first && first.second == second.second;
}

//-----------------------------------

int getDistance(const Coord& first, const Coord& second)
{
   return std::abs(first.first - second.first) + std::abs(first.second - second.second);
}