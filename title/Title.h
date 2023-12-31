﻿#pragma once
#include <Novice.h>
#include<Vector2.h>
#include <math.h>
#include<time.h>
#define _USE_MATH_DEFINES

class Title {

private:

	Vector2 titlepos_[4];
	Vector2 Space_;
	Vector2 veloclty_[6];
	Vector2 acceleration_[6];
	Vector2 Box[2];
	int Boxstart_;

	Vector2 SpritePos_[3];
	Vector2 Rad_[3];
	Vector2 size_[3];

	Vector2 titlestarts_[2];
	Vector2 titlesends_[2];

	int SpriteWidth_[3];
	int Spriteheight_;

	Vector2 particle_[50];
	Vector2 particleV_[50];
	Vector2 particleA_[50];
	int ballFlag_[50];
	int particletime_;
	int particlecount_[50];
	int particlestart_;

	Vector2 backGroundPos_[2];

	Vector2 chargeBox;
	int Boxsize_;
	int Restart_;
	int BgDraw_ = 1;

	float t_[2];
	float thite_[2];
	int fige_;
	int figeok_;
	int time_;
	int titlecount_[5];
	int timecount_[5];
	int Titleend_;
	int EnterHet_;
	int Voicefiag_[2];
	int VoiceHandle_[2];

	Vector2 titleplayer_;
	Vector2 titleplayerveloclty_;
	Vector2 titleplayeracceleration_;
	int titleplayerfigr_;
	float theta;
	float amplitude_;
	int junpfige_;
	int titleplayertime_;

public:

	int Resources[10] = {
	Novice::LoadTexture("./images/tltie1.png"),
	Novice::LoadTexture("./images/tltie2.png"),
	Novice::LoadTexture("./images/SPACE.png"),
	Novice::LoadTexture("./images/frame.png"),
	Novice::LoadTexture("./images/backGround.png"),
	Novice::LoadTexture("./images/coin.png"),
	Novice::LoadTexture("./images/credit.png"),
	Novice::LoadTexture("./images/esc.png"),
	Novice::LoadTexture("./images/player.png"),
	Novice::LoadTexture("./images/map1.png"),
	};

	int Voice[2] = {
		Voice[0] = Novice::LoadAudio("./Sounds/SE/change.mp3"),
		Voice[1] = Novice::LoadAudio("./Sounds/SE/SceneChange.mp3"),
	};

	void Init() {

		titleplayer_ = { -500.0f,658.0f };
		titleplayerveloclty_ = { 0.0f,0.0f };
		titleplayeracceleration_ = { 0.0f,0.8f };
		titleplayerfigr_ = rand() % 3 + 0;
		junpfige_ = 0;
		titleplayertime_ = 0;
		theta = 4.0f;
		amplitude_ = 70.0f;

		Voicefiag_[0] = -1;
		Voicefiag_[1] = -1;

		titlepos_[0] = { 300,800, };
		titlepos_[1] = { 410,800, };
		titlepos_[2] = { 540,800, };
		titlepos_[3] = { 1600,180, };
		Space_ = { 540, 800 };
		chargeBox = Space_;
		backGroundPos_[0] = { 0.0f, 0.0f };
		backGroundPos_[1] = { 1280.0f, 0.0f };
		Restart_ = 0;
		fige_ = 1;
		Boxsize_ = 0;

		for (int i = 0; i < 10; i++) {

			if (i < 3) {
				veloclty_[i] = { 0.0f,-6.0f };
				acceleration_[i] = { 0.0f,0.3f, };
			}
			if (i < 5) {

				titlecount_[i] = { 0 };
				timecount_[i] = { (i * 10) + 10 };
			}
			if (i >= 3 && i < 7) {
				veloclty_[i] = { 0.0f,0.0f };
				acceleration_[i] = { 0.0f,0.2f };
			}
		}

		Rad_[0] = { (85.0f / 260.0f), (97.0f / 97.0f) };
		Rad_[1] = { (108.0f / 260.0f), (97.0f / 97.0f) };
		Rad_[2] = { (85.0f / 260.0f), (79.0f / 97.0f) };

		size_[0] = { 85, 97 };
		size_[1] = { 106, 97 };
		size_[2] = { 83, 97 };

		SpritePos_[0] = { 0 , 0 };
		SpritePos_[1] = { 97 ,16 };
		SpritePos_[2] = { 200 , 0 };

		SpriteWidth_[0] = 85;
		SpriteWidth_[1] = 106;
		SpriteWidth_[2] = 83;
		Spriteheight_ = 97;

		//---イージング---//
		t_[0] = 0.0f;
		t_[1] = 0.0f;
		thite_[0] = 1.0f / 120.0f;
		thite_[1] = 1.0f / 160.0f;


		titlestarts_[0] = { 1600.0f,180.0f };
		titlesends_[0] = { 500.0f, 180.0f };
		titlestarts_[1] = { 540.0f,800.0f };
		titlesends_[1] = { 540.0f, 450.0f };

		//---パーティクル---//
		particlestart_ = 0;
		for (int i = 0; i < 50; i++) {
			particle_[i] = { -64.0f,0.0f };
			particlecount_[i] = (i * 10) + 5;
			ballFlag_[i] = { 0 };
			particleV_[i] = { 0.0f,5.0f };
			particleA_[i] = { 0.0f,0.03f };
		}
		Box[0] = { -1280,0 };
		Box[1] = { 1280,0 };

		EnterHet_ = 0;
		figeok_ = 0;
		Boxstart_ = 0;
		Titleend_ = 0;
		time_ = 0;
		particletime_ = { 0 };
	};

	//アップデート
	void Update(char* keys, bool& isGameStart, bool isBackTitle, bool& isSceneChange);

	//ドロー
	void Draw();

	//イージング関数
	float EaseInQuad(float t) {
		return t * t;
	}

	float EaseOutCubic(float t) {
		return 1.0f - powf(1.0f - t, 3.0f);
	}

};