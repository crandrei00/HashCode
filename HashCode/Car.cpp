#include "stdafx.h"
#include "Car.hpp"

//-----------------------------------

void getCars(Reader& reader, Cars& cars)
{
   cars.reserve(reader.m_numOfCars * 2);
   for (unsigned i = 0; i < reader.m_numOfCars; i++)
   {
      Car newCar(i);
      cars.push_back(newCar);
   }
}

//-----------------------------------
