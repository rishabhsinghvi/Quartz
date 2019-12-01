#include "UIText.h"

#include<iostream>

namespace Quartz
{
	UIText::UIText(float centerX, float centerY, float scaleX, float scaleY, const std::string& str, const std::string& fontName) :
		m_centerX(centerX), m_centerY(centerY), m_scaleX(scaleX), m_scaleY(scaleY), m_isText(true)
	{

		if (!m_Font.loadFromFile(FONT_DIRECTORY + fontName))
		{
			std::cout << "Unable to load font: " << fontName << '\n';
			__debugbreak();
		}

		m_Text.setFont(m_Font);
		m_Text.setCharacterSize(100);
		m_Text.setString(str);

		m_Text.setPosition(static_cast<int>(m_centerX), static_cast<int>(m_centerY));
		m_Text.setScale(m_scaleX, m_scaleY);

		//
		m_Text.setFillColor(sf::Color::Red);

	}

	UIText::UIText(float centerX, float centerY, float scaleX, float scaleY, const sf::Sprite& sprite) :
		m_centerX(centerX), m_centerY(centerY), m_scaleX(scaleX), m_scaleY(scaleY), m_isText(false), m_Sprite(sprite)
	{

		m_Sprite.setPosition(m_centerX, m_centerY);
		m_Sprite.setScale(m_scaleX, m_scaleY);

	}


	bool UIText::contains(float x, float y) const
	{
		return false;
	}

	void UIText::onHover(float x, float y)
	{
		// NOTHING
	}

	void UIText::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_isText)
		{
			target.draw(m_Text, states);
		}
		else
		{
			target.draw(m_Sprite, states);
		}
	}
}