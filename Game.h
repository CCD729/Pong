// Our include guards
// These are critical for preventing collision related errors from a file accidentally getting fully included multiple times
#ifndef GAME_H
#define GAME_H

/* SFML Includes             *
 * Add to every SFML project */
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

 /* Our Includes */
#include "SquareBall.h"
#include "Paddle.h"
#include "PlayerController.h"
#include "AIController.h"

// Place our classes, functions, variables, and so forth in their own namespace to avoid naming collisions
namespace gm {
	const int GameWidth = 640;
	const int GameHeight = 640;

	enum GameMode {
		OnePlayer = 0,
		TwoPlayer = 1
	};

	/* Our Game Class                               *
	 * Implements the Game Loop Programming Pattern */
	class Game {
	private:
		// The game window
		sf::RenderWindow window;
		// For tracking/maintaining delta time
		sf::Clock clock;
		float deltaTime;
		// Game mode (stretch goal)
		GameMode gameMode;
		// Our game objects
		SquareBall ball;
		Paddle paddle1;
		Paddle paddle2;
		// PlayerController
		PlayerController playerController;
		// AI Controller
		AIController aiController;
		// ScoreTracker UI
			//TODO
		//SoundManager
			//TODO

	public:
		/* Protoypes */
		// Constructor
		Game();
		// Will start and manage the game loop programming pattern
		void run();
		// Game Loop Programming Pattern Methods
		void handleInput();
		void update();
		void render();
		// Destructor
		~Game();
	};

	//Help functions
	int Rand(int min, int max);
	float Randf(float min, float max);
	sf::Color hsv(int hue, float sat, float val);

}

#endif