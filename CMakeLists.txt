CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(RANKSTR VERSION 0.2.0)

# Mac rpath Policy
IF(POLICY CMP0042)
          CMAKE_POLICY(SET CMP0042 NEW)
ENDIF(POLICY CMP0042)
SET(CMAKE_MACOSX_RPATH ON)

# Linux rpath settings
SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Configuration Options
OPTION(BUILD_SHARED_LIBS "Whether to build shared libraries" ON)
MESSAGE(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")

if (BUILD_SHARED_LIBS)
   OPTION(RANKSTR_LINK_STATIC "Default to static linking? (Needed for Cray)" OFF)
else()
   OPTION(RANKSTR_LINK_STATIC "Default to static linking? (Needed for Cray)" ON)
endif()
MESSAGE(STATUS "RANKSTR_LINK_STATIC: ${RANKSTR_LINK_STATIC}")

OPTION(ENABLE_TESTS "Whether to build tests" ON)
MESSAGE(STATUS "ENABLE_TESTS: ${ENABLE_TESTS}")

# Find Packages & Files

LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

## MPI
INCLUDE(SetupMPI)
IF(NOT MPI_C_FOUND)
    MESSAGE(FATAL_ERROR
        "Could not find MPI! "
        "Either add an MPI compiler to your path "
        "or force CMake to build using the correct compiler (`export CC=mpicc`).")
ENDIF(NOT MPI_C_FOUND)

## HEADERS
INCLUDE(CheckIncludeFile)
INCLUDE(GNUInstallDirs)

# Subdirectories
ADD_SUBDIRECTORY(src)

IF(ENABLE_TESTS)
   INCLUDE(CTest)
   INCLUDE(RANKSTR_ADD_TEST)
   ADD_SUBDIRECTORY(test)
ENDIF(ENABLE_TESTS)

# Generate config.h with all our build #defs
CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/cmake/config.h.in ${PROJECT_BINARY_DIR}/config.h)
SET_SOURCE_FILES_PROPERTIES(${PROJECT_BINARY_DIR}/config.h PROPERTIES GENERATED TRUE)

# CMake configs

# Install the exports file
INSTALL(EXPORT rankstrTargets FILE rankstrTargets.cmake NAMESPACE rankstr:: DESTINATION share/rankstr/cmake)

# Export so we can use in-tree
EXPORT(EXPORT rankstrTargets NAMESPACE rankstr:: FILE rankstrTargets.cmake)

# Setup the package config
INCLUDE(CMakePackageConfigHelpers)
CONFIGURE_PACKAGE_CONFIG_FILE(cmake/rankstrConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/rankstrConfig.cmake INSTALL_DESTINATION share/rankstr/cmake)
WRITE_BASIC_PACKAGE_VERSION_FILE(${CMAKE_CURRENT_BINARY_DIR}/rankstrConfigVersion.cmake COMPATIBILITY SameMajorVersion)

# Install package config
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/rankstrConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/rankstrConfigVersion.cmake DESTINATION share/rankstr/cmake)

# Package
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Splits processes into groups based on input string")
SET(CPACK_PACKAGE_VENDOR "Lawrence Livermore National Laboratory")
# SET(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.md")
# SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.TXT")
