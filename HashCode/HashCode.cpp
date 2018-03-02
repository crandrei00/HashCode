// HashCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include "Ride.hpp"
#include "Car.hpp"

Car car;

int main()
{
   int rows = 0;
   int columns = 0;
   int numOfCars = 0;
   int numOfRides = 0;
   int bonus = 0;
   int T;

   std::vector<Ride> rides; 
   std::vector<Car> cars;
   std::vector<std::vector<int> > ridesPerCar(350, std::vector<int>());

   std::ifstream inFile;
   std::ofstream outFile;
   inFile.open("Input.in");
   outFile.open("Write.out");

   // read rides info
   inFile >> rows >> columns >> numOfCars >> numOfRides >> bonus >> T;
   for (auto i = 0; i < numOfRides; i++)
   {
      int startX, startY, endX, endY, startT, endT; 
      inFile >> startX >> startY >> endX >> endY >> startT >> endT; 

      Ride ride(std::make_pair(startX, startY), std::make_pair(endX, endY), startT, endT, i);
      rides.push_back(ride);
   }

   for (auto i = 0; i < numOfCars; i++)
   {
      //Car newCar(Ride(std::make_pair(0, 0), std::make_pair(0, 0), 0, 0, 0));
      Car newCar;
      newCar.m_carID = i;
      newCar.m_onTrip = false;
      newCar.m_currentPosition = std::make_pair(0, 0);
      cars.push_back(newCar);
   }

   for (auto step = 0; step < T; step++)
   {
      for (auto bigCar : cars)
      {
         car = bigCar;
         if (!car.m_onTrip)
         {
            std::sort(rides.begin(), rides.end(), [](const Ride& first, const Ride& second) 
            {
               auto distanceToFirst = std::abs(car.m_currentPosition.first - first.startPosition().first)
                  + std::abs(car.m_currentPosition.second - first.startPosition().second);

               auto distanceToSecond = std::abs(car.m_currentPosition.first - second.startPosition().first)
                  + std::abs(car.m_currentPosition.second - second.startPosition().second);

               auto firstRideLen = std::abs(first.startPosition().first - first.endPosition().first)
                  + std::abs(first.startPosition().second - first.endPosition().second);

               auto secondRideLen = std::abs(second.startPosition().first - second.endPosition().first)
                  + std::abs(second.startPosition().second - second.endPosition().second);

               auto firstRideScore = first.finishTime() - (distanceToFirst + firstRideLen);
               auto secondRideScore = second.finishTime() - (distanceToSecond + secondRideLen);
               
               if (firstRideScore < 0)
                  return false;     

               if (secondRideScore < 0)
                  return true;

               return firstRideScore <= secondRideScore;               
            });

            // we chose ride[0];
            auto firstIT = rides.begin();
            Ride chosenRide(rides[0]);

            // update current car
            car.m_distanceToFinish = std::abs(chosenRide.endPosition().first - car.m_currentPosition.first)
               + std::abs(chosenRide.endPosition().second - car.m_currentPosition.second) - 1;
            car.m_rideNumber = chosenRide.id();
            car.m_currentRide = chosenRide;
            car.m_onTrip = true;

            // store ride id for current car
            
            ridesPerCar[car.m_carID].push_back(car.m_rideNumber);

            // mark ride as assigned
            rides.erase(rides.begin());
         }
         else // car on trip
         {
            if (--car.m_distanceToFinish == 0)
            {
               // car finished current ride - update underlying info
               car.m_currentPosition = car.m_currentRide.endPosition();
               car.m_rideNumber = -1;
               car.m_onTrip = false;                              
            }
         }
      }
   }

   for (auto carRides : ridesPerCar)
   {
      outFile << carRides.size();
      for (auto ride : carRides)
      {
         outFile << " " << ride; 
      }
      outFile << "\n";
   }

   //for (auto i = 0; i < numOfCars; i++)
   //{
   //   outFile << 1 << " " << i << "\n";
   //}

   //std::sort(rides.begin(), rides.end(), compareRides());

   inFile.close();
   outFile.close();

   return 0;
}

