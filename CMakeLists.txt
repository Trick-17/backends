MESSAGE( STATUS ">> -------------------------------------------------------------------- <<" )
MESSAGE( STATUS ">> --------------------- Backends ------------------------------------- <<" )

######### CMake Version #####################
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
### We need at least C++11
set (CMAKE_CXX_STANDARD 11)
### Distinction between Clang and AppleClang
cmake_policy(SET CMP0025 NEW)
#############################################


### Set the cmake subdirectory
# list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" )


# ######### Get git revision ##################
# include(GetGitRevisionDescription)
# get_git_head_revision(GIT_REFSPEC GIT_SHA1)
# string(SUBSTRING "${GIT_SHA1}" 0 12 GIT_REV)
# #############################################


######### Meta information about the project
set(META_PROJECT_NAME         "Backends")
set(META_PROJECT_DESCRIPTION  "Exchangeable header-only numerics backends in c++ cuda and opencl")
set(META_AUTHOR_ORGANIZATION  "")
set(META_AUTHOR_DOMAIN        "https://github.com/trick-17/backends")
set(META_AUTHOR_MAINTAINER    "")
set(META_VERSION_MAJOR        "0")
set(META_VERSION_MINOR        "0")
set(META_VERSION_PATCH        "0")
set(META_VERSION              "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
# set(META_VERSION_REVISION     "${GIT_REV}")
### Propagate version and name_version upwards
set(BACKENDS_META_VERSION              "${META_VERSION}" PARENT_SCOPE)
set(BACKENDS_META_NAME_VERSION         "${META_PROJECT_NAME} v${META_VERSION} (${META_VERSION_REVISION})" PARENT_SCOPE)
#############################################


######### Project Name ######################
project(${META_PROJECT_NAME} VERSION ${BACKENDS_META_VERSION})
#############################################


# #############################################
# SET( BACKENDS_USE_CUDA          OFF  CACHE BOOL "Use CUDA to speed up certain parts of the code." )
SET( BACKENDS_USE_OPENMP        OFF  CACHE BOOL "Use OpenMP to speed up certain parts of the code." )
# #############################################


# ######### CUDA decisions ####################
# if ( BACKENDS_USE_CUDA )
#     find_package( CUDA REQUIRED )
#     add_definitions( -DUSE_CUDA )
# 	# set (CUDA_PROPAGATE_HOST_FLAGS ON)
# 	# --std=c++11 flag may be necessary, but it is propagated from global flags...
# 	# if it appears twice, for some reason the compilation breaks
#     set( CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -arch=sm_60 --expt-relaxed-constexpr" )
# endif()
# #############################################


#############################################
if ( BACKENDS_USE_OPENMP )
	include( FindOpenMP )
    if( OPENMP_FOUND )
        set( CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}" )
        set( CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
        set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}" )
		message( STATUS ">> OpenMP found." )
		message( STATUS ">> OpenMP C Flags:          ${OpenMP_C_FLAGS}" )
		message( STATUS ">> OpenMP CXX Flags:        ${OpenMP_CXX_FLAGS}" )
		message( STATUS ">> OpenMP EXE Linker Flags: ${OpenMP_EXE_LINKER_FLAGS}" )
	else( OPENMP_FOUND )
		message( STATUS ">> WARNING: OpenMP could not be found." )
	endif( OPENMP_FOUND )
endif( )
#############################################


######### Where to search for library headers
include_directories( ${PROJECT_SOURCE_DIR} )
#############################################


# ######### Declare File groups ###############
# ### Header Gropus
# set(HEADER_BACKENDS_ROOT)
# set(HEADER_BACKENDS)
# set(HEADER_BACKENDS_DATA)
# set(HEADER_BACKENDS_ENGINE)
# set(HEADER_BACKENDS_UTILITY)
# ### Source Groups
# set(SOURCE_BACKENDS_ROOT)
# set(SOURCE_BACKENDS)
# set(SOURCE_BACKENDS_DATA)
# set(SOURCE_BACKENDS_ENGINE)
# set(SOURCE_BACKENDS_UTILITY)
# #############################################


# ######### IDE Folders #######################
# ### Folder include
# source_group("include" FILES ${HEADER_BACKENDS_ROOT})
# source_group("include\\data" FILES ${HEADER_BACKENDS_DATA})
# source_group("include\\engine" FILES ${HEADER_BACKENDS_ENGINE})
# source_group("include\\utility" FILES ${HEADER_BACKENDS_UTILITY})
# source_group("include\\backends" FILES ${HEADER_BACKENDS})
# ### Folder src
# source_group("src" FILES  ${SOURCE_BACKENDS_ROOT}) #${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
# source_group("src\\data" FILES ${SOURCE_BACKENDS_DATA})
# source_group("src\\engine" FILES ${SOURCE_BACKENDS_ENGINE})
# source_group("src\\utility" FILES ${SOURCE_BACKENDS_UTILITY})
# source_group("src\\backends" FILES ${SOURCE_BACKENDS})
# #############################################




######### Test executable ###################
set( TEST_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
### Test creation macro
macro( add_framework_test testName testSrc )
    # Executable
    add_executable( ${testName} test/main.cpp ${testSrc} )
    # Properties
    set_property(TARGET ${testName} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${TEST_RUNTIME_OUTPUT_DIRECTORY})
    set_property(TARGET ${testName} PROPERTY CXX_STANDARD 11)
    set_property(TARGET ${testName} PROPERTY CXX_STANDARD_REQUIRED ON)
    set_property(TARGET ${testName} PROPERTY CXX_EXTENSIONS OFF)
    # Include Directories
    target_include_directories( ${testName} PRIVATE ${PROJECT_SOURCE_DIR}/test)
    # Add the test
    add_test( NAME        ${testName}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND           ${testName} --use-colour=yes )
endmacro( add_framework_test testName testSrc )

### Create tests
### Enable CTest testing
enable_testing()

### Tests
add_framework_test( test1 test/test1.cpp )
#############################################




MESSAGE( STATUS ">> --------------------- Backends done -------------------------------- <<" )
MESSAGE( STATUS ">> -------------------------------------------------------------------- <<" )