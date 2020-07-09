from math import ceil
from scimitar import core
import scimitar.core.modules
import scimitar.core.libscimitar
from scimitar.runtime.Utility import RuntimeVersion
from ast import literal_eval
from datetime import datetime

DEFAULT_SCRIPT_FILENAME = "myscript.py"
DEFAULT_SCRIPT_LOCATION = "./"
DEFAULT_EXECUTABLE = "a.out"
DEFAULT_INPUT_FILENAME = "parameters.in"
DEFAULT_OUTPUT_FILENAME = "logfile.out"
DEFAULT_ARGUMENTS = ""

class ScimitarRunError( Exception ):
    """
    Generic Scimitar run exception.
    """
    def __init__( self, value ):
        self.value = value

    def __str__( self ):
        return repr( self.value )


class RunSettings:
    bool_types = ["disableInputRedirection", "generateCheckStatusScript"]
    int_types = ["numberOfSplitScripts", "single.numSimultaneousRuns", "single.processCheckWaitTime"]

    """
    Struct that contains various basic configuration settings for the run.
    """
    def __init__( self ):
        self.cfg = dict()

        self.cfg["scriptFilename"] = str( DEFAULT_SCRIPT_FILENAME )
        self.cfg["scriptLocation"] = str( DEFAULT_SCRIPT_LOCATION )
        self.cfg["executable"] = str( DEFAULT_EXECUTABLE )
        self.cfg["inputFilename"] = str( DEFAULT_INPUT_FILENAME )
        self.cfg["outputFilename"] = str( DEFAULT_OUTPUT_FILENAME )
        self.cfg["arguments"] = str( DEFAULT_ARGUMENTS )
        self.cfg["disableInputRedirection"] = False
        self.cfg["generateCheckStatusScript"] = True
        self.cfg["numberOfSplitScripts"] = 1

        self.cfg["single.numSimultaneousRuns"] = 62
        self.cfg["single.processCheckWaitTime"] = 5
        self.cfg["single.preExecutionCommands"] = ""
        self.cfg["single.postExecutionCommands"] = ""

class AvailableModules:
    """
    Struct containing instantiations of all available modules.
    """

    # Available so settings of each module can be maintained and written to file. These
    # modules should be activated in order to include them in the script.
    def __init__( self, run ):
        self.CreateDirectoryStructure = scimitar.core.modules.DirectoryStructureModule( run )
        self.HeaderModule = scimitar.core.modules.HeaderModule( run )
        self.SingleMachineResourceManager = scimitar.core.modules.SingleMachineModule( run )
        self.CheckStatus = scimitar.core.modules.CheckStatusModule( run )


def _sortModuleList( moduleList ):
    # Yes, this is bubble sort. No, I didn't feel like being smart. These lists will be very short.
    for i in range( 0, len( moduleList ) ):
        for j in range( len( moduleList ) - 1, i, -1 ):
            if moduleList[ j ].priority < moduleList[ j - 1 ].priority:
                moduleList[ j ], moduleList[ j - 1 ] = moduleList[ j - 1 ], moduleList[ j ]

def str_to_bool( value ):
    if value.strip() in [ "true", "True", "1" ]:
        return True
    elif value.strip() in [ "false", "False", "0" ]:
        return False
    else:
        raise ScimitarRunError( "Unknown token '" + str( value ) + "' expected to be a boolean value." )


class RunConfiguration:

    def __init__( self, RUN_CODE ):
        self.name = "DefaultRun"
        self.runSettings = RunSettings()
        self.availableModules = AvailableModules( self )
        self.runNotes = ""
        self.RUN_CODE = RUN_CODE

        # Active Scimitar modules.
        self.activeResourceManager = "NO_RESOURCE_MANAGER"
        self.activePreExecutionModules = [ ]
        self.activePostExecutionModules = [ ]

        # By default, set the active resource manager to be SingleMachine.
        self.activeResourceManager = self.availableModules.SingleMachineResourceManager

        # By default, activate all of the very important modules.
        self.activateModule( self.availableModules.HeaderModule )
        self.activateModule( self.availableModules.CreateDirectoryStructure )
        self.activateModule( self.availableModules.CheckStatus )


    def activateModule( self, module ):
        """
        Activate a module.
        :param module:
        :return:
        """
        if module.moduleType == scimitar.core.modules.ModuleTypes.ResourceManager:
            self.activeResourceManager = module
        elif module.moduleType == scimitar.core.modules.ModuleTypes.PreExecutionModule:
            self.activePreExecutionModules.append( module )
        elif module.moduleType == scimitar.core.modules.ModuleTypes.PostExecutionModule:
            self.activePostExecutionModules.append( module )
        else:
            raise ScimitarRunError( "Module '" + module.name + "' does not have a valid type." )


    def deactivateModule( self, module ):
        """
        Deactivate a module. The object will still remain in AvailableModules.
        :param module:
        :return:
        """
        if module.moduleType == scimitar.core.modules.ModuleTypes.ResourceManager:
            # Note that here we assume that we want the resource manager removed no matter
            # what (even if the passed resource manager does match the current one).
            self.activeResourceManager = "NO_RESOURCE_MANAGER"
        elif module.moduleType == scimitar.core.modules.ModuleTypes.PreExecutionModule:
            for i in range( 0, len( self.activePreExecutionModules ) ):
                if module == self.activePreExecutionModules[ i ]:
                    del self.activePreExecutionModules[ i ]
                    return
            raise ScimitarRunError( "Provided module is not active." )
        elif module.moduleType == scimitar.core.modules.ModuleTypes.PostExecutionModule:
            for i in range( 0, len( self.activePostExecutionModules ) ):
                if module == self.activePostExecutionModules[ i ]:
                    del self.activePostExecutionModules[ i ]
                    return
            raise ScimitarRunError( "Provided module is not active." )
        else:
            raise ScimitarRunError( "Module '" + module.name + "' does not have a valid type." )

    def isModuleActive( self, module ):
        if module in self.activePreExecutionModules:
            return True
        elif module in self.activePostExecutionModules:
            return True
        elif module == self.activeResourceManager:
            return True
        else:
            return False

    def getReportCard( self ):
        reportCard = "All grid checks passed!\n"
        reportCard += "Total number of runs: " + str( self.species.getRunCount() ) + "\n"
        return reportCard


    def getRunListing( self ):
        pass

    def generateScript( self, report=False ):
        """
        Generate the script for this run.
        :return:
        """

        # Initialize variables which will be produced by the compilation.
        STATUS = None
        RUN_LISTING = None
        DIR_ORDER = None
        ERROR_MSG = None

        # Compile and execute the result.
        C_RES = core.libscimitar.compile( self.RUN_CODE )
        for line in C_RES.split( "\n" ):
            identifier, value = line.split( "=" )
            identifier = identifier.strip()
            value = value.strip()

            if identifier == "STATUS":
                STATUS = literal_eval( value )
            elif identifier == "RUN_LISTING":
                RUN_LISTING = literal_eval( value )
            elif identifier == "DIR_ORDER":
                DIR_ORDER = literal_eval( value )
            elif identifier == "ERROR_MSG":
                ERROR_MSG = literal_eval( value )
            elif identifier == "OPTION":
                OPTION = literal_eval( value )
            else:
                raise ScimitarRunError( "Unknown identifier provided by compiler." )

        # Check if the result code indicates compilation failed.
        if STATUS != 0:
            return STATUS, ERROR_MSG

        # Check if only a report is requested; if so, generate the report.
        if report:
            noun = "jobs"
            if len( RUN_LISTING ) == 1: noun = "job"
            result = 0, "{} ".format( len( RUN_LISTING ) ) + noun + " requested."
            return result

        # Apply updated options.
        for opt in OPTION:
            try:
                self.option( opt, OPTION[ opt ] )
            except KeyError:
                raise ScimitarRunError( "Unknown option '" + str( opt ) + "'." )

        # Split runs into groups by the number of requested scripts.
        numRunsPerScript = ceil( len( RUN_LISTING ) / self.runSettings.cfg["numberOfSplitScripts"] )
        groups = []
        run = 0
        while run < len( RUN_LISTING ):
            if run + numRunsPerScript > len( RUN_LISTING ):
                groups.append( [ RUN_LISTING[ run: ] ] )
                break
            else:
                groups.append( [ RUN_LISTING[ run:( run + numRunsPerScript ) ] ] )
                run += numRunsPerScript

        scripts = []
        for group in groups:
            script = ""  # Start with an empty script.

            # Add comment indicating when the script was generated.
            script += "#  Script generated by the Scimitar compiler (version " + RuntimeVersion.VERSION + \
                      " [" + RuntimeVersion.DATE + "]) on " + str( datetime.now() ) + ".\n\n"

            # Copy the run listing and directory order into the top of the script as global variables. Individual
            # modules should reference these variables directly.
            script += "RUN_LISTING = " + str( RUN_LISTING ) + "\n"
            script += "DIR_ORDER = " + str( DIR_ORDER ) + "\n"
            script += "RUN_CONFIG = " + str( self.runSettings.cfg ) + "\n\n"

            # Add required imports to script.
            script += "import scimitar\n"

            # Load the pre-execution module.
            for module in self.activePreExecutionModules:
                script += module.getScriptContribution()

            # Load the execution module.
            if self.activeResourceManager == "NO_RESOURCE_MANAGER":
                raise ScimitarRunError( "There does not seem to be a valid resource manager loaded!" )

            script += self.activeResourceManager.getScriptContribution()

            # Load the post-execution module.
            for module in self.activePostExecutionModules:
                script += module.getScriptContribution()

            script += "\nprint('>> Scimitar submission script complete.')\n"

            scripts.append( script )

        return STATUS, scripts


    def option( self, option, value ):
        try:

            if option.strip() in RunSettings.int_types:
                try:
                    self.runSettings.cfg[ option.strip() ] = int( value )
                except ValueError:
                    raise ScimitarRunError( "Failed to parse option '" + str( option.strip() ) + "' as an integer." )
            elif option.strip() in RunSettings.bool_types:
                self.runSettings.cfg[ option.strip() ] = str_to_bool( value )
            else:
                self.runSettings.cfg[ option.strip() ] = value

        except KeyError:
            raise ScimitarRunError( "Unknown option '" + str( option.strip() ) + "'." )

