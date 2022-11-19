#include "Paddle.h"

using namespace sf;
using namespace gm;

Paddle::Paddle(const Vector2f& position, const Vector2f& size) : GameObject(position, size), direction(MovementDirection::None) {
	body.setPosition(position);
	body.setSize(size);
}

void Paddle::update(sf::RenderWindow& window, float deltaTime) {
	move(Vector2f(0, PlayerMovementSpeedPerSecond * direction * deltaTime));
}

void Paddle::render(sf::RenderWindow& window, float deltaTime) {
	window.draw(body);
}

void Paddle::setPosition(const Vector2f& position) {
	GameObject::setPosition(position);
	// Don't forget to update the Box's shape position to match the new position
	body.setPosition(position);
}

void Paddle::move(const Vector2f& velocity) {
	GameObject::move(velocity);
	// Don't forget to update the Box's shape position to match the new position
	body.setPosition(position);
}

void Paddle::setMovementDirection(MovementDirection direction) {
	this->direction = direction;
}

MovementDirection Paddle::getMovementDirection() const {
	return direction;
}

const Color& Paddle::getFillColor() const {
	return body.getFillColor();
}

void Paddle::setFillColor(const Color& color) {
	body.setFillColor(color);
}

const Vector2f Paddle::getSize() const {
	return body.getSize();
}

void Paddle::setSize(const Vector2f& size) {
	body.setSize(size);
}