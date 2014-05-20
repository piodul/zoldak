set(SOURCES
	main.cpp
	Game.cpp
	GameSystem.cpp
)

add_executable(ZkGame ${SOURCES})
target_link_libraries(ZkGame
	${QT_LIBRARIES}
	${SFML_LIBRARIES}
	${BOX2D_LIBRARIES}
	${OPENGL_LIBRARIES}
	ManyMouse
)
