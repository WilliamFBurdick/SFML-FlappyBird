#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024

#define SPLASH_STATE_SHOWTIME 3.0

#define SPLASH_SCENE_BACKGROUND_PATH "../Resources/res/SplashBackground.png"
#define MAIN_MENU_BG_PATH "../Resources/res/sky.png"
#define GAME_TITLE_PATH "../Resources/res/title.png"
#define PLAY_BUTTON_PATH "../Resources/res/PlayButton.png"
#define GAME_BG_PATH "../Resources/res/sky.png"
#define GAME_OVER_BG_PATH "../Resources/res/sky.png"
#define PIPE_UP_PATH "../Resources/res/PipeUp.png"
#define PIPE_DOWN_PATH "../Resources/res/PipeDown.png"
#define LAND_PATH "../Resources/res/Land.png"
#define BIRD_1_PATH "../Resources/res/bird-01.png"
#define BIRD_2_PATH "../Resources/res/bird-02.png"
#define BIRD_3_PATH "../Resources/res/bird-03.png"
#define BIRD_4_PATH "../Resources/res/bird-04.png"
#define SCORING_PIPE_PATH "../Resources/res/InvisibleScoringPipe.png"

#define FLAPPY_FONT_PATH "../Resources/fonts/FlappyFont.ttf"

#define GAME_OVER_TITLE_PATH "../Resources/res/Game-Over-Title.png"
#define GAME_OVER_BODY_PATH "../Resources/res/Game-Over-Body.png"

#define BRONZE_MEDAL_PATH "../Resources/res/Bronze-Medal.png"
#define SILVER_MEDAL_PATH "../Resources/res/Silver-Medal.png"
#define GOLD_MEDAL_PATH "../Resources/res/Gold-Medal.png"
#define PLATINUM_MEDAL_PATH "../Resources/res/Platinum-Medal.png"

#define HIT_SOUND_PATH "../Resources/audio/Hit.wav"
#define POINT_SOUND_PATH "../Resources/audio/Point.wav"
#define WING_SOUND_PATH "../Resources/audio/Wing.wav"

#define PIPE_MOVE_SPEED 250.f
#define PIPE_SPAWN_FREQUENCY 1.f

#define BIRD_ANIMATION_DURATION 0.4f

#define BIRD_STATE_STILL 1
#define BIRD_STATE_FALL 2
#define BIRD_STATE_FLY 3

#define GRAVITY 350.f
#define FLYING_SPEED 350.f

#define FLY_DURATION 0.25f

#define ROTATION_SPEED 100.f

enum GameStates {
	Ready,
	Playing,
	GameOver
};

#define FLASH_SPEED 1500.f

#define GAME_END_TIME 1.5f

#define BRONZE_SCORE 0
#define SILVER_SCORE 5
#define GOLD_SCORE 25
#define PLATINUM_SCORE 100