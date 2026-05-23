cmake_minimum_required(VERSION 3.14)
project(MonsterSlayerCPP VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ==================== Logging Configuration ====================

# Print important info during configuration
message(STATUS "Project Root: ${CMAKE_SOURCE_DIR}")
message(STATUS "Build Directory: ${CMAKE_BINARY_DIR}")
message(STATUS "Generator: ${CMAKE_GENERATOR}")

# Optional: Save compile commands (useful for tools)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ==================== Executable ====================
add_executable(monster_slayer
    src/main.cpp
)

target_include_directories(monster_slayer PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# ==================== Compiler Options ====================
if(MSVC)
    target_compile_options(monster_slayer PRIVATE /W4)
else()
    target_compile_options(monster_slayer PRIVATE -Wall -Wextra)
endif()

message(STATUS "✅ Project configured successfully!")