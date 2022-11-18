#include "SquareBall.h"

using namespace sf;
using namespace gm;

SquareBall::SquareBall(const Vector2f& position, const Vector2f& size) : GameObject(position, size), direction(MovementDirection::None) {
	body.setPosition(position);
	body.setSize(size);
}

void SquareBall::update(sf::RenderWindow& window, float deltaTime){
	move(Vector2f(PlayerMovementSpeedPerSecond * direction * deltaTime, 0));
}

void SquareBall::render(sf::RenderWindow& window, float deltaTime) {
	window.draw(body);
}

void SquareBall::setPosition(const Vector2f& position) {
	GameObject::setPosition(position);
	// Don't forget to update the Box's shape position to match the new position
	body.setPosition(position);
}

void SquareBall::move(const Vector2f& velocity) {
	GameObject::move(velocity);
	// Don't forget to update the Box's shape position to match the new position
	body.setPosition(position);
}

void SquareBall::setMovmentDirection(MovementDirection direction) {
	this->direction = direction;
}

MovementDirection SquareBall::getMovementDirection() const {
	return direction;
}


const Color& SquareBall::getFillColor() const {
	return body.getFillColor();
}

void SquareBall::setFillColor(const Color& color) {
	body.setFillColor(color);
}

const Vector2f& SquareBall::getVelocity() const {

}

void SquareBall::getVelocity(const Vector2f& velocity) {

}

// Changing velocity direction and maybe magnitude when there's a collision 
void SquareBall::Bounce(const FloatRect& other) {
	//check the collider
}

// overloaded Bounce when it reaches the top/bottom of screen
void SquareBall::Bounce() {
	//if top or bottom
}