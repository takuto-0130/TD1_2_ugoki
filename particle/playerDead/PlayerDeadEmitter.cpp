#include "PlayerDeadEmitter.h"
#include "particle/util/Util.h"

PlayerDeadEmitter::PlayerDeadEmitter()
{
}

PlayerDeadEmitter::~PlayerDeadEmitter()
{
}

void PlayerDeadEmitter::Update()
{
	// パーティクル全ての更新処理を呼ぶ
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update();

		// DelFlagがtrueだったら
		if (itr->GetDelFlag()) {
			itr = particleList.erase(itr);
		} else {
			itr++; // eraseしなかった場合のみイテレーターをインクリメント
		}
	}

	// 広がる円の更新処理
	circleRadius_ += 8;

	if (circleAlpha_ > 0) {
		circleAlpha_ -= 12;
	} 

	if (circleAlpha_ <= 0) {
		circleDel_ = true;
	}
}

void PlayerDeadEmitter::Draw()
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw();
	}

	// 広がる円の描画
	if (circleDel_ == false) {
		Novice::DrawEllipse(
			static_cast<int>(circlePos_.x), static_cast<int>(circlePos_.y),
			circleRadius_, circleRadius_,
			0.0f,
			0xFFCC7700 + circleAlpha_, kFillModeSolid
		);
	}
}

void PlayerDeadEmitter::Emit(Vector2 centerPos)
{
	// ここで指定した数だけパーティクルを生成する
	for (int i = 0; i < 32; i++) {
		float particleX = static_cast<float>(Random((int)centerPos.x - range_, (int)centerPos.x + range_));
		float particleY = static_cast<float>(Random((int)centerPos.y - range_, (int)centerPos.y + range_));

		float velocityX = static_cast<float>(Random(-12, 12));
		float velocityY = static_cast<float>(Random(-12, 12));

		float size = static_cast<float>(Random(16, 24));

		unsigned int color = 0x00000000;
		int R = Random(230, 250);
		int G = Random(180, 220);
		int B = Random(50, 120);
		color += R << 24;
		color += G << 16;
		color += B << 8;

		PlayerDeadParticle newParticle = PlayerDeadParticle({ particleX,particleY }, { velocityX,velocityY }, size, color);
		particleList.push_back(newParticle);
	}

	// 広がる円の情報を初期化
	circlePos_.x = centerPos.x;
	circlePos_.y = centerPos.y;

	circleRadius_ = 42;
	circleAlpha_ = 192;

	circleDel_ = false;
}
