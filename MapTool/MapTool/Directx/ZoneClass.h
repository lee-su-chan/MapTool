#pragma once

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
#include "PickingToolClass.h"

class ZoneClass
{
public:
	ZoneClass();
	ZoneClass(const ZoneClass &);
	~ZoneClass();

	bool Initialize(D3DClass *, HWND, int, int, float, const MyStruct::TERRAIN_DESC &);
	bool Frame(D3DClass *, InputClass *, ShaderManagerClass *, TextureManagerClass *, float, int, const MyStruct::TERRAIN_DESC &);
	bool Render(D3DClass *, ShaderManagerClass *, TextureManagerClass *, const MyStruct::TERRAIN_DESC &);
	void Shutdown();

private:
	void HandleMovementInput(D3DClass *, InputClass *, float);
	void PushedF3Button(float);

private:
	UserInterfaceClass *m_UserInterface;
	CameraClass *m_Camera;
	LightClass *m_Light;
	FrustumClass *m_Frustum;
	SkyDomeClass *m_SkyDome;
	TerrainClass *m_Terrain;
	PickingToolClass *m_Pick;

	HWND m_Hwnd;

public:
	bool m_IsDisplayUI;
	bool m_IsWireFrame;
	bool m_IsPlay;
	bool m_IsCellLines;
	bool m_IsHeightLocked;

	float m_PosX;
	float m_PosY;
	float m_PosZ;

	int m_ScreenWidth;
	int m_ScreenHeight;

	XMVECTOR m_PickPos;
};