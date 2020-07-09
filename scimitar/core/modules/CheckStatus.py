from scimitar.core.modules.BaseModules import PreExecutionModule
from scimitar.core.RunConfiguration import str_to_bool

class CheckStatusModule( PreExecutionModule ):
    def __init__( self, RUN_CONFIG ):
        PreExecutionModule.__init__( self, "Generate Check Status Script", 20, RUN_CONFIG )

    def getScriptContribution( self ):
        contribution = ""
        if self.run.runSettings.cfg[ "generateCheckStatusScript" ]:
            contribution = "# ***** PreExecution: Generate Check Status Script *****\n"
            contribution += "scimitar.runtime.modules.CheckStatus.ModuleRuntime( RUN_LISTING, DIR_ORDER, RUN_CONFIG ).execute()\n\n"
        
        return contribution
