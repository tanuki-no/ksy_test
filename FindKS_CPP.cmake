# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindKS_CPP
----------

Find the Kaitai Struct: runtime library for C++/STL:

IMPORTED Targets
^^^^^^^^^^^^^^^^

``KS_CPP::KS_CPP``
  The libkaitai_struct_cpp_stl library, if found.

Result Variables
^^^^^^^^^^^^^^^^

This module defines the following variables:

``KS_CPP_FOUND``
  system has KS_CPP
``KS_CPP_INCLUDE_DIRS``
  .. versionadded:: 3.22

  the KS_CPP include directory
``KS_CPP_LIBRARIES``
  the libraries needed to use KS_CPP
``KS_CPP_VERSION_STRING``
  the version of KS_CPP found

Cache variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``KS_CPP_INCLUDE_DIR``
  where to find jasper/jasper.h, etc.
``KS_CPP_LIBRARY_RELEASE``
  where to find the KS_CPP library (optimized).
``KS_CPP_LIBARRY_DEBUG``
  where to find the KS_CPP library (debug).
#]=======================================================================]

cmake_policy(PUSH)
cmake_policy(SET CMP0159 NEW) # file(STRINGS) with REGEX updates CMAKE_MATCH_<n>

find_path(KS_CPP_INCLUDE_DIR kaitai/kaitaistruct.h)
mark_as_advanced(KS_CPP_INCLUDE_DIR)

if(NOT KS_CPP_LIBRARIES)
  find_library(KS_CPP_LIBRARY NAMES kaitai_struct_cpp_stl_runtime libkaitai_struct_cpp_stl_runtime)
endif()

set(KS_CPP_LIBRARIES ${KS_CPP_LIBRARIES})
set(KS_CPP_INCLUDE_DIRS ${KS_CPP_INCLUDE_DIR})

cmake_policy(POP)
