#include "ScoreUI.h"
#include <iostream>
using namespace sf;
using namespace gm;


ScoreUI::ScoreUI() : score(Vector2i(0,0)) {
	// Initial Setup
	if (!font.loadFromFile("Assets/PressStart2P-vaV7.ttf"))
	{
		// error...
		std::cerr << "Error: Failed to load font!" << std::endl;
		exit(-1);
	}
	// select the font
	scoreText1.setFont(font);
	scoreText2.setFont(font);
	maxScoreText.setFont(font);
	scoreText1.setString("0");
	scoreText2.setString("0");
	maxScoreText.setString("7");
	// set the character size (in pixels)
	scoreText1.setCharacterSize(48);
	scoreText2.setCharacterSize(48);
	maxScoreText.setCharacterSize(60);
	// set the color
	scoreText1.setFillColor(sf::Color::White);
	scoreText2.setFillColor(sf::Color::White);
	maxScoreText.setFillColor(sf::Color::White);
	// set the text style
	scoreText1.setStyle(sf::Text::Bold);
	scoreText2.setStyle(sf::Text::Bold);
	maxScoreText.setStyle(sf::Text::Bold);
	// set the position
	scoreText1.setPosition(Vector2f(175, 40));
	scoreText2.setPosition(Vector2f(421, 40));
	maxScoreText.setPosition(Vector2f(293, 30));
}
const Vector2i& ScoreUI::GetScore() const {
	return score;
}
void ScoreUI::SetScore(const sf::Vector2i score) {
	this->score = score;
}
void ScoreUI::update(sf::RenderWindow& window, int maxScore) {
	scoreText1.setString(std::to_string(score.x));
	scoreText2.setString(std::to_string(score.y));
	maxScoreText.setString(std::to_string(maxScore));
}
void ScoreUI::render(sf::RenderWindow& window) {
	window.draw(scoreText1);
	window.draw(scoreText2);
	window.draw(maxScoreText);
}
ScoreUI::~ScoreUI() {

}