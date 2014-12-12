#include <SFML/Graphics.hpp>

#include <algorithm>
#include <memory>

#include "../../GameSystem.hpp"
#include "../../Player.hpp"
#include "../../Entities/PlayerEntity.hpp"
#include "../Renderable.hpp"
#include "FovGraphicsLayer.hpp"

using namespace Zk::Game;

FovGraphicsLayer::FovGraphicsLayer(
	const sf::VertexArray & edges,
	const std::string & hierarchyPath,
	const std::string & name
)
	: ContainerGraphicsLayer(hierarchyPath, name)
{
	constructExtrudedMesh(edges);

	maskVShader.loadFromFile(
		GameSystem::resourcePath("shaders/fov-mask.vsh"),
		GameSystem::resourcePath("shaders/fov-mask.fsh")
	);

	maskApplicationShader.loadFromFile(
		GameSystem::resourcePath("shaders/fov-mask-apply.fsh"),
		sf::Shader::Fragment
	);

	const Config & config = GameSystem::getInstance()->getConfig();
	const sf::VideoMode & vm = config.graphicsConfig.videoMode;
	mask.create(vm.width, vm.height);
	colorBuffer.create(vm.width, vm.height);

	enableFovEffect = true;
}

void FovGraphicsLayer::paint(sf::RenderTarget * rt, const Player & viewer)
{
	auto peWeak = viewer.getPlayerEntity();
	auto pe = peWeak.lock();

	if (pe != nullptr && enableFovEffect)
	{
		//Rysujemy obiekty do bufora
		colorBuffer.setView(rt->getView());
		colorBuffer.clear(sf::Color(0, 0, 0, 0));
		ContainerGraphicsLayer::paint(&colorBuffer, viewer);
		colorBuffer.display();

		//Rysujemy maskę do bufora
		auto pos = pe->getCenterPosition();
		maskVShader.setParameter("vPlayerPos", pos.x, pos.y, 0.f, 1.f);
		maskVShader.setParameter("fExtrusionLength", 4096.f);

		mask.setView(rt->getView());
		mask.clear(sf::Color(0, 0, 0, 0));
		mask.draw(extrudedMesh, &maskVShader);
		mask.display();

		//Nakładamy maskę
		maskApplicationShader.setParameter("sSource", colorBuffer.getTexture());
		maskApplicationShader.setParameter("sMask", mask.getTexture());
		maskApplicationShader.setParameter("cFogColor", sf::Color(0, 0, 0, 127));

		sf::View v = rt->getView();
		rt->setView(rt->getDefaultView());

		sf::Sprite quad(colorBuffer.getTexture());
		rt->draw(quad, &maskApplicationShader);

		rt->setView(v);
	}
	else
		ContainerGraphicsLayer::paint(rt, viewer);
}

void FovGraphicsLayer::constructExtrudedMesh(const sf::VertexArray & edges)
{
	extrudedMesh.clear();
	extrudedMesh.setPrimitiveType(sf::Triangles);

	for (unsigned int i = 0; i < edges.getVertexCount(); i += 2)
	{
		sf::Vertex b0, b1, e0, e1;

		b0 = e0 = edges[i];
		b1 = e1 = edges[i + 1];

		b0.texCoords.x = b1.texCoords.x = 0.f;
		e0.texCoords.x = e1.texCoords.x = 1.f;

		extrudedMesh.append(b0);
		extrudedMesh.append(b1);
		extrudedMesh.append(e0);

		extrudedMesh.append(b1);
		extrudedMesh.append(e0);
		extrudedMesh.append(e1);
	}
}
