#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Vector2.h"
#include <time.h>
#include "player/player.h"
#include "particle/flying/FlyingEmitter.h"
#include "particle/running/RunningEmitter.h"
#include "particle/playerDead/PlayerDeadEmitter.h"
#include "particle/clearParticle/ClearEmitter.h"
#include "particle/jump/jumpEnergyEmitter.h"
#include "particle/BackGroundParticle/BackGroundEmitter.h"
#include "particle/GetCoin/GetCoinEmitter.h"
#include "particle/ModeChange/ModeChangeEmitter.h"

// キー入力結果を受け取る箱
char keys[256] = { 0 };
char preKeys[256] = { 0 };

const char kWindowTitle[] = "TD1_2回目_プロトタイプ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 756);

	MapChipNum mapCollision;
	MapChipNum mapDisplay;
	MapChipNum saveMapCollision;
	int mapNum = 0;
	
	FILE* fp;//ファイルポインタを宣言
	errno_t error;//ファイルが読み取れているかどうか
	error = fopen_s(&fp, "./mapDisplay.csv", "r");
	if (error != 0) {//ファイルが読み取れていないときに動かさないようにする
		return 1;
	}
	else {
		while (mapNum < kMapNumHeight * kMapNumWidth && fscanf_s(fp, "%d,", &mapDisplay.mapData[mapNum / kMapNumWidth][mapNum % kMapNumWidth]) != EOF) {
			mapNum++;
		}
	}
	fclose(fp);//ファイルを閉じる

	mapNum = 0;
	error = fopen_s(&fp, "./mapCollision.csv", "r");
	if (error != 0) {//ファイルが読み取れていないときに動かさないようにする
		return 1;
	}
	else {
		while (mapNum < kMapNumHeight * kMapNumWidth && fscanf_s(fp, "%d,", &mapCollision.mapData[mapNum / kMapNumWidth][mapNum % kMapNumWidth]) != EOF) {
			mapNum++;
		}
	}
	fclose(fp);//ファイルを閉じる

	saveMapCollision = mapCollision;

	Player player;
	PlayerInitialize(player);
	Player oldPlayer = player;
	Player savePlayer = player;
	Player saveOldPlayer = oldPlayer;

	const float kRunScrollSpeed = 5;

	const float kFlightScrollSpeed = 7;

	float scroll = 0;
	float saveScroll = scroll;

	int block = Novice::LoadTexture("white1x1.png");

	bool isCheckPoint = 0;

	bool isClear = 0;

	FlyingEmitter flyingEmitter;
	RunningEmitter runningEmitter;
	PlayerDeadEmitter playerDeadEmitter;
	ClearEmitter clearEmitter;
	JumpEnergyEmitter jumpEnergyEmitter;
	BackGroundEmitter backGroundEmitter;
	GetCoinEmitter getCoinEmitter;
	ModeChangeEmitter modeChangeEmitter;

	Vector2 playerWorldPos = { player.pos.x + scroll, player.pos.y };
	Vector2 flightPlayerMS = { kFlightScrollSpeed, 0 };

	Vector2 gaugePos = { 100,((250 * (player.maxFlyEnergy / 600.0f) - 8) * player.flyEnergy / player.maxFlyEnergy) };

	enum Scene {
		TITLE,
		GAME
	};
	int scene = TITLE;
	
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (scene) {
		case TITLE:
			if (keys[DIK_RETURN])
			{
				scene = GAME;
				backGroundEmitter.Update(playerWorldPos);
			}
			break;
		case GAME:
			if (preKeys[DIK_R] == 0 && keys[DIK_R] != 0) {
				isCheckPoint = 0;
				isClear = 0;
				PlayerInitialize(player);
				oldPlayer = player;
				scroll = 0;
				savePlayer = player;
				saveOldPlayer = oldPlayer;
				saveScroll = scroll;
				mapNum = 0;
				error = fopen_s(&fp, "./mapCollision.csv", "r");
				if (error != 0) {
					return 1;
				}
				else {
					while (mapNum < kMapNumHeight * kMapNumWidth && fscanf_s(fp, "%d,", &mapCollision.mapData[mapNum / kMapNumWidth][mapNum % kMapNumWidth]) != EOF) {
						mapNum++;
					}
				}
				fclose(fp);
				saveMapCollision = mapCollision;
			}

			if (isClear == 0)
			{
				if (player.life > 0)
				{
					oldPlayer = player;
					if (player.isFly == 0)
					{
						RunMove(player, keys, preKeys);
						//スクロール速度
						scroll += kRunScrollSpeed;
						runningEmitter.Update({ player.pos.x - player.radius, player.pos.y + 14 }, player.jumpCount);
					}
					else
					{
						FlightMove(player, keys);
						//スクロール速度
						scroll += kFlightScrollSpeed;
						flyingEmitter.Update(player.pos);
					}

					flightPlayerMS = { kFlightScrollSpeed, player.velocityY };

					gaugePos = { ((250 * (player.maxFlyEnergy / 600.0f) - 8) * player.flyEnergy / player.maxFlyEnergy),669 };
					jumpEnergyEmitter.EmitGoal(gaugePos);

					player.pos.y += player.velocityY;

					PlayerVertex(oldPlayer.pos, player.collisionLen, player.collisionLen, oldPlayer.lt, oldPlayer.rt, oldPlayer.lb, oldPlayer.rb);
					PlayerVertex(player.pos, player.collisionLen, player.collisionLen, player.lt, player.rt, player.lb, player.rb);

					if (mapChipCollision1(mapCollision, 5, player, player, scroll))
					{
						getCoinEmitter.Emit(playerWorldPos);
					}

					PlayerStageCollision(mapCollision, player, scroll);

					if (mapChipCollision1(mapCollision, 11, player, player, scroll) == 1) {
						isCheckPoint = 1;
						saveMapCollision = mapCollision;
						savePlayer = player;
						saveOldPlayer = oldPlayer;
						saveScroll = scroll;
					}
					if (mapChipCollision1(mapCollision, 400, player, player, scroll) == 1) {
						isClear = 1;
					}


					//======================================
					//デバッグ用ゲージマックス
					if (keys[DIK_9]) {
						player.flyEnergy = player.maxFlyEnergy;
					}

					// プレイヤーの飛行
					PlayerFlight(player, oldPlayer, keys, preKeys);
					if (player.isFly == 1 && oldPlayer.isFly == 0) {
						modeChangeEmitter.Emit(playerWorldPos);
					}

					//空中でジャンプできない||ジャンプ回数1減少
					if (mapChipCollision2(mapCollision, 1, player, player, scroll) == 0 &&
						mapChipCollision2(mapCollision, 2, player, player, scroll) == 0 &&
						player.jumpCount == 0)//後で床の判定に変える
					{
						player.jumpCount = 1;
					}
				}
				else
				{
					if (keys[DIK_RETURN])
					{
						mapCollision = saveMapCollision;
						player = savePlayer;
						oldPlayer = saveOldPlayer;
						scroll = saveScroll;
						player.flyEnergy = 0;
						player.isFly = 0;
						player.velocityY = 0;
					}
				}
				if (player.life <= 0)
				{
					player.pos = oldPlayer.pos;
				}
				if (oldPlayer.life > 0 && player.life <= 0)
				{
					playerDeadEmitter.Emit(player.pos);
				}
				jumpEnergyEmitter.Update(player.pos, player.isJump, player.life);
				playerDeadEmitter.Update();
				if (player.isFly == 0)
					PlayerVertex(player.pos, player.collisionLen, player.collisionLen, player.lt, player.rt, player.lb, player.rb);
				oldPlayer = player;
				backGroundEmitter.Update(playerWorldPos);
				playerWorldPos = { player.pos.x + scroll, player.pos.y };
			}
			else
			{
				if (player.pos.x < 1320) {
					player.pos.x += kRunScrollSpeed;
				}
				clearEmitter.Update();
				PlayerVertex(player.pos, player.collisionLen, player.collisionLen, player.lt, player.rt, player.lb, player.rb);
				backGroundEmitter.Update(playerWorldPos);
			}
			getCoinEmitter.Update();
			modeChangeEmitter.Update(flightPlayerMS);
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		for (int y = 0; y < kMapNumHeight; y++)
		{
			for (int x = 0; x < kMapNumWidth; x++)
			{
				if (((x * blockSize) + (blockSize * 3)) > 0 + scroll && ((x * blockSize) - blockSize) < 1280 + scroll)
				{
					//壁と天井
					if (mapCollision.mapData[y][x] == 1)
					{
						Novice::DrawSprite((x * blockSize) - int(scroll), y * blockSize, block, 41.0f, 41.0f, 0.0f, 0x000000FF);
					}
					//
					if (mapCollision.mapData[y][x] == 2)
					{
						Novice::DrawSprite((x * blockSize) - int(scroll), y * blockSize, block, 41.0f, 41.0f, 0.0f, 0xFFFF99FF);
					}
					//
					if (mapCollision.mapData[y][x] == 5)
					{
						Novice::DrawSprite((x * blockSize) - int(scroll), y * blockSize, block, 41.0f, 41.0f, 0.0f, 0xFFFF00FF);
					}
					//
					if (mapCollision.mapData[y][x] == 11)
					{
						Novice::DrawSprite((x * blockSize) - int(scroll), y * blockSize, block, 41.0f, 41.0f, 0.0f, 0x99FF99FF);
					}
					//
					if (mapCollision.mapData[y][x] == 400)
					{
						Novice::DrawSprite((x * blockSize) - int(scroll), y * blockSize, block, 41.0f, 41.0f, 0.0f, 0x444444FF);
					}
				}
			}
		}

		backGroundEmitter.Draw(int(scroll));

		if(player.life > 0)
		{
			Novice::DrawQuad(int(player.lt.x), int(player.lt.y), int(player.rt.x + 1), int(player.rt.y), int(player.lb.x), int(player.lb.y + 1), int(player.rb.x + 1), int(player.rb.y + 1), 1, 1, 1, 1, block, 0xFFFFFFFF);
			
			if(isClear == 0)
			{
				if (player.isFly == 1)
				{
					Novice::DrawBox(int(player.pos.x - player.radius - kChargeCollisionDistance), int(player.pos.y - player.radius - kChargeCollisionDistance), int(player.collisionLen + kChargeCollisionDistance * 2), int(player.collisionLen + kChargeCollisionDistance * 2), 0.0f, 0x0000FFFF, kFillModeWireFrame);
					flyingEmitter.Draw();
				}
				else
				{
					runningEmitter.Draw();
					jumpEnergyEmitter.Draw();
				}

				Novice::DrawBox(20, 654, int(250 * (player.maxFlyEnergy / 600.0f)), 30, 0.0f, 0xFFFFFFFF, kFillModeSolid);

				Novice::DrawBox(24, 658, int((250 * (player.maxFlyEnergy / 600.0f) - 8) * player.flyEnergy / player.maxFlyEnergy), 22, 0.0f, 0xFF0000FF, kFillModeSolid);
			}
		}
		else
		{
			playerDeadEmitter.Draw();
		}

		getCoinEmitter.Draw(int(scroll - 21));
		modeChangeEmitter.Draw(int(scroll));

		if (isClear == 1) {
			clearEmitter.Draw();
		}

		//Novice::ScreenPrintf(20, 45, "1:AUTO  2:CANCEL  3:FLIGHT  4:kikakushonoyatu");
		Novice::ScreenPrintf(20, 70, "RUN:SPACE(JUMP)  FLIGHT:W(UP) S(DWON)");
		Novice::ScreenPrintf(20, 95, "SHIFT:ModeChange");
		Novice::ScreenPrintf(20, 175, "coin = %d", player.getCoin);
		Novice::ScreenPrintf(20, 200, "isJump = %d", player.isJump);
		Novice::ScreenPrintf(20, 225, "%.02f", player.maxFlyEnergy);


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
