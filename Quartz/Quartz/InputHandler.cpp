#include "InputHandler.h"
#include "Logger/Logger.h"

#include "SFML/Graphics.hpp"

#define KEY_PRESSED(x) sf::Keyboard::isKeyPressed(sf::Keyboard::##x)
#define MOUSE_PRESSED(x) sf::Mouse::isButtonPressed(sf::Mouse::##x)

namespace Quartz
{

	void InputHandler::init(DeviceContext* dc)
	{
		m_deviceContext = dc;

		// TODO: Read input mapping from config JSON
		m_inputMapping = {
			{Keycode::K_None, Action::A_None},
			{Keycode::K_A, Action::A_WalkLeft},
			{Keycode::K_D, Action::A_WalkRight},
			{Keycode::K_ShiftA, Action::A_RunLeft},
			{Keycode::K_ShiftD, Action::A_RunRight},
			{Keycode::K_Space, Action::A_Jump},
			{Keycode::M_Left, Action::A_Slash}
		};

		LOG_INFO("InputHandler: Initialized successfully.");
	}

	Action InputHandler::getUserInput() const
	{
		if (!m_isActive)
			return Action::A_None;

		Keycode keycode = getKeycodeFromInput();
		return m_inputMapping.find(keycode)->second;
	}

	void InputHandler::handleApplicationEvent(AppEvent& event)
	{
		if (event.eventType == EventType::SetInputHandlerEvent)
		{
			setActive(std::get<SetInputHandlerEvent>(event.m_Info).m_Value);
		}
	}

	void InputHandler::setActive(bool val)
	{
		m_isActive = val;
	}

	Keycode InputHandler::getKeycodeFromInput() const
	{
		if (KEY_PRESSED(D) && KEY_PRESSED(LShift))
		{
			return Keycode::K_ShiftD;
		}
		else if (KEY_PRESSED(A) && KEY_PRESSED(LShift))
		{
			return Keycode::K_ShiftA;
		}
		else if (KEY_PRESSED(A))
		{
			return Keycode::K_A;
		}
		else if (KEY_PRESSED(D))
		{
			return Keycode::K_D;
		}
		else if (KEY_PRESSED(Space))
		{
			return Keycode::K_Space;
		}
		else if (MOUSE_PRESSED(Left))
		{
			return Keycode::M_Left;
		}
		else
		{
			return Keycode::K_None;
		}
	}
}