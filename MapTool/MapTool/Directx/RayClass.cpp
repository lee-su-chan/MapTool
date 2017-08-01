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

void RayClass::SetRay(D3DClass *direct3D, CameraClass *camera, int screenWidth, int screenHeight, int x, int y)
{
	RayAtLocalSpace(direct3D, camera, screenWidth, screenHeight, x, y);
}

void RayClass::RayAtViewSpace(D3DClass *direct3D, RayClass &ray, int screenWidth, int screenHeight, int x, int y)
{
	XMMATRIX matProjection;
	XMFLOAT4X4 tempProjection;
	
	direct3D->GetProjectionMatrix(matProjection);
	XMStoreFloat4x4(&tempProjection, matProjection);

	float vx = ((2.0f * x) / screenWidth - 1.0f) / tempProjection._11;
	float vy = ((-2.0f * y) / screenHeight + 1.0f) / tempProjection._22;

	ray.m_vOriginal = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	ray.m_vDirection = XMVectorSet(vx, vy, 1.0f, 0.0f);
}

void RayClass::RayAtLocalSpace(D3DClass *direct3D, CameraClass *camera, int screenWidth, int screenHeight, int x, int y)
{
	XMMATRIX matView, matInvView;
	XMMATRIX matWorld, matInvWorld;
	XMMATRIX matLocal;
	RayClass ray;

	RayAtViewSpace(direct3D, ray, screenWidth, screenHeight, x, y);

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