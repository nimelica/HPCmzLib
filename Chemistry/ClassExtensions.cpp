﻿/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "ClassExtensions.h"
#include "Interfaces/IHasMass.h"
#include "Constants.h"

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

namespace Chemistry {

    double ClassExtensions::ToMz(IHasMass *objectWithMass, int charge) {
        return ToMz(objectWithMass->getMonoisotopicMass(), charge);
    }

    double ClassExtensions::ToMz(double mass, int charge) {
        return mass / std::abs(charge) + sign(charge) * Constants::protonMass;
    }

    double ClassExtensions::ToMass(double massToChargeRatio, int charge) {
        return std::abs(charge) * massToChargeRatio - charge * Constants::protonMass;
    }

    std::optional<double> ClassExtensions::RoundedDouble(std::optional<double> &myNumber, int places)
    {
        if (myNumber.has_value())
        {
#ifdef ORIG
            myNumber = std::make_optional(Math::Round(static_cast<double>(myNumber), places,
                                                       MidpointRounding::AwayFromZero));
#endif
            if ( places == 0 ) {
                myNumber = std::make_optional(floor(static_cast<double>(myNumber.value())));
            }
            else {
                myNumber = std::make_optional((floor((static_cast<double>(myNumber.value())*pow(10,places))+.5))/pow(10,places));
            }
        }
        return myNumber;
    }

    double ClassExtensions::RoundedDouble(double myNumber, int places)
    {
        
        if ( places == 0 ) {
            myNumber = floor(myNumber);
        }
        else {
            myNumber = (floor(myNumber*pow(10,places))+.5)/pow(10,places);
        }
        return myNumber;
    }

    
}
