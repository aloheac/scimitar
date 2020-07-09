/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Source code file input/output utility class implementations.
 *
 *    DESCRIPTION: This file implements utility classes used to handle file input/output operations for loading source
 *                 code files into the compiler.
 *
 *    CREATION DATE: November 19, 2019
 *
 *********************************************************************************************************************/


#include <iostream>
#include "SourceFileStream.h"

/**********************************************************************************************************************
 * EngineException Class Implementation
 *********************************************************************************************************************/
SourceFileStreamException::SourceFileStreamException( std::string this_msg ) : exception(), msg( this_msg ) { }


const char* SourceFileStreamException::what() const throw() {
    return msg.c_str();
}


/**********************************************************************************************************************
 * SourceFileStream Class Implementation
 *********************************************************************************************************************/
SourceFileStream::SourceFileStream( std::string this_filename ) : filename( this_filename ) {
    std::ifstream ifs( filename, std::ifstream::in );

    if ( ifs.good() ) {
        buffer = std::string( std::istreambuf_iterator<char>( ifs ), std::istreambuf_iterator<char>() );
    } else {
        throw SourceFileStreamException( "Failed to open source file." );
    }

    ifs.close();
}


std::string SourceFileStream::get() {
    return buffer;
}