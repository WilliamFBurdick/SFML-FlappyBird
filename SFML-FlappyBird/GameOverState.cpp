#include "GameOverState.h"

#include <sstream>
#include "Defs.h"
#include <iostream>
#include "GameState.h"
#include <fstream>

GameOverState::GameOverState(GameDataRef data, int score) : _data(data), _score(score) {

}

void GameOverState::Init() {
	std::ifstream inFile;
	inFile.open("../Resources/Highscore.txt");
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			inFile >> _highscore;
		}
	}
	inFile.close();

	std::ofstream outFile("../Resources/Highscore.txt");
	if (outFile.is_open()) {
		if (_score > _highscore) {
			_highscore = _score;
		}
		outFile << _highscore;
	}
	outFile.close();

	_data->assets.LoadTexture("Game Over Background",
		GAME_OVER_BG_PATH);
	_data->assets.LoadTexture("Game Over Title",
		GAME_TITLE_PATH);
	_data->assets.LoadTexture("Game Over Body",
		GAME_OVER_BODY_PATH);
	_data->assets.LoadTexture("Retry Button",
		PLAY_BUTTON_PATH);
	_data->assets.LoadTexture("Bronze Medal",
		BRONZE_MEDAL_PATH);
	_data->assets.LoadTexture("Silver Medal",
		SILVER_MEDAL_PATH);
	_data->assets.LoadTexture("Gold Medal",
		GOLD_MEDAL_PATH);
	_data->assets.LoadTexture("Platinum Medal",
		PLATINUM_MEDAL_PATH);

	_bgSprite.setTexture(this->_data->assets.GetTexture("Game Over Background"));
	_gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));
	_gameOverContainer.setTexture(this->_data->assets.GetTexture("Game Over Body"));
	_retryButton.setTexture(this->_data->assets.GetTexture("Retry Button"));

	_gameOverContainer.setPosition((_data->window.getSize().x / 2) - (_gameOverContainer.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_gameOverContainer.getGlobalBounds().height / 2));
	_gameOverTitle.setPosition((_data->window.getSize().x / 2) - (_gameOverTitle.getGlobalBounds().width / 2), _gameOverContainer.getPosition().y - (_gameOverTitle.getGlobalBounds().height * 1.2));
	_retryButton.setPosition((_data->window.getSize().x / 2) - (_retryButton.getGlobalBounds().width / 2), _gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height + (_retryButton.getGlobalBounds().height * 0.2));

	_scoreText.setFont(_data->assets.GetFont("Flappy Font"));
	_scoreText.setString(std::to_string(_score));
	_scoreText.setCharacterSize(56);
	_scoreText.setFillColor(sf::Color::White);
	_scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
	_scoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 2.15);

	_highscoreText.setFont(_data->assets.GetFont("Flappy Font"));
	_highscoreText.setString(std::to_string(_highscore));
	_highscoreText.setCharacterSize(56);
	_highscoreText.setFillColor(sf::Color::White);
	_highscoreText.setOrigin(_highscoreText.getGlobalBounds().width / 2, _highscoreText.getGlobalBounds().height / 2);
	_highscoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 1.78);

	if (_score >= PLATINUM_SCORE) {
		_medal.setTexture(_data->assets.GetTexture("Platinum Medal"));
	}
	else if (_score >= GOLD_SCORE) {
		_medal.setTexture(_data->assets.GetTexture("Gold Medal"));
	}
	else if (_score >= SILVER_SCORE) {
		_medal.setTexture(_data->assets.GetTexture("Silver Medal"));
	}
	else{
		_medal.setTexture(_data->assets.GetTexture("Bronze Medal"));
	}
	_medal.setPosition(175, 465);

}

void GameOverState::HandleInput() {
	sf::Event event;
	while (_data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			_data->window.close();
		}
		if (_data->input.IsSpriteClicked(_retryButton, sf::Mouse::Left, _data->window)) {
			_data->machine.AddState(StateRef(new GameState(_data)));
		}
	}
}

void GameOverState::Update(float dt) {

}

void GameOverState::Draw(float dt) {
	_data->window.clear(sf::Color::Red);
	_data->window.draw(_bgSprite);
	_data->window.draw(_gameOverTitle);
	_data->window.draw(_gameOverContainer);
	_data->window.draw(_retryButton);
	_data->window.draw(_scoreText);
	_data->window.draw(_highscoreText);
	_data->window.draw(_medal);
	_data->window.display();
}