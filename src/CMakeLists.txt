add_subdirectory(helpers)

add_executable(play-cli main.c)
target_link_libraries(play-cli pulse pulse-simple helpers)
