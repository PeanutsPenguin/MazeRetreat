# ------- Platformer Project ------- #

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# ------- Sources files
# ------- Retrieving all the source files and putting them into a kind of list ------- #

message("[${TARGET_NAME}] Starting source file fetching..")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

### ------- Header files

file(GLOB_RECURSE TARGET_HEADER_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl)
list(FILTER TARGET_HEADER_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

### ------- Source (C++) files

file(GLOB_RECURSE TARGET_SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
list(FILTER TARGET_SOURCE_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

### ------- Shader files

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE TARGET_SHADERS_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*.vert
	${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*.frag
	${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*.glsl)
list(FILTER TARGET_SHADERS_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

### ------- Assets (everything inside the folder)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE TARGET_ASSETS_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/Assets/*)
list(FILTER TARGET_ASSETS_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${BIN_DEPENDENCIES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/)
file(COPY ${BIN_DEPENDENCIES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release/)

# ------- Putting all those files under a common name/variable TARGET_FILES ------- #

set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES} ${TARGET_SHADERS_FILES} )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_ASSETS_FILES})


# ------- Executable
# ------- In this part of the code will link everything together ------- #


add_executable(${TARGET_NAME})

message("[${TARGET_NAME}] The executable is being linked with the project's dependencies..")

### ------- Appending the previous source files into the executable

target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES} ${TARGET_ASSETS_FILES})
set_source_files_properties(${TARGET_ASSETS_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

### ------- Specifies the include directories so Visual Studio knows 

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Header)

target_link_libraries(${TARGET_NAME} PRIVATE ${MODERN_LIBRARY})

# set( DLLlib ${CMAKE_INSTALL_PATH}/bin)

# set(("${CMAKE_INSTALL_PATH}")


message("[${TARGET_NAME}] Done.")
