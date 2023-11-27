#pragma once
#include "CheckPointParticle.h"
#include <list>
#define _USE_MATH_DEFINES
#include <math.h>
#include "particle/util/Util.h"

class CheckPointEmitter
{
public:
	CheckPointEmitter();
	~CheckPointEmitter();

	void Update();
	void Draw(int scroll);

	void Emit(Vector2 centerPos);

private:
	std::list<CheckPointParticle> particleList;
};

