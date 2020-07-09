from scimitar.core.modules.BaseModules import PreExecutionModule

class HeaderModule( PreExecutionModule ):
    def __init__( self, run ):
        PreExecutionModule.__init__( self, "Header Module", 1, run )

    def getScriptContribution( self ):
        contribution = "# ***** PreExecution: Print Log Header *****\n"
        contribution += "scimitar.runtime.modules.HeaderModule.ModuleRuntime( RUN_LISTING, DIR_ORDER, RUN_CONFIG ).execute()\n\n"
        return contribution