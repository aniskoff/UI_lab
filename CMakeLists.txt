cmake_minimum_required(VERSION 3.13)
project(UI_lab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(UI_lab
        OtherTasks/IBrocker.h
        ICompact/ICompact.cpp
        ICompact/ICompact.h
        ICompact/ICompactImpl.cpp
        ICompact/ICompactImpl.h
        ILogger/ILogger.cpp
        ILogger/ILogger.h
        ILogger/ILoggerImpl.cpp
        ILogger/ILoggerImpl.h
        OtherTasks/IProblem.h
        ISet/ISet.cpp
        ISet/ISet.h
        ISet/ISetImpl.cpp
        ISet/ISetImpl.h
        OtherTasks/ISolver.h
        IVector/IVector.cpp
        IVector/IVector.h
        IVector/IVectorImpl.cpp
        IVector/IVectorImpl.h
        RC.h
        Testing.cpp
        tests/ICompact_tests.h
        tests/ICompact_tests.cpp
        tests/ISet_tests.h
        tests/ISet_tests.cpp
        tests/IVector_tests.h
        tests/IVector_tests.cpp
        tests/SimpleTests.cpp
        tests/SimpleTests.h)
