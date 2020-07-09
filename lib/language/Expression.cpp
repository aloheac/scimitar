/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Expression base class implementation.
 *
 *    DESCRIPTION: This file provides implementations for methods defined in the Expression base class. This class
 *                 provides a base type for arithmetic and conditional expressions appearing in the Scimitar language.
 *                 The implementations here are rather sparse, as nearly all the implementation details are expected to
 *                 be provided by derived types. This base class primarily exists to enable polymorphic behavior.
 *
 *    CREATION DATE: May 5, 2020
 *
 *********************************************************************************************************************/


#include "Expression.h"

Expression::Expression( Type this_type ) : type( this_type ) { }

Expression::Type Expression::get_type() {
    return type;
}