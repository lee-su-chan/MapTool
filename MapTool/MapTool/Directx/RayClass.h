#pragma once

#include "D3DClass.h"
#include "CameraClass.h"

class RayClass
{
public:
	RayClass();
	RayClass(const RayClass &other);
	~RayClass();

public:
	XMVECTOR GetOriginal() { return this->m_vOriginal; };
	XMVECTOR GetDirection() { return this->m_vDirection; };

public:
	void SetRay(D3DClass *direct3D, CameraClass *camera, HWND hwnd, int screenWidth, int screenHeight, int cursorX, int cursorY);

private:
	void RayAtViewSpace(D3DClass *direct3D, RayClass &ray, int screenWidth, int screenHeight, int cursorX, int cursorY);
	void RayAtLocalSpace(D3DClass *direct3D, CameraClass *camera, int screenWidth, int screenHeight, int cursorX, int cursorY);

private:
	XMVECTOR m_vOriginal;
	XMVECTOR m_vDirection;
};