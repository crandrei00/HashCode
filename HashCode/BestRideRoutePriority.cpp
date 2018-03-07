/**
Sort rides based not only on closeness to current car, but also on a time-based priority, i.e. fastest 
arrival to final ride step. Also added car wait for current route - route assigned, car on start, but too
soon to start ride.
**/

#include "stdafx.h"
#include "HashCode.hpp"
#include <iostream>

void execute_bestRoutePriority(const Reader& reader, CarsPtr cars, Rides& rides)
{
   std::cout << "Processing file " + reader.m_fileName + " ... \n";

   // sort rides
   for (unsigned step = 0; step < reader.m_totalT && rides.size(); ++step)
   {
      purgeExpiredRidesForStep(rides, step);

      for (auto carIt = 0; carIt < cars->size(); carIt++)
      {
         if (rides.size() == 0)
         {
            break;
         }

         Car& car = cars->at(carIt);
         if (!car.m_onTrip && !car.m_onRoute)
         {
            int rideIndex = generateBestPriorityScore(car.m_currentPosition, rides, step);

            // pick first ride, as it is assumed to be the best for current car
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
               car.m_onRoute = true;
               car.m_distanceToFinish = getDistance(car.m_currentPosition, car.m_currentRide.endPosition());
               --car.m_distanceToFinish;
            }
            else
            {
               // car too soon on ride starting point
               car.m_distanceToRideStart > 0 ? --car.m_distanceToRideStart : car.m_distanceToRideStart;
            }
         }
         else if (car.m_onTrip && !car.m_onRoute)
         {
            car.m_distanceToRideStart > 0 ? --car.m_distanceToRideStart : car.m_distanceToRideStart;

            if (car.m_distanceToRideStart == 0 && car.m_currentRide.startTime() <= step)
            {
               car.m_onRoute = true;
               car.m_distanceToFinish = getDistance(car.m_currentPosition, car.m_currentRide.endPosition());
            }
         }
         else if (car.m_onTrip && car.m_onRoute)
         {
            --car.m_distanceToFinish;

            if (car.m_distanceToFinish == 0)
            {
               car.finishRide();
            }
         }
      }
   }

   std::ofstream outFile;
   std::string fileName = "bestRoutePriority_" + reader.m_fileName.substr(0, reader.m_fileName.find(".in")) + ".out";
   outFile.open(fileName);
   for (auto car : *cars)
   {
      outFile << car.m_rides.size();
      for (auto rideTaken : car.m_rides)
      {
         outFile << " " << rideTaken;
      }
      outFile << "\n";
   }
   outFile.close();

   std::cout << "Processing file " + reader.m_fileName + " ... done! \n";
}