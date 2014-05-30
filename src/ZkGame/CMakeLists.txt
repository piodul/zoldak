set(SOURCES
	main.cpp
	Camera.cpp
	Physics.cpp
	Game.cpp
	GameSystem.cpp
	InputSystem.cpp
	Entities/Entity.cpp
	Entities/CrateEntity.cpp
	Entities/PlayerEntity.cpp
	Entities/LevelMeshEntity.cpp
	Entities/MouseTrackEntity.cpp
	Renderables/BoxRenderable.cpp
	Renderables/MeshRenderable.cpp
)

add_executable(ZkGame ${SOURCES})
target_link_libraries(ZkGame
	ZkCommon
	${QT_LIBRARIES}
	${SFML_LIBRARIES}
	${BOX2D_LIBRARIES}
	${OPENGL_LIBRARIES}
	ManyMouse
)
