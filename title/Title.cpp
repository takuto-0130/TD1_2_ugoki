#include "title.h"

void Title::Update(char* keys, bool& isGameStart, bool isBackTitle, bool& isSceneChange) {

	isSceneChange = 0;

	//---タイトルに戻る処理---// (  未完成　)
	//(仮にZを押したとき)
	if (isBackTitle == 1) {
		Restart_ = 1;
		isGameStart = 0;
		if (Restart_ == 1) {
			Box[0] = { -1280,0 };
			Box[1] = { 1280,0 };
			Boxstart_ = 0;
		}
	}
	//---タイトルの初期化---//
	if (Restart_ == 1 && Box[1].x < 700 && Box[1].x > 630) {
		BgDraw_ = 1;
		isSceneChange = 1;
	}
	if (Restart_ == 1 && Box[1].x > 1400) {
		Init();
	}
	//--------------------------------------//

	//---SPACE---//
	if (Space_.y <= 450.0f) {
		if (keys[DIK_SPACE]) {
			Boxsize_ += 5;
			if (Boxsize_ > 205) {
				Boxsize_ = 205;
				EnterHet_ = 1;
			}
		}
		if (!keys[DIK_SPACE] && (Boxsize_ < 205)) {
			if (Boxsize_ > 0) {
				Boxsize_ -= 5;
			}
			if (Boxsize_ < 0) {
				Boxsize_ = 0;
			}
		}
	}

	//---シーンの移り変わり---//
	if (EnterHet_ == 1 or Restart_ == 1) {
		for (int i = 0; i < 2; i++) {
			if (Boxstart_ == 0) {

				veloclty_[4].x = 40.0f;
				acceleration_[4].x = -0.9f;
				veloclty_[5].x = -40.0f;
				acceleration_[5].x = 0.9f;
				Boxstart_ = 1;
			}
			if (Boxstart_ == 1) {

				veloclty_[i + 4].x += acceleration_[i + 4].x;
				Box[i].x += veloclty_[i + 4].x;
			}
			if (Box[0].x + 1280 > 640) {
				Titleend_ = 1;
				BgDraw_ = 0;
				particlestart_ = 0;
			}

			if (Box[0].x < -1500) {
				veloclty_[4].x = 0.0f;
				acceleration_[0].x = 0.0f;
			}

			if (Box[1].x > 1500) {
				veloclty_[5].x = 0.0f;
				acceleration_[1].x = 0.0f;
				if (BgDraw_ == 0) {
					isGameStart = 1;
				}
			}
		}
	}


	//---タイトル(とべ！)の動き---//
	if (fige_ == 1) {
		time_++;
		for (int i = 0; i < 3; i++) {

			if (titlecount_[i] == 0 && timecount_[i] == time_) {
				if (figeok_ == 0) {
					veloclty_[i].y = -23.0f;
				}
				else {
					veloclty_[i].y = -6.0f;
				}
				acceleration_[i].y = 0.3f;
				titlecount_[i] = 1;

			}


			if (titlecount_[i] == 1) {

				veloclty_[i].y += acceleration_[i].y;
				titlepos_[i].y += veloclty_[i].y;

			}
			if (titlepos_[2].y < 80) {
				figeok_ = 1;

			}

			if (figeok_ == 1) {

				if (titlepos_[i].y > 80) {
					titlepos_[i].y = 80.0f;
					veloclty_[i].y = 0.0f;
					acceleration_[i].y = 0.0f;
					titlecount_[i] = 0;

				}
			}

			if (figeok_ == 0 && time_ > 400) {
				time_ = 0;
			}
			else if (figeok_ == 1 && time_ > 200) {
				time_ = 0;

			}


		}

	}


	//---タイトル(キューブ)とSPACE---//
	if (fige_ == 1 && titlepos_[0].y < 450) {
		t_[0] += thite_[0];
		t_[1] += thite_[1];
		titlepos_[3].x = (1.0f - EaseOutCubic(t_[0])) * titlestarts_[0].x + t_[0] * titlesends_[0].x;
		Space_.y = (1.0f - EaseInQuad(t_[1])) * titlestarts_[1].y + t_[1] * titlesends_[1].y;
	}
	for (int i = 0; i < 2; i++) {
		if (t_[i] > 1.0f) {
			t_[i] = 1.0f;
		}
	}

	if (particlestart_ >= 0) {
		//---パーティクル---//
		particletime_++;
		for (int i = 0; i < 50; i++) {


			if (ballFlag_[i] == 0 && particletime_ == particlecount_[i]) {
				particleV_[i].y = 5.0f;
				particleA_[i].y = 0.03f;
				if (i < 25) {
					//左から
					particle_[i].x = float(rand() % 230 + 1 + 0);
					particle_[i].y = float(rand() % 1 - 300 + -500);
				}
				else if (i >= 25) {
					//右から
					particle_[i].x = float(rand() % 260 + 1 + 950);
					particle_[i].y = float(rand() % 1 - 300 + -800);
				}

				ballFlag_[i] = 1;
			}

			particleV_[i].y += particleA_[i].y;
			particle_[i].y += particleV_[i].y;

			if (particle_[i].y > 720) {
				ballFlag_[i] = 0;
			}

			if (particletime_ >= particlecount_[49]) {
				particletime_ = 0;
			}
		}

	}

	chargeBox.x = Space_.x + 2;
	chargeBox.y = Space_.y + 1;


}


void Title::Draw() {

	//Novice::ScreenPrintf(0, 50, "%d", time_);

	if (BgDraw_ == 1) {

		Novice::DrawSprite(
			0, 0,
			Resources[4],
			1, 1, 0.0f,
			0xFFFFFFFF
		);

		Novice::DrawSprite(
			280 + 25, 15,
			Resources[3],
			1, 1, 0.0f,
			0xFFFFFFFF
		);
	}


	if (Titleend_ == 0) {

		//---パーティクル---//
		for (int i = 0; i < 50; i++) {
			Novice::DrawSprite(
				int(particle_[i].x), int(particle_[i].y),
				Resources[5],
				1, 1,
				0.0f, 0xFFFFFFFF);
		}

		//---とべ！---//
		for (int i = 0; i < 3; i++) {
			Novice::DrawSpriteRect(
				int(titlepos_[i].x) + 25, int(titlepos_[i].y),
				int(SpritePos_[i].x), int(SpritePos_[i].y),
				SpriteWidth_[i], Spriteheight_,
				Resources[0],
				Rad_[i].x, Rad_[i].y,
				0.0f,
				0xFFFFFFFF
			);

		}

		//---キューブ---//
		Novice::DrawSprite(
			int(titlepos_[3].x) + 25, int(titlepos_[3].y),
			Resources[1],
			1, 1, 0.0f,
			0xFFFFFFFF
		);

		//---SpaceのBox---//
		Novice::DrawBox(
			int(chargeBox.x), int(chargeBox.y),
			Boxsize_, 63,
			0.0f,
			0x00FF00BB,
			kFillModeSolid
		);

		//---Space---//
		Novice::DrawSprite(
			int(Space_.x), int(Space_.y),
			Resources[2],
			1, 1, 0.0f,
			0xFFFFFFFF
		);

		if (BgDraw_ == 1) {

			Novice::DrawSprite(
				950, 700,
				creditTex,
				1, 1, 0.0f,
				0xFFFFFFFF
			);
			Novice::DrawSprite(
				30, 20,
				escTex,
				1, 1, 0.0f,
				0xFFFFFFFF
			);
		}
	}


	for (int i = 0; i < 2; i++) {
		Novice::DrawBox(
			int(Box[i].x), int(Box[i].y),
			1280, 756,
			0.0f,
			BLACK,
			kFillModeSolid
		);

	}

}