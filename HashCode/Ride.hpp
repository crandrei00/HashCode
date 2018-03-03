#pragma once

#include <utility>
#include <vector>

class Ride;
typedef std::pair<int, int>            Coord;
typedef std::vector<Ride>              Rides;
typedef std::vector<std::vector<int> > RidesPerCar;

class Ride
{
   Coord m_startPos;
   Coord m_endPos;
   int m_startTime;
   int m_finishTime;
   int m_rideID;

public:
   Ride()
      : m_startPos(Coord())
      , m_endPos(Coord())
      , m_startTime(0)
      , m_finishTime(0)
      , m_rideID(-1)
   {
   }

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

bool operator==(const Coord& first, const Coord& second);

//-----------------------------------

int getDistance(const Coord& first, const Coord& second);

//-----------------------------------

struct compareRides_closestToStart
{
   bool operator()(const Ride& first, const Ride& second)
   {
      auto firstDistanceToStart = first.startPosition().first + first.startPosition().second;
      auto secondDistanceToStart = second.startPosition().first + second.startPosition().second;

      if (firstDistanceToStart < secondDistanceToStart)
         return true;
      else
         return false;
   }
};

//-----------------------------------

struct compareRides_closestToStartAndEarliestStart
{
   bool operator()(const Ride& first, const Ride& second)
   {
      auto firstDistanceToStart = first.startPosition().first + first.startPosition().second;
      auto secondDistanceToStart = second.startPosition().first + second.startPosition().second;

      if (firstDistanceToStart < secondDistanceToStart)
         return true;
      else if (firstDistanceToStart == secondDistanceToStart && first.startTime() < second.startTime())
         return true;
      else
         return false;
   }
};

//-----------------------------------

struct compareRides_closestToCar
{
   compareRides_closestToCar(Coord position)
      : m_referecenCarCurrentPosition(position)
   {
   }

   bool operator()(const Ride& first, const Ride& second)
   {
      return true;
   }

   Coord m_referecenCarCurrentPosition;
};
