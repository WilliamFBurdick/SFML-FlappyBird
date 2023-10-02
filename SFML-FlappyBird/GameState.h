#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"
#include "HUD.h"

class GameState : public State {
public:
	GameState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	sf::Sprite _bgSprite;
	sf::Clock clock;
	Pipe* pipe;
	Land* land;
	Bird* bird;
	Collision collision;
	Flash* flash;
	HUD* hud;

	int _gameState;
	int _score;

	sf::SoundBuffer _hitSoundBuffer;
	sf::SoundBuffer _wingSoundBuffer;
	sf::SoundBuffer _pointSoundBuffer;

	sf::Sound _hitSound;
	sf::Sound _wingSound;
	sf::Sound _pointSound;
};

