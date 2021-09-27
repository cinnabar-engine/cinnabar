include_directories(
	${CE_INCLUDE}
	${PROJECT_SOURCE_DIR}/include
)

file(GLOB PROJECTS
	"*/CMakeLists.txt"
)

foreach(PROJECT_PATH ${PROJECTS})
	get_filename_component(PROJ_DIR ${PROJECT_PATH} DIRECTORY)
	get_filename_component(PROJECT ${PROJ_DIR} NAME)
	message(NOTICE "ADDING PROJECT: " ${PROJECT})
	add_subdirectory(${PROJECT})
endforeach()