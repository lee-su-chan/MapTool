#include "InputClass.h"

InputClass::InputClass()
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
}

InputClass::InputClass(const InputClass &other)
{
}

InputClass::~InputClass()
{
}

bool InputClass::initialze(HINSTANCE hinstance,
	HWND hwnd, 
	int screenWidth,
	int screenHeight)
{
	HRESULT result;
	
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_mouseX = 0;
	m_mouseY = 0;

	result = DirectInput8Create(hinstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void **)&m_directInput,
		NULL);

	if (FAILED(result))
		return false;

	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
		return false;

	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
		return false;

	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
		return false;

	result = m_keyboard->Acquire();
	if (FAILED(result))
		return false;

	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
		return false;

	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
		return false;

	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
		return false;

	result = m_mouse->Acquire();
	if (FAILED(result))
		return false;

	m_F1_released = true;
	m_F2_released = true;
	m_F3_released = true;
	m_F4_released = true;
	m_F5_released = true;

	return true;
}

void InputClass::Shutdown()
{
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = NULL;
	}

	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = NULL;
	}

	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = NULL;
	}

	return;
}

bool InputClass::Frame()
{
	bool result;

	result = ReadKeyboard();
	if (!result)
		return false;

	result = ReadMouse();
	if (!result)
		return false;

	ProcessInput();

	return true;
}

bool InputClass::IsEscapePressed()
{
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
		return true;

	return false;
}

void InputClass::GetMouseLocation(int &mouseX, int &mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;

	return;
}

bool InputClass::IsMouseRightClick()
{
	if (m_mouseState.rgbButtons[1] & 0x80)
		return true;

	return false;
}

bool InputClass::IsMouseMoved()
{
	if (m_mouseState.lX != 0 && m_mouseState.lY != 0)
		return true;

	return false;
}

void InputClass::GetMouseAddPos(int &mouseAddX, int &mouseAddY)
{
	mouseAddX = m_mouseState.lX;
	mouseAddY = m_mouseState.lY;

	return;
}

bool InputClass::IsLeftPressed()
{
	if (m_keyboardState[DIK_LEFT] & 0x80)
		return true;

	return false;
}

bool InputClass::IsRightPressed()
{
	if (m_keyboardState[DIK_RIGHT] & 0x80)
		return true;

	return false;
}

bool InputClass::IsUpPressed()
{
	if (m_keyboardState[DIK_UP] & 0x80)
		return true;

	return false;
}

bool InputClass::IsDownPressed()
{
	if (m_keyboardState[DIK_DOWN] & 0x80)
		return true;

	return false;
}

bool InputClass::IsWPressed()
{
	if (m_keyboardState[DIK_W] & 0x80)
		return true;

	return false;
}

bool InputClass::IsXPressed()
{
	if (m_keyboardState[DIK_X] & 0x80)
		return true;

	return false;
}

bool InputClass::IsAPressed()
{
	if (m_keyboardState[DIK_A] & 0x80)
		return true;

	return false;
}

bool InputClass::IsSPressed()
{
	if (m_keyboardState[DIK_S] & 0x80)
		return true;

	return false;
}

bool InputClass::IsDPressed()
{
	if (m_keyboardState[DIK_D] & 0x80)
		return true;

	return false;
}

bool InputClass::IsQPressed()
{
	if (m_keyboardState[DIK_Q] & 0x80)
		return true;

	return false;
}

bool InputClass::IsEPressed()
{
	if (m_keyboardState[DIK_E] & 0x80)
		return true;

	return false;
}

bool InputClass::IsPgUpPressed()
{
	if (m_keyboardState[DIK_PGUP] & 0x80)
		return true;

	return false;
}

bool InputClass::IsPgDownPressed()
{
	if (m_keyboardState[DIK_PGDN] & 0x80)
		return true;

	return false;
}

bool InputClass::IsF1Toggled()
{
	if (m_keyboardState[DIK_F1] & 0x80)
	{
		if (m_F1_released)
		{
			m_F1_released = false;
			
			return true;
		}
	}
	else
	{
		m_F1_released = true;
	}

	return false;
}

bool InputClass::IsF2Toggled()
{
	if (m_keyboardState[DIK_F2] & 0x80)
	{
		if (m_F2_released)
		{
			m_F2_released = false;

			return true;
		}
	}
	else
	{
		m_F2_released = true;
	}

	return false;
}

bool InputClass::IsF3Toggled()
{
	if (m_keyboardState[DIK_F3] & 0x80)
	{
		if (m_F3_released)
		{
			m_F3_released = false;

			return true;
		}
	}
	else
	{
		m_F3_released = true;
	}

	return false;
}

bool InputClass::IsF4Toggled()
{
	if (m_keyboardState[DIK_F4] & 0x80)
	{
		if (m_F4_released)
		{
			m_F4_released = false;

			return true;
		}
	}
	else
	{
		m_F4_released = true;
	}

	return false;
}

bool InputClass::IsF5Toggled()
{
	if (m_keyboardState[DIK_F5] & 0x80)
	{
		if (m_F5_released)
		{
			m_F5_released = false;

			return true;
		}
	}
	else
	{
		m_F5_released = true;
	}

	return false;
}

bool InputClass::ReadKeyboard()
{
	HRESULT result;

	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_keyboard->Acquire();
		else
			return false;
	}

	return true;
}

bool InputClass::ReadMouse()
{
	HRESULT result;

	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_mouse->Acquire();
		else
			return false;
	}

	return true;
}

void InputClass::ProcessInput()
{
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	if (m_mouseX < 0) m_mouseX = 0;
	if (m_mouseY < 0) m_mouseY = 0;

	if (m_mouseX > m_screenWidth) m_mouseX = m_screenWidth;
	if (m_mouseY > m_screenHeight) m_mouseY = m_screenHeight;

	return;
}