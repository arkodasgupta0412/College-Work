# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DrawingApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DrawingApp_autogen.dir\\ParseCache.txt"
  "DrawingApp_autogen"
  )
endif()
