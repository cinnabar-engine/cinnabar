set(NAME cinnabar-engine)

file(GLOB_RECURSE CE_SRC
	"*.hpp"
	"*.cpp"
	"*.c"
)

add_executable(${NAME}
	WIN32
	${CE_SRC}
)

target_link_libraries(${NAME}
	${CE_LIBS}
)
if(!MINGW)
target_link_directories(${NAME} BEFORE
	${CE_LIB_DIRS}
)
endif()

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CE_INCLUDES}
)


#set_property(TARGET engine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/res")
#add_custom_command(
#	TARGET ${NAME}
#	POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:${NAME}>
#)
set_target_properties(
	${NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/res"
)
#add_test(
#	NAME run
#	COMMAND ${NAME}
#	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/res/
#)
