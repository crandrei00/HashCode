#pragma once

#include <memory>
#include "Ride.hpp"
#include "Reader.hpp"

struct Car
{
   Coord m_currentPosition;
   bool  m_onTrip;
   bool  m_onRoute;
   int   m_rideNumber;
   Ride  m_currentRide;
   int   m_distanceToFinish;
   int   m_distanceToRideStart;
   int   m_carID;

   std::vector<int> m_rides;

   Car(int id)
      : m_currentPosition(Coord())
      , m_onTrip(false)
      , m_onRoute(false)
      , m_rideNumber(-1)
      , m_currentRide()
      , m_distanceToFinish(-1)
      , m_distanceToRideStart(-1)
      , m_carID(id)
   {
   }

   void takeRide(Ride& ride)
   {
      m_onTrip = true;
      m_rideNumber = ride.id();
      m_currentRide = ride;  
      m_distanceToRideStart = getDistance(m_currentPosition, m_currentRide.startPosition());

      m_rides.push_back(m_rideNumber);
   }

   void finishRide()
   {
      m_onTrip = false;
      m_onRoute = false;
      m_rideNumber = -1;
      m_distanceToRideStart = -1;
      m_distanceToFinish = -1;
   }
};

typedef std::vector<Car> Cars;
typedef std::shared_ptr<Cars> CarsPtr;

CarsPtr getCars(Reader& reader);
