#include "FrustumClass.h"

FrustumClass::FrustumClass()
{
}

FrustumClass::FrustumClass(const FrustumClass &other)
{
}

FrustumClass::~FrustumClass()
{
}

void FrustumClass::Initialize(float screenDepth)
{
	m_screenDepth = screenDepth;

	return;
}

void FrustumClass::ConstructFrustum(XMMATRIX projectionMatrix, XMMATRIX viewMatrix)
{
	XMFLOAT4X4 pMatrix, matrix;
	float zMinimum, r, length;
	XMMATRIX finalMatrix;

	XMStoreFloat4x4(&pMatrix, projectionMatrix);

	zMinimum = -pMatrix._43 / pMatrix._33;
	r = m_screenDepth / (m_screenDepth - zMinimum);

	pMatrix._33 = r;
	pMatrix._43 = -r * zMinimum;
	projectionMatrix = XMLoadFloat4x4(&pMatrix);

	finalMatrix = XMMatrixMultiply(viewMatrix, projectionMatrix);
	XMStoreFloat4x4(&matrix, finalMatrix);

	// Calculate near plane of frustum
	m_planes[0][0] = matrix._14 + matrix._13;
	m_planes[0][1] = matrix._24 + matrix._23;
	m_planes[0][2] = matrix._34 + matrix._33;
	m_planes[0][3] = matrix._44 + matrix._43;
	// Normalize the near plane
	length = sqrtf(m_planes[0][0] * m_planes[0][0] +
		m_planes[0][1] * m_planes[0][1] +
		m_planes[0][2] * m_planes[0][2]);
	// Calculate far plane of frustum
	m_planes[0][0] /= length;
	m_planes[0][1] /= length;
	m_planes[0][2] /= length;
	m_planes[0][3] /= length;

	m_planes[1][0] = matrix._14 - matrix._13;
	m_planes[1][1] = matrix._24 - matrix._23;
	m_planes[1][2] = matrix._34 - matrix._33;
	m_planes[1][3] = matrix._44 - matrix._43;
	length = sqrtf(m_planes[1][0] * m_planes[1][0] +
		m_planes[1][1] * m_planes[1][1] +
		m_planes[1][2] * m_planes[1][2]);
	m_planes[1][0] /= length;
	m_planes[1][1] /= length;
	m_planes[1][2] /= length;
	m_planes[1][3] /= length;

	m_planes[2][0] = matrix._14 + matrix._11;
	m_planes[2][1] = matrix._24 + matrix._21;
	m_planes[2][2] = matrix._34 + matrix._31;
	m_planes[2][3] = matrix._44 + matrix._41;
	length = sqrtf(m_planes[2][0] * m_planes[2][0] +
		m_planes[2][1] * m_planes[2][1] +
		m_planes[2][2] * m_planes[2][2]);
	m_planes[2][0] /= length;
	m_planes[2][1] /= length;
	m_planes[2][2] /= length;
	m_planes[2][3] /= length;

	m_planes[3][0] = matrix._14 - matrix._11;
	m_planes[3][1] = matrix._24 - matrix._21;
	m_planes[3][2] = matrix._34 - matrix._31;
	m_planes[3][3] = matrix._44 - matrix._41;
	length = sqrtf(m_planes[3][0] * m_planes[3][0] +
		m_planes[3][1] * m_planes[3][1] +
		m_planes[3][2] * m_planes[3][2]);
	m_planes[3][0] /= length;
	m_planes[3][1] /= length;
	m_planes[3][2] /= length;
	m_planes[3][3] /= length;

	m_planes[4][0] = matrix._14 - matrix._12;
	m_planes[4][1] = matrix._24 - matrix._22;
	m_planes[4][2] = matrix._34 - matrix._32;
	m_planes[4][3] = matrix._44 - matrix._42;
	length = sqrtf(m_planes[4][0] * m_planes[4][0] +
		m_planes[4][1] * m_planes[4][1] +
		m_planes[4][2] * m_planes[4][2]);
	m_planes[4][0] /= length;
	m_planes[4][1] /= length;
	m_planes[4][2] /= length;
	m_planes[4][3] /= length;

	m_planes[5][0] = matrix._14 + matrix._12;
	m_planes[5][1] = matrix._24 + matrix._22;
	m_planes[5][2] = matrix._34 + matrix._32;
	m_planes[5][3] = matrix._44 + matrix._42;
	length = sqrtf(m_planes[5][0] * m_planes[5][0] +
		m_planes[5][1] * m_planes[5][1] +
		m_planes[5][2] * m_planes[5][2]);
	m_planes[5][0] /= length;
	m_planes[5][1] /= length;
	m_planes[5][2] /= length;
	m_planes[5][3] /= length;

	return;
}

bool FrustumClass::CheckPoint(float x, float y, float z)
{
	int i;
	float dotProduct;

	for (i = 0; i < 6; ++i)
	{
		dotProduct = m_planes[i][0] * x +
			m_planes[i][1] * y +
			m_planes[i][2] * z +
			m_planes[i][3] * 1.0f;

		if (dotProduct <= 0.0f)
			return false;
	}

	return true;
}

bool FrustumClass::CheckCube(float xCenter, 
	float yCenter, 
	float zCenter, 
	float radius)
{
	int i;
	float dotProduct;

	for (i = 0; i < 6; ++i)
	{
		dotProduct = m_planes[i][0] * (xCenter - radius) +
			m_planes[i][1] * (yCenter - radius) +
			m_planes[i][2] * (zCenter - radius) +
			m_planes[i][3] * 1.0f;
		if (dotProduct > 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter + radius) +
			m_planes[i][1] * (yCenter - radius) +
			m_planes[i][2] * (zCenter - radius) +
			m_planes[i][3] * 1.0f;
		if (dotProduct > 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter - radius) +
			m_planes[i][1] * (yCenter + radius) +
			m_planes[i][2] * (zCenter - radius) +
			m_planes[i][3] * 1.0f;
		if (dotProduct > 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter + radius) +
			m_planes[i][1] * (yCenter + radius) +
			m_planes[i][2] * (zCenter - radius) +
			m_planes[i][3] * 1.0f;
		if (dotProduct > 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter - radius) +
			m_planes[i][1] * (yCenter - radius) +
			m_planes[i][2] * (zCenter + radius) +
			m_planes[i][3] * 1.0f;
		if (dotProduct > 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter + radius) +
			m_planes[i][1] * (yCenter - radius) +
			m_planes[i][2] * (zCenter + radius) +
			m_planes[i][3] * 1.0f;
		if (dotProduct > 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter - radius) +
			m_planes[i][1] * (yCenter + radius) +
			m_planes[i][2] * (zCenter + radius) +
			m_planes[i][3] * 1.0f;
		if (dotProduct > 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter + radius) +
			m_planes[i][1] * (yCenter + radius) +
			m_planes[i][2] * (zCenter + radius) +
			m_planes[i][3] * 1.0f;
		if (dotProduct > 0.0f)
			continue;

		return false;
	}

	return true;
}

bool FrustumClass::CheckSphere(float xCenter,
	float yCenter,
	float zCenter,
	float radius)
{
	int i;
	float dotProduct;

	for (i = 0; i < 6; ++i)
	{
		dotProduct = m_planes[i][0] * xCenter +
			m_planes[i][1] * yCenter +
			m_planes[i][2] * zCenter +
			m_planes[i][3] * 1.0f;

		if (dotProduct <= -radius)
			return false;
	}

	return true;
}

bool FrustumClass::CheckRectangle(float xCenter, 
	float yCenter,
	float zCenter,
	float xSize,
	float ySize,
	float zSize)
{
	int i;
	float dotProduct;

	for (i = 0; i < 6; ++i)
	{
		dotProduct = m_planes[i][0] * (xCenter - xSize) +
			m_planes[i][1] * (yCenter - ySize) +
			m_planes[i][2] * (zCenter - zSize) +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter + xSize) +
			m_planes[i][1] * (yCenter - ySize) +
			m_planes[i][2] * (zCenter + zSize) +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter - xSize) +
			m_planes[i][1] * (yCenter + ySize) +
			m_planes[i][2] * (zCenter - zSize) +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter + xSize) +
			m_planes[i][1] * (yCenter + ySize) +
			m_planes[i][2] * (zCenter - zSize) +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter + xSize) +
			m_planes[i][1] * (yCenter - ySize) +
			m_planes[i][2] * (zCenter + zSize) +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter + xSize) +
			m_planes[i][1] * (yCenter - ySize) +
			m_planes[i][2] * (zCenter + zSize) +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter - xSize) +
			m_planes[i][1] * (yCenter + ySize) +
			m_planes[i][2] * (zCenter + zSize) +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * (xCenter + xSize) +
			m_planes[i][1] * (yCenter + ySize) +
			m_planes[i][2] * (zCenter + zSize) +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		return false;
	}

	return true;
}

bool FrustumClass::CheckRectangle2(float maxWidth,
	float maxHeight,
	float maxDepth,
	float minWidth,
	float minHeight,
	float minDepth)
{
	int i;
	float dotProduct;

	for (i = 0; i < 6; ++i)
	{
		dotProduct = m_planes[i][0] * minWidth +
			m_planes[i][1] * minHeight +
			m_planes[i][2] * minDepth +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * maxWidth +
			m_planes[i][1] * minHeight +
			m_planes[i][2] * minDepth +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * minWidth +
			m_planes[i][1] * maxHeight +
			m_planes[i][2] * minDepth +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * maxWidth +
			m_planes[i][1] * maxHeight +
			m_planes[i][2] * minDepth +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * minWidth +
			m_planes[i][1] * minHeight +
			m_planes[i][2] * maxDepth +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * maxWidth +
			m_planes[i][1] * minHeight +
			m_planes[i][2] * maxDepth +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * minWidth +
			m_planes[i][1] * maxHeight +
			m_planes[i][2] * maxDepth +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		dotProduct = m_planes[i][0] * maxWidth +
			m_planes[i][1] * maxHeight +
			m_planes[i][2] * maxDepth +
			m_planes[i][3] * 1.0f;
		if (dotProduct >= 0.0f)
			continue;

		return false;
	}

	return true;
}
