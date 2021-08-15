# src/CMakeLists.txt

project (main)

# Creating the future executable file

add_executable (${PROJECT_NAME} main.c)

add_subdirectory (processing)

# Linking proc::lib static library to the executable

target_link_libraries (${PROJECT_NAME}
	proc::lib
)
