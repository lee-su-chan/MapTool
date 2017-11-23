#pragma once

#define DIRECTINPUT_VERTSION 0x0800

#include <dinput.h>
#include "../MFC_Core.h"

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass &);
	~InputClass();

	bool initialze(HINSTANCE, HWND[], int, int);
	void Shutdown();
	bool Frame();

	bool IsEscapePressed();

	void GetMouseLocation(int &, int &);
	bool IsMouseLeftClick();
	bool IsMouseRightClick();
	bool IsMouseMoved();
	void GetMouseAddPos(int &, int &);
	bool GetMouseWindowPosition(int &, int &);

	bool IsLeftPressed();
	bool IsRightPressed();
	bool IsUpPressed();
	bool IsDownPressed();
	bool IsWPressed();
	bool IsAPressed();
	bool IsSPressed();
	bool IsDPressed();
	bool IsQPressed();
	bool IsEPressed();
	bool IsXPressed();
	bool IsPgUpPressed();
	bool IsPgDownPressed();

	bool IsF1Toggled();
	bool IsF2Toggled();
	bool IsF3Toggled();
	bool IsF4Toggled();
	bool IsF5Toggled();

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8 *m_directInput;
	IDirectInputDevice8 *m_keyboard;
	IDirectInputDevice8 *m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;

	bool m_F1_released;
	bool m_F2_released;
	bool m_F3_released;
	bool m_F4_released;
	bool m_F5_released;

	HWND m_directXViewHwnd;
};