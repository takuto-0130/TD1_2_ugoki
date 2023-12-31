﻿#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Vector2.h"
#include <time.h>
#include <Novice.h>

const int kMapNumHeight = 18;
const int kMapNumWidth = 936;
const int blockSize = 42;
struct MapChipNum {
	int mapData[kMapNumHeight][kMapNumWidth];
};

struct Timedisp {
	int seconds[2];
	int minutes[2];
};

//近くを通ってエネルギーが溜まる時の距離
const float kChargeCollisionDistance = 32.0f;
//近くを通って溜まるエネルギー
const float kCollisionChargeValue = 0.2f;
//ジャンプでたまるエネルギー
const float kJumpChargeValue = 40.0f;

const float kFlyEnergyMax = 360.0f;

struct Player {
	Vector2 pos;
	Vector2 lt;
	Vector2 rt;
	Vector2 lb;
	Vector2 rb;
	int radius;
	int collisionLen;
	float gravity;
	float jump;
	float velocityY;
	float fallSpeedMax;
	int maxLife;
	int life;
	float flySpeedY;
	int maxJumpCount;
	int jumpCount;
	float maxFlyEnergy;
	float flyEnergy;
	bool isFly;
	int dirY;
	bool isJump;
	float kCollisionChargeValue;
	float kJumpChargeValue;
	int getCoin;
	bool isChageArea;
};

void PlayerVertex(Vector2 center, int width, int height, Vector2& lt, Vector2& rt, Vector2& lb, Vector2& rb);

void PlayerInitialize(Player& a);

int mapChipCollision1(MapChipNum& map, int mapNum, Player posX, Player posY, float scroll);

int mapChipCollision2(MapChipNum& map, int mapNum, Player posX, Player posY, float scroll);

void flyEnergyCharge(MapChipNum& map, int mapNum, Player& a, float scroll);

void mapNumChange0(MapChipNum& map, int mapNum, Player posX, Player posY, float scroll);

void PlayerStageCollision(MapChipNum& map, Player& a, float scroll);

void RunMove(Player& player, char* keys, char* preKeys);

void FlightMove(Player& player, char* keys);

void PlayerFlight(Player& now, Player& old, char* keys, char* preKeys);

void TimeDisplay(const int time, Timedisp& a);