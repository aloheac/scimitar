########################################################################################################################
# Scimitar 7 - A tool for parameter-space exploration.
# Compiler Library Implementation
#
# Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
# See LICENSE.TXT distributed with the source for for license information.
#
#    CMakeLists file for the CMake build system.
#
#    DESCRIPTION: This file provides directives for defining the project's source file and compilation targets under the
#                 CMake build system. This Makefile will build the Scimitar compiler library (libscimitar.so) and the
#                 interactive compiler executable (scic).
#
#    CREATION DATE: December 13, 2019
########################################################################################################################


cmake_minimum_required(VERSION 3.14)
project(Scimitar7)

# Set include and library paths below.
set(ANTLR4_RUNTIME_INCLUDE "/home/loheac/.local/etc/antlr4/include/antlr4-runtime")
set(PYBIND11_INCLUDE "/home/loheac/.local/include/python3.8")
set(PYTHON_INCLUDE "/usr/include/python3.8")
set(ANTLR4_LIBRARY "/home/loheac/.local/etc/antlr4/lib")
include_directories(${ANTLR4_RUNTIME_INCLUDE} ${PYBIND11_INCLUDE} ${PYTHON_INCLUDE})

set(CMAKE_CXX_STANDARD 14)

set(GRAMMAR_SOURCE grammar/ScimitarVisitor.h grammar/ScimitarParser.h grammar/ScimitarParser.cpp grammar/ScimitarLexer.h
        grammar/ScimitarLexer.cpp grammar/ScimitarBaseVisitor.h grammar/ScimitarBaseVisitor.cpp
        grammar/GrammarErrorHandler.cpp grammar/GrammarErrorHandler.h)

set(CORE_ENGINE_SOURCE engine/BasicStructures.cpp engine/BasicStructures.h engine/Engine.cpp engine/Engine.h
        engine/EngineAction.cpp engine/EngineAction.h engine/EngineAction.cpp engine/EngineAuxiliary.h
        engine/EngineAuxiliary.cpp engine/Group.cpp engine/Group.h)

set(CORE_FRONTEND_SOURCE frontend/ParserFrontend.cpp frontend/ParserFrontend.h frontend/SourceFileStream.cpp
        frontend/SourceFileStream.h)

set(CORE_LANGUAGE_SOURCE language/ArithmeticExpression.cpp language/ArithmeticExpression.h
        language/ConditionalExpression.cpp language/ConditionalExpression.h language/Expression.cpp
        language/Expression.h language/LoopStatement.cpp language/LoopStatement.h language/UserFunction.cpp
        language/UserFunction.h)

set(CORE_PARAMETER_SOURCE parameter/Parameter.cpp parameter/Parameter.h parameter/ParameterValue.cpp
        parameter/ParameterValue.h parameter/Symbol.cpp parameter/Symbol.h)

set(CORE_SOURCE ${CORE_ENGINE_SOURCE} ${CORE_FRONTEND_SOURCE} ${CORE_LANGUAGE_SOURCE} ${CORE_PARAMETER_SOURCE})
set(LIBRARY_SOURCE frontend/PythonInterface.cpp frontend/PythonInterface.h)
set(EXEC_SOURCE main.cpp)

add_executable(scic ${EXEC_SOURCE} ${CORE_SOURCE} ${GRAMMAR_SOURCE})
add_library(scimitar SHARED ${LIBRARY_SOURCE} ${CORE_SOURCE} ${GRAMMAR_SOURCE})

target_link_directories(scic PUBLIC ${ANTLR4_LIBRARY})
target_link_libraries(scic "antlr4-runtime")
target_compile_options(scic PUBLIC "-O3")

target_link_directories(scimitar PUBLIC ${ANTLR4_LIBRARY})
target_link_libraries(scimitar "antlr4-runtime" "python3.8")
target_compile_options(scimitar PUBLIC "-Wall" "-Wattributes" "-fPIC" "-flto" "-fvisibility=hidden" "-O3")