﻿/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include <vector>
#include <functional>
#include <optional>
#include <type_traits>

#include "DoubleRange.h"
#include "IPeak.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (ISpectrum.cs) is part of MassSpectrometry.
//
// MassSpectrometry is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpectrometry is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY ors
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpectrometry. If not, see <http://www.gnu.org/licenses/>.

using namespace MzLibUtil;

namespace Spectra
{
    /// <summary>
    /// Spectrum that has at least an X array and a Y array
    /// </summary>
    /// <typeparam name="TPeak"></typeparam>
    //C# TO C++ CONVERTER TODO TASK: C++ does not allow specifying covariance or contravariance
    // in a generic type list:
    //ORIGINAL LINE: public interface ISpectrum<out TPeak> where TPeak : IPeak

    template<typename TPeak>
    class ISpectrum
    {
#ifndef NDEBUG
        //static_assert(std::is_base_of<IPeak, TPeak>::value, "TPeak must inherit from IPeak");
#endif
    public:
        virtual std::vector<double> getXArray() const = 0;
        virtual std::vector<double> getYArray() const = 0;

        virtual std::optional<double> getFirstX() const = 0;
        virtual std::optional<double> getLastX() const = 0;
        virtual int getSize() const = 0;
        virtual std::optional<double> getYofPeakWithHighestY() = 0;
        virtual std::optional<double> getXofPeakWithHighestY() = 0;
        virtual double getSumOfAllY() = 0;
        virtual DoubleRange *getRange() const = 0;

        virtual std::vector<std::vector<double>> CopyTo2DArray() = 0;

        virtual int NumPeaksWithinRange(double minX, double maxX) = 0;

        virtual std::optional<int> GetClosestPeakIndex(double x) = 0;

        virtual std::optional<double> GetClosestPeakXvalue(double x) = 0;

        virtual std::vector<TPeak> FilterByNumberOfMostIntense(int topNPeaks) = 0;

        virtual std::vector<TPeak> Extract(DoubleRange *xRange) = 0;

        virtual std::vector<TPeak> Extract(double minX, double maxX) = 0;

        virtual std::vector<TPeak> FilterByY(double minY, double maxY) = 0;

        virtual std::vector<TPeak> FilterByY(DoubleRange *yRange) = 0;

        virtual void ReplaceXbyApplyingFunction(std::function<double(IPeak*)> convertor) = 0;
    };
}
