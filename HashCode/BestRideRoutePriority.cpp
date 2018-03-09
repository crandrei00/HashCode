/**
Sort rides based not only on closeness to current car, but also on a time-based priority, i.e. fastest 
arrival to final ride step. Also added car wait for current route - route assigned, car on start, but too
soon to start ride.
**/

//-----------------------------------

#include "stdafx.h"
#include "HashCode.hpp"

//-----------------------------------

void execute_bestRoutePriority(const Reader& reader, Cars& cars, Rides& rides)
{
   std::cout << "Processing execute_bestRoutePriority() on file " + reader.m_fileName + " ... \n";

   for (unsigned step = 0; step < reader.m_totalT && rides.size(); ++step)
   {
      purgeExpiredRidesForStep(rides, step);

      for (auto carIt = 0; carIt < cars.size(); carIt++)
      {
         if (rides.size() == 0) break;

         Car& car = cars[carIt];         
         if (!car.m_onTrip && !car.m_onRoute)
         {
            // car available; find next ride
            int rideIndex = generateBestPriorityScore(car.m_currentPosition, rides, step);

            // pick ride based on index; if negative, no ride available for current car position and step
            if (rideIndex < 0)
            {
               continue;
            }

            car.takeRide(rides[rideIndex]);

            // ride is no longer available, delete
            auto rideIt = rides.begin() + rideIndex;
            rides.erase(rideIt);

            if (car.m_distanceToRideStart == 0 && car.m_currentRide.startTime() <= step)
            {
               // car on starting point & able to start ride
               car.m_onRoute = true;               
               car.m_distanceToRideFinish = getDistance(car.m_currentPosition, car.m_currentRide.endPosition());
               car.advanceToRideFinish();
            }
            else 
            {
               // car too soon on ride starting point
               car.advanceToRideStart();
            }
         }
         else if (car.m_onTrip && !car.m_onRoute)
         {
            // car not available, but ride not started
            car.advanceToRideStart();
            
            if (car.m_distanceToRideStart == 0 && car.m_currentRide.startTime() <= step)
            {
               // start ride
               car.m_onRoute = true;
               car.m_distanceToRideFinish = getDistance(car.m_currentPosition, car.m_currentRide.endPosition());
            }
         }
         else if (car.m_onTrip && car.m_onRoute)
         {
            // car not available, currently on route to destination
            if (car.advanceToRideFinish() == 0)
            {
               car.finishRide();
            }
         }
      }
   }

   std::ofstream outFile;
   std::string fileName = "bestRoutePriority_" + reader.m_fileName.substr(0, reader.m_fileName.find(".in")) + ".out";
   outFile.open(fileName);
   for (auto car : cars)
   {
      outFile << car.m_rides.size();
      for (auto rideTaken : car.m_rides)
      {
         outFile << " " << rideTaken;
      }
      outFile << "\n";
   }
   outFile.close();

   std::cout << "Processing execute_bestRoutePriority() on file " + reader.m_fileName + " ... done! \n";
}

//-----------------------------------
