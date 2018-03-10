/**
Change of perspective: instead of assigning rides to available cars, assign best car (available or not)
to current ride, where the "bestness" shall be computed based on how soon can a car be available at the
ride start position and deliver the passenger on time. 
*/

//-----------------------------------

#include "stdafx.h"
#include "HashCode.hpp"

//-----------------------------------

void execute_bestCarForRide(const Reader& reader, Cars& cars, Rides& rides)
{
   std::cout << "Processing execute_bestCarForRide() on file " + reader.m_fileName + " ... \n";

   // sort rides according to (i) distance to origin and (ii) start time
   std::sort(rides.begin(), rides.end(), compareRides_closestToStartAndEarliestStart());

   for (auto ride : rides)
   {
      //if (hasTimeRunOut(cars, reader.m_totalT)) break;

      findCarForRide(ride, cars);
   }

   std::ofstream outFile;
   std::string fileName = "bestCarForRide_" + reader.m_fileName.substr(0, reader.m_fileName.find(".in")) + ".out";
   outFile.open(fileName);
   for (auto car : cars)
   {
      outFile << car.m_rides.size();
      for (auto rideTaken : car.m_rides)
      {
         outFile << " " << rideTaken;
      }
      outFile << "\n";
   }
   outFile.close();

   std::cout << "Processing execute_bestCarForRide() on file " + reader.m_fileName + " ... done! \n";
}

//-----------------------------------
