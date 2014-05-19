set(SOURCES
	BackgroundItem.cpp
	main.cpp
	MainWindow.cpp
	LevelView.cpp
	MeshTriangleNode.cpp
	MeshTriangle.cpp
	MeshTriangleEdge.cpp
	MeshLayer.cpp
)

add_executable(ZkLevelEditor ${SOURCES})
target_link_libraries(ZkLevelEditor ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
