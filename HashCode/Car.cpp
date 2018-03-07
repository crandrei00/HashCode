#include "stdafx.h"
#include "Car.hpp"

CarsPtr getCars(Reader& reader)
{
   CarsPtr cars = std::make_shared<Cars>();
   for (unsigned i = 0; i < reader.m_numOfCars; i++)
   {
      Car newCar(i);
      cars->push_back(newCar);
   }

   return cars;
}
