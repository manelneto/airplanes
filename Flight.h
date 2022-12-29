//
// Created by manue on 29/12/2022.
//

#ifndef AIRPLANES_FLIGHT_H
#define AIRPLANES_FLIGHT_H


#include <string>
#include "Airport.h"
#include "Airline.h"

class Flight {
private:
    Airport source;
    Airport target;
    Airline airline;
};


#endif //AIRPLANES_FLIGHT_H
