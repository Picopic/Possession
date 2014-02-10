//AnimatedSprites.h

#ifndef ANIMATEDSPRITE_INCLUDE
#define ANIMATEDSPRITE_INCLUDE

#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include "Animation.h"

class AnimatedSprites : public sf::Drawable, public sf::Transformable {
public:
    explicit AnimatedSprites(sf::Time frameTime = sf::seconds(0.2f), bool paused = false, bool looped = true);

    void Update(sf::Time deltaTime);
    void SetAnimation(const Animation& animation);
    void SetFrameTime(sf::Time time);
    void Play();
    void Play(const Animation& animation);
    void Pause();
    void Stop();
    void SetLooped(bool looped);
    void SetColor(const sf::Color& color);
    const Animation* GetAnimation() const;
    sf::FloatRect GetLocalBounds() const;
    sf::FloatRect GetGlobalBounds() const;
    bool isLooped() const;
    bool isPlaying() const;
    sf::Time GetFrameTime() const;
    void SetFrame(std::size_t newFrame, bool resetTime = true);

private:
    const Animation* _animation;
    sf::Time _frameTime;
    sf::Time _currentTime;
    std::size_t _currentFrame;
    bool _isPaused;
    bool _isLooped;
    const sf::Texture* _texture;
    sf::Vertex _vertices[4];

    virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif