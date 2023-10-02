#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

class GameOverState : public State {
public:
	GameOverState(GameDataRef data, int score);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	sf::Clock _clock;
	sf::Sprite _bgSprite;
	sf::Sprite _gameOverTitle;
	sf::Sprite _gameOverContainer;
	sf::Sprite _retryButton;
	sf::Sprite _medal;

	sf::Text _scoreText;
	sf::Text _highscoreText;

	int _score;
	int _highscore;
};

