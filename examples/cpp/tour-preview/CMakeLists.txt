SET (TARGET tour-preview)
PROJECT (${TARGET})

include_directories(
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 ${QT_INCLUDE_DIR}
)

set( ${TARGET}_SRC tour-preview.cpp)
add_executable( ${TARGET} ${${TARGET}_SRC} )

target_link_libraries( ${TARGET} ${OpenCV_LIBS} ${MARBLEWIDGET} )
target_link_libraries( ${TARGET} ${Qt5Core_LIBRARIES} )

install( TARGETS ${TARGET} RUNTIME DESTINATION bin )
