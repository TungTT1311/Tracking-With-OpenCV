cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(SET CMP0054 NEW)
project(TrackinguselibraryOpencv)

add_executable (TrackinguselibraryOpencv maic.cpp)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
  target_include_directories(TrackinguselibraryOpencv PUBLIC
    ${OpenCV_INCLUDE_DIRS})
  target_link_libraries (TrackinguselibraryOpencv ${OpenCV_LIBS})

  get_target_property(__dll_dbg opencv_world IMPORTED_LOCATION_DEBUG) 
  get_target_property(__dll_release opencv_world  IMPORTED_LOCATION_RELEASE)

endif()
