#include "RayClass.h"

RayClass::RayClass()
{

}
RayClass::RayClass(const RayClass &other)
{

}
RayClass::~RayClass()
{
	
}

void RayClass::SetRay(D3DClass *direct3D, 
	CameraClass *camera, 
	HWND hwnd, 
	int screenWidth, 
	int screenHeight, 
	int cursorX, 
	int cursorY)
{
	RayAtLocalSpace(direct3D, camera, screenWidth, screenHeight, cursorX, cursorY);
}

void RayClass::RayAtViewSpace(D3DClass *direct3D, RayClass &ray, int screenWidth, int screenHeight, int cursorX, int cursorY)
{
	XMMATRIX matProjection;
	XMFLOAT4X4 tempProjection;
	
	direct3D->GetProjectionMatrix(matProjection);
	XMStoreFloat4x4(&tempProjection, matProjection);

	float vx = ((2.0f * cursorX) / screenWidth - 1.0f) / tempProjection._11;
	float vy = ((-2.0f * cursorY) / screenHeight + 1.0f) / tempProjection._22;

	ray.m_vOriginal = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	ray.m_vDirection = XMVectorSet(vx, vy, 1.0f, 0.0f);
}

void RayClass::RayAtLocalSpace(D3DClass *direct3D, CameraClass *camera, int screenWidth, int screenHeight, int cursorX, int cursorY)
{
	XMMATRIX matView, matInvView;
	XMMATRIX matWorld, matInvWorld;
	XMMATRIX matLocal;
	RayClass ray;

	RayAtViewSpace(direct3D, ray, screenWidth, screenHeight, cursorX, cursorY);

	camera->GetViewMatrix(matView);
	matInvView = XMMatrixInverse(&XMMatrixDeterminant(matView), matView);

	direct3D->GetWorldMatrix(matWorld);
	matInvWorld = XMMatrixInverse(&XMMatrixDeterminant(matWorld), matWorld);

	matLocal = XMMatrixMultiply(matInvView, matInvWorld);

	ray.m_vOriginal = XMVector3TransformCoord(ray.m_vOriginal, matLocal);
	ray.m_vDirection = XMVector3TransformNormal(ray.m_vDirection, matLocal);
	ray.m_vDirection = XMVector3Normalize(ray.m_vDirection);

	this->m_vDirection = ray.m_vDirection;
	this->m_vOriginal = ray.m_vOriginal;
}