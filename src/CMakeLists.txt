# Define language
ENABLE_LANGUAGE ( CXX )

# Tune compiler
SET(CMAKE_CXX_STANDARD          11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS        OFF)

# Version
CONFIGURE_FILE (
  ${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
  NEWLINE_STYLE UNIX )

# Generate Kaitai data
SET (
  KSC_OPTIONS
    "-t" "cpp_stl"
    "--cpp-namespace" "mts::test"
    "--cpp-standard" "11"
    ${CMAKE_CURRENT_SOURCE_DIR}/teltonica.ksy
  )
EXECUTE_PROCESS (
  COMMAND ${KSC} ${KSC_OPTIONS}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )

# Includes
INCLUDE_DIRECTORIES (
  ${CMAKE_SOURCE_DIR}/include
  ${JSONCPP_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
  )

# Project sources
SET (
  ${PROJECT_NAME}_SOURCES

  ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/teltonica_proto.cpp
  "main.cpp"
  )

# Project Executable
ADD_EXECUTABLE(
  ${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES}
  )

TARGET_COMPILE_OPTIONS(
  ${PROJECT_NAME} PRIVATE -Wall -Werror
  )

TARGET_LINK_LIBRARIES(
  ${PROJECT_NAME} PRIVATE Threads::Threads
  ${JSONCPP_LIBRARIES}
  ${KS_CPP_LIBRARY}
  )

# Small utility to convert dump to binary data
SET ( DUMP2HEX_NAME "dump2hex" )

SET (
  ${DUMP2HEX_NAME}_SOURCES
  
  "dump2hex.cpp"
  )

ADD_EXECUTABLE(
  ${DUMP2HEX_NAME} ${${DUMP2HEX_NAME}_SOURCES}
  )


# End of filee