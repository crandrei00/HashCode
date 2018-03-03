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

//-----------------------------------

unsigned generateBestPriorityScore(Coord refPosition, Rides& rides, unsigned step)
{
   unsigned bestScore = std::numeric_limits<unsigned>::max();
   unsigned bestScoreIndex = -1;

   for (auto i = 0; i < rides.size() && bestScore != 0; i++)
   {
      Ride& ride = rides[i];

      auto distanceToRide = getDistance(refPosition, ride.startPosition());
      auto rideLen = getDistance(ride.startPosition(), ride.endPosition());
      auto rideScore = ride.finishTime() - (distanceToRide + rideLen) - step;

      if (rideScore >= 0 && rideScore < bestScore)
      {
         bestScore = rideScore; 
         bestScoreIndex = i;
      }
   }

   return bestScoreIndex;
}