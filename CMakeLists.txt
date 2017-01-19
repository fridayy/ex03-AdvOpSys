cmake_minimum_required(VERSION 3.6)
project(LabExercise3)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES src/ushell/PathOperation.c src/ushell/DirectoryOperation.c src/ushell/FileOperation.c src/ushell/InternalOperation.c src/ushell/CommandExecutor.c src/ushell/parser.c src/ushell/Commands.c)
add_executable(LabExercise3 ${SOURCE_FILES} src/ushell/ushell.c)