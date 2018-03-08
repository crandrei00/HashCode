/**
The idea is to sort all the rides based on distance to start and assign those rides to all the available cars.
It's not meant to be the best idea, but rather an intermediary step toward a better solution.
**/

//-----------------------------------

#include "stdafx.h"
#include "HashCode.hpp"

//-----------------------------------

void execute_closestToStart(const Reader& reader, Rides& rides)
{
   // sort rides
   std::sort(rides.begin(), rides.end(), compareRides_closestToStart());

   std::ofstream outFile;
   std::string fileName = "closestToStart_" + reader.m_fileName + ".out";
   outFile.open(fileName);
   for (unsigned i = 0; i < reader.m_numOfCars; i++)
   {
      outFile << 1<< " " << rides[i].id() << "\n";
   }
   outFile.close();
}

//-----------------------------------

void execute_closestToStartAndEarliestStart(const Reader& reader, Rides& rides)
{
   // sort rides
   std::sort(rides.begin(), rides.end(), compareRides_closestToStart());

   std::ofstream outFile;
   std::string fileName = "closestToStart2_" + reader.m_fileName + ".out";
   outFile.open(fileName);
   for (unsigned i = 0; i < reader.m_numOfCars; i++)
   {
      outFile << 1 << " " << rides[i].id() << "\n";
   }
   outFile.close();
}

//-----------------------------------
