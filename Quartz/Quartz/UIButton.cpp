#include "UIButton.h"

#include<iostream>

constexpr float HOVER_FACTOR = 1.5f;

namespace Quartz
{

	extern const unsigned int WINDOW_WIDTH;
	extern const unsigned int WINDOW_HEIGHT;

	UIButton::UIButton(float centerX, float centerY, float scaleX, float scaleY, const std::string& str, const std::string& fontName):
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

		m_Text.setPosition(m_centerX * WINDOW_WIDTH, m_centerY * WINDOW_HEIGHT);
		m_Text.setScale(m_scaleX, m_scaleY);
		m_Text.setOrigin(m_Text.getLocalBounds().width / 2, m_Text.getLocalBounds().height / 2);

		//
		m_Text.setFillColor(sf::Color::Red);

	}

	UIButton::UIButton(float centerX, float centerY, float scaleX, float scaleY, const sf::Sprite& sprite):
		m_centerX(centerX), m_centerY(centerY), m_scaleX(scaleX), m_scaleY(scaleY), m_isText(false), m_Sprite(sprite) {
		
		m_Sprite.setPosition(m_centerX * WINDOW_WIDTH, m_centerY * WINDOW_HEIGHT);
		m_Sprite.setScale(m_scaleX, m_scaleY);

	}


	bool UIButton::contains(float x, float y) const
	{
		if (m_isText)
		{
			return m_Text.getGlobalBounds().contains(x, y);
		}
		else
		{
			return m_Sprite.getGlobalBounds().contains(x, y);
		}
	}

	void UIButton::onHover(float x, float y)
	{
		if (contains(x, y))
		{
			if (m_isText)
			{
				m_Text.setScale(m_scaleX * HOVER_FACTOR, m_scaleY * HOVER_FACTOR);
			}
			else
			{
				m_Sprite.setScale(m_scaleX * HOVER_FACTOR, m_scaleY * HOVER_FACTOR);
			}
		}
		else
		{
			if (m_isText)
			{
				m_Text.setScale(m_scaleX, m_scaleY);
			}
			else
			{
				m_Sprite.setScale(m_scaleX, m_scaleY);
			}
		}
	}

	void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
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

	void UIButton::setCallback(const std::function<void(DeviceContext*)> callback)
	{
		m_Callback = callback;
	}

	void UIButton::callback(DeviceContext* dc)
	{
		m_Callback(dc);
	}




}
