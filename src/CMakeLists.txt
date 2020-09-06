set(NAME engine)

file(GLOB_RECURSE CE_SRC
"*.hpp"
"*.h"
"*.cpp"
"*.c"
)

add_executable(${NAME}
#WIN32
${CE_SRC})

target_link_libraries(${NAME}
${CE_LIBS}
)


#set_property(TARGET engine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:engine>")
add_custom_command(
	TARGET ${NAME}
	PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:${NAME}>
)
set_target_properties(
	${NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${NAME}>"
)
	
add_test(
	NAME run
	COMMAND ${NAME}
	WORKING_DIRECTORY "$<TARGET_FILE_DIR:${NAME}>"
)