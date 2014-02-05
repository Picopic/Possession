//AnimatedSprites.cpp

#include "stdafx.h"
#include "AnimatedSprites.h"

AnimatedSprites::AnimatedSprites(sf::Time frameTime, bool paused, bool looped) :
    _animation(NULL), _frameTime(frameTime), _currentFrame(0),
	_isPaused(paused), _isLooped(looped), _texture(NULL)
{

};

void AnimatedSprites::SetAnimation(const Animation& animation) {
    _animation = &animation;
    _texture = _animation->GetSpritesheet();
    _currentFrame = 0;
    SetFrame(_currentFrame);
};

void AnimatedSprites::SetFrameTime(sf::Time time) {
    _frameTime = time;
};

void AnimatedSprites::Play() {
    _isPaused = false;
};

void AnimatedSprites::Play(const Animation& animation) {
    if (GetAnimation() != &animation)
        SetAnimation(animation);
    Play();
};

void AnimatedSprites::Pause() {
    _isPaused = true;
};

void AnimatedSprites::Stop() {
    _isPaused = true;
    _currentFrame = 0;
    SetFrame(_currentFrame);
};

void AnimatedSprites::SetLooped(bool looped) {
    _isLooped = looped;
};

void AnimatedSprites::SetColor(const sf::Color& color) {
    // Update the vertices' color
    _vertices[0].color = color;
    _vertices[1].color = color;
    _vertices[2].color = color;
    _vertices[3].color = color;
};

const Animation* AnimatedSprites::GetAnimation() const {
    return _animation;
};

sf::FloatRect AnimatedSprites::GetLocalBounds() const {
    sf::IntRect rect = _animation->GetFrame(_currentFrame);

    float width = static_cast<float>(std::abs(rect.width));
    float height = static_cast<float>(std::abs(rect.height));

    return sf::FloatRect(0.f, 0.f, width, height);
};

sf::FloatRect AnimatedSprites::GetGlobalBounds() const {
    return getTransform().transformRect(GetLocalBounds());
};

bool AnimatedSprites::isLooped() const {
    return _isLooped;
};

bool AnimatedSprites::isPlaying() const {
    return !_isPaused;
};

sf::Time AnimatedSprites::GetFrameTime() const {
    return _frameTime;
};

void AnimatedSprites::SetFrame(std::size_t newFrame, bool resetTime) {
    if (_animation) {
        //calculate new vertex positions and texture coordiantes
        sf::IntRect rect = _animation->GetFrame(newFrame);

        _vertices[0].position = sf::Vector2f(0.f, 0.f);
        _vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
        _vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
        _vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

        float left = static_cast<float>(rect.left) + 0.0001f;
        float right = left + static_cast<float>(rect.width);
        float top = static_cast<float>(rect.top);
        float bottom = top + static_cast<float>(rect.height);

        _vertices[0].texCoords = sf::Vector2f(left, top);
        _vertices[1].texCoords = sf::Vector2f(left, bottom);
        _vertices[2].texCoords = sf::Vector2f(right, bottom);
        _vertices[3].texCoords = sf::Vector2f(right, top);
    }

    if (resetTime)
        _currentTime = sf::Time::Zero;
};

void AnimatedSprites::Update(sf::Time deltaTime) {
    // if not paused and we have a valid animation
    if (!_isPaused && _animation) {
        // add delta time
        _currentTime += deltaTime;

        // if current time is bigger then the frame time advance one frame
        if (_currentTime >= _frameTime)
        {
            // reset time, but keep the remainder
            _currentTime = sf::microseconds(_currentTime.asMicroseconds() % _frameTime.asMicroseconds());

            // get next Frame index
            if (_currentFrame + 1 < _animation->GetSize())
                _currentFrame++;
            else
            {
                // animation has ended
                _currentFrame = 0; // reset to start

                if (!_isLooped)
                {
                    _isPaused = true;
                }

            }

            // set the current frame, not reseting the time
            SetFrame(_currentFrame, false);
        }
    }
};

void AnimatedSprites::Draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (_animation && _texture) {
		states.transform *= getTransform();
		states.texture = _texture;
		target.draw(_vertices, 4, sf::Quads, states);
    }
};