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
Game::Game() : window(VideoMode(GameWidth, GameHeight), "Game"), clock(), deltaTime(0), ball(centerPosition, Vector2f(10,10)), paddle1(paddle1Position, Vector2f(10, 120)), paddle2(paddle2Position, Vector2f(10, 120)), gameMode(GameMode::OnePlayer) {
	// Set our fps to 60
	window.setFramerateLimit(60);
}

void Game::run() {
	// This is our game loop!
	// All input, logic, and rendering should be handled here
	
	// Setup
	//gameMode = GameMode::TwoPlayer;
	// First recenter the ball and paddle
	ball.setPosition(centerPosition - Vector2f(ball.getSize().x / 2, ball.getSize().y / 2));
	paddle1.setPosition(paddle1Position - Vector2f(paddle1.getSize().x / 2, paddle1.getSize().y / 2));
	paddle2.setPosition(paddle2Position - Vector2f(paddle2.getSize().x / 2, paddle2.getSize().y / 2));

	// Start moving the ball at random direction
	ball.setVelocity(Vector2f(120,Randf(-20,20)));

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

		// Handle keyboard input to move paddle 1 (pack in player controller)
		if (gameMode == GameMode::OnePlayer) {
			playerController.handleInput(event,paddle1,GameHeight,0);
		}
		else {
			playerController.handleInput(event, paddle1, GameHeight, 1);
			playerController.handleInput(event, paddle2, GameHeight, 2);
		}
	}
	// AI should be able to sense even if there's no event
	if (gameMode == GameMode::OnePlayer) {
		// Simple AI for p2 control (decision)
		aiController.sense(paddle2, ball);
	}

}

// Implements the update portion of our Game Loop Programming Pattern
void Game::update() {
	// Update Inputs
		if (gameMode == GameMode::OnePlayer) {
			playerController.update(paddle1,GameHeight);
			// AI update
			aiController.update(paddle2, GameHeight);
		}
		else {
			playerController.update(paddle1, GameHeight);
			playerController.update(paddle2, GameHeight);
		}

	// Update our boxes (i.e., move them based on the block's specified movement direction)
	ball.update(window, deltaTime);
	paddle1.update(window, deltaTime);
	paddle2.update(window, deltaTime);
	

	// Collision handling with paddles
	if (ball.collide(paddle1.getCollider())) {
		//Determine which direction they collided
			//TODO
		
		// If hitting on side
		//Reset ball position to Avoid weird stick (temporary)
		ball.setPosition(Vector2f(paddle1.getPosition().x + paddle1.getSize().x + 0.1f, ball.getPosition().y));
		//Regular situation: bump back with a speedup and a slight angle change
		if (paddle1.getMovementDirection() == MovementDirection::Up) {
			ball.setVelocity(Vector2f((-1) * (ball.getVelocity().x-40), ball.getVelocity().y-70));
		}
		else if (paddle1.getMovementDirection() == MovementDirection::Down) {
			ball.setVelocity(Vector2f((-1) * (ball.getVelocity().x - 40), ball.getVelocity().y + 70));
		}
		else {
			ball.setVelocity(Vector2f((-1) * (ball.getVelocity().x - 40), ball.getVelocity().y));
		}
	}
	else if (ball.collide(paddle2.getCollider())) {
		//Determine which direction they collided
			//TODO

		// If hitting on side
		//Reset ball position to Avoid weird stick (temporary)
		ball.setPosition(Vector2f(paddle2.getPosition().x - ball.getSize().x - 0.1f, ball.getPosition().y));

		if (paddle2.getMovementDirection() == MovementDirection::Up) {
			ball.setVelocity(Vector2f((-1) * (ball.getVelocity().x + 40), ball.getVelocity().y - 70));
		}
		else if (paddle2.getMovementDirection() == MovementDirection::Down) {
			ball.setVelocity(Vector2f((-1) * (ball.getVelocity().x + 40), ball.getVelocity().y + 70));
		}
		else {
			ball.setVelocity(Vector2f((-1) * (ball.getVelocity().x + 40), ball.getVelocity().y));
		}
	} //If hitting up or down edge
	else if (ball.getPosition().y <= 0 || ball.getPosition().y >= (GameHeight - ball.getSize().y)) {
		ball.setVelocity(Vector2f(ball.getVelocity().x, (-1) * ball.getVelocity().y));
	}
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


//Help functions
//Randoms
int gm::Rand(int min, int max) // Ranged
{
	static bool setup = true;
	if (setup)
	{
		srand(unsigned int(time(NULL))); //seeding
		setup = false;
	}
	int tmp = min + rand() % ((max + 1) - min);
	return (tmp == 0) ? 1 : tmp;
}

float gm::Randf(float min, float max) {
	static bool setup = true;
	if (setup)
	{
		srand(unsigned int(time(NULL))); //seeding
		setup = false;
	}
	return (min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))));
}

//Implementation of HSV Tool Function by Tenry
sf::Color gm::hsv(int hue, float sat, float val)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(Uint8(val * 255), Uint8(t * 255), Uint8(p * 255));
	case 1: return sf::Color(Uint8(q * 255), Uint8(val * 255), Uint8(p * 255));
	case 2: return sf::Color(Uint8(p * 255), Uint8(val * 255), Uint8(t * 255));
	case 3: return sf::Color(Uint8(p * 255), Uint8(q * 255), Uint8(val * 255));
	case 4: return sf::Color(Uint8(t * 255), Uint8(p * 255), Uint8(val * 255));
	case 5: return sf::Color(Uint8(val * 255), Uint8(p * 255), Uint8(q * 255));
	}
}