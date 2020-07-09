/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Source code file input/output utility class definitions.
 *
 *    DESCRIPTION: This header file defines utility classes used to handle file input/output operations for loading
 *                 source code files into the compiler.
 *
 *    CREATION DATE: November 19, 2019
 *
 *********************************************************************************************************************/


#ifndef SCIMITAR7_SOURCEFILESTREAM_H
#define SCIMITAR7_SOURCEFILESTREAM_H

#include <fstream>


/**
 * Exception class which is thrown when a file stream input/output error is encountered within the SourceFileStream
 * class.
 */
class SourceFileStreamException : public std::exception {

public:
    /**
     * Constructor.
     * @param msg Error message associated with this exception.
     */
    SourceFileStreamException( std::string msg );

    /**
     * Provides the exception's error message.
     * @return The error message.
     */
    virtual const char* what() const throw();

private:
    /**
     * The associated error message.
     */
    std::string msg;

};


/**
 * Utility class to handle loading a source code file from disk and provide the loaded string to the compiler.
 */
class SourceFileStream {

public:
    /**
     * Constructor. The file is loaded in its entirety into an internal buffer upon calling the constructor. The file
     * must be accessible when this method is called.
     * @param filename Path and filename to the source code file to be loaded.
     */
    SourceFileStream( std::string filename );

    /**
     * Gets the entire contents of the loaded source code file as a string, as stored in the object's internal buffer.
     * @return The loaded file's contents as a string.
     */
    std::string get();

private:
    /**
     * Path and filename of the source code file to be loaded.
     */
    std::string filename;

    /**
     * Internal buffer to hold the loaded file contents. This buffer is populated when the constructor is called.
     */
    std::string buffer;

};

#endif //SCIMITAR7_SOURCEFILESTREAM_H
