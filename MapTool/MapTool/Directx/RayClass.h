#ifndef _RAY_H_
#define _RAY_H_

#include <iostream>
#include <direct.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>

#include "D3DClass.h"
#include "CameraClass.h"

using namespace DirectX;
using namespace std;

class RayClass
{
public:
	RayClass();
	RayClass(const RayClass &other);
	~RayClass();

	void OnRay(D3DClass *direct3D, CameraClass *camera, int screenWidth, int screenHeight, int x, int y);

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

#endif