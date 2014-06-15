set(SOURCES
	main.cpp
	Camera.cpp
	Player.cpp
	PlayerUI.cpp
	Physics.cpp
	Game.cpp
	GameSystem.cpp
	InputSystem.cpp
	TextureCache.cpp
	SpawnerMesh.cpp
	
	Entities/Entity.cpp
	Entities/CrateEntity.cpp
	Entities/MedKitEntity.cpp
	Entities/GrenadePackEntity.cpp
	Entities/PlayerEntity.cpp
	Entities/LevelMeshEntity.cpp
	Entities/SpawnerMeshEntity.cpp
	Entities/MouseTrackEntity.cpp
	Entities/BulletEntity.cpp
	Entities/CrosshairEntity.cpp
	
	Renderables/BoxRenderable.cpp
	Renderables/MeshRenderable.cpp
	
	Weapons/Weapon.cpp
	Weapons/WeaponDef.cpp
	
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
