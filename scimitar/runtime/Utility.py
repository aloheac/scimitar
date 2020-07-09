"""
Scimitar 7 - A tool for parameter-space exploration.
Python Frontend

Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
See LICENSE.TXT distributed with the source for for license information.

    Runtime utility classes.

    DESCRIPTION: This provides simple utility classes used in the runtime module.

    CREATION DATE: December 13, 2019
"""


class Run:
    def __init__( self, run ):
        self.run = run

    def get_value( self, parameter ):
        for param in self.run.items():
            if param[ 0 ] == parameter:
                return param[ 1 ]

    def get_pairs( self ):
        pairs = []
        for param in self.run.items():
            pairs.append( param )

        return pairs


class RuntimeVersion:
    """
    A simple structure which holds constants defining the version of the runtime.

    Fields:
        VERSION : Defines a version number string of the runtime. Generally in the form MAJOR.MINOR.REVISION.
        DATE : Defines a release date string of the runtime. Generally in the format MONTH YEAR.
    """
    VERSION = "7.0.0"
    DATE = "Jul 2020"

    def __init__( self ):
        """
        Constructor. No actions required.
        """
        pass