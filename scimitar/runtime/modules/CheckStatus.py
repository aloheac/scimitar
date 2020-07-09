def construct_run( job, dir ):
    run = ""
    for param in dir:
        run += str(param) + "_" + job[param] + "/"

    return run

class ModuleRuntime:

    def __init__( self, RUN_LISTING, DIR_ORDER, RUN_CONFIG ):
        self.RUN_LISTING = RUN_LISTING
        self.DIR_ORDER = DIR_ORDER
        self.RUN_CONFIG = RUN_CONFIG

        self.script_filename = "checkstat.py"
        self.num_lines = 5

    def execute( self ):
        script = open( self.script_filename, 'w' )
        script.write( "from subprocess import Popen, PIPE\n" )
        script.write( "import sys\n")
        script.write( "import time\n")
        script.write( "from os.path import isfile\n" )
        script.write( "import scimitar.runtime.modules\n\n" )
        script.write( "RUN_LISTING = " + str( self.RUN_LISTING ) + "\n" )
        script.write( "DIR_ORDER = " + str( self.DIR_ORDER ) + "\n" )
        script.write( "NUM_LINES = " + str( self.num_lines ) + "\n" )
        script.write( "jobID = 0\n" )
        script.write( "numRunningJobs = 0\n" )
        script.write( "for job in RUN_LISTING:\n" )
        script.write( "    jobPath = scimitar.runtime.modules.CheckStatus.construct_run( job, DIR_ORDER )\n")
        script.write( "    print(\">> (\" + str( jobID ) + \") \" + jobPath )\n")
        script.write( "    if isfile( \"./exec/\" + jobPath + \"/" + str( self.RUN_CONFIG["outputFilename"] ) + "\"):\n" )
        script.write( "        proc = Popen([\"tail\", \"-n \" + str( NUM_LINES ), \"./exec/\" + jobPath + \"/" + str( self.RUN_CONFIG["outputFilename"] ) + "\"], stdout=PIPE, universal_newlines=True)\n" )
        script.write( "        ( output, err ) = proc.communicate()\n" )
        script.write( "        exit_stat = proc.wait()\n" )
        script.write( "        print( output )\n" )
        script.write( "        numRunningJobs +=1\n")
        script.write( "    else:\n" )
        script.write( "        print( \"Run has not yet started or the path is invalid.\" )\n" )
        script.write( "    jobID +=1\n" )
        script.write( "    print(\"-------------------------------------------------------\")\n" )
        script.write( "print(\">> \" + str(numRunningJobs) + \" of \" + str(jobID) + \" jobs have executed.\")\n" )
        script.close()