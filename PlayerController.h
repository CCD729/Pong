#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Paddle.h"

namespace gm {
	class PlayerController
	{
	public:
		PlayerController();
		void handleInput(const sf::Event& event, Paddle& paddle, int GameHeight, int playerID = 0);
		void update(Paddle& paddle, int GameHeight);
		~PlayerController();
	};
}
#endif
