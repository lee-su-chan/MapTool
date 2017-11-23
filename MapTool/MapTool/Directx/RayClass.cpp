#include "RayClass.h"

void RayClass::SetRay(D3DClass *direct3D, 
	CameraClass *camera, 
	int screenWidth, 
	int screenHeight, 
	int mousePosX,
	int mousePosY)
{
	SetRayAtViewSpace(camera, screenWidth, screenHeight, mousePosX, mousePosY);
	SetRayAtLocalSpace(direct3D, camera);
}

void RayClass::SetRayAtViewSpace(CameraClass *camera, int screenWidth, int screenHeight, int mousePosX, int mousePosY)
{
	XMMATRIX matProjection;
	XMFLOAT4X4 tempProjection;
	
	camera->GetViewMatrix(matProjection);
	XMStoreFloat4x4(&tempProjection, matProjection);

	float vx = ((2.0f * mousePosX) / screenWidth - 1.0f) / tempProjection._11;
	float vy = ((-2.0f * mousePosY) / screenHeight + 1.0f) / tempProjection._22;

	m_vOriginal = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	m_vDirection = XMVectorSet(vx, vy, 1.0f, 0.0f);
}

void RayClass::SetRayAtLocalSpace(D3DClass *direct3D, CameraClass *camera)
{
	XMMATRIX matView, matInvView;
	XMMATRIX matWorld, matInvWorld;
	XMMATRIX matLocal;

	camera->GetViewMatrix(matView);
	matInvView = XMMatrixInverse(&XMMatrixDeterminant(matView), matView);

	direct3D->GetWorldMatrix(matWorld);
	matInvWorld = XMMatrixInverse(&XMMatrixDeterminant(matWorld), matWorld);
	matLocal = XMMatrixMultiply(matInvView, matInvWorld);
	
	m_vOriginal = XMVector3TransformCoord(m_vOriginal, matLocal);
	m_vDirection = XMVector3TransformNormal(m_vDirection, matLocal);
	m_vDirection = XMVector3Normalize(m_vDirection);
}