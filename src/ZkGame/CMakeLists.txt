set(SOURCES
	main.cpp
	Camera.cpp
	Player.cpp
	PlayerUI.cpp
	PlayerUILayout.cpp
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
	Entities/BulletEntity.cpp
	Entities/GrenadeEntity.cpp
	Entities/CrosshairEntity.cpp
	Entities/PlayerTrackEntity.cpp

	Renderables/BoxRenderable.cpp
	Renderables/MeshRenderable.cpp
	Renderables/SpriteRenderable.cpp
	Renderables/CrosshairRenderable.cpp
	Renderables/BulletRenderable.cpp

	Renderables/GraphicsLayers/GraphicsLayer.cpp
	Renderables/GraphicsLayers/ContainerGraphicsLayer.cpp
	Renderables/GraphicsLayers/FovGraphicsLayer.cpp

	Weapons/Weapon.cpp
	Weapons/WeaponDef.cpp

	Lobby/LobbyWindow.cpp
	Lobby/PlayTab.cpp
	Lobby/GraphicsTab.cpp
	Lobby/InputTab.cpp
	Lobby/SettingsTab.cpp
	Lobby/InputChoiceDialog.cpp
	Lobby/MouseChoiceDialog.cpp

	Config/Config.cpp
	Config/GraphicsConfig.cpp
	Config/InputConfig.cpp
	Config/PlayerAction.cpp
	Config/InputAction.cpp
	Config/SettingsConfig.cpp
)

set(LIBS
	ZkCommon
	${QT_LIBRARIES}
	${SFML_LIBRARIES}
	${BOX2D_LIBRARIES}
	${OPENGL_LIBRARIES}
	ManyMouse
	Box2D
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	list(APPEND SOURCES win-res.rc)
else ()
	list(APPEND LIBS dl)
endif ()

add_executable(ZkGame ${SOURCES})
target_link_libraries(ZkGame ${LIBS})
