add_library(Functions commands.cpp commands.h timeparser.cpp timeparser.h features.cpp features.h)

target_include_directories(Functions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(Functions PRIVATE nlohmann_json::nlohmann_json)
