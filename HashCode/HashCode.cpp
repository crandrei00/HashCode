// HashCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashCode.hpp"

int main()
{
   Rides rides; 
   Cars cars;
   RidesPerCar ridesPerCar(350, std::vector<int>());

   // read rides info
   Reader reader;
   
   reader.read("a_example.in", rides);
   //reader.read("b_should_be_easy.in", rides);
   //reader.read("c_no_hurry.in", rides);
   //reader.read("d_metropolis.in", rides);
   //reader.read("e_high_bonus.in", rides);

   for (unsigned i = 0; i < reader.m_numOfCars; i++)
   {
      Car newCar(i);
      cars.push_back(newCar);
   }

   //execute_closestToStart(reader, rides);
   //execute_closestToCar(reader, cars, rides);
   //execute_closestToStartAndEarliestStart(reader, rides);
   execute_bestRoutePriority(reader, cars, rides);

   return 0;
}

