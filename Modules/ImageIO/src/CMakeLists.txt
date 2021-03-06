# ============================================================================
# Medical Image Registration ToolKit (MIRTK) LBFGS Library
#
# Copyright 2013-2015 Imperial College London
# Copyright 2013-2015 Andreas Schuh
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ============================================================================

##############################################################################
# @file  CMakeLists.txt
# @brief Build configuration of MIRTK ImageIO library.
##############################################################################

set(HEADERS
  ${BINARY_INCLUDE_DIR}/mirtkImageIOConfig.h
  mirtkGIPLImageReader.h
  mirtkGIPLImageWriter.h
  mirtkPGMImageReader.h
  mirtkPGMImageWriter.h
)

set(SOURCES
  mirtkGIPL.h
  mirtkGIPLImageReader.cc
  mirtkGIPLImageWriter.cc
  mirtkImageIOConfig.cc
  mirtkPGM.h
  mirtkPGMImageReader.cc
  mirtkPGMImageWriter.cc
)

set(DEPENDS
  LibImage
)

if (NiftiCLib_FOUND)
  list(APPEND HEADERS
    mirtkNiftiImageInfo.h
    mirtkNiftiImageReader.h
    mirtkNiftiImageWriter.h
  )
  list(APPEND SOURCES
    mirtkNiftiImage.h
    mirtkNiftiImage.cc
    mirtkNiftiImageInfo.cc
    mirtkNiftiImageReader.cc
    mirtkNiftiImageWriter.cc
  )
  list(APPEND DEPENDS ${NiftiCLib_LIBRARIES})
endif ()

if (PNG_FOUND)
  add_definitions(${PNG_DEFINITIONS})
  list(APPEND HEADERS mirtkPNGImageWriter.h)
  list(APPEND SOURCES mirtkPNGImageWriter.cc)
  list(APPEND DEPENDS ${PNG_LIBRARIES})
endif ()

if (ZLIB_FOUND)
  list(APPEND DEPENDS ${ZLIB_LIBRARIES})
endif ()

mirtk_add_library(AUTO_REGISTER)
