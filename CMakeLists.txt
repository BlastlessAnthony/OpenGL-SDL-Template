cmake_minimum_required(VERSION 3.15)
project(
    "OpenGL SDL Template" #Replace this with the name of your project.
    VERSION 1.0.0.0
    DESCRIPTION "A basic C project that builds and links SDL and GLEW automatically."
    HOMEPAGE_URL "" #Replace or remove this.
    LANGUAGES C CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/CMake")

#A fix to allow the _DEBUG macro on all compilers.
if (UNIX)
    add_compile_options("$<$<CONFIG:DEBUG>:-D_DEBUG>")
endif (UNIX)

#Alternative names
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASE)

#Stop stupidity.
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.\n")
endif()

#Build dependencies
set(PROJECT_DEPENDENCIES_DIR "${CMAKE_CURRENT_LIST_DIR}/Dependencies/Third-Party")
set(PROJECT_DEPENDENCIES_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Third-Party")

find_package(OpenGL REQUIRED)

include(BuildSDL)
include(BuildGLEW)


#Add your sources here...
set(PROJECT_TARGET_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/Source")

set(PROJECT_TARGET_SOURCES 
    "${PROJECT_TARGET_SOURCE_DIR}/Main.c"
)

set(PROJECT_TARGET_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/Include")
set(PROJECT_TARGET_HEADERS
    ""
)

#Create the target
set(PROJECT_TARGET_NAME "OpenGL_SDL_Template")
add_executable(${PROJECT_TARGET_NAME})
target_sources(${PROJECT_TARGET_NAME} PRIVATE ${PROJECT_TARGET_SOURCES} ${PROJECT_TARGET_HEADERS})
target_include_directories(${PROJECT_TARGET_NAME} PRIVATE ${PROJECT_TARGET_INCLUDE_DIR})

#Add dependencies
add_dependencies(${PROJECT_TARGET_NAME}  SDL3::SDL3 libglew_static)

target_link_libraries(${PROJECT_TARGET_NAME} PRIVATE OpenGL::GL SDL3::SDL3 libglew_static)

# Setting the language standard and some helpful warnings.
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CompilerWarnings)
set_project_warnings(${PROJECT_TARGET_NAME})

#On Windows NT, to help with linking with the MultiThreaded library /MT this option is added.
#If issues occur, feel free to comment this out.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

#Basic Alias
add_executable(${PROJECT_TARGET_NAME}::${PROJECT_TARGET_NAME} ALIAS ${PROJECT_TARGET_NAME})

#Easy installation.
include(GNUInstallDirs)
install(
  TARGETS
  ${PROJECT_TARGET_NAME}
  RUNTIME DESTINATION
  ${CMAKE_INSTALL_BINDIR}
)
