// We need to include our header file to implement the function prototypes of our Game class
#include "Game.h"

// Since we are in our private .cpp file, it's fine to use a namespace here
using namespace gm;
using namespace sf;

// Some global variables
Vector2f centerPosition = Vector2f(GameWidth / 2, GameHeight / 2);
Vector2f paddle1Position = Vector2f(30, GameHeight / 2);
Vector2f paddle2Position = Vector2f(GameWidth-30, GameHeight / 2);

// Implement constructor, this will effectively be a setup function as the game gets more complex
Game::Game() : window(VideoMode(GameWidth, GameHeight), "Game"), clock(), deltaTime(0), ball(centerPosition, Vector2f(10,10)), paddle1(paddle1Position, Vector2f(12.5, 150)), paddle2(paddle2Position, Vector2f(12.5, 150)) {
	// Set our fps to 60
	window.setFramerateLimit(60);
}

void Game::run() {
	// This is our game loop!
	// All input, logic, and rendering should be handled here
	// First recenter the ball
	ball.setPosition(centerPosition - Vector2f(ball.getSize().x / 2, ball.getSize().y / 2));
	paddle1.setPosition(paddle1Position - Vector2f(paddle1.getSize().x / 2, paddle1.getSize().y / 2));
	paddle2.setPosition(paddle2Position - Vector2f(paddle2.getSize().x / 2, paddle2.getSize().y / 2));
	while (window.isOpen())
	{
		// Every frame we...
		// Keep track of the delta time for smoother movement
		deltaTime = clock.restart().asSeconds();

		// Handle input first...
		handleInput();

		// Then update...
		update();

		// Then render...
		render();
	}
}

// Implements the handle input portion of our Game Loop Programming Pattern
void Game::handleInput() {
	// Check for events from the window
	// E.g., is the window being closed?
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();

		// Handle keyboard input to move box 1
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Up) {
				//paddle1.setMovmentDirection(MovementDirection::Up);
			}else if (event.key.code == Keyboard::Down) {
				//paddle1.setMovmentDirection(MovementDirection::Down);
			}
		}
		/*
		if (event.type == Event::KeyReleased) {
			if (event.key.code == Keyboard::Left && paddle1.getMovementDirection() == MovementDirection::Left) {
				//paddle1.setMovmentDirection(MovementDirection::None);
			}
			if (event.key.code == Keyboard::Right && paddle1.getMovementDirection() == MovementDirection::Right) {
				//paddle1.setMovmentDirection(MovementDirection::None);
			}
		}
		*/
	}
}

// Implements the update portion of our Game Loop Programming Pattern
void Game::update() {
	// Update our boxes (i.e., move them based on the block's specified movement direction)
	ball.update(window, deltaTime);
	paddle1.update(window, deltaTime);
	paddle2.update(window, deltaTime);

	// Collision handling with paddles
	/*if (ball.collide(paddle1.getCollider())) {

	}
	else if (ball.collide(paddle2.getCollider())) {

	} //If hitting up or down edge
	else if (ball.getPosition().y <= 0 || ball.getPosition().y >= (GameHeight - ball.getSize().y)) {

	}*/
}

// Implements the render portion of our Game Loop Programming Pattern
void Game::render() {
	// This clears the window at the beginning of every frame
	window.clear();

	// Draw game objects
	ball.render(window, deltaTime);
	paddle1.render(window, deltaTime);
	paddle2.render(window, deltaTime);

	// Display the window buffer for this frame
	window.display();
}

// Implement destructor, make sure we free up any memory that we allocated here!
Game::~Game() {

}