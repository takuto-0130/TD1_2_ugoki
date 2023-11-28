#include "jumpEnergyEmitter.h"

JumpEnergyEmitter::JumpEnergyEmitter()
{
}

JumpEnergyEmitter::~JumpEnergyEmitter()
{
}

void JumpEnergyEmitter::Update(Vector2 pos, bool isJump, int life, bool isClear)
{
	if (isJump == 1) {
		isEmit_ = 1;
		timer_ = 0;
	}
	// タイマーを進める
	if(isEmit_ == 1){
		timer_++;
	}

	// 設定した間隔毎にパーティクルを生成する
	if (timer_ % interval_ == 0 && timer_ < kTimerMax_ && isEmit_ == 1 && timer_ > 10) {
		JumpEnergyEmitter::Emit({ pos.x,pos.y });
	}
	if (timer_ >= kTimerMax_) {
		isEmit_ = 0;
	}

	// パーティクル全ての更新処理を呼ぶ
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update();

		// DelFlagがtrueだったら
		if (itr->GetDelFlag() || life == 0 || isClear == 1) {
			itr = particleList.erase(itr);
		}
		else {
			itr++; // eraseしなかった場合のみイテレーターをインクリメント
		}
	}
}

void JumpEnergyEmitter::EmitGoal(Vector2 pos)
{
	// パーティクルのゴール地点をプレイヤーの中心に設定
	for (auto& particle : particleList) {
		particle.EmitGoal(pos);
	}
}

void JumpEnergyEmitter::Draw()
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw();
	}
}

void JumpEnergyEmitter::Emit(Vector2 pos)
{
	// エミッター範囲内で座標をランダムに設定

	// 向きをランダムに設定
	Vector2 angle = {
		static_cast<float>(Random(-200, 200)),
		static_cast<float>(Random(-200, 200))
	};

	float denominator = sqrtf(angle.x * angle.x + angle.y * angle.y);
	if (denominator != 0) {
		angle = { angle.x / denominator, angle.y / denominator };
	}

	// サイズをランダムに設定
	float size = static_cast<float>(Random(40, 80)) * 0.1f;

	unsigned int color = 0x00000000;
	int R = 255;
	int G = Random(150, 230);
	int B = Random(0, 100);
	color += R << 24;
	color += G << 16;
	color += B << 8;

	// ランダムに設定した数値を生成したパーティクルに格納
	JumpEnergyParticle newParticle = JumpEnergyParticle(pos, angle, size, color);
	particleList.push_back(newParticle);
}