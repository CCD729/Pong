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
Game::Game() : window(VideoMode(GameWidth, GameHeight), "Game"), clock(), deltaTime(0), ball(centerPosition, Vector2f(10,10)), paddle1(paddle1Position, Vector2f(10, 120)), paddle2(paddle2Position, Vector2f(10, 120)), gameMode(GameMode::OnePlayer), gameState(GameState::Menu), maxScore(7) {
	// Set our fps to 60
	window.setFramerateLimit(60);
	// Initial Setup for menu UI
	if (!font.loadFromFile("Assets/PressStart2P-vaV7.ttf"))
	{
		// error...
		std::cerr << "Error: Failed to load font!" << std::endl;
		exit(-1);
	}
	// select the font
	title.setFont(font);
	gm1Text.setFont(font);
	gm2Text.setFont(font);
	beginPrompt.setFont(font);
	endMessage.setFont(font);
	restartPrompt.setFont(font);
	// set the string to display
	title.setString("P O N G");
	gm1Text.setString("1P vs COM");
	gm2Text.setString("1P vs 2P");
	beginPrompt.setString("Arrows to select, Space to begin");
	endMessage.setString("who wins");
	restartPrompt.setString("Space to replay, B to menu");
	// set the character size (in pixels)
	title.setCharacterSize(48);
	gm1Text.setCharacterSize(24);
	gm2Text.setCharacterSize(24);
	beginPrompt.setCharacterSize(18);
	endMessage.setCharacterSize(36);
	restartPrompt.setCharacterSize(22);
	// set the color
	title.setFillColor(sf::Color::White);
	gm1Text.setFillColor(sf::Color::White);
	gm2Text.setFillColor(sf::Color::White);
	beginPrompt.setFillColor(sf::Color::White);
	endMessage.setFillColor(sf::Color::White);
	restartPrompt.setFillColor(sf::Color::White);
	// set the text style
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	gm1Text.setStyle(sf::Text::Regular);
	gm2Text.setStyle(sf::Text::Regular);
	beginPrompt.setStyle(sf::Text::Bold);
	endMessage.setStyle(sf::Text::Bold);
	restartPrompt.setStyle(sf::Text::Regular);
	// set the position
	title.setPosition(Vector2f(152, 80));
	gm1Text.setPosition(Vector2f(225, 250));
	gm2Text.setPosition(Vector2f(225, 350));
	beginPrompt.setPosition(Vector2f(18, 500));
	endMessage.setPosition(Vector2f(190, 80));
	restartPrompt.setPosition(Vector2f(35, 350));

	// Menu Mode Selector
	modeSelector.setFillColor(Color::White);
	modeSelector.setSize(Vector2f(10, 10));
	modeSelector.setPosition(Vector2f(200,255)); //First position 200,255 second position 200,355

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
		if (gameState == GameState::Menu)
		{
			// Handle mode selection and start game
			if (event.type == Event::KeyPressed) {
				if (gameMode == GameMode::OnePlayer && event.key.code == Keyboard::Down) {
					gameMode = GameMode::TwoPlayer;
					modeSelector.setPosition(Vector2f(200, 355));
					soundManager.PlaySFX(SFX::button);
				}
				else if (gameMode == GameMode::TwoPlayer && event.key.code == Keyboard::Up) {
					gameMode = GameMode::OnePlayer;
					modeSelector.setPosition(Vector2f(200, 255));
					soundManager.PlaySFX(SFX::button);
				}
				else if (event.key.code == Keyboard::Space) {
					GameStateChange(GameState::InGame);
					soundManager.PlaySFX(SFX::button);
				}
			}
		}
		if (gameState == GameState::InGame) {
			// Handle keyboard input to move paddle 1 (pack in player controller)
			if (gameMode == GameMode::OnePlayer) {
				playerController.handleInput(event, paddle1, GameHeight, 0);
			}
			else {
				playerController.handleInput(event, paddle1, GameHeight, 1);
				playerController.handleInput(event, paddle2, GameHeight, 2);
			}
		}
		if (gameState == GameState::EndGame) {
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Space) {
					GameStateChange(GameState::InGame);
					soundManager.PlaySFX(SFX::button);
				}
				if (event.key.code == Keyboard::B) {
					GameStateChange(GameState::Menu);
					soundManager.PlaySFX(SFX::button);
				}
			}
		}
	}
	if (gameState == GameState::InGame) {
		// AI should be able to sense even if there's no event
		if (gameMode == GameMode::OnePlayer) {
			// Simple AI for p2 control (decision)
			aiController.sense(paddle2, ball);
		}
	}
}

// Implements the update portion of our Game Loop Programming Pattern
void Game::update() {
	if (gameState == GameState::InGame) {
		// Update paddle limits
		if (gameMode == GameMode::OnePlayer) {
			playerController.update(paddle1, GameHeight);
			// AI update
			aiController.update(paddle2, GameHeight);
		}
		else {
			playerController.update(paddle1, GameHeight);
			playerController.update(paddle2, GameHeight);
		}

		// Update our game objects
		ball.update(window, deltaTime);
		paddle1.update(window, deltaTime);
		paddle2.update(window, deltaTime);

		// Collision handling with paddles
		if (ball.collide(paddle1.getCollider())) {
			//SFX
			soundManager.PlaySFX(SFX::bounce);
			ball.Bounce(paddle1, -1);
		}
		else if (ball.collide(paddle2.getCollider())) {
			//SFX
			soundManager.PlaySFX(SFX::bounce);
			ball.Bounce(paddle2, 1);
		} // If hitting up or down edge
		else if (ball.getPosition().y <= 0 || ball.getPosition().y >= (GameHeight - ball.getSize().y)) {
			ball.Bounce(ball.getPosition().y <= 0, GameHeight);
			soundManager.PlaySFX(SFX::bounce);
		} // If goal
		else if (!goal && (ball.getPosition().x <= 0 || ball.getPosition().x >= (GameHeight - ball.getSize().x))) {
			//SFX
			soundManager.PlaySFX(SFX::goal);
			// Trigger respawn 
			goal = true;
			respawnClock.restart();
			// Score update
			if (ball.getPosition().x <= 0) {
				scoreUI.SetScore(Vector2i(scoreUI.GetScore().x, scoreUI.GetScore().y + 1));
			}
			else {
				scoreUI.SetScore(Vector2i(scoreUI.GetScore().x+1, scoreUI.GetScore().y));
			}
			// Stop the ball
			ball.setPosition(centerPosition - Vector2f(ball.getSize().x / 2, ball.getSize().y / 2) + Vector2f(-1000, 0));
			ball.setVelocity(Vector2f(0, 0));
		}
		// ScoreUI update
		scoreUI.update(window, maxScore);

		// Winning check / respawn ball
		if (goal) {
			// Win
			if (scoreUI.GetScore().x == 7) {
				endMessage.setString("P1 wins");
				//endMessage.setPosition(Vector2f(0,0));
				goal = false;
				GameStateChange(GameState::EndGame);
			}
			else if (scoreUI.GetScore().y == 7) {
				if (gameMode == GameMode::OnePlayer) {
					endMessage.setString("COM wins");
					goal = false;
					//endMessage.setPosition(Vector2f(0,0));
				}
				else {
					endMessage.setString("P2 wins");
					goal = false;
					//endMessage.setPosition(Vector2f(0,0));
				}
				GameStateChange(GameState::EndGame);
			}
			else { // On Timer respawn the ball
				if (respawnClock.getElapsedTime().asSeconds() >= 3) {
					ball.setPosition(centerPosition - Vector2f(ball.getSize().x / 2, ball.getSize().y / 2));
					ball.setVelocity(Vector2f(float(pow(-1,Rand(1,2))) *120.f, Randf(-30, 30)));
					goal = false;
				}
			}
		} 
	}
	
}

// Implements the render portion of our Game Loop Programming Pattern
void Game::render() {
	// This clears the window at the beginning of every frame
	window.clear();
	if (gameState == GameState::Menu) {
		window.draw(title);
		window.draw(gm1Text);
		window.draw(gm2Text);
		window.draw(beginPrompt);
		window.draw(modeSelector);
	}
	if (gameState == GameState::InGame) {
		// Draw game objects
		ball.render(window, deltaTime);
		paddle1.render(window, deltaTime);
		paddle2.render(window, deltaTime);
		//ScoreUI update
		scoreUI.render(window);
	}
	if (gameState == GameState::EndGame) {
		// Draw game objects
		window.draw(endMessage);
		window.draw(restartPrompt);
	}
	// Display the window buffer for this frame
	window.display();
}

// Implement destructor, make sure we free up any memory that we allocated here!
Game::~Game() {

}

//Switch game state functions
void Game::GameStateChange(GameState state) {

	// Clean up what we had
	if (state == GameState::Menu) {
		gameState = GameState::Menu;
		// Reset (from end)

		// Initalize
		gameMode = GameMode::OnePlayer;
		modeSelector.setPosition(Vector2f(200, 255));
	}
	else if (state == GameState::InGame) {
		gameState = GameState::InGame;
		// Reset (from menu or end, gamemode keeps)
		
		// Initalize (based on game mode)
		// First recenter the ball and paddle
		ball.setPosition(centerPosition - Vector2f(ball.getSize().x / 2, ball.getSize().y / 2));
		paddle1.setPosition(paddle1Position - Vector2f(paddle1.getSize().x / 2, paddle1.getSize().y / 2));
		paddle2.setPosition(paddle2Position - Vector2f(paddle2.getSize().x / 2, paddle2.getSize().y / 2));
		scoreUI.SetScore(Vector2i(0, 0));
		// Start moving the ball at random direction
		ball.setVelocity(Vector2f(120, Randf(-30, 30)));
	}
	else if (state == GameState::EndGame) {
		gameState = GameState::EndGame;
		// Retrieve winner data if End State (Done in update)
		
		// Reset
		// Stop the ball
		ball.setPosition(centerPosition - Vector2f(ball.getSize().x / 2, ball.getSize().y / 2) + Vector2f(-1000, 0));
		ball.setVelocity(Vector2f(0, 0));
		paddle1.setPosition(paddle1Position - Vector2f(paddle1.getSize().x / 2, paddle1.getSize().y / 2));
		paddle2.setPosition(paddle2Position - Vector2f(paddle2.getSize().x / 2, paddle2.getSize().y / 2));
		paddle1.setMovementDirection(MovementDirection::None);
		paddle2.setMovementDirection(MovementDirection::None);
		// Initalize
	}
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