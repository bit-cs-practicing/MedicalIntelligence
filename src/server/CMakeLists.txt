project(server)

find_package(Qt5 REQUIRED Core Network Sql)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

include_directories(${PROJECT_SOURCE_DIR}/../core/src)
link_directories(${CMAKE_BINARY_DIR}/src/core)

include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES "src/**/*.cpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/**/*.h")
file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE RESOURCES "src/**/*.qrc")
file(GLOB_RECURSE RESOURCES "src/*.qrc")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${CORE_SOURCES} ${CORE_HEADERS} ${RESOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network Qt5::Sql core)

target_compile_definitions(${PROJECT_NAME} PRIVATE QT_DEPRECATED_WARNINGS)

