#ifndef SCORE_UI_H
#define SCORE_UI_H

#include "GameObject.h"

namespace gm {
	class ScoreUI
	{
	protected:
		sf::Vector2i score;
		sf::Text scoreText1, scoreText2;
		sf::Font font;
	public:
		ScoreUI();
		const sf::Vector2i& GetScore() const;
		void SetScore(const sf::Vector2i score);
		void update(sf::RenderWindow& window);
		void render(sf::RenderWindow& window);
		~ScoreUI();
	};
}

#endif
