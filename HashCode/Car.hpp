#pragma once

#include "Ride.hpp"

struct Car
{
   Coord m_currentPosition;
   bool  m_onTrip;
   int   m_rideNumber;
   Ride  m_currentRide;
   int   m_distanceToFinish;
   int   m_carID;

   Car() {}
};