// HashCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashCode.hpp"

int main()
{
   Rides    ridesA,  ridesB,  ridesC,  ridesD,  ridesE; 
   Cars     carsA,   carsB,   carsC,   carsD,   carsE;
   Reader   readerA, readerB, readerC, readerD, readerE;
   
   readerA.read("a_example.in", ridesA);
   readerB.read("b_should_be_easy.in", ridesB);
   readerC.read("c_no_hurry.in", ridesC);
   readerD.read("d_metropolis.in", ridesD);
   readerE.read("e_high_bonus.in", ridesE);

   getCars(readerA, carsA);
   getCars(readerB, carsB);
   getCars(readerC, carsC);
   getCars(readerD, carsD);
   getCars(readerE, carsE);

   //execute_closestToStart(reader, rides);
   //execute_closestToCar(reader, cars, rides);
   //execute_closestToStartAndEarliestStart(reader, rides);
   
   execute_bestRoutePriority(readerA, carsA, ridesA);
   execute_bestRoutePriority(readerB, carsB, ridesB);
   execute_bestRoutePriority(readerC, carsC, ridesC);
   execute_bestRoutePriority(readerD, carsD, ridesD);
   execute_bestRoutePriority(readerE, carsE, ridesE);

   return 0;
}

