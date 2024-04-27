add_library(terminal STATIC src/terminal.cxx)
target_include_directories(terminal PUBLIC include)
target_link_libraries(terminal libc)