cmake_minimum_required(VERSION 3.0)

project(RoonyBin)

#Make sure we can include everything in project directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("thirdparty")
include_directories("thirdparty/glew")

link_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories("thirdparty")

#Find all source, header, and shader files to add to build
file(GLOB_RECURSE allCodeFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.hpp" "*.cpp" "*.h" "*.c" "*.vs" "*.fs")

#Compile them to an executable
if(WIN32)
  add_executable(RoonyBin WIN32 ${allCodeFiles})

  #Because I want the console window, we can remove parts of this later on
  set_target_properties(RoonyBin PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
  set_target_properties(RoonyBin PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
  set_target_properties(RoonyBin PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
  set_target_properties(RoonyBin PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
  set_target_properties(RoonyBin PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:windows")
  set_target_properties(RoonyBin PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows")
  target_compile_definitions(RoonyBin
	PRIVATE rblinkPlatWin)
  target_link_libraries(RoonyBin OpenGL32)
  #Warning level 4
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
elseif(UNIX)
  add_executable(RoonyBin ${allCodeFiles})
  if(NOT APPLE)
	target_compile_definitions(RoonyBin
	  PRIVATE rblinkPlatWin)
	target_link_libraries(RoonyBin gl)
  endif(NOT APPLE)
endif()

#Load libraries (must come after add_executable)
#target_link_libraries(RoonyBin glfw/glfw3)
#target_link_libraries(OpenGL assimp/assimp)
target_link_libraries(RoonyBin glew/glew32)
target_link_libraries(RoonyBin glew/glew32s)

#Fix Visual studio source groups to correspond to the folder they're in
foreach(src ${allCodeFiles})
  get_filename_component(dir ${src} DIRECTORY)
  if(dir)
	string(REPLACE "/" "\\" fixedDir ${dir})
	source_group(${fixedDir} FILES ${src})
  else()
	source_group("\\\\" FILES ${src})
  endif()
endforeach()

#Copy appropriate files to build directory
file(GLOB_RECURSE shaders RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.vs" "*.fs")
foreach(shader ${shaders})
  file(COPY ${shader} DESTINATION "${CMAKE_BINARY_DIR}/shaders")
endforeach()
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glew/glew32.dll" DESTINATION "${CMAKE_BINARY_DIR}")
