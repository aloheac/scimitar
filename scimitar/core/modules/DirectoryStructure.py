from scimitar.core.modules.BaseModules import PreExecutionModule

class DirectoryStructureModule( PreExecutionModule ):
    def __init__( self, RUN_CONFIG ):
        PreExecutionModule.__init__( self, "Create Directory Structure", 20, RUN_CONFIG )

    def getScriptContribution( self ):
        contribution = "# ***** PreExecution: Create Directory Structure *****\n"
        contribution += "scimitar.runtime.modules.DirectoryStructure.ModuleRuntime( RUN_LISTING, DIR_ORDER, RUN_CONFIG ).execute()\n\n"
        return contribution

