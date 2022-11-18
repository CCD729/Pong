#ifndef SQUARE_BALL_H
#define SQUARE_BALL_H

#include "GameObject.h"

namespace gm {
    // Box movement speed
    const int PlayerMovementSpeedPerSecond = 300;

    enum MovementDirection {
        None = 0,
        Left = -1,
        Right = 1
    };

    class SquareBall :
        public GameObject
    {
    protected:
        sf::RectangleShape body;
        MovementDirection direction;
    public:
        SquareBall(const sf::Vector2f& position, const sf::Vector2f& size);

        virtual void update(sf::RenderWindow& window, float deltaTime) override;

        virtual void render(sf::RenderWindow& window, float deltaTime) override;

        virtual void setPosition(const sf::Vector2f& position) override;

        // Move from current position to a new one with a specified velocity
        virtual void move(const sf::Vector2f& velocity) override;

        virtual void setMovmentDirection(MovementDirection direction);

        virtual MovementDirection getMovementDirection() const;

        const sf::Color& getFillColor() const;

        void setFillColor(const sf::Color& color);

        const sf::Vector2f& getVelocity() const;

        void getVelocity(const sf::Vector2f& velocity);

        // Changing velocity direction and maybe magnitude when there's a collision 
        void Bounce(const sf::FloatRect& other);

        // overloaded Bounce when it reaches the top/bottom of screen
        void Bounce();
    };
}

#endif