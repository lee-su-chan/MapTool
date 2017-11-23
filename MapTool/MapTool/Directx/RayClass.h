#pragma once

#include "D3D_Core.h"
#include "D3DClass.h"
#include "CameraClass.h"

class RayClass
{
public:
	RayClass() = default;
	RayClass(const RayClass &other) = default;
	~RayClass() = default;

public:
	inline XMVECTOR GetOriginal() { return m_vOriginal; };
	inline XMVECTOR GetDirection() { return m_vDirection; };

public:
	void SetRay(D3DClass *direct3D, CameraClass *camera, int screenWidth, int screenHeight, int mousePosX, int mousePosY);

private:
	void SetRayAtViewSpace(CameraClass *camera, int screenWidth, int screenHeight, int cursorX, int cursorY);
	void SetRayAtLocalSpace(D3DClass *direct3D, CameraClass *camera);

private:
	XMVECTOR m_vOriginal;
	XMVECTOR m_vDirection;
};