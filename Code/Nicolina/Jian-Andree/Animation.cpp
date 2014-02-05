//Animation.cpp

#include "stdafx.h"
#include "Animation.h"

Animation::Animation() : _texture(NULL) {

};

void Animation::AddFrame(sf::IntRect rect) {
    _frames.push_back(rect);
};

void Animation::SetSpritesheet(const sf::Texture& texture) {
    _texture = &texture;
};

const sf::Texture* Animation::GetSpritesheet() const {
    return _texture;
};

std::size_t Animation::GetSize() const {
    return _frames.size();
};

const sf::IntRect& Animation::GetFrame(std::size_t n) const {
    return _frames[n];
};