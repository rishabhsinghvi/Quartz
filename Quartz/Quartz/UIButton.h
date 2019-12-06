#ifndef QUARTZ_UI_BUTTON_H
#define QUARTZ_UI_BUTTON_H

#include "UIElement.h"
#include "DeviceContext.h"
#include "Events/ApplicationEvents.h"

#include "SFML/Graphics.hpp"

#include<functional>

namespace Quartz
{
	extern const std::string FONT_DIRECTORY;

	class UIButton : public UIElement
	{
	private:
		float m_centerX;
		float m_centerY;
		float m_scaleX;
		float m_scaleY;
		bool m_isText; // decides whether to draw text or texture
		sf::Text m_Text; 
		sf::Font m_Font;
		sf::Sprite m_Sprite;
		std::function<void(DeviceContext*)> m_Callback;

	public:

		UIButton() = delete;

		// for text
		UIButton(float centerX, float centerY, float scaleX, float scaleY, const std::string& str,  const std::string& fontName = "QuiteMagical.ttf");

		// for textures
		UIButton(float centerX, float centerY, float scaleX, float scaleY, const sf::Sprite& sprite);

		virtual bool contains(float x, float y) const override;

		virtual void onHover(float x, float y) override;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void setCallback(const std::function<void(DeviceContext*)> callback);

		virtual void callback(DeviceContext* dc) override; 
	};
}


#endif