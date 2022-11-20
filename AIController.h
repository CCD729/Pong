#ifndef AI_CONTROLLER_H
#define AI_CONTROLLER_H

#include "Paddle.h"
#include "SquareBall.h"
#include <iostream>

namespace gm {
	class AIController
	{
	public:
		AIController();
		void sense(Paddle& paddle, const SquareBall& ball);
		void update(Paddle& paddle, int GameHeight);
		~AIController();
	};
}

#endif
