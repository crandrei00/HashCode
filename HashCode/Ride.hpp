#pragma once

#include <utility>
#include <vector>
#include <limits>

class Ride;
typedef std::pair<int, int>            Coord;
typedef std::vector<Ride>              Rides;
typedef std::vector<std::vector<int> > RidesPerCar;

//-----------------------------------

unsigned long getDistance(const Coord& first, const Coord& second);

//-----------------------------------

class Ride
{
   Coord m_startPos;
   Coord m_endPos;
   unsigned m_rideLen;
   unsigned m_startTime;
   unsigned m_finishTime;
   unsigned m_rideID;

public:
   Ride()
      : m_startPos(Coord())
      , m_endPos(Coord())
      , m_rideLen(0)
      , m_startTime(0)
      , m_finishTime(0)
      , m_rideID(-1)
   {
   }

   Ride(Coord start, Coord end, int startTime, int endTime, int id)
      : m_startPos(start)
      , m_endPos(end)
      , m_rideLen(getDistance(start, end))
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

   unsigned rideLength() const
   {
      return m_rideLen;
   }

   unsigned startTime() const
   {
      return m_startTime;
   }

   unsigned finishTime() const
   {
      return m_finishTime;
   }

   unsigned id() const
   {
      return m_rideID;
   }
};

//-----------------------------------

bool operator==(const Coord& first, const Coord& second);

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
      auto firstDistanceToStart = getDistance(Coord(0, 0), first.startPosition());
      auto secondDistanceToStart = getDistance(Coord(0, 0), second.startPosition());

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
      : m_referenceCarCurrentPosition(position)
   {
   }

   bool operator()(const Ride& first, const Ride& second)
   {
      auto distanceToFirst = getDistance(m_referenceCarCurrentPosition, first.startPosition());
      auto distanceToSecond = getDistance(m_referenceCarCurrentPosition, second.startPosition());

      if (distanceToFirst < distanceToSecond)
         return true;
      else if (distanceToFirst == distanceToSecond && first.startTime() < second.startTime())
         return true;
      else
         return false;
   }

   Coord m_referenceCarCurrentPosition;
};

//-----------------------------------

struct compareRides_closestToCar_
{
   compareRides_closestToCar_(Coord position, unsigned currentStep)
      : m_referenceCarCurrentPosition(position)
      , m_currentStep(currentStep)
   {
   }

   bool operator()(const Ride& first, const Ride& second)
   {
      auto distanceToFirst = getDistance(m_referenceCarCurrentPosition, first.startPosition());
      auto distanceToSecond = getDistance(m_referenceCarCurrentPosition, second.startPosition());

      auto firstLen = getDistance(first.startPosition(), first.endPosition());
      auto secondLen = getDistance(second.startPosition(), second.endPosition());

      auto firstRidePriorityScore = first.finishTime() - (distanceToFirst + firstLen) - m_currentStep;
      auto secondRidePriorityScore = second.finishTime() - (distanceToSecond + secondLen) - m_currentStep;

      if (firstRidePriorityScore < 0)
         return false;
      else if (firstRidePriorityScore == 0)
         return true;
      else if (secondRidePriorityScore < 0 && firstRidePriorityScore > 0)
         return true;
      else if (secondRidePriorityScore == 0 && firstRidePriorityScore > 0)
         return false;
      else if (firstRidePriorityScore < secondRidePriorityScore)
         return true;
      else
         return false;
   }

   Coord m_referenceCarCurrentPosition;
   unsigned m_currentStep;
};

//-----------------------------------

int generateBestPriorityScore(Coord refPosition, Rides& rides, unsigned step);

//-----------------------------------

void purgeExpiredRidesForStep(Rides& rides, unsigned step);
