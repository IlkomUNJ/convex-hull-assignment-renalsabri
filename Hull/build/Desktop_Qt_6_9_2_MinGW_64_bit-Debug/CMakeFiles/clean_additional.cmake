# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Hull_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Hull_autogen.dir\\ParseCache.txt"
  "Hull_autogen"
  )
endif()
