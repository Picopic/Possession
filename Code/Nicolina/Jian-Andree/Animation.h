//Animation.h

#ifndef ANIMATION_INCLUDE
#define ANIMATION_INCLUDE

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

class Animation {
public:
    Animation();

    void AddFrame(sf::IntRect rect);
    void SetSpritesheet(const sf::Texture& texture);
    const sf::Texture* GetSpritesheet() const;
    std::size_t GetSize() const;
    const sf::IntRect& GetFrame(std::size_t n) const;

private:
    std::vector<sf::IntRect> _frames;
    const sf::Texture* _texture;
};

#endif