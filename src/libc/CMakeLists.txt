add_library(libc STATIC 
                    src/string.c
                    src/compiler.cxx
                    src/stdio.cxx
            )

target_include_directories(libc PUBLIC include)
target_link_libraries(libc terminal)