#ifndef QUARTZ_INPUT_HANDLER_H
#define QUARTZ_INPUT_HANDLER_H

#include "Events/AppEventQueue.h"
#include "Events/ApplicationEvents.h"
#include "DeviceContext.h"
#include "Inputs.h"

#include <unordered_map>

namespace Quartz
{
	class InputHandler : public Observable
	{
	private:
		DeviceContext* m_deviceContext = nullptr;
		std::unordered_map<Keycode, Action> m_inputMapping;

	public:

		void init(DeviceContext* dc);

		Action getUserInput() const;

		virtual void handleApplicationEvent(AppEvent& event);

	private:

		Keycode getKeycodeFromInput() const;

	};
}

#endif