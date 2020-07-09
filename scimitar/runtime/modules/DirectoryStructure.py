import os
import scimitar.runtime.Utility

def _createRunInputFile( run ):
    inputFile = ""

    for param in run.get_pairs():
        inputFile += param[ 1 ] + "\t# " + param[ 0 ] + "\n"

    return inputFile


class ModuleRuntime:

    def __init__( self, RUN_LISTING, DIR_ORDER, RUN_CONFIG ):
        self.RUN_LISTING = RUN_LISTING
        self.DIR_ORDER = DIR_ORDER
        self.RUN_CONFIG = RUN_CONFIG

    def execute( self ):
        initWorkingDir = os.getcwd()
        okayToCreateDirectoryStructure = True

        # Check if the execution directory structure already exists. If is does, show a
        # warning to the user and let them decide if they should continue.
        if os.path.isdir( initWorkingDir + '/exec' ):
            print( '>> WARNING: It appears that an execution directory structure already exists,' )
            print( '            and will not be recreated unless it is first removed. This script' )
            print( '            may overwrite existing data. If you are restarting a run after it' )
            print( '            aborted, please continue.' )

            while True:
                userResponse = input( 'Do you want to continue running the script? (y/n): ' )
                if userResponse == 'y':
                    okayToCreateDirectoryStructure = False
                    print( '>> Continuing the script with the existing directory structure.' )
                    break
                elif userResponse == 'n':
                    print( '>> Terminating the script at the user\'s request.' )
                    raise SystemExit

        if okayToCreateDirectoryStructure:
            print( '>> Initializing directory structure...' )

            for run_dict in self.RUN_LISTING:
                path = "/exec/"
                run = scimitar.runtime.Utility.Run( run_dict )

                # Construct subdirectory path.
                for directory in self.DIR_ORDER:
                    path += directory + '_' + run.get_value( directory ) + '/'

                # Create subdirectories.
                os.makedirs( initWorkingDir + path, exist_ok=True )  # exist_ok argument must be set so an exception
                                                                     # is not thrown when children of a parent
                                                                     # directory are created.

                # Create parameter input file.
                os.chdir( initWorkingDir + path )
                inputFile = open( initWorkingDir + path + self.RUN_CONFIG["inputFilename"], 'w' )
                inputFile.write( _createRunInputFile( run ) )
                inputFile.close()

            os.chdir( initWorkingDir )
