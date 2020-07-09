from scimitar.core.modules.BaseModules import ResourceManagerModule

class SingleMachineModule( ResourceManagerModule ):
    def __init__( self, RUN_CONFIG ):
        ResourceManagerModule.__init__( self, "Single Machine Resource Manager", RUN_CONFIG )

    def getScriptContribution( self ):
        contribution = "# ***** ResourceManager: Single Machine*****\n"
        contribution += "scimitar.runtime.modules.ResourceManager.SingleMachineRuntime( RUN_LISTING, DIR_ORDER, RUN_CONFIG ).execute()\n\n"
        return contribution
