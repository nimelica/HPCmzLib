﻿/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include "IHasMass.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Chemistry { class ChemicalFormula; }


// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016, 2017 Stefan Solntsev
//
// This file (IHasChemicalFormula.cs) is part of Chemistry Library.
//
// Chemistry Library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chemistry Library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Chemistry Library. If not, see <http://www.gnu.org/licenses/>.

namespace Chemistry {
    /// <summary>
    /// An object that has a chemical formula
    /// </summary>
    class IHasChemicalFormula : public IHasMass {

        /// <summary>
        /// The chemical formula of this object
        /// </summary>
    public:
        virtual ChemicalFormula *getThisChemicalFormula() const = 0;

    };
}
