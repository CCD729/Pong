// We need to include our header file to implement the function prototypes of our Game class
#include "Game.h"

// Since we are in our private .cpp file, it's fine to use a namespace here
using namespace gm;
using namespace sf;

// Implement constructor, this will effectively be a setup function as the game gets more complex
Game::Game() : window(VideoMode(GameWidth, GameHeight), "Game"), clock(), deltaTime(0), box1(Vector2f(250, 300), Vector2f(50,50)), box2(Vector2f(350, 300), Vector2f(50, 50)) {
	// Set our fps to 60
	window.setFramerateLimit(60);
}

void Game::run() {
	// This is our game loop!
	// All input, logic, and rendering should be handled here
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
			if (event.key.code == Keyboard::Left) {
				box1.setMovmentDirection(MovementDirection::Left);
			}else if (event.key.code == Keyboard::Right) {
				box1.setMovmentDirection(MovementDirection::Right);
			}
		}

		if (event.type == Event::KeyReleased) {
			if (event.key.code == Keyboard::Left && box1.getMovementDirection() == MovementDirection::Left) {
				box1.setMovmentDirection(MovementDirection::None);
			}
			if (event.key.code == Keyboard::Right && box1.getMovementDirection() == MovementDirection::Right) {
				box1.setMovmentDirection(MovementDirection::None);
			}
		}
	}
}

// Implements the update portion of our Game Loop Programming Pattern
void Game::update() {
	// Update our boxes (i.e., move them based on the block's specified movement direction)
	box1.update(window, deltaTime);
	box2.update(window, deltaTime);

	// If the mouse has entered box 1 then color it green
	if (box1.collide(Vector2f(Mouse::getPosition(window)))) {
		box1.setFillColor(Color::Green);
	} else {
		box1.setFillColor(Color::White);
	}

	// If the mouse has entered box 2 then color it green
	if (box2.collide(Vector2f(Mouse::getPosition(window)))) {
		box2.setFillColor(Color::Green);
	}
	else {
		box2.setFillColor(Color::White);
	}

	// If box 1 and 2 have collided then turn 1 blue and 2 red
	if (box2.collide(box1.getCollider())) {
		box1.setFillColor(Color::Blue);
		box2.setFillColor(Color::Red);
	}
}

// Implements the render portion of our Game Loop Programming Pattern
void Game::render() {
	// This clears the window at the beginning of every frame
	window.clear();

	// Draw our boxes
	box1.render(window, deltaTime);
	box2.render(window, deltaTime);

	// Display the window buffer for this frame
	window.display();
}

// Implement destructor, make sure we free up any memory that we allocated here!
Game::~Game() {

}