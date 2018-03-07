#include "stdafx.h"
#include "Ride.hpp"

//-----------------------------------

bool operator==(const Coord& first, const Coord& second)
{
   return first.first == second.first && first.second == second.second;
}

//-----------------------------------

unsigned long getDistance(const Coord& first, const Coord& second)
{
   return std::abs(first.first - second.first) + std::abs(first.second - second.second);
}

//-----------------------------------

int generateBestPriorityScore(Coord refPosition, Rides& rides, unsigned step)
{
   unsigned long bestScore = std::numeric_limits<unsigned long>::max();
   int bestScoreIndex = -1;

   for (auto i = 0; i < rides.size() && bestScore != 0; i++)
   {
      Ride& ride = rides[i];

      unsigned long distanceToRide = getDistance(refPosition, ride.startPosition());
      unsigned long rideLen = getDistance(ride.startPosition(), ride.endPosition());
      unsigned long rideScore = ride.finishTime() - (distanceToRide + rideLen) - step;

      if (rideScore >= 0 && rideScore < bestScore)
      {
         bestScore = rideScore; 
         bestScoreIndex = i;
      }
   }

   return bestScoreIndex;
}

//-----------------------------------

void purgeExpiredRidesForStep(Rides& rides, unsigned step)
{
   auto ride = rides.begin();
   while (ride != rides.end())
   {
      if (ride->finishTime() <= step)
      {
         ride = rides.erase(ride);
      }
      else
      {
         ++ride;
      }
   }
}

//-----------------------------------
