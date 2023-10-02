#include "Bird.h"

Bird::Bird(GameDataRef data) : _data(data) {
	_animIndex = 0;
	_animFrames.push_back(_data->assets.GetTexture("Bird Frame 1"));
	_animFrames.push_back(_data->assets.GetTexture("Bird Frame 2"));
	_animFrames.push_back(_data->assets.GetTexture("Bird Frame 3"));
	_animFrames.push_back(_data->assets.GetTexture("Bird Frame 4"));

	_birdSprite.setTexture(_data->assets.GetTexture("Bird Frame 1"));

	_birdSprite.setPosition((_data->window.getSize().x / 4) - (_birdSprite.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_birdSprite.getGlobalBounds().height / 2));

	_birdState = BIRD_STATE_STILL;
	sf::Vector2f origin = sf::Vector2f(_birdSprite.getGlobalBounds().width / 2, _birdSprite.getGlobalBounds().height / 2);
	_birdSprite.setOrigin(origin);
	_rotation = 0;
}

void Bird::Draw() {
	_data->window.draw(_birdSprite);
}

void Bird::Update(float dt) {
	switch (_birdState) {
	case BIRD_STATE_FALL:
		_birdSprite.move(0, GRAVITY * dt);
		_rotation += ROTATION_SPEED * dt;
		if (_rotation > 25.f) {
			_rotation = 25.f;
		}
		_birdSprite.setRotation(_rotation);
		break;
	case BIRD_STATE_FLY:
		_birdSprite.move(0, -FLYING_SPEED * dt);
		_rotation -= ROTATION_SPEED * dt;
		if (_rotation < -25.f) {
			_rotation = -25.f;
		}
		_birdSprite.setRotation(_rotation);
		break;
	default:
		break;
	}

	if (_moveClock.getElapsedTime().asSeconds() > FLY_DURATION) {
		_moveClock.restart();
		_birdState = BIRD_STATE_FALL;
	}
}

void Bird::Tap() {
	_moveClock.restart();
	_birdState = BIRD_STATE_FLY;
}

void Bird::Animate(float dt) {
	if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animFrames.size()) {
		if (_animIndex < _animFrames.size() - 1) {
			_animIndex++;
		}
		else {
			_animIndex = 0;
		}
		_birdSprite.setTexture(_animFrames.at(_animIndex));
		_clock.restart();
	}
}

const sf::Sprite& Bird::GetSprite() const {
	return _birdSprite;
}