#include "Box.h"

using namespace sf;
using namespace gm;

Box::Box(const Vector2f& position, const Vector2f& size) : GameObject(position, size), direction(MovementDirection::None) {
	body.setPosition(position);
	body.setSize(size);
}

void Box::update(sf::RenderWindow& window, float deltaTime){
	move(Vector2f(PlayerMovementSpeedPerSecond * direction * deltaTime, 0));
}

void Box::render(sf::RenderWindow& window, float deltaTime) {
	window.draw(body);
}

void Box::setPosition(const Vector2f& position) {
	GameObject::setPosition(position);
	// Don't forget to update the Box's shape position to match the new position
	body.setPosition(position);
}

void Box::move(const Vector2f& velocity) {
	GameObject::move(velocity);
	// Don't forget to update the Box's shape position to match the new position
	body.setPosition(position);
}

void Box::setMovmentDirection(MovementDirection direction) {
	this->direction = direction;
}

MovementDirection Box::getMovementDirection() const {
	return direction;
}


const Color& Box::getFillColor() const {
	return body.getFillColor();
}

void Box::setFillColor(const Color& color) {
	body.setFillColor(color);
}