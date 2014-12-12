#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <memory>

#include "../Renderable.hpp"
#include "ContainerGraphicsLayer.hpp"

namespace Zk {
namespace Game {

class FovGraphicsLayer : public ContainerGraphicsLayer
{
public:
	FovGraphicsLayer(
		const sf::VertexArray & edges,
		const std::string & hierarchyPath,
		const std::string & name
	);
	virtual ~FovGraphicsLayer() {}

	virtual void paint(sf::RenderTarget * rt, const Player & viewer);

	inline void setFovEffectEnabled(bool enable)
	{ enableFovEffect = enable; }

private:
	sf::Shader maskVShader, maskApplicationShader;
	sf::RenderTexture mask, colorBuffer;
	sf::VertexArray extrudedMesh;

	bool enableFovEffect;

	void constructExtrudedMesh(const sf::VertexArray & edges);
};

}}
