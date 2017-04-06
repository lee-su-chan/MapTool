#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#include "InputClass.h"
#include "D3DClass.h"
#include "ShaderManagerClass.h"
#include "TextureManagerClass.h"
#include "TimerClass.h"
#include "FpsClass.h"
#include "ZoneClass.h"

class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass &);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND[], int, int);
	void Shutdown();
	bool Frame();

private:
	InputClass *m_Input;
	D3DClass *m_Direct3D;
	ShaderManagerClass *m_ShaderManager;
	TextureManagerClass *m_TextureManager;
	TimerClass *m_Timer;
	FpsClass *m_Fps;
	ZoneClass *m_Zone;
};

#endif