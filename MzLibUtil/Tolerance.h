﻿/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include <string>
#include <cmath>
#include <regex>

#include "DoubleRange.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (Tolerance.cs) is part of MassSpectrometry.
//
// MassSpectrometry is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpectrometry is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpectrometry. If not, see <http://www.gnu.org/licenses/>.


namespace MzLibUtil {
    /// <summary>
    /// The tolerance, or error, of two points
    /// </summary>
    class Tolerance {
    private:
        double privateValue = 0;

        /// <summary>
        /// A regex for parsing a string representation of a tolerance
        /// <para>
        /// i.e., "10 PPM", "-+10 PPM", "5 Absolute", etc...
        /// </para>
        /// </summary>

        /// <summary>
        /// Creates a new tolerance given a unit, value, and whether the tolerance is ±
        /// </summary>
        /// <param name="unit">The units for this tolerance</param>
        /// <param name="value">The numerical value of the tolerance</param>
    protected:
        Tolerance(double value);

        /// <summary>
        /// The value of the tolerance
        /// </summary>
    public:
        double getValue() const;

        /// <summary>
        /// Calculates a tolerance from the string representation
        /// <para>
        /// i.e., "10 PPM", "-+10 PPM", "5 Absolute", etc...
        /// </para>
        /// </summary>
        /// <param name="s"></param>
        static Tolerance *ParseToleranceString(const std::string &s);

        /// <summary>
        /// Gets the range of values encompassed by this tolerance
        /// </summary>
        /// <param name="mean">The mean value</param>
        /// <returns></returns>
        virtual DoubleRange *GetRange(double mean) {
            return NULL;
        }

        /// <summary>
        /// Gets the minimum value that is still within this tolerance
        /// </summary>
        /// <param name="mean"></param>
        /// <returns></returns>
        virtual double GetMinimumValue(double mean) {
            return (double) 0.0;
        }
             

        /// <summary>
        /// Gets the maximum value that is still within this tolerance
        /// </summary>
        /// <param name="mean"></param>
        /// <returns></returns>
        virtual double GetMaximumValue(double mean) {
            return (double) 0.0;
        }


        /// <summary>
        /// Indicates if the two values provided are within this tolerance
        /// </summary>
        /// <param name="experimental">The experimental value</param>
        /// <param name="theoretical">The theoretical value</param>
        /// <returns>Returns true if the value is within this tolerance  </returns>
        virtual bool Within(double experimental, double theoretical){
            return false;
        }
                

    };
}
