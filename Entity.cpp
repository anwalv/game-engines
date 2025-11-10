#include "Entity.h"
#include <iostream>
void resizeImage(const sf::Image& originalImage, sf::Image& resizedImage)
{
    const sf::Vector2u originalImageSize = originalImage.getSize();
    const sf::Vector2u resizedImageSize = resizedImage.getSize();

    for (unsigned int y = 0u; y < resizedImageSize.y; ++y)
    {
        for (unsigned int x = 0u; x < resizedImageSize.x; ++x)
        {
            unsigned int origX = static_cast<unsigned int>(
                static_cast<double>(x) / resizedImageSize.x * originalImageSize.x
                );
            unsigned int origY = static_cast<unsigned int>(
                static_cast<double>(y) / resizedImageSize.y * originalImageSize.y
                );

            resizedImage.setPixel(x, y, originalImage.getPixel(origX, origY));
        }
    }
}

Entity::Entity(const std::string& texturePath, const sf::Vector2f& position)
{
    sf::Image originalImage;
    if (!originalImage.loadFromFile(texturePath))
    {
        std::cerr << "Error: Could not load image from " << texturePath << std::endl;
        return;
    }

    sf::IntRect spriteRect(0, 0, 64, 96);
    sf::Vector2u originalSize = originalImage.getSize();
    sf::Vector2u newSize(64, 96);

    sf::Image resizedImage;
    resizedImage.create(newSize.x, newSize.y);
    resizeImage(originalImage, resizedImage);

    if (!m_texture.loadFromImage(resizedImage))
    {
        std::cerr << "Error: Could not create texture from resized image" << std::endl;
        return;
    }

    m_texture.setSmooth(false);


    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(spriteRect);
    m_sprite.setPosition(position);

    m_shape.setSize(sf::Vector2f(spriteRect.width * 0.4f, spriteRect.height * 0.25f));
    m_shape.setOrigin(m_shape.getSize().x / 2.f, m_shape.getSize().y);
    m_shape.setPosition(position.x + spriteRect.width / 2.f, position.y + spriteRect.height);
    m_shape.setFillColor(sf::Color(0, 255, 0, 100));
    m_shape.setOutlineColor(sf::Color::Green);
    m_shape.setOutlineThickness(1.f);
}


void Entity::draw(sf::RenderWindow& window, bool isDebugMode) const
{
    window.draw(m_sprite);
    if (isDebugMode) { window.draw(m_shape); };
}
