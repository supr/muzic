project(muzic)
cmake_minimum_required(VERSION 2.8)

add_definitions(
    -std=c++11
)

include(FindPkgConfig)

pkg_check_modules(PULSEAUDIO libpulse)
pkg_check_modules(PULSEAUDIO_SIMPLE libpulse-simple)

include_directories(${PULSEAUDIO_INCLUDE_DIRS} ${PULSEAUDIO_SIMPLE_INCLUDE_DIRS})
link_directories(${PULSEAUDIO_LIBRARY_DIRS} ${PULSEAUDIO_SIMPLE_LIBRARY_DIRS})

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${PULSEAUDIO_LIBRARIES} ${PULSEAUDIO_SIMPLE_LIBRARIES})

