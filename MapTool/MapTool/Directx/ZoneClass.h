#pragma once

#include "D3D_Defines.h"

#include "D3DClass.h"
#include "InputClass.h"
#include "ShaderManagerClass.h"
#include "TextureManagerClass.h"
#include "TimerClass.h"
#include "UserInterfaceClass.h"
#include "CameraClass.h"
#include "LightClass.h"	
#include "PositionClass.h"
#include "FrustumClass.h"
#include "SkyDomeClass.h"
#include "TerrainClass.h"
#include "PickingToolSingletonClass.h"

class ZoneClass
{
public:
	ZoneClass();
	ZoneClass(const ZoneClass &);
	~ZoneClass();

	bool Initialize(D3DClass *, HWND, int, int, float, const MyStruct::TERRAIN_DESC &);
	void Shutdown();
	bool Frame(D3DClass *, InputClass *, ShaderManagerClass *, TextureManagerClass *, float, int, const MyStruct::TERRAIN_DESC &);
	bool Render(D3DClass *, ShaderManagerClass *, TextureManagerClass *, const MyStruct::TERRAIN_DESC &);

private:
	void HandleMovementInput(D3DClass *, InputClass *, float);
	void PushedF3Button(float);

private:
	UserInterfaceClass *m_UserInterface;
	CameraClass *m_Camera;
	LightClass *m_Light;
	PositionClass *m_Position;
	FrustumClass *m_Frustum;
	SkyDomeClass *m_SkyDome;
	TerrainClass *m_Terrain;

	HWND m_Hwnd;

public:
	bool m_IsDisplayUI, m_IsWireFrame, m_IsPlay, m_IsCellLines, m_IsHeightLocked;
	float m_PosX, m_PosY, m_PosZ;
	int m_ScreenWidth, m_ScreenHeight;
};