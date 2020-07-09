class ModuleTypes:
    GeneralModule, ResourceManager, PreExecutionModule, PostExecutionModule = range( 4 )


class ScimitarModule:
    """
    Base class for a module.
    """
    def __init__( self, name, moduleType, priority, run ):
        self.moduleName = name
        self.moduleType = moduleType
        self.priority = priority
        self.run = run

    def getScriptContribution( self ):
        return "print( \"Script contribution not implemented for module '" + self.name + "'!\" )"

class ResourceManagerModule( ScimitarModule ):
    """
    Base class for a resource manager module.
    """
    def __init__( self, name, run ):
        ScimitarModule.__init__( self, name, ModuleTypes.ResourceManager, 0, run )

    def getScriptContribution( self ):
        return "print( \"Script contribution not implemented for ResourceManger module '" \
               + self.name + "'!\" )"


class PreExecutionModule( ScimitarModule ):
    """
    Base class for a pre-execution module.
    """
    def __init__( self, name, priority, run ):
        ScimitarModule.__init__( self, name, ModuleTypes.PreExecutionModule, priority, run )

    def getScriptContribution( self ):
        return "print( \"Script contribution not implemented for PreExecution module '" \
               + self.name + "'!\" )"


class PostExecutionModule( ScimitarModule ):
    """
    Base class for a post-execution module.
    """
    def __init__( self, name, priority ):
        ScimitarModule.__init__( self, name, ModuleTypes.PostExecutionModule, priority )

    def getScriptContribution( self ):
        return "print( \"Script contribution not implemented for PostExecution module '" \
               + self.name + "'!\" )"