set(SOURCES
	main.cpp
)

add_executable(ZkLevelEditor ${SOURCES})
target_link_libraries(ZkLevelEditor ${QT_LIBRARIES})
