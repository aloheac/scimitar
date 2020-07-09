# Scimitar Readme
Scimitar is a small software application which provides a robust but simple
scripting language to define a highly-dimensional parameter space over which to
execute a numerical simulation. This tool automates the process of configuring,
organizing, executing, and monitoring a large number of simulation jobs on
compute resources. In practice, the Scimitar compiler generates a Python script
which will execute an instance of a program for each combination of selected
parameters in an organized fashion, which helps to simplify data reduction and
post-processing.

The scripting language used to define the parameter space to be explored and
configure available options provides functionality including:

- defining floating-point and integer parameters using lists, ranges, and
functions,
- assigning format specifiers to parameters to control conversions from
floating-point to strings, 
- support for random-number generation using uniform and normal
distributions,
- support for defining a variety of function objects which utilize loops,
conditionals, and array,
- defining parameter groupings which provide finer-grained control over the
parameter space.

## Documentation
Detailed documentation on the Scimitar scripting language and functionality is
provided in the "doc" directory.

## Building from Source
Scimitar is designed to compile using the CMake build system and is tested
using the GNU C++ compiler and Python 3.8. Note that running a binary release
of Scimitar requires the following:

- Python 3.5+ distribution,
- The 'colorama' Python library,

In addition, compiling Scimitar from source requires the following dependencies:

- ANTLR 4 development library for the C++ target,
- pybind11 development library,
- Boost C++ library,
- Python 3.5+ C++ header files,
- a C++11 compatible compiler.

After installing the appropriate libraries mentioned above, the header and
library paths must be updated in the ``CMakeLists.txt`` file. Compilation
may then be invoked as usual on ``CMakeLists.txt``.

## License
The source code for Scimitar is released under an open-source license. See LICENSE.txt included with this package for details.

## Disclaimer
Please note that this software is in **beta** and may contain bugs, may have incomplete documentation, or could use improvement. The content of this project is continually evolving. However, it is made available in the hope it will be useful. Feedback is most welcome.