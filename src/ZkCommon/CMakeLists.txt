set(SOURCES
	Level.cpp
)

add_library(ZkCommon ${SOURCES})
target_link_libraries(ZkCommon ${QT_LIBRARIES})
