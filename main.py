"""
Scimitar 7 - A tool for parameter-space exploration.
Python Frontend

Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
See LICENSE.TXT distributed with the source for for license information.

    Main entry point for Scimitar script compilation.

    DESCRIPTION: This script provides the primary executable entry point for generating a simulation execution Python
                 script from a Scimitar source file.

    CREATION DATE: December 13, 2019
"""

import argparse
import os.path
from sys import exit
import colorama
import scimitar


# Define useful global constants.
color_err = colorama.Fore.RED + colorama.Style.BRIGHT
version = "Scimitar " + scimitar.Utility.RuntimeVersion.VERSION + "(" + scimitar.Utility.RuntimeVersion.DATE + "). " + scimitar.cli.get_copyright()

if __name__ == "__main__":
    # Define an argument parser, and execute it.
    parser = argparse.ArgumentParser( prog="scimitar", description="Scimitar compiler driver." )
    parser.add_argument( "-v", "--version", action="version", version=version )
    parser.add_argument( "-r", "--report", help="compiles source files and returns only a summary report.", action="store_true" )
    parser.add_argument( "filename", help="the source file to compile to a script.", action="store" )
    args = parser.parse_args()

    # Initialize the colorama package.
    colorama.init( autoreset=True )

    # Verify the source file exists.
    if not os.path.isfile( args.filename ):
        print( color_err + "Error:" + " source file '" + args.filename + "' does not exist, or you do not have permission to access it." )
        exit( -1 )

    # Load the source file.
    try:
        f = open( args.filename, 'r' )
    except IOError:
        print( color_err + "Error:" + " source file '" + args.filename + "' is not accessible." )
        exit( -1 )

    script = f.read()
    f.close()

    # Compile the script and obtain the result. Generate the corresponding scripts.
    run = scimitar.core.RunConfiguration( script )
    status, result = run.generateScript( args.report )

    # Check if only a report is requested; if so produce it and exit.
    if args.report:
        print( result )
        exit( 0 )

    # Save the resulting scripts to disk if the input successfully compiled.
    if status == 0:
        if len( result ) == 1:  # If true, no split scripts were requested. Save the single script.
            scimitar.cli.save_script( run.runSettings.cfg["scriptFilename"], result[ 0 ] )
        else:
            # Generate filename prefix for all scripts.
            split_filename = run.runSettings.cfg["scriptFilename"].split(".")
            base_filename = split_filename[ 0 ] + "_"

            # Save all scripts to disk.
            for n in range( 0, len( result ) ):
                filename = base_filename + str( n ) + ".py"
                scimitar.cli.save_script( filename, result[ n ] )
    else:
        print( color_err +  "Compilation failed: " + result )
