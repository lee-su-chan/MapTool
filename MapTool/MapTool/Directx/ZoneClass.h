#ifndef _ZONECLASS_H_
#define _ZONECLASS_H_

#include <DirectXCollision.h>

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
#include "Ray.h"
#include "Resources\MyResource.h"

class ZoneClass
{
public:
	ZoneClass();
	ZoneClass(const ZoneClass &);
	~ZoneClass();

	bool Initialize(D3DClass *, HWND, int, int, float, MyStruct::TERRAIN_DESC &);
	void Shutdown();
	bool Frame(D3DClass *, InputClass *, ShaderManagerClass *, TextureManagerClass *, float, int, MyStruct::TERRAIN_DESC &);

private:
	void HandleMovementInput(D3DClass *, InputClass *, float);
	bool Render(D3DClass *, ShaderManagerClass *, TextureManagerClass *, MyStruct::TERRAIN_DESC &);

	void PushedF3Button(float);

private:
	UserInterfaceClass *m_UserInterface;
	CameraClass *m_Camera;
	LightClass *m_Light;
	PositionClass *m_Position;
	FrustumClass *m_Frustum;
	SkyDomeClass *m_SkyDome;
	TerrainClass *m_Terrain;
	Ray m_Ray;
	bool m_displayUI, m_wireFrame, m_play, m_cellLines, m_heightLocked;
	float m_posX, m_posY, m_posZ;
	int m_ScreenWidth, m_ScreenHeight;
};

#endif