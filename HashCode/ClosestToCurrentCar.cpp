/**
For each car we sort the rides based on current car position and pick those rides which are closest
**/

#include "stdafx.h"
#include "HashCode.hpp"

void execute_closestToCar(const Reader& reader, Cars& cars, Rides& rides)
{
   // sort rides
   for (unsigned step = 0; step < reader.m_totalT && rides.size(); ++step)
   {
      for (auto carIt = 0; carIt < cars.size(); carIt++)
      {
         Car& car = cars[carIt];

         if (rides.size() == 0)
         {
            break;
         }

         if (!car.m_onTrip && !car.m_onRoute)
         {
            std::sort(rides.begin(), rides.end(), compareRides_closestToCar(car.m_currentPosition));

            // pick first ride, as it is assumed to be the best for current car
            car.takeRide(rides[0]);

            // ride is no longer available, delete
            rides.erase(rides.begin());

            if (car.m_distanceToRideStart == 0)
            {
               car.m_onRoute = true;               
               car.m_distanceToFinish = getDistance(car.m_currentPosition, car.m_currentRide.endPosition());
               --car.m_distanceToFinish;
            }
            else
            {
               --car.m_distanceToRideStart;
            }
         }
         else if (car.m_onTrip && !car.m_onRoute)
         {
            --car.m_distanceToRideStart;

            if (car.m_distanceToRideStart == 0)
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
   std::string fileName = "closestToCar_" + reader.m_fileName + ".out";
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
}