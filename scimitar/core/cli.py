import colorama

color_err = colorama.Fore.RED + colorama.Style.BRIGHT

# Define helper functions.
def get_copyright():
    res = "Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut. See LICENSE.TXT provided with the source code " \
          "for licensing information."
    return res

def save_script( filename, script ):
    """
    Helper function to save a script to disk.
    :param filename: Filename of the script to write.
    :param script: Contents of the script as a string.
    :return: None.
    """
    try:
        f = open( filename, "w" )
        f.write( script )
        f.close()
    except IOError:
        print( color_err + "Failed to open script '" + filename + "' for writing." )
        exit( -1 )