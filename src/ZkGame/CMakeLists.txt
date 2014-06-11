set(SOURCES
	main.cpp
	Camera.cpp
	PlayerUI.cpp
	Physics.cpp
	Game.cpp
	GameSystem.cpp
	InputSystem.cpp
	TextureCache.cpp
	
	Entities/Entity.cpp
	Entities/CrateEntity.cpp
	Entities/PlayerEntity.cpp
	Entities/LevelMeshEntity.cpp
	Entities/MouseTrackEntity.cpp
	
	Renderables/BoxRenderable.cpp
	Renderables/MeshRenderable.cpp
	
	Lobby/LobbyWindow.cpp
	Lobby/PlayTab.cpp
	Lobby/GraphicsTab.cpp
	Lobby/InputTab.cpp
	Lobby/InputChoiceDialog.cpp
	
	Config/Config.cpp
	Config/GraphicsConfig.cpp
	Config/InputConfig.cpp
	Config/PlayerAction.cpp
	Config/InputAction.cpp
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	list(APPEND SOURCES win-res.rc)
endif ()

add_executable(ZkGame ${SOURCES})
target_link_libraries(ZkGame
	ZkCommon
	${QT_LIBRARIES}
	${SFML_LIBRARIES}
	${BOX2D_LIBRARIES}
	${OPENGL_LIBRARIES}
	ManyMouse
)
