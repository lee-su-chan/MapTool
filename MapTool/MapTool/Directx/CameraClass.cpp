#include "CameraClass.h"

CameraClass::CameraClass()
{
	m_posX = m_posY = m_posZ = 0.0f;
	m_rotX = m_rotY = m_rotZ = 0.0f;
}

CameraClass::CameraClass(const CameraClass &)
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;

	return;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotX = x;
	m_rotY = y;
	m_rotZ = z;

	return;
}

XMFLOAT3 CameraClass::GetPosition()
{
	return XMFLOAT3(m_posX, m_posY, m_posZ);
}

XMFLOAT3 CameraClass::GetRotation()
{
	return XMFLOAT3(m_rotX, m_rotY, m_rotZ);
}

void CameraClass::Render()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVec, positionVec, lookAtVec;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	upVec = XMLoadFloat3(&up);

	position.x = m_posX;
	position.y = m_posY;
	position.z = m_posZ;

	positionVec = XMLoadFloat3(&position);

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	lookAtVec = XMLoadFloat3(&lookAt);

	// Set the yaw(Y axis), pitch(X axis), and roll(Z axis) rotations in radians.
	pitch = m_rotX * 0.0174532925f;
	yaw = m_rotY * 0.0174532925f;
	roll = m_rotZ * 0.0174532925f;

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVec = XMVector3TransformCoord(lookAtVec, rotationMatrix);
	upVec = XMVector3TransformCoord(upVec, rotationMatrix);

	// Translate the rotate camera position to the location of the viewer.
	lookAtVec = XMVectorAdd(positionVec, lookAtVec);

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(positionVec, lookAtVec, upVec);

	return;
}

void CameraClass::GetViewMatrix(XMMATRIX &viewMatrix)
{
	viewMatrix = m_viewMatrix;

	return;
}
