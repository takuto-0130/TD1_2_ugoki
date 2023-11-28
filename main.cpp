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
#include "particle/CheckPoint/CheckPointEmitter.h"
#include "particle/flying/flyingEnergyEmitter.h"

// キー入力結果を受け取る箱
char keys[256] = { 0 };
char preKeys[256] = { 0 };

const char kWindowTitle[] = "1206_とべ！キューブ";

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
	int bgScroll = 0;

	//int block = Novice::LoadTexture("white1x1.png");
	int map1Tex = Novice::LoadTexture("./images/map1.png");
	int bgTex = Novice::LoadTexture("./images/backGround.png");
	int playerRunTex = Novice::LoadTexture("./images/playerRunning.png");
	int playerFlyTex = Novice::LoadTexture("./images/player.png");
	int playerTex = playerRunTex;
	int checkPointTex = Novice::LoadTexture("../images/checkPoint.png");
	int coinTex = Novice::LoadTexture("./images/coin.png");
	int energyBlockTex = Novice::LoadTexture("./images/energyBlock.png");
	int titleTex = Novice::LoadTexture("./images/title.png");
	int resultTex = Novice::LoadTexture("./images/result.png");
	int goalTex = Novice::LoadTexture("./images/goal.png");
	int retryTex = Novice::LoadTexture("./images/retry.png");
	int numberTex = Novice::LoadTexture("./images/number.png");
	int colonTex = Novice::LoadTexture("./images/colon.png");
	int downTex = Novice::LoadTexture("./images/down.png");
	int upTex = Novice::LoadTexture("./images/up.png");
	int poseButtonTex = Novice::LoadTexture("./images/poseButton.png");
	int poseRetrunTex = Novice::LoadTexture("./images/posesaisei.png");
	int playerChangeTex = Novice::LoadTexture("./images/playerChange.png");
	int gaugeTex = Novice::LoadTexture("./images/gauge.png");
	int posegamenTex = Novice::LoadTexture("./images/posegamen.png");
	int modoruTex = Novice::LoadTexture("./images/modoru.png");
	int tudukeruTex = Novice::LoadTexture("./images/tudukeru.png");
	


	int checkPointSEHandle = Novice::LoadAudio("./Sounds/SE/checkPoint.mp3");
	int checkPointSE = -1;
	bool isCheckPointSE = 0;

	int jumpSEHandle = Novice::LoadAudio("./Sounds/SE/jump.mp3");
	int jumpSE = -1;

	int getCoinSEHandle = Novice::LoadAudio("./Sounds/SE/getCoin.mp3");
	int getCoinSE = -1;
	bool isGetCoinSE = 0;

	int modeChangeSEHandle = Novice::LoadAudio("./Sounds/SE/modeChange.mp3");
	int modeChangeSE = -1;
	bool isModeChangeSE = 0;

	int gaugeIncreaseSEHandle = Novice::LoadAudio("./Sounds/SE/gaugeIncrease.mp3");
	int gaugeIncreaseSE = -1;
	int gaugeSETimer = 0;
	bool isGaugeIncreaseSE = 0;

	int playerDeadSEHandle = Novice::LoadAudio("./Sounds/SE/playerDead.mp3");
	int playerDeadSE = -1;
	bool isPlayerDeadSE = 0;

	int poseSEHandle = Novice::LoadAudio("./Sounds/SE/pose.mp3");
	int poseSE = -1;
	bool isPoseSE = 0;

	int selectSEHandle = Novice::LoadAudio("./Sounds/SE/select.mp3");
	int selectSE = -1;
	bool isSelectSE = 0;


	bool isCheckPoint = 0;
	bool isOldCheckPoint = isCheckPoint;

	bool isClear = 0;

	int inGameTime = 0;

	int pauseMenu = 0;
	bool isPause = 0;
	bool isEnd = 0;

	int byou = int(inGameTime / 60) % 60;
	int fun = int(inGameTime / 60) / 60;

	FlyingEmitter flyingEmitter;
	RunningEmitter runningEmitter;
	PlayerDeadEmitter playerDeadEmitter;
	ClearEmitter clearEmitter;
	JumpEnergyEmitter jumpEnergyEmitter;
	FlyingEnergyEmitter flyingEnergyEmitter;
	BackGroundEmitter backGroundEmitter;
	GetCoinEmitter getCoinEmitter;
	ModeChangeEmitter modeChangeEmitter;
	CheckPointEmitter checkPointEmitter;

	Vector2 playerWorldPos = { player.pos.x + scroll, player.pos.y };
	Vector2 flightPlayerMS = { kFlightScrollSpeed, 0 };

	Timedisp time;

	TimeDisplay(inGameTime, time);

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

		isPoseSE = 0;
		isCheckPointSE = 0;
		isGetCoinSE = 0;
		isModeChangeSE = 0;
		isGaugeIncreaseSE = 0;
		isPlayerDeadSE = 0;
		isSelectSE = 0;

		switch (scene) {
		case TITLE:
			isPause = 0;
			inGameTime = 0;
			isPause = 0;
			if (keys[DIK_SPACE] !=0 && preKeys[DIK_SPACE] == 0)
			{
				scene = GAME;
				backGroundEmitter.Update(playerWorldPos);
			}
			if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
				isEnd = 1;
			}
			break;
		case GAME:
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0 && isClear == 1 && player.pos.x >= 1320) {
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
				mapNum = 0;
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
				saveMapCollision = mapCollision;
				playerTex = playerRunTex;
				scene = TITLE;
			}

			if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0 && isClear == 0) {
				if(isPause == 1)
				{
					isPause = 0;
					isPoseSE = 1;
				}
				else {
					isPause = 1;
					isPoseSE = 1;
				}
			}

			if (isPause == 1) {
				if (preKeys[DIK_W] == 0 && keys[DIK_W] != 0 || preKeys[DIK_UP] == 0 && keys[DIK_UP] != 0) {
					pauseMenu = 0;
					isSelectSE = 1;
				}
				if (preKeys[DIK_S] == 0 && keys[DIK_S] != 0 || preKeys[DIK_DOWN] == 0 && keys[DIK_DOWN] != 0) {
					pauseMenu = 1;
					isSelectSE = 1;
				}
				if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
					if (pauseMenu == 0) {
						isPause = 0;
						isPoseSE = 1;
					}
					else {
						isPoseSE = 1;
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
						mapNum = 0;
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
						saveMapCollision = mapCollision;
						playerTex = playerRunTex;
						scene = TITLE;
					}
				}
			}

			if(isPause == 0)
			{
				if (isClear == 0)
				{
					isOldCheckPoint = isCheckPoint;
					isCheckPoint = 0;
					if (player.life > 0)
					{
						inGameTime++;
						oldPlayer = player;
						if (player.isFly == 0)
						{
							RunMove(player, keys, preKeys);
							//スクロール速度
							scroll += kRunScrollSpeed;
							runningEmitter.Update({ player.pos.x - player.radius, player.pos.y + 14 }, player.jumpCount);
							playerTex = playerRunTex;
						}
						else
						{
							FlightMove(player, keys);
							//スクロール速度
							scroll += kFlightScrollSpeed;
							flyingEmitter.Update(player.pos);
							playerTex = playerFlyTex;
						}
						bgScroll = int(scroll / 5) % 1280;
						flightPlayerMS = { kFlightScrollSpeed, player.velocityY };

						gaugePos = { 48, float(535 - int((150 * (player.maxFlyEnergy / 360.0f)) * player.flyEnergy / player.maxFlyEnergy)) };
						jumpEnergyEmitter.EmitGoal(gaugePos);
						flyingEnergyEmitter.EmitGoal(gaugePos);

						player.pos.y += player.velocityY;

						PlayerVertex(oldPlayer.pos, player.collisionLen, player.collisionLen, oldPlayer.lt, oldPlayer.rt, oldPlayer.lb, oldPlayer.rb);
						PlayerVertex(player.pos, player.collisionLen, player.collisionLen, player.lt, player.rt, player.lb, player.rb);

						if (mapChipCollision1(mapCollision, 5, player, player, scroll))
						{
							getCoinEmitter.Emit(playerWorldPos);
							isGetCoinSE = 1;
						}

						PlayerStageCollision(mapCollision, player, scroll);

						if (mapChipCollision1(mapCollision, 11, player, player, scroll) == 1) {
							isCheckPoint = 1;
							saveMapCollision = mapCollision;
							savePlayer = player;
							saveOldPlayer = oldPlayer;
							saveScroll = scroll;
						}
						if (isCheckPoint == 1 && isOldCheckPoint == 0) {
							checkPointEmitter.Emit(playerWorldPos);
							isCheckPointSE = 1;
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
							isModeChangeSE = 1;
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
						if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE]!= 0)
						{
							mapCollision = saveMapCollision;
							player = savePlayer;
							oldPlayer = saveOldPlayer;
							scroll = saveScroll;
							//player.flyEnergy = 0;
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
						isPlayerDeadSE = 1;
					}
					flyingEnergyEmitter.Update(player.pos, player.isChageArea, player.life);
					playerDeadEmitter.Update();
					checkPointEmitter.Update();
					if (player.isFly == 0)
						PlayerVertex(player.pos, player.collisionLen, player.collisionLen, player.lt, player.rt, player.lb, player.rb);
					oldPlayer = player;
					backGroundEmitter.Update(playerWorldPos);
					playerWorldPos = { player.pos.x + scroll, player.pos.y };
					if (player.isJump == 1) {
						gaugeSETimer++;
					}
					if (gaugeSETimer > 0) {
						gaugeSETimer++;
					}
					if (gaugeSETimer >= 11) {
						gaugeSETimer = 0;
						isGaugeIncreaseSE = 1;
					}
				}
				else
				{
					player.isFly = 0;
					if (player.pos.x < 1320) {
						player.pos.x += kRunScrollSpeed;
						player.velocityY += player.gravity;
						if (player.velocityY > player.fallSpeedMax)
						{
							player.velocityY = player.fallSpeedMax;
						}
						player.pos.y += player.velocityY;
						PlayerVertex(oldPlayer.pos, player.collisionLen, player.collisionLen, oldPlayer.lt, oldPlayer.rt, oldPlayer.lb, oldPlayer.rb);
						PlayerVertex(player.pos, player.collisionLen, player.collisionLen, player.lt, player.rt, player.lb, player.rb);
						PlayerStageCollision(mapCollision, player, scroll);
						if (player.velocityY == 0) {
							player.jumpCount = 0;
						}
						runningEmitter.Update({ player.pos.x - player.radius, player.pos.y + 14 }, player.jumpCount);
					}


					clearEmitter.Update();
					PlayerVertex(player.pos, player.collisionLen, player.collisionLen, player.lt, player.rt, player.lb, player.rb);
					backGroundEmitter.Update(playerWorldPos);
				}
				jumpEnergyEmitter.Update(player.pos, player.isJump, player.life, isClear);
				getCoinEmitter.Update();
				modeChangeEmitter.Update(flightPlayerMS);
				byou = int(inGameTime / 60) % 60;
				fun = int(inGameTime / 60) / 60;
				TimeDisplay(inGameTime, time);
			}
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::DrawSprite(0 - bgScroll, 0, bgTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		Novice::DrawSprite(1280 - bgScroll, 0, bgTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

		for (int y = 0; y < kMapNumHeight; y++)
		{
			for (int x = 0; x < kMapNumWidth; x++)
			{
				if (((x * blockSize) + (blockSize * 3)) > 0 + scroll && ((x * blockSize) - blockSize) < 1280 + scroll)
				{
					//壁と天井
					if (mapCollision.mapData[y][x] == 1)
					{
						Novice::DrawSprite((x * blockSize) - int(scroll), y * blockSize, map1Tex, 1.0f, 1.0f, 0.0f, 0x555566FF);
					}
					//
					if (mapCollision.mapData[y][x] == 2)
					{
						Novice::DrawSprite((x * blockSize) - int(scroll), y * blockSize, energyBlockTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
					}
					//coin
					if (mapCollision.mapData[y][x] == 5)
					{
						Novice::DrawSprite((x * blockSize) - int(scroll), y * blockSize, coinTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
					}
					//goal
					if (mapDisplay.mapData[y][x] == 11)
					{
						Novice::DrawSprite((x * blockSize) - int(scroll), y * blockSize - blockSize, checkPointTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
					}
					//
					if (mapCollision.mapData[y][x] == 400)
					{
						Novice::DrawSprite((x * blockSize) - int(scroll), y * blockSize, goalTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
					}
				}
			}
		}
		if (isClear == 0 && scene != TITLE)
		{
			Novice::DrawBox(20, 654, int(500 * (player.maxFlyEnergy / 600.0f)), 30, 0.0f, 0xFFFFFFFF, kFillModeSolid);
			Novice::DrawBox(24, 658, int((500 * (player.maxFlyEnergy / 600.0f) - 8)* player.flyEnergy / player.maxFlyEnergy), 22, 0.0f, 0xFFAA88FF, kFillModeSolid);
			for(int i = 0; i < 2; i++)
			{
				Novice::DrawSpriteRect(1180 + 40*i, 0, 64 * time.seconds[i], 0, 64, 64, numberTex, 1.0f/12.0f, 1.0f/1.2f, 0.0f, 0xFFFFFFFF);
			}
			for (int i = 0; i < 2; i++)
			{
				Novice::DrawSpriteRect(1090 + 40 * i, 0, 64 * time.minutes[i], 0, 64, 64, numberTex, 1.0f / 12.0f, 1.0f / 1.2f, 0.0f, 0xFFFFFFFF);
			}
			Novice::DrawSprite(1155, 0, colonTex, 1.0f / 1.2f, 1.0f / 1.2f, 0.0f, 0xFFFFFFFF);
		}


		backGroundEmitter.Draw(int(scroll));

		if(player.life > 0)
		{
			if (player.isFly == 1)
			{
				flyingEmitter.Draw();

			}
			Novice::DrawQuad(int(player.lt.x), int(player.lt.y), int(player.rt.x + 1), int(player.rt.y), int(player.lb.x), int(player.lb.y + 1), int(player.rb.x + 1), int(player.rb.y + 1), 0, 0, 42, 42, playerTex, 0xFFFFFFFF);
			
			if(scene != TITLE)
			{
				if (player.isFly == 1)
				{
					//Novice::DrawBox(int(player.pos.x - player.radius - kChargeCollisionDistance), int(player.pos.y - player.radius - kChargeCollisionDistance), int(player.collisionLen + kChargeCollisionDistance * 2), int(player.collisionLen + kChargeCollisionDistance * 2), 0.0f, 0x0000FFFF, kFillModeWireFrame);
					flyingEnergyEmitter.Draw();
				}
				else
				{
					if(player.pos.x < 1300)
					{
						runningEmitter.Draw();
					}
					jumpEnergyEmitter.Draw();
				}
			}
		}
		else
		{
			playerDeadEmitter.Draw();
		}

		getCoinEmitter.Draw(int(scroll - 21));
		checkPointEmitter.Draw(int(scroll));
		modeChangeEmitter.Draw(int(scroll));

		if (isClear == 1) {
			clearEmitter.Draw();
		}

		if (isClear == 0 && scene != TITLE) {
			if(player.isFly == 1 || player.flyEnergy == player.maxFlyEnergy)
			{
				Novice::DrawSprite(20, 561, playerChangeTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			}
			else
			{
				Novice::DrawSprite(20, 561, playerChangeTex, 1.0f, 1.0f, 0.0f, 0x555555FF);
			}
			Novice::DrawSprite(186, 540, upTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			if(player.isFly == 1)
			{
				Novice::DrawSprite(186, 624, downTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			}
			else
			{
				Novice::DrawSprite(186, 624, downTex, 1.0f, 1.0f, 0.0f, 0x555555FF);
			}
			Novice::DrawSprite(20, 20, poseButtonTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			Novice::DrawBox(48, 535 - int(150 * (player.maxFlyEnergy / 360.0f)), 30, int(150 * (player.maxFlyEnergy / 360.0f)), 0.0f, 0x777777FF, kFillModeSolid);
			Novice::DrawBox(48, 535 - int((150 * (player.maxFlyEnergy / 360.0f)) * player.flyEnergy / player.maxFlyEnergy), 30, int((150 * (player.maxFlyEnergy / 360.0f))* player.flyEnergy / player.maxFlyEnergy), 0.0f, 0xFFA044FF, kFillModeSolid);
			Novice::DrawSprite(44, 181, gaugeTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		}

		if (isPause == 1) {
			Novice::DrawSprite(0, 0, posegamenTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF); 
			if(pauseMenu == 0)
			{
				Novice::DrawSprite(448, 315, tudukeruTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
				Novice::DrawSprite(448, 420, modoruTex, 1.0f, 1.0f, 0.0f, 0x555555FF);
			}
			else
			{
				Novice::DrawSprite(448, 315, tudukeruTex, 1.0f, 1.0f, 0.0f, 0x555555FF);
				Novice::DrawSprite(448, 420, modoruTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			}
			Novice::DrawSprite(20, 20, poseRetrunTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		}

		//Novice::ScreenPrintf(20, 45, "1:AUTO  2:CANCEL  3:FLIGHT  4:kikakushonoyatu");
		/*Novice::ScreenPrintf(20, 70, "RUN:SPACE(JUMP)  FLIGHT:W(UP) S(DWON)");
		Novice::ScreenPrintf(20, 95, "SHIFT:ModeChange");
		Novice::ScreenPrintf(20, 175, "coin = %d", player.getCoin);
		Novice::ScreenPrintf(20, 200, "isJump = %d", player.isJump);
		Novice::ScreenPrintf(20, 225, "%.02f", player.maxFlyEnergy);
		Novice::ScreenPrintf(20, 250, "time = %d", inGameTime);
		Novice::ScreenPrintf(20, 275, "%dminutes:%dseconds", fun, byou);*/

		if (isCheckPointSE == 1) {
			if (!Novice::IsPlayingAudio(checkPointSE) || checkPointSE == -1) {
				checkPointSE = Novice::PlayAudio(checkPointSEHandle, 0, 0.5f);
			}
		}

		if (player.isJump == 1) {
			Novice::StopAudio(jumpSE);
			if (!Novice::IsPlayingAudio(jumpSE) || jumpSE == -1) {
				jumpSE = Novice::PlayAudio(jumpSEHandle, 0, 0.6f);
			}
		}

		if (isGaugeIncreaseSE == 1) {
			Novice::StopAudio(gaugeIncreaseSE);
			if (!Novice::IsPlayingAudio(gaugeIncreaseSE) || gaugeIncreaseSE == -1) {
				gaugeIncreaseSE = Novice::PlayAudio(gaugeIncreaseSEHandle, 0, 0.6f);
			}
		}

		if (isGetCoinSE == 1) {
			Novice::StopAudio(getCoinSE);
			if (!Novice::IsPlayingAudio(getCoinSE) || getCoinSE == -1) {
				getCoinSE = Novice::PlayAudio(getCoinSEHandle, 0, 0.5f);
			}
		}

		if (isModeChangeSE == 1) {
			Novice::StopAudio(modeChangeSE);
			if (!Novice::IsPlayingAudio(modeChangeSE) || modeChangeSE == -1) {
				modeChangeSE = Novice::PlayAudio(modeChangeSEHandle, 0, 0.6f);
			}
		}

		if (isPlayerDeadSE == 1) {
			Novice::StopAudio(playerDeadSE);
			if (!Novice::IsPlayingAudio(playerDeadSE) || playerDeadSE == -1) {
				playerDeadSE = Novice::PlayAudio(playerDeadSEHandle, 0, 0.6f);
			}
		}

		if (isPoseSE == 1) {
			Novice::StopAudio(poseSE);
			if (!Novice::IsPlayingAudio(poseSE) || poseSE == -1) {
				poseSE = Novice::PlayAudio(poseSEHandle, 0, 0.6f);
			}
		}

		if (isSelectSE == 1) {
			Novice::StopAudio(selectSE);
			if (!Novice::IsPlayingAudio(selectSE) || selectSE == -1) {
				selectSE = Novice::PlayAudio(selectSEHandle, 0, 0.6f);
			}
		}

		if (isClear == 0 && player.life == 0) {
			Novice::DrawSprite(0, 0, retryTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		}

		if (isClear == 1 && player.pos.x >= 1240) {
			Novice::DrawSprite(0, 0, resultTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		}

		if (scene == TITLE) {
			Novice::DrawSprite(0, 0, titleTex, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		}


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (isEnd == 1) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
