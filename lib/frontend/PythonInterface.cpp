/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Python library interface implementation.
 *
 *    DESCRIPTION: This file implements the target Python library interface, as provided using the external PYBIND11
 *                 library. This file is sparse, as all the relevant logic is provided through functions that are
 *                 defined elsewhere. The functions provided here, however, provide a "connection" between Python and
 *                 the compiled C++ library.
 *
 *    CREATION DATE: November 22, 2019
 *
 *********************************************************************************************************************/

#include "PythonInterface.h"
#include "ParserFrontend.h"

std::string compile( std::string input ) {
    return evaluate_job( input );
}