#pragma once

//-----------------------------------

#include <memory>
#include "Ride.hpp"
#include "Reader.hpp"

//-----------------------------------

struct Car
{
   Coord          m_currentPosition;
   bool           m_onTrip;
   bool           m_onRoute;
   int            m_rideNumber;
   Ride           m_currentRide;
   int            m_distanceToRideFinish;
   int            m_distanceToRideStart;
   int            m_carID;

   std::vector<int> m_rides;

   Car(int id)
      : m_currentPosition(Coord())
      , m_onTrip(false)
      , m_onRoute(false)
      , m_rideNumber(-1)
      , m_currentRide()
      , m_distanceToRideFinish(-1)
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
      m_distanceToRideFinish = m_distanceToRideStart + ride.rideLength();

      m_rides.push_back(m_rideNumber);
   }

   void finishRide()
   {
      m_currentPosition = m_currentRide.endPosition();
      m_onTrip = false;
      m_onRoute = false;
      m_rideNumber = -1;
      m_distanceToRideStart = -1;
      m_distanceToRideFinish = -1;
   }

   int advanceToRideStart()
   {
      m_distanceToRideStart > 0 ? --m_distanceToRideStart : m_distanceToRideStart;
      return m_distanceToRideStart;
   }

   int advanceToRideFinish()
   {
      m_distanceToRideFinish > 0 ? --m_distanceToRideFinish : m_distanceToRideFinish;
      return m_distanceToRideFinish;
   }
};

//-----------------------------------

typedef std::vector<Car> Cars;

//-----------------------------------

void getCars(Reader& reader, Cars& cars);

//-----------------------------------

bool hasTimeRunOut(const Cars& cars, unsigned totalTime);

//-----------------------------------

void findCarForRide(Ride& ride, Cars& cars);

//-----------------------------------
