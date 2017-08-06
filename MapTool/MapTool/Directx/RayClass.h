#pragma once

#include "D3DClass.h"
#include "CameraClass.h"

class RayClass
{
public:
	RayClass();
	RayClass(const RayClass &other);
	~RayClass();

	void SetRay(D3DClass *direct3D, CameraClass *camera, int screenWidth, int screenHeight, int pointx, int y);

public:
	XMVECTOR GetOriginal() { return this->m_vOriginal; };
	XMVECTOR GetDirection() { return this->m_vDirection; };

private:
	void RayAtViewSpace(D3DClass *direct3D, RayClass &ray, int screenWidth, int screenHeight, int x, int y);
	void RayAtLocalSpace(D3DClass *direct3D, CameraClass *camera, int screenWidth, int screenHeight, int x, int y);
	bool IsPick();

private:
	XMVECTOR m_vOriginal;
	XMVECTOR m_vDirection;
};