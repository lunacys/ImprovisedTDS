cmake_minimum_required(VERSION 3.0)
project(ImprovisedTDS)

add_subdirectory(3rdParty)

include_directories(
  3rdParty/glad/include/
  3rdParty/stb/
  3rdParty/glfw/include/
  3rdParty/glm/glm/
  ${PROJECT_NAME}/include/
  )

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa -O3 -mbig-obj -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

option(BUILD_SHARED_LIBS OFF)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLM_TEST_ENABLE OFF)


set (CMAKE_CXX_STANDARD 11)

  set(ALL_LIBS
	opengl32.lib
	glad
	glm
	#stb
    glfw
	#libpng.lib
	#zlib.lib
    ) 
#endif()


file(GLOB PROJECT_SOURCES ${PROJECT_NAME}/src/*.cpp)
file(GLOB PROJECT_HEADERS
  ${PROJECT_NAME}/include/*.hpp
  ${PROJECT_NAME}/include/*.h
  )
file(GLOB PROJECT_IMAGES ${PROJECT_NAME}/data/images/*.jpg
  ${PROJECT_NAME}/data/images/*.png
  )
file(GLOB PROJECT_MUSIC ${PROJECT_NAME}/data/music/*.ogg)
file(GLOB PROJECT_FONTS ${PROJECT_NAME}/data/fonts/*.png
  ${PROJECT_NAME}/data/fonts/*.txt
  ${PROJECT_NAME}/data/fonts/*.ttf
  )
file(GLOB PROJECT_SHADERS ${PROJECT_NAME}/data/shaders/*.vert
  ${PROJECT_NAME}/data/shaders/*.frag
  )
file(GLOB PROJECT_SFX ${PROJECT_NAME}/data/sfx/*.wav
  ${PROJECT_NAME}/data/images/*.png
  )
file(GLOB PROJECT_CONFIGS CMakeLists.txt )

add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_definitions(-DCMAKE-C-FLAGS)

#if (WIN32)
#  set(ADDITIONAL_FLAGS WIN32)
#else ()
#  set(ADDITIONAL_FLAGS "")
#endif()

add_executable(${PROJECT_NAME} ${ADDITIONAL_FLAGS}
  ${PROJECT_SOURCES} ${PROJECT_HEADERS}
  ${PROJECT_IMAGES} ${PROJECT_MUSIC}
  ${PROJECT_FONTS} ${PROJECT_SHADERS}
  ${PROJECT_SFX}  ${PROJECT_CONFIGS}
  )

#target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)

target_link_libraries(${PROJECT_NAME}
  ${ALL_LIBS}
  )

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME})
