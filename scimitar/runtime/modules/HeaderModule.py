from datetime import datetime
from scimitar.runtime.Utility import RuntimeVersion

class ModuleRuntime:

    def __init__( self, RUN_LISTING, DIR_ORDER, RUN_CONFIG ):
        self.RUN_LISTING = RUN_LISTING
        self.DIR_ORDER = DIR_ORDER
        self.RUN_CONFIG = RUN_CONFIG

    def execute( self ):
        print( '***************************************' )
        print( '* Scimitar Execution Script' )
        print( '* Version ' + RuntimeVersion.VERSION + ' (' + RuntimeVersion.DATE + ')' )
        print( '***************************************' )
        print( 'Started ' + str( datetime.now() ) )
