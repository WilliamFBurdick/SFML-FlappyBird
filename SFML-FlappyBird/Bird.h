#pragma once

#include <SFML/Graphics.hpp>
#include "Defs.h"
#include "Game.h"
#include <vector>

class Bird {
public:
	Bird(GameDataRef data);
	void Draw();
	void Animate(float dt);
	void Update(float dt);
	void Tap();

	const sf::Sprite& GetSprite() const;
private:
	GameDataRef _data;
	sf::Sprite _birdSprite;
	std::vector<sf::Texture> _animFrames;

	unsigned int _animIndex;

	sf::Clock _clock;

	sf::Clock _moveClock;
	int _birdState;
	float _rotation;
};

