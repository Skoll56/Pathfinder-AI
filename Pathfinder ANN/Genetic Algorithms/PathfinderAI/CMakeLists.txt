cmake_minimum_required(VERSION 2.6)

project(PathfinderAI)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib/32)

add_executable(PathfinderAI
	"src/ANN.cpp"
	"src/ANN.h"
	"src/Console.cpp"
	"src/Console.h"
	"src/Entity.cpp"
	"src/Entity.h"
	"src/Game.cpp"
	"src/Game.h"
	"src/Input.cpp"
	"src/Input.h"
	"src/MapLoader.h"
	"src/MapLoader.cpp"
	"src/Pathfind.cpp"
	"src/Pathfind.h"
	"src/Sheet.h"
)

target_link_libraries(PathfinderAI SDL2)

if(MSVC)
	set_property(TARGET PathfinderAI PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/runtime")
endif()