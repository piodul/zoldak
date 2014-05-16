set(SOURCES
	main.cpp
	MainWindow.cpp
	LevelView.cpp
	TriangleNode.cpp
	MeshTriangle.cpp
	MeshTriangleEdge.cpp
	MeshLayer.cpp
)

add_executable(ZkLevelEditor ${SOURCES})
target_link_libraries(ZkLevelEditor ${QT_LIBRARIES})
