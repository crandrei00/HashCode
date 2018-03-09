#include "stdafx.h"
#include "Car.hpp"

//-----------------------------------

void getCars(Reader& reader, Cars& cars)
{
   cars.reserve(reader.m_numOfCars * 2);
   for (unsigned i = 0; i < reader.m_numOfCars; i++)
   {
      Car newCar(i);
      cars.push_back(newCar);
   }
}

//-----------------------------------

void findCarForRide(Ride& ride, Cars& cars)
{
   unsigned long minDistanceToStart = std::numeric_limits<unsigned long>::max();
   int minDistanceCarIndex = -1;

   for (auto i = 0; i < cars.size(); ++i)
   {
      Car& car = cars[i];
      unsigned long distanceToStart = std::numeric_limits<unsigned long>::max();
      if (!car.m_onTrip && !car.m_onRoute) // car available
      {
         distanceToStart = getDistance(ride.startPosition(), car.m_currentPosition);
      }
      else if (car.m_onTrip && !car.m_onRoute) // car has current trip to start
      {
         distanceToStart = getDistance(car.m_currentPosition, car.m_currentRide.startPosition())
            + car.m_currentRide.rideLength()
            + getDistance(ride.startPosition(), car.m_currentRide.endPosition());

      }
      else // if (car->m_onTrip && car->m_onRoute) // car has current trip to finish
      {
         distanceToStart = getDistance(ride.startPosition(), car.m_currentRide.endPosition())
            + car.m_currentRide.rideLength(); // ? not entirely correct, since we don't really know where the car is; presumably ride start
      }

      if (distanceToStart < minDistanceToStart &&
         ride.finishTime() - (distanceToStart + ride.rideLength()) >= 0)
      {
         minDistanceToStart = distanceToStart;
         minDistanceCarIndex = i;
      }
   }

   if (minDistanceCarIndex != -1)
   {
      // assign ride to cars[carIndex]
      cars[minDistanceCarIndex].takeRide(ride);
   }
}

//-----------------------------------

bool hasTimeRunOut(const Cars& cars, unsigned totalTime)
{
   unsigned outOfTimeLimitCars = 0;
   for (auto car : cars)
   {
      if (!car.m_rides.size() && car.m_currentRide.startTime() > totalTime)
      {
         ++outOfTimeLimitCars;
      }
   }

   return (outOfTimeLimitCars == cars.size());
}

//-----------------------------------
