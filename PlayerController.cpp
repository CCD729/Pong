#include "PlayerController.h"

using namespace sf;
using namespace gm;

PlayerController::PlayerController()  {
	//This is more than a helper function set than a one-to-one controller
	//so one controller is good for both paddles
}
void PlayerController::handleInput(const sf::Event& event, Paddle& paddle, int GameHeight, int playerID) {
	//Get the paddle info for corresponding keys (0 = single player p1, 1 = multiplayer p1, 2 = multiplayer p2)
	if (playerID == 0 || playerID == 2) {
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Up && paddle.getPosition().y > 0) {
				paddle.setMovementDirection(MovementDirection::Up);
			}
			else if (event.key.code == Keyboard::Down && paddle.getPosition().y < (GameHeight - paddle.getSize().y)) {
				paddle.setMovementDirection(MovementDirection::Down);
			}
		}

		if (event.type == Event::KeyReleased) {
			if (event.key.code == Keyboard::Up && paddle.getMovementDirection() == MovementDirection::Up) {
				paddle.setMovementDirection(MovementDirection::None);
			}
			if (event.key.code == Keyboard::Down && paddle.getMovementDirection() == MovementDirection::Down) {
				paddle.setMovementDirection(MovementDirection::None);
			}
		}
	}
	else if (playerID == 1) { //Different Key
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::W && paddle.getPosition().y > 0) {
				paddle.setMovementDirection(MovementDirection::Up);
			}
			else if (event.key.code == Keyboard::S && paddle.getPosition().y < (GameHeight - paddle.getSize().y)) {
				paddle.setMovementDirection(MovementDirection::Down);
			}
		}

		if (event.type == Event::KeyReleased) {
			if (event.key.code == Keyboard::W && paddle.getMovementDirection() == MovementDirection::Up) {
				paddle.setMovementDirection(MovementDirection::None);
			}
			if (event.key.code == Keyboard::S && paddle.getMovementDirection() == MovementDirection::Down) {
				paddle.setMovementDirection(MovementDirection::None);
			}
		}
	}
}
void PlayerController::update(Paddle& paddle, int GameHeight) {
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
PlayerController::~PlayerController() {

}