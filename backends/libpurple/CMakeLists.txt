cmake_minimum_required(VERSION 2.6)
FILE(GLOB SRC *.cpp)

ADD_EXECUTABLE(spectrum2_libpurple_backend ${SRC})

if(CMAKE_COMPILER_IS_GNUCXX)
	if (NOT WIN32)
	target_link_libraries(spectrum2_libpurple_backend ${PURPLE_LIBRARY} ${GLIB2_LIBRARIES} ${EVENT_LIBRARIES} transport-plugin pthread)
	else()
	target_link_libraries(spectrum2_libpurple_backend ${PURPLE_LIBRARY} ${GLIB2_LIBRARIES} ${EVENT_LIBRARIES} transport-plugin)
	endif()
else()
target_link_libraries(spectrum2_libpurple_backend sqlite3 ${PURPLE_LIBRARY} ${GLIB2_LIBRARIES} ${LIBXML2_LIBRARIES} ${EVENT_LIBRARIES} transport-plugin ${PROTOBUF_LIBRARY})
endif()

INSTALL(TARGETS spectrum2_libpurple_backend RUNTIME DESTINATION bin)

