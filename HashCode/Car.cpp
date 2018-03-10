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

      // timeFactor > 0    --> BONUS
      // timeFactor == 0   --> ON TIME
      // timeFactor < 0    --> LATE, should not pair car with ride
      unsigned long timeFactor = std::numeric_limits<unsigned long>::min();
      unsigned long distanceToStart = std::numeric_limits<unsigned long>::max();
      
      if (!car.m_onTrip && !car.m_onRoute) // car available
      {
         distanceToStart = getDistance(ride.startPosition(), car.m_currentPosition);
         timeFactor = ride.time() - (distanceToStart + ride.rideLength());
      }
      else // car unavailable, either on trip and/or on route
      {
         distanceToStart = car.m_distanceToRideStart + car.m_currentRide.rideLength()
            + getDistance(ride.startPosition(), car.m_currentRide.endPosition());  
         timeFactor = ride.time() - 
            (distanceToStart + (car.m_currentRide.startTime() + car.m_currentRide.rideLength()) + ride.rideLength());
      }

      if (distanceToStart < minDistanceToStart && timeFactor >= 0)
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
