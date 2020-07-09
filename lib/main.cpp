/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Main entry point implementation.
 *
 *    DESCRIPTION: This file implements the main entry point for the demonstration compiler frontend which is
 *                 intended for debugging purposes. This frontend may compile a source file as indicated through
 *                 command-line arguments, and also provides an interactive prompt.
 *
 *    CREATION DATE: December 13, 2019
 *
 *********************************************************************************************************************/


#include <iostream>
#include <string>
#include <unistd.h>
#include <boost/algorithm/string/trim.hpp>
#include <antlr4-runtime.h>
#include "frontend/SourceFileStream.h"
#include "engine/Engine.h"
#include "grammar/ScimitarLexer.h"
#include "grammar/ScimitarParser.h"
#include "grammar/ScimitarBaseVisitor.h"
#include "grammar/GrammarErrorHandler.h"

// Define global information.
static const std::string SCIMITAR_VERSION = "7.0.0";
static const std::string BUILD_TIMESTAMP = "built " __DATE__ " " __TIME__;
static const std::string COMPILER_VERSION = "gcc:" __VERSION__;
static const std::string PROMPT = ">>>";
static const std::string EOF_TOKEN = "end;";
static const std::string TERMINATE_TOKEN = "quit;";

using namespace std;

/**
 * Structure to indicate the status of passed command-line arguments.
 */
struct ArgFlags {
    bool interactive = true;  // Flag to indicate if we should enter interactive mode.
    bool verbose = false;     // Flag to indicate if verbose mode was requested.
    std::string filename;     // The passed source file name.
    bool failure = false;     // Flag to indicate if a caught exception occurred while parsing arguments.
    bool show_help = false;   // Flag to indicate if help and version information should be shown, then exit.
};

/**
 * Subroutine to process command-line arguments. This information is returned as a ArgFlags objects, with appropriate
 * fields populated.
 * @param argc Command-line argument count, as provided by main().
 * @param argv Command-line argument values, as provided by main().
 * @return Populated structure with information provided on the command line.
 */
ArgFlags process_args( int argc, char* argv[] ) {
    const char* ARG_DEF = "vh";  // String indicating valid command-line arguments in the format expected by getopt().
    ArgFlags flags;
    int c;

    while ( ( c = getopt( argc, argv, ARG_DEF ) ) != -1 ) {
        switch ( c ) {
            case 'v':  // Verbose mode.
                flags.verbose = true;
                break;
            case 'h':  // Show help and version information.
                flags.show_help = true;
                break;
            default:
                // Encountered an unknown argument.
                cout << "Unknown command-line argument '" << c << "'.";
                flags.failure = true;
                return flags;
        }
    }

    // There should only be one non-option argument - the filename to process. If it exists, take the last non-option
    // argument. If not, the flag to use interactive mode will remain set.
    for ( int index = optind; index < argc; index++ ) {
        flags.interactive =  false;
        flags.filename = string( argv[ index ] );
    }

    return flags;
}


/**
 * Subroutine to parse one or more language statements and execute those statements on the engine.
 * @param source Source text to parse. May contain zero, one, or more language statements.
 * @param engine The Engine object upon which to execute parsed statements.
 * @param flags Command-line argument flag information.
 * @return True if a parsing or compilation error occurred in the process of parsing and executing the provided
 *         statements, false if the execution was otherwise successful.
 */
bool parse( std::string source, Engine &engine, ArgFlags &flags ) {
    boost::algorithm::trim( source );
    antlr4::ANTLRInputStream input( source );
    ScimitarLexer lexer( &input );
    GrammarErrorHandler errorHandler;
    lexer.removeErrorListeners();
    lexer.addErrorListener( &errorHandler );

    bool errorEncountered = false;
    try {
        antlr4::CommonTokenStream tokens( &lexer );
        tokens.fill();

        ScimitarParser parser( &tokens );
        parser.removeErrorListeners();
        parser.addErrorListener( &errorHandler );

        ScimitarBaseVisitor eval;
        antlr4::tree::ParseTree* tree = parser.root();
        eval.visit( tree );
        std::vector< std::shared_ptr<EngineAction> > actions = eval.get_result();

        for ( auto action : actions ) {
            action->execute( &engine );
            if ( flags.verbose ) cout << engine.to_string() << endl;
        }

        // Check if an unrecognizable statement resulting in an empty parse tree was provided. If so, and we are in
        // interactive mode, print a warning message.
        if ( not source.empty() and actions.empty() and flags.interactive )
            cout << "Comment or unrecognized statement." << endl;

    } catch ( GrammarException e ) {
        errorEncountered = true;
        cout << "Parsing error: " << e.what() << endl;
    } catch ( EngineException e ) {
        errorEncountered = true;
        cout << "Compilation error: " << e.what() << endl;
    } catch ( ParameterValueException e ) {
        errorEncountered = true;
        cout << "Compilation error: " << e.what() << endl;
    }

    return errorEncountered;
}


/**
 * Subroutine to handle parsing in standard mode. In standard mode, a source file name has been provided on the
 * command line and we do not enter interactive mode.
 * @param flags Command-line argument information.
 */
void standard_mode( ArgFlags flags ) {
    if ( flags.verbose ) cout << "Source file: " << flags.filename << endl << endl;

    // Open the source file and get the text. Initialize the engine.
    SourceFileStream sfs( flags.filename );
    string source = sfs.get();
    Engine engine;

    // Parse the whole source file.
    bool errorEncountered = parse( source, engine, flags);

    cout << endl;

    // If a compilation error has not occurred, execute the engine and print the result.
    if ( not errorEncountered ) {
        ExecutionResult result;

        // Execute the engine.
        try {
            result = engine.execute();
        } catch ( EngineException e ) {
            errorEncountered = true;
            cout << "Engine error: " << e.what() << endl;
        } catch ( ParameterValueException e ) {
            errorEncountered = true;
            cout << "Engine error: " << e.what() << endl;
        }

        if ( not errorEncountered ) cout << result.emit() << endl;
    }
}


/**
 * Subroutine to handle parsing in interactive mode, where statements are entered at the command line and parsed
 * individually.
 * @param flags Command-line argument information.
 * @return 0 if the interactive session has proceeded normally, -1 if the user has requsted early termination.
 */
int interactive_mode( ArgFlags flags ) {
    const string HEADER = "Scimitar Interactive Parser" ;

    cout << HEADER << " [" << SCIMITAR_VERSION << " " << BUILD_TIMESTAMP << " " << COMPILER_VERSION << "]" << endl;

    std::string line;
    Engine engine;

    while ( true ) {
        // Display prompt and receive next line.
        cout << PROMPT << " ";
        getline( cin, line );
        boost::algorithm::trim( line );

        if ( line == EOF_TOKEN ) break;
        if ( line == TERMINATE_TOKEN ) return -1;

        parse( line, engine, flags );  // We can safely ignore the return result here.
    }

    cout << endl;

    ExecutionResult result;
    bool errorEncountered = false;

    // Execute the engine.
    try {
        result = engine.execute();
    } catch ( EngineException e ) {
        errorEncountered = true;
        cout << "Engine error: " << e.what() << endl;
    } catch ( ParameterValueException e ) {
        errorEncountered = true;
        cout << "Engine error: " << e.what() << endl;
    }

    if ( not errorEncountered ) cout << result.emit() << endl;

    return 0;
}


void print_help() {
    cout << "Scimitar Compiler" << " [" << SCIMITAR_VERSION << " " << BUILD_TIMESTAMP << " " << COMPILER_VERSION << "]"
         << endl;
    cout << "Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al." << endl << endl;
    cout << "Usage: scic [-h] [-v] [filename]" << endl;
    cout << "  -h         print this help message and version information" << endl;
    cout << "  -v         enable verbose mode" << endl;
    cout << "  filename   source file to compile. If omitted, interactive mode will be started" << endl;
}

/**
 * Main entry point.
 * @param argc Command-line argument count.
 * @param argv Command-line argument values.
 * @return 0 if compilation has executed, -1 if command-line arguments failed to be parsed.
 */
int main( int argc, char* argv[] ) {
    ArgFlags flags = process_args( argc, argv );
    if ( flags.failure ) return -1;

    if ( flags.show_help ) {
        print_help();
        return 0;
    } else if ( flags.interactive ) {
        int status = interactive_mode( flags );
        if ( status == -1 ) cout << "Termination requested." << endl;
    } else {
        standard_mode( flags );
    }

    return 0;
}
