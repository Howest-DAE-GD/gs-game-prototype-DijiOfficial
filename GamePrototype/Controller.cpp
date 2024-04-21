#define WIN32_LEAN_AND_MEAN
#include "pch.h"
#include "windows.h"
#include <XInput.h>
#include "Controller.h"
#include <cassert>

#include <iostream>
class Controller::XInput
{
	public:
		XInput(int controllerIdx) 
			: m_ControllerIdx{ controllerIdx }
		{
			//this does not work the way I intended
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));
			DWORD dwResult = XInputGetState(controllerIdx, &state);

			//if (dwResult != ERROR_SUCCESS)
			//{
			//	assert("Controller not connected");
			//}
			if (dwResult != ERROR_SUCCESS)
			{
				switch (dwResult)
				{
				case ERROR_DEVICE_NOT_CONNECTED:
					std::cout << "Controller error! Device not connected! \n";
					break;
				case ERROR_NOT_SUPPORTED:
					std::cout << "Controller error! Not supported! \n";
					break;
				default:
					std::cout << "Controller error! \n";
					break;
				}
			}
		}

		XInput(const XInput& other) = delete;
		XInput(XInput&& other) = delete;
		XInput& operator=(const XInput& other) = delete;
		XInput& operator=(XInput&& other) = delete;

		void ProcessControllerInput()
		{
			CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
			XInputGetState(m_ControllerIdx, &m_CurrentState);

			auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
			m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
			m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
		}

		bool IsDownThisFrame(unsigned int button) { return m_ButtonsPressedThisFrame & button; }
		bool IsUpThisFrame(unsigned int button) { return m_ButtonsReleasedThisFrame & button; };
		bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }

	private:
		int m_ControllerIdx{};
		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};
		unsigned int m_ButtonsPressedThisFrame{};
		unsigned int m_ButtonsReleasedThisFrame{};
};

Controller::Controller(int controllerIdx) 
	: m_XInputUPtr{ std::make_unique<XInput>(controllerIdx) }
{
}

Controller::~Controller()
{
}

void Controller::ProcessControllerInput()
{
	m_XInputUPtr->ProcessControllerInput();
}

bool Controller::IsKeyDownThisFrame(const Button& button)
{
	return m_XInputUPtr->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool Controller::IsKeyUpThisFrame(const Button& button)
{
	return m_XInputUPtr->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool Controller::IsPressed(const Button& button) const
{
	return m_XInputUPtr->IsPressed(static_cast<unsigned int>(button));;
}
