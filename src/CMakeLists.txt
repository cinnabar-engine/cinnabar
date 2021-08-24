include_directories(
	${PROJECT_SOURCE_DIR}/include
	${CE_INCLUDE}
)
# add_subdirectory(cinnabar-core)
# add_subdirectory(cinnabar-render)
# add_subdirectory(cinnabar-text)
# add_subdirectory(cinnabar-render-demo)



file(GLOB PROJECTS
	"*/CMakeLists.txt"
)
foreach(PROJECT_PATH ${PROJECTS})
get_filename_component(PROJ_DIR ${PROJECT_PATH} DIRECTORY)
get_filename_component(PROJECT ${PROJ_DIR} NAME)
message(NOTICE "ADDING PROJECT: " ${PROJECT})
add_subdirectory(${PROJECT})
endforeach()
