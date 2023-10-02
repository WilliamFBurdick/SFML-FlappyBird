#include "GameState.h"

#include <sstream>
#include "Defs.h"
#include <iostream>
#include "GameOverState.h"

GameState::GameState(GameDataRef data) : _data(data) {

}

void GameState::Init() {
	if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_PATH))
		std::cout << "FAILED TO LOAD HIT SOUND" << std::endl;
	if (!_wingSoundBuffer.loadFromFile(WING_SOUND_PATH))
		std::cout << "FAILED TO LOAD WING SOUND" << std::endl;
	if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_PATH))
		std::cout << "FAILED TO LOAD POINT SOUND" << std::endl;

	_hitSound.setBuffer(_hitSoundBuffer);
	_wingSound.setBuffer(_wingSoundBuffer);
	_pointSound.setBuffer(_pointSoundBuffer);


	_data->assets.LoadTexture("Game Background",
		GAME_BG_PATH);
	_data->assets.LoadTexture("Pipe Up",
		PIPE_UP_PATH);
	_data->assets.LoadTexture("Pipe Down",
		PIPE_DOWN_PATH);
	_data->assets.LoadTexture("Land",
		LAND_PATH);
	_data->assets.LoadTexture("Bird Frame 1",
		BIRD_1_PATH);
	_data->assets.LoadTexture("Bird Frame 2",
		BIRD_2_PATH);
	_data->assets.LoadTexture("Bird Frame 3",
		BIRD_3_PATH);
	_data->assets.LoadTexture("Bird Frame 4",
		BIRD_4_PATH);
	_data->assets.LoadTexture("Scoring Pipe", 
		SCORING_PIPE_PATH);
	_data->assets.LoadFont("Flappy Font",
		FLAPPY_FONT_PATH);

	pipe = new Pipe(_data);
	land = new Land(_data);
	bird = new Bird(_data);
	flash = new Flash(_data);
	hud = new HUD(_data);

	_bgSprite.setTexture(this->_data->assets.GetTexture("Game Background"));

	_score = 0;
	hud->UpdateScore(_score);
	_gameState = GameStates::Ready;
}

void GameState::HandleInput() {
	sf::Event event;
	while (_data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			_data->window.close();
		}

		if (_data->input.IsSpriteClicked(_bgSprite, sf::Mouse::Left, _data->window)) {
			if (_gameState != GameStates::GameOver) {
				_gameState = GameStates::Playing;
				bird->Tap();

				_wingSound.play();
			}
		}
	}
}

void GameState::Update(float dt) {
	if (_gameState != GameStates::GameOver) {
		bird->Animate(dt);
		land->MoveLand(dt);
	}

	if (_gameState == GameStates::Playing) {
		pipe->MovePipes(dt);
		pipe->RandomizePipeOffset();

		if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY) {
			pipe->SpawnInvisiblePipe();
			pipe->SpawnBottomPipe();
			pipe->SpawnTopPipe();
			pipe->SpawnScoringPipe();

			clock.restart();
		}

		bird->Update(dt);

		std::vector<sf::Sprite> landSprites = land->GetSprites();
		for (int i = 0; i < landSprites.size(); i++) {
			if (collision.CheckSpriteCollision(bird->GetSprite(), 0.7f, landSprites.at(i), 1.0f)) {
				_gameState = GameStates::GameOver;
				clock.restart();
				_hitSound.play();
			}

		}
		std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();
		for (int i = 0; i < pipeSprites.size(); i++) {
			if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, pipeSprites.at(i), 1.0f)) {
				_gameState = GameStates::GameOver;
				clock.restart();
				_hitSound.play();
			}
		}
	}
	if (_gameState == GameStates::Playing) {
		std::vector<sf::Sprite>& scoringSprites = pipe->GetScoringSprites();
		for (int i = 0; i < scoringSprites.size(); i++) {
			if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoringSprites.at(i), 1.0f)) {
				_score++;
				hud->UpdateScore(_score);
				scoringSprites.erase(scoringSprites.begin() + i);

				_pointSound.play();
			}
		}
	}

	if (_gameState == GameStates::GameOver) {
		flash->Show(dt);
		if (clock.getElapsedTime().asSeconds() > GAME_END_TIME) {
			_data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
		}
	}
}

void GameState::Draw(float dt) {
	_data->window.clear(sf::Color::Red);

	_data->window.draw(_bgSprite);
	pipe->DrawPipes();
	land->DrawLand();
	bird->Draw();

	flash->Draw();

	hud->Draw();

	_data->window.display();
}