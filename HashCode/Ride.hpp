#pragma once

#include <utility>

typedef std::pair<int, int> Coord;

class Ride
{
   Coord m_startPos;
   Coord m_endPos;
   int m_startTime;
   int m_finishTime;
   int m_rideID;

public:
   Ride() {}

   Ride(Coord start, Coord end, int startTime, int endTime, int id)
      : m_startPos(start)
      , m_endPos(end)
      , m_startTime(startTime)
      , m_finishTime(endTime)
      , m_rideID(id)
   {
   }

   Coord startPosition() const
   {
      return m_startPos;
   }

   Coord endPosition() const
   {
      return m_endPos;
   }

   int startTime() const
   {
      return m_startTime;
   }

   int finishTime() const
   {
      return m_finishTime;
   }

   int id() const
   {
      return m_rideID;
   }
};

//-----------------------------------

struct compareRides
{
   bool operator()(const Ride& first, const Ride& second)
   {
      // TODO

      return true;
   }
};