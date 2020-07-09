import os
import subprocess
from datetime import datetime
from time import sleep
import scimitar


def _constructRunPath( run, dir ):
    path = "/"
    for param in dir:
        path += param + '_' + run.get_value( param ) + '/'

    return path


class SingleMachineRuntime:
    def __init__( self, RUN_LISTING, DIR_ORDER, RUN_CONFIG ):
        self.RUN_LISTING = RUN_LISTING
        self.DIR_ORDER = DIR_ORDER
        self.RUN_CONFIG = RUN_CONFIG
        self.JOB_COUNT = len( RUN_LISTING )

    def _ping_processes( self, initialWorkingDir, runningJobs, processDictionary ):
        for proc in runningJobs:
            if proc.poll() is not None:
                runningJobs.remove( proc )
                run = scimitar.runtime.Run( self.RUN_LISTING[ processDictionary[ proc.pid ] ] )
                run_path = _constructRunPath( run, self.DIR_ORDER )

                # Write out temporary file indicating run completion.
                f_temp = open( initialWorkingDir + '/exec' + run_path + '/job_completed.tmp', 'w' )
                f_temp.write(
                    'PID ' + str( proc.pid ) + ' / JOB ' + str( processDictionary[ proc.pid ] ) + ' / COMPLETED ' + str(
                        datetime.now() ) )
                f_temp.close()

        sleep( self.RUN_CONFIG["single.processCheckWaitTime"] )


    def execute( self ):
        if self.RUN_CONFIG["disableInputRedirection"]:
            inputRedirection = " "
        else:
            inputRedirection = " < "

        jobID = -1
        initialWorkingDir = os.getcwd()

        # Verify that the executable to be run can be found.
        if not os.path.isfile( self.RUN_CONFIG["executable"] ):
            print( '>> The executable \'' + str( self.RUN_CONFIG["executable"] + '\' cannot be found.' ) )
            raise SystemExit

        # Execute pre-execution commands if they are provided.
        if not self.RUN_CONFIG["single.preExecutionCommands"].strip() == "":
            print( '>> Executing additional pre-execution commands...' )

            for execLine in self.RUN_CONFIG["preExecutionCommands"].splitlines():
                proc = subprocess.Popen( execLine, shell=True )
                proc.wait()

        # Submit and run the jobs.
        print( '>> Submitting jobs (' + str( self.JOB_COUNT ) + ' total jobs)...' )
        processDictionary = dict()
        runningJobs = []
        for run_dict in self.RUN_LISTING:
            run = scimitar.runtime.Utility.Run( run_dict )
            run_path = _constructRunPath( run, self.DIR_ORDER )
            jobID += 1
            print ( '>>->> Submitting job {} of {} [{}]...'.format( jobID + 1, self.JOB_COUNT, run_path ) )
            os.chdir( initialWorkingDir + '/exec' + run_path )

            # If the job has already completed, skip the run.
            if not os.path.isfile( './job_completed.tmp' ):
                proc = subprocess.Popen( self.RUN_CONFIG["executable"] + " " + self.RUN_CONFIG["arguments"] + inputRedirection
                                         + self.RUN_CONFIG["inputFilename"] + " > "
                                         + self.RUN_CONFIG["outputFilename"], shell=True )
                runningJobs.append( proc )
                processDictionary[ proc.pid ] = jobID
            else:
                print( '>>->> Job {} of {} has already completed.'.format( jobID + 1, self.JOB_COUNT ) )

            # While we are running at the maximum number of jobs, keep checking for when other jobs finish so we can
            # launch another one.
            while len( runningJobs ) >= self.RUN_CONFIG["single.numSimultaneousRuns"]:
                self._ping_processes( initialWorkingDir, runningJobs, processDictionary )

        # After all jobs have been launched, wait for the last jobs to finish.
        while len( runningJobs ) > 0:
            self._ping_processes( initialWorkingDir, runningJobs, processDictionary )

        # Execute post-execution commands if they are provided.
        if not self.RUN_CONFIG["single.postExecutionCommands"].strip() == "":
            print( '>> Executing additional post-execution commands...' )

            for execLine in self.RUN_CONFIG["single.postExecutionCommands"].splitlines():
                proc = subprocess.Popen( execLine, shell=True )
                proc.wait()

        print( '>> Execution completed at ' + str( datetime.now() ) + '.' )




