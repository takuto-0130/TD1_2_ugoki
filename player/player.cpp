#include "player.h"

void PlayerVertex(Vector2 center, int width, int height, Vector2& lt, Vector2& rt, Vector2& lb, Vector2& rb)
{
	lt = { center.x - width / 2, center.y - height / 2 };
	rt = { (center.x + width / 2) - 1, center.y - height / 2 };
	lb = { center.x - width / 2, (center.y + height / 2) - 1 };
	rb = { (center.x + width / 2) - 1, (center.y + height / 2) - 1 };
};

void PlayerInitialize(Player& a) {
	a.pos = { 400,680 };
	a.radius = blockSize / 2;
	a.collisionLen = blockSize;
	a.gravity = 0.3f;
	a.jump = -10.0f;
	a.velocityY = 0;
	a.flySpeedY = 4.0f;
	a.fallSpeedMax = 12;
	a.maxLife = 3;
	a.life = a.maxLife;
	a.maxJumpCount = 1;
	a.jumpCount = 0;
	a.maxFlyEnergy = kFlyEnergyMax;
	a.flyEnergy = 0;
	a.isFly = 0;
	a.dirY = 0;
	a.isJump = 0;
	a.kJumpChargeValue = 40.0f;
	a.kCollisionChargeValue = 2.0f;
	a.getCoin = 0;
	PlayerVertex(a.pos, a.collisionLen, a.collisionLen, a.lt, a.rt, a.lb, a.rb);
}

int mapChipCollision1(MapChipNum& map, int mapNum, Player posX, Player posY, float scroll) {
	if (map.mapData[int(posY.lt.y) / blockSize][int(posX.lt.x + scroll) / blockSize] == mapNum ||
		map.mapData[int(posY.lb.y) / blockSize][int(posX.lb.x + scroll) / blockSize] == mapNum ||
		map.mapData[int(posY.rt.y) / blockSize][int(posX.rt.x + scroll) / blockSize] == mapNum ||
		map.mapData[int(posY.rb.y) / blockSize][int(posX.rb.x + scroll) / blockSize] == mapNum)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int mapChipCollision2(MapChipNum& map, int mapNum, Player posX, Player posY, float scroll) {
	if (map.mapData[int(posY.lt.y) / blockSize][int(posX.lt.x + scroll) / blockSize] == mapNum ||
		map.mapData[int(posY.lb.y + 2) / blockSize][int(posX.lb.x + scroll) / blockSize] == mapNum ||
		map.mapData[int(posY.rt.y) / blockSize][int(posX.rt.x + scroll + 1) / blockSize] == mapNum ||
		map.mapData[int(posY.rb.y + 2) / blockSize][int(posX.rb.x + scroll + 1) / blockSize] == mapNum)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void flyEnergyCharge(MapChipNum& map, int mapNum, Player& a, float scroll) {
	for (int y = int(a.lt.y - kChargeCollisionDistance) / blockSize; y <= int(a.lb.y + kChargeCollisionDistance) / blockSize; y++) {
		for (int x = int(a.lt.x + scroll - kChargeCollisionDistance) / blockSize; x <= int(a.rb.x + scroll + kChargeCollisionDistance) / blockSize; x++) {
			if (map.mapData[y][x] == mapNum) {
				a.flyEnergy += a.kCollisionChargeValue;
			}
		}
	}
}

void mapNumChange0(MapChipNum& map, int mapNum, Player posX, Player posY, float scroll) {
	if (map.mapData[int(posY.lt.y) / blockSize][int(posX.lt.x + scroll) / blockSize] == mapNum) {
		map.mapData[int(posY.lt.y) / blockSize][int(posX.lt.x + scroll) / blockSize] = 0;
	}
	if (map.mapData[int(posY.lb.y) / blockSize][int(posX.lb.x + scroll) / blockSize] == mapNum) {
		map.mapData[int(posY.lb.y) / blockSize][int(posX.lb.x + scroll) / blockSize] = 0;
	}
	if (map.mapData[int(posY.rt.y) / blockSize][int(posX.rt.x + scroll) / blockSize] == mapNum) {
		map.mapData[int(posY.rt.y) / blockSize][int(posX.rt.x + scroll) / blockSize] = 0;
	}
	if (map.mapData[int(posY.rb.y) / blockSize][int(posX.rb.x + scroll) / blockSize] == mapNum) {
		map.mapData[int(posY.rb.y) / blockSize][int(posX.rb.x + scroll) / blockSize] = 0;
	}
}

void PlayerStageCollision(MapChipNum& map, Player& a, float scroll) {
	for (int i = 1; i <= 2; i++)
	{
		//壁床等判定
		if (a.isFly == 0)
		{

			if ((map.mapData[int(a.lb.y) / blockSize][int(a.lb.x + scroll) / blockSize] == i ||
				map.mapData[int(a.rb.y) / blockSize][int(a.rb.x + scroll) / blockSize] == i) &&
				a.velocityY >= 0)
			{
				a.velocityY = 0;
				a.pos.y = float(int(int(a.lb.y) / blockSize) * blockSize - a.radius);
				a.jumpCount = 0;
			}

			if (a.velocityY < 0)
			{
				if (map.mapData[int(a.rt.y - a.jump) / blockSize][int(a.rt.x + scroll) / blockSize] == i ||
					map.mapData[int(a.rb.y) / blockSize][int(a.rb.x + scroll) / blockSize] == i)
				{
					a.life = 0;
				}
			}
			else if (a.velocityY > 0)
			{
				if (map.mapData[int(a.rt.y) / blockSize][int(a.rt.x + scroll) / blockSize] == i ||
					map.mapData[int(a.rb.y) / blockSize][int(a.rb.x + scroll) / blockSize] == i)
				{
					a.life = 0;
				}
			}
			else
			{
				if (map.mapData[int(a.rt.y - a.jump) / blockSize][int(a.rt.x + scroll) / blockSize] == i ||
					map.mapData[int(a.rb.y - a.velocityY - a.fallSpeedMax) / blockSize][int(a.rb.x + scroll) / blockSize] == i)
				{
					a.life = 0;
				}
			}

			if ((map.mapData[int(a.lt.y) / blockSize][int(a.lt.x + scroll) / blockSize] == i ||
				map.mapData[int(a.rt.y) / blockSize][int(a.rt.x + scroll) / blockSize] == i) &&
				a.velocityY <= 0)
			{
				a.velocityY = 0;
				a.pos.y = float(int(int(a.lt.y) / blockSize) * blockSize + blockSize + a.radius);
			}
		}
		else
		{
			if (mapChipCollision1(map, i, a, a, scroll))
			{
				a.life = 0;
			}
			flyEnergyCharge(map, 2, a, scroll);
		}
		

	}
	if (mapChipCollision1(map, 5, a, a, scroll))
	{
		mapNumChange0(map, 5, a, a, scroll);
		a.getCoin++;
	}
	a.maxFlyEnergy = kFlyEnergyMax + (120 * int(a.getCoin / 5.0f));
	a.kCollisionChargeValue = kCollisionChargeValue + (0.1f * int(a.getCoin / 5.0f));
	a.kJumpChargeValue = kJumpChargeValue + (8 * int(a.getCoin / 5.0f));
}

void RunMove(Player& player, char* keys, char* preKeys) {
	player.isJump = 0;
	if ((preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0 || preKeys[DIK_W] == 0 && keys[DIK_W] != 0 || preKeys[DIK_UP] == 0 && keys[DIK_UP] != 0) && player.jumpCount < player.maxJumpCount)
	{
		player.velocityY = player.jump;
		player.jumpCount++;
		player.flyEnergy += player.kJumpChargeValue;
		player.isJump = 1;
	}
	player.velocityY += player.gravity;

	if (player.velocityY > player.fallSpeedMax)
	{
		player.velocityY = player.fallSpeedMax;
	}
}

void FlightMove(Player& player, char* keys) {

	player.dirY = 0;
	if (keys[DIK_W] || keys[DIK_SPACE] || keys[DIK_UP])
	{
		player.dirY--;
	}
	if (keys[DIK_S] || keys[DIK_LCONTROL] || keys[DIK_RCONTROL] || keys[DIK_DOWN])
	{
		player.dirY++;
	}
	player.velocityY = player.flySpeedY * player.dirY;
	player.flyEnergy--;
}

void PlayerFlight(Player& now, Player& old, char* keys, char* preKeys) {
	if (preKeys[DIK_LSHIFT] == 0 && keys[DIK_LSHIFT] != 0 && old.isFly == 0 && now.flyEnergy == now.maxFlyEnergy) {
		now.isFly = 1;
	}
	//シフトで飛行解除、ゲージ消失
	if (preKeys[DIK_LSHIFT] == 0 && keys[DIK_LSHIFT] != 0 && old.isFly == 1) {
		now.flyEnergy = 0;
	}
	if (now.flyEnergy >= now.maxFlyEnergy) {
		now.flyEnergy = now.maxFlyEnergy;
	}
	//ゲージが無くなったら飛べなくなる
	if (now.flyEnergy <= 0) {
		now.isFly = 0;
	}
}