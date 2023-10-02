#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Defs.h"

class Flash {
public:
	Flash(GameDataRef data);

	void Show(float dt);
	void Draw();

private:
	GameDataRef _data;
	sf::RectangleShape _shape;
	bool _flashOn;
};

