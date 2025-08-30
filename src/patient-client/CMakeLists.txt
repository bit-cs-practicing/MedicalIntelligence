project(patient-client)

find_package(Qt5 REQUIRED Core Gui Widgets Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

include_directories(${PROJECT_SOURCE_DIR}/../core/src)

file(GLOB_RECURSE CORE_SOURCES "../core/src/**/*.cpp")
file(GLOB_RECURSE CORE_SOURCES "../core/src/*.cpp")
file(GLOB_RECURSE CORE_HEADERS "../core/src/**/*.h")
file(GLOB_RECURSE CORE_HEADERS "../core/src/*.h")

include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES "src/**/*.cpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/**/*.h")
file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE FORMS "src/**/*.ui")
file(GLOB_RECURSE FORMS "src/*.ui")
file(GLOB_RECURSE RESOURCES "src/**/*.qrc")
file(GLOB_RECURSE RESOURCES "src/*.qrc")

add_executable(
    ${PROJECT_NAME}
    ${SOURCES} ${HEADERS} ${CORE_SOURCES} ${CORE_HEADERS} ${FORMS} ${RESOURCES}
)

target_link_libraries(patient-client Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)

target_compile_definitions(patient-client PRIVATE QT_DEPRECATED_WARNINGS)
