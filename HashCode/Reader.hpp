#pragma once

#include <string>
#include <fstream>
#include "Ride.hpp"

struct Reader
{
   unsigned int m_numOfRows;
   unsigned int m_numOfColumns;
   unsigned int m_numOfCars;
   unsigned int m_numOfRides;
   unsigned int m_bonus;
   unsigned int m_totalT;
   std::string  m_fileName;

   Reader()
      : m_numOfRows(0)
      , m_numOfColumns(0)
      , m_numOfCars(0)
      , m_numOfRides(0)
      , m_bonus(0)
      , m_fileName("")
   {
   }

   bool read(std::string fileName, Rides& rides)
   {
      bool readSuccessfully = true;

      // open file
      m_fileName = fileName;
      std::ifstream inFile;
      inFile.open(m_fileName);

      // read problem params: number of rows and columns, total number of cars and rides, bonus for each ride and total time
      inFile >> m_numOfRows >> m_numOfColumns >> m_numOfCars >> m_numOfRides >> m_bonus >> m_totalT;

      // todo - parse in values; if not valid, readSuccessfully = false;

      // read rides information
      rides.reserve(m_numOfRides * 2);
      for (auto i = 0; i < m_numOfRides; i++)
      {
         int startX, startY, endX, endY, startT, endT; 
         inFile >> startX >> startY >> endX >> endY >> startT >> endT; 

         Ride ride(std::make_pair(startX, startY), std::make_pair(endX, endY), startT, endT, i);
         rides.push_back(ride);
      }

      // close file
      inFile.close();
      return readSuccessfully;
   }
};