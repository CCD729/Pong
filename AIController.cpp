#include "AIController.h"

using namespace sf;
using namespace gm;

AIController::AIController() {

}

void AIController::sense(Paddle& paddle, const SquareBall& ball) {
	//Simplist decision... (to start with)
	//std::cout << "BallPosition: "<< ball.getPosition().y + ball.getSize().y / 2 << std::endl;
	if ((ball.getPosition().y+ball.getSize().y/2)+10 < (paddle.getPosition().y+ paddle.getSize().y/2)) {
		paddle.setMovementDirection(MovementDirection::Up);
	}
	else if ((ball.getPosition().y+ball.getSize().y / 2)-10 > (paddle.getPosition().y + paddle.getSize().y/2)) {
		paddle.setMovementDirection(MovementDirection::Down);
	}
	else {
		paddle.setMovementDirection(MovementDirection::None);
	}
}

void AIController::update(Paddle& paddle, int GameHeight) {
	//Limit paddle within screen
	if (paddle.getPosition().y < 0) {
		paddle.setPosition(Vector2f(paddle.getPosition().x, 0));
		paddle.setMovementDirection(MovementDirection::None);
	}
	else if (paddle.getPosition().y > (GameHeight - paddle.getSize().y)) {
		paddle.setPosition(Vector2f(paddle.getPosition().x, GameHeight - paddle.getSize().y));
		paddle.setMovementDirection(MovementDirection::None);
	}
}

AIController::~AIController() {

}