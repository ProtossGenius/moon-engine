cmake_minimum_required(VERSION 3.8)
project(moon-engine)
set(CXX_FLAGS
        -g
        # -DVALGRIND
        -DCHECK_PTHREAD_RETURN_VALUE
        -D_FILE_OFFSET_BITS=64
        -Wall
        -Wextra
        -Werror
        -Wconversion
        -Wno-unused-parameter
        -Wold-style-cast
        -Woverloaded-virtual
        -Wpointer-arith
        -Wshadow
        -Wwrite-strings
        -march=native
        # -MMD
        -rdynamic
		-std=c++2a
        )
# add packages
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(.)
aux_source_directory(. src_files)

add_executable(moon-engine ${src_files})

target_link_libraries(moon-engine stb_image tests unit_test oogl_s2d oogl_s3d oogl smgame imgui glfw stb)
add_subdirectory(oogl)
add_subdirectory(smgame)
add_subdirectory(stb_image)
add_subdirectory(tests)
add_subdirectory(unit_test)

