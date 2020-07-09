# Scimitar 7 Documentation

_Scimitar_  is a tool designed to assist a large parameter space exploration of numerical simulations in the physical sciences. This software is designed to work with custom numerical simulation packages which accepts a given set of input parameters to produce some output result. Generally, a large number of such input parameter combinations must be evaluated in order to fully analyze a model, and perhaps these combinations are conceived in non-trivial ways. Scimitar automates the process of configuring, organizing, executing, and monitoring a large number of runs on a single machine or across a large computing cluster. In the broadest sense, Scimitar takes an "embarassingly parallel" approach by using an allocated set of computing resources and simultaneously executing many instances of a simulation at once. In practice, Scimitar's goal is to automatically generate a Python script which will easily execute an instance of a program for each combination of selected parameters in an organized fashion, which simplifies data reduction and post-processing.

The parameter space which will be explored is configured using a simple scripting language which expresses the number of parameters, their data, and how a parameter should be iterated over. Parameters may be expressed in terms of a constant, a list, a range, or a function. This small script is passed to a "compiler" which produces an equivalent Python script which may be executed on the target machine to invoke the job.

# Installation
This version of Scimitar consists of multiple components:

1. the compiler driver module (written in C++) which handles interpretation of the script,
2. the Python package which produces the resulting Python script based on results provided by the compiler,
3. and the Python runtime, which executes a job script on a target machine.

## Dependencies
Running a binary release of Scimitar requires the following:

- Python 3.5+ distribution,
- The 'colorama' Python library,

In addition, compiling Scimitar from source requires the following dependencies:

- ANTLR 4 development library for the C++ target,
- pybind11 development library,
- Boost C++ library,
- Python 3.5+ C++ header files,
- a C++11 compatible compiler (tested on the GNU compiler).

## Installing the Python module
The directory to place the ``scimitar`` module can be confirmed by running ``python3 -m site --user-site``, but should be located on a Linux distribution at

    /home/<user>/.local/lib/python3.x/site-packages

where the appropriate substitutions for the user name and Python version are made. Copy the compiled Scimitar dynamic library ``libscimitar.so`` to the ``scimitar/core`` directory. 

# Scripting Language

It is important to recognize that the Scimitar "scripting" language is not any sort of general-purpose programming language. This language is designed to succinctly express a parameter space and relevant execution options, and not perform any complex operations. However, Scimitar does support more powerful features, such as user-defined functions and the ``run`` loop, to enable you to define a complex parameter space. As much logic as possible should be incorporated into the executing simulation, while still allowing for flexibility.

The language is comprised of a series of different statements which perform different actions on the internal state of the compiler. These actions include defining parameters, constructing groups of parameters, and setting execution options. Most statements also support additional elements to perform additional configuration, such as setting formats and directory orders. At the end of the script, the compiler takes the gathered information and generates a listing of all runs to be executed. The compiler emits valid Python code which contains this listing and configured options, and is included within the Python script to be executed on the target machine.

## Language Statements

### ``param`` Statement

The ``param`` statement defines a new parameter, its data type, value, and associated options.

    param <type> <identifier> <value> { [<option>=<opt-value>...] [hide] }
    
| Token | Description |
| ----- | ----------- |
| ``<type>`` | The data type of the parameter. One of ``int``, ``real``, ``string``, or ``function``. See data types.
| ``<identifier>`` | The parameter name. Cannot start with a number, be a reserved keyword, or contain special characters.
| ``<value>``| The value of the parameter. May be an arithmetic expression, a list, or a range. If ``function`` is specified, the expression may be a single-valued function of other parameters. See value specifiers and functions.
| ``<option>=`` | Sets a related parameter option. One or more of ``dir=`` or ``format=``.
| ``hide`` | Sets the parameter to hidden. The parameter will not be written out to the script, but may be used as a function argument. Useful for performing intermediate calculations. This option must be specified when the parameter declared.

#### Examples:

Define a ``int`` parameter named ``x`` which takes the value ``5`` and assumes the default format:

    param int x 5;

Define a ``real`` parameter named ``alpha`` which takes the value ``137.036``, is explicitly formatted to three decimal places, and appears first in the generated directory structure:

    param real alpha 137.036 {format=%.3f dir=1};

### ``group`` Statement

    group <identifier-1> <identifier-2> [<identifier-3>...]

The ``group`` statement groups one or more parameters of identical length together such that they appear in 'lock step' with one another. For instance, if the parameter ``x`` takes the values ``[1, 2, 3]`` and ``y`` takes on ``[7, 8, 9]``, where the ``group x y`` statement is executed, the following three runs would be generated:

    RUN_LISTING = [ { "x" : "1", "y" : "7" }, { "x" : "2", "y" : "8" }, { "x" : "3", "y" : "9" } ]

Where the ``group`` statement is omitted, nine runs would be generated by the parameters ``x`` and ``y``.

### ``set option`` Statement

    set option <option1>=<value1> [<option2>=<value2>...]

The ``set option`` statement sets script-related options from their defaults or previously set values. The available options are listed below, and in the Resource Managers section.

| Option | Default | Description |
| ------ | ------- | ----------- |
| scriptFilename | myscript.py | The filename of the compiled script to output.|
| scriptLocation | ./ | The directory to place the compiled script in. The default is the current working directory. |
| executable | a.out | The path of the executable to run when executing the script. |
| inputFilename | parameters.in | The filename of the input parameter listing which will be accepted by the executed program. |
| outputFilename | logfile.out | The filename of the output log file which contains text written to STDOUT and STDERR during program execution. |
| arguments | | Command line arguments to apply to the executable when called.
| disableInputRedirection | False | By default, a '<' is inserted between the executable and Scimitar input file (e.g., the Scimitar input is directed as command line input). If set to True, this character is not included.|
| generateCheckStatusScript | True | If true, the ``checkstat.py`` script will be generated upon execution of the resulting script.|
| numberOfSplitScripts | 1 | Provides the ability to split the set of generated runs among multiple scripts, such that each script may independently be executed across multiple machines. |

### ``system`` Statement
    
    system <option1>=<value1> [<option2>=<value2>...]

The ``system`` statement sets compiler-level options. These options usually do not directly affect the behavior of the resulting Python script. The available options are listed below.

| Option | Description |
| ------ | ----------- |
| seed | Sets the seed of the internal random number generator used for randomly-generated parameters. |
| recursion_limit | Sets the number of times any user-defined function may be called for the evaluation of a run. This limit prevents the compiler from entering an accidental infinite loop. Default value is 2000. |

### Comments
Comments begin with ``//`` and comment any text until a new line is reached. Block comments, which may span multiple lines, begin with ``/*`` and end with ``*/``.

### Additional Statements
The following statements exist for testing of the compiler, and should generally be avoided in production use.

#### ``ungroup`` Statement

    ungroup <identifier-1> [<identifier-2>...]

#### ``set param`` Statement

    set param <identifier> { <option>=<value>... }

The ``set param`` statement updates options for a parameter which has been previously defined. Generally this statement should be avoided; parameter options should be addressed when first declared.

| Token | Description |
| ----- | ----------- |
| ``<identifier>`` | The identifier of a previously-defined parameter.
| ``<option>=`` | Sets an related option. One of ``dir=``, ``format=``, ``value=``, or ``function=``.

## Data Types and Values
Scimitar supports the following data types:

| Identifier |  Description |
|---|---|
| ``int`` | Long integer
| ``real``| Double-precision floating point value
| ``string`` | String
| ``function`` | A function of zero or more previously defined parameters

### Lists
A parameter may be defined to take multiple values by providing a list in the format ``[x1, x2, x3,...]``. All elements of a list must be of the same data type. Elements of a list may contain functions of numeric literals, which will be evaluated at compile time.

### Ranges
A parameter may also be defined in terms of a range consisting of an upper and lower limit, and a finite step size using the syntax

    <lower-limit>:<step-size>:<upper-limit>

Ranges are inclusive of the lower limit, and exclusive of the upper limit. For instance, ``1:2:10`` is equivalent to ``[1,3,5,7,9]``. Ranges also work with floating point values (e.g., ``[1:0.1:2]``). Ranges may also be included as an element as a list, for instance, ``[1,2,7:3:15]``, which will expand to ``[1,2,7,10,13]``. Arguments of ranges may contain functions of numeric literals, which will be evaluated at compile time.

### Function Parameters

Function parameters set the value of a parameter in terms of the evaluation of other parameters. Functions may call user-defined functions or supported intrinsic functions. User-defined functions may accept conditional expressions for boolean arguments; see the "Run Loop Statements" section for details. Note that calculations are always performed using double-precision arithemtic; the appearance of the result may be set using formats. 

For instance, to define a parameter ``y`` which is the square of another hidden parameter ``x`` which ranges from 1 to 5, we may write

    param int x 1:1:5 {hide};
    param function y x**2 {dir=1};


Supported operators within functions:
| Operator | Description |
|---|-----| 
| ``+`` | addition |
| ``-`` | subtraction |
| ``*`` | multiplication |
| ``\`` | division |
| ``**`` | exponent |
| ``%`` | modulus |

Supported functions:
|  Function | Description  |
| ---- | ---- |
| ``sqrt(x)`` | square root |
| ``log(x)`` | natural logarithm |
| ``sin(x)`` | sine|
| ``cos(x)`` | cosine |
| ``tan(x)`` | tangent |
| ``abs(x)`` | absolute value |
| ``rand(low, high)`` | Randomly-generated value from a uniform distribution of integers ranging from ``low`` to ``high``.|
| ``uniform(low, high)`` | Randomly-generated value from a uniform, real-valued continuous distribution ranging from ``low`` to ``high``. |
| ``normal(mu, std)`` | Randomly-generated value from a Gaussian real-valued distribution with mean ``mu`` and standard deviation ``std``. |

## Run Loop Statements

_Run loop statements_ allows for a finer-grained control over how a parameter space is constructed. A run loop executes a series of defined statements on each run produced by the compiler. These statements may modify a parameter's value based on the value of other parameters, or remove the run entirely from the set of runs based on given conditions. A run loop is indicated by the keyword ``run``, and statements which will be executed are enclosed in curly brackets `{`...`}`.

### Conditional Statements

Supported boolean and relational operators:
| Operator  |  Description  |
| ----- | ----- |
| ``and`` | Boolean 'and' operation |
| ``or`` | Boolean 'or' operation |
| ``eq`` | Boolean equality operation |
| ``not`` | Boolean negation operation |
| ``>`` | 'Greater than' comparison |
| ``<`` | 'Less than' comparison |
| ``>=`` | 'Greater than or equal' comparison |
| ``<=`` | 'Less than or equal' comparision |
| ``==`` | Equality comparison |
| ``!=`` | 'Not equal' comparison | 

### Assignment Statement

An assignment statement assigns a new value to a parameter, and takes the form ``<identifier> = expr``, where ``expr`` takes any valid arithmetic expression. Assignment statements may appear within a conditional statement block.

### ``remove`` Statement

The remove statement deletes a run from the set of runs to be executed, and is generally within a conditional block such that a run is removed is certain critera or met. As an example, to remove all runs where ``alpha * beta > 1``, the following run loop may be used:

    run {
        if ( alpha * beta > 1 ) {
            remove;
        }
    }

## User-Defined Functions

Scimitar supports the ability to define new functions which may be called in the definition of a ``function`` parameter or within a ``run`` loop. Functions always return a ``real`` (double-precision float) value and may accept ``int``, ``real``, or ``bool`` parameter types as arguments. The syntax to define a function is

    def <identifier>( <type> <arg1>, <type> <arg2>,...) {
        <statements>
    }

Identifiers may not match a reserved keyword or the name of an intrinsic function. Valid statements within a function include assignments and conditionals in the same way they are supported within ``run`` loops, except
new variables within the scope of a function must be declared with a type:

    <type> <identifier> [= <initial-value>];

Notice that a variable may optionally be initialized at the same time as declaration. Return statements are additionally supported by calling ``return <expr>``, where the expression is an arithmetic expression which will be evaluated to a floating-point value by the compiler. A value should always be explicitly retured, otherwise ``0.0`` is returned by default.

### Loops

For loops are also supported using the following syntax:

    for ( <type> <identifier> = <initial-value>, <conditional>, <step> ) {
        <statements>
    }

**Example:** Loop over an integer value `i` from `i = 0` to `i = 10` with an increment of 1 each iteration.

    for ( int i = 0, i < 10, 1 ) { 
        // additional code here
    }

Within a for loop, the type of the loop variable may be ``int`` or ``real``, and the matching identifier will only be in scope within the loop. The conditional determines the termination condition of the loop; the first time the condition evaluates to false, the loop will end. The step is an arithmetic expression which will evaluate to the same type as the loop variable, and the value will be added to the loop variable at the end of each loop. The ``continue`` and ``break`` statements are supported within the loop, where ``continue`` skips ahead to the next iteration, and ``break`` terminates the loop.

In a similar manner, ``while`` loops are also supported:

    while ( <condition> ) {
        <statements>
    }

### Lists

User-defined functions also support a primitive form of lists, or arrays. Lists may contain elements of different types, including reals, ints, and other lists. Lists may be declared using the ``list`` keyword, but may not be initialized upon declaration (elements must be added using the ``append`` statement). 

Elements may be accessed using square brackets, where elements are zero-indexed. For example, to access the second element of a list ``x``, write ``x[1]``. Element access may appear in any arithmetic or conditional expression within scope.

New elements may be added to the end of a list using the ``append`` statement:

    <list-identifier> : append <type>( <expression> );

Note that since elements of multiple types may be added to the same list, the type of the element must be specified in this statement. For instance, to add an integer to the list ``x``, write ``x : append int(5);``.

To remove an element at a specified index, use the ``remove`` statement:

    <list-identifier> : remove <index>

where ``<index>`` may be any expression which evaluates to an integer.

# Resource Managers

_Resource managers_ define how a job is executed on the target machine, and is a part of the Python runtime. For instance, a resource manager may be defined to execute a series of jobs sequentially on a single machine, or submit a batch of jobs to a cluster job schedulder on PBS. At present, Scimitar only supports executing jobs on a single machine, but is developed in a manner to extend functionality to other execution methods if demanded.

## Single Machine

The _single machine resource manager_ executes a series of jobs in a straightforward manner on a single instance of a machine.

| Option | Default | Description |
| ------ | ------- | ----------- |
| single.numSimultaneousRuns | 62 | The number of runs which will be executed simultanelously on the target machine. The script will wait for one or more of these instances to complete before starting additional runs. |
| single.processCheckWaitTime | 5 | The resulting script will wait this number of seconds before checking if any runs have completed since the last check. |
| single.preExecutionCommands | none | A series of commands which will be executed in a bash shell before calling the main executable. |
| single.postExecutionCommands | none | A series of commands which will be executed in a bash shell after calling the main executable and its execution completes. |

# Executing the Compiler

The Scimitar compiler may be invoked by executing the provided ``main.py`` script; for instance, to compile the Scimitar script ``script.sci``, run

    python3 main.py script.sci

In practice, however, a distribution of the Scimitar compiler should provide a symbolic link to a shell executable form of this script such that a Scimitar script may be compiled with

    scimitar script.sci

A description of command-line options may be produced by using the ``-h`` switch. Additional switches will perform the following tasks:

| Switch | Description |
| ------ | ----------- |
| -v, --version | Prints version and copyright information. |
| -r, --report | Compiles the source file and produces information about the script, including the number of jobs to be executed, without writing an actual execution script.

## Interactive Compiler

A second compiler program ``scic`` is provided which produces the result of the core compiler driver library from either
a passed source file or line-by-line entry into an interactive prompt. This result includes a listing of all simulation
runs to be executed, the directory order, and any options to configure the execution runtime. This output is valid
Python code which is included in the beginning of every script produced by the standard compiler. However, this
second compiler is provided only for testing purposes or for cases where the compiler driver output is used further in
a user-defined process.

# Executing the Generated Script
The output of the compiler is a Python file which should be executed on the machine intended to run the batch of simulations. The script should generally be placed in an empty directory, and then executed as usual. The script with then perform the following steps by default (which may be modified through various options):

- create the hierarchical directory structure to hold each invocation of the simulation in a unique directory,
- generate parameter input files,
- produce a script which can be used to check the status of executed runs,
- invoke all simulations in order and according to configured options.