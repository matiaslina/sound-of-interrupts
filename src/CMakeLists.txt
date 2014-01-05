add_subdirectory(helpers)
add_subdirectory(qtgui)

set(HELPERS_LIBRARIES helpers)

add_executable(play-cli main.c)
target_link_libraries(play-cli pulse pulse-simple ${HELPERS_LIBRARIES})
