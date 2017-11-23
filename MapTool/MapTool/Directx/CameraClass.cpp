#include "CameraClass.h"

CameraClass::CameraClass()
{
	m_Position = new PositionClass;
	m_Position->SetPosition(0.0f, 0.0f, 0.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);
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

	m_Position->GetPosition(position.x, position.y, position.z);

	positionVec = XMLoadFloat3(&position);

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	lookAtVec = XMLoadFloat3(&lookAt);

	// Set the yaw(Y axis), pitch(X axis), and roll(Z axis) rotations in radians.
	m_Position->GetRotation(pitch, yaw, roll);
	pitch *= 0.0174532925f;
	yaw *= 0.0174532925f;
	roll *= 0.0174532925f;

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVec = XMVector3TransformCoord(lookAtVec, rotationMatrix);
	upVec = XMVector3TransformCoord(upVec, rotationMatrix);

	// Translate the rotate camera position to the location of the viewer.
	lookAtVec = XMVectorAdd(positionVec, lookAtVec);

	// Finally create the view matrix from the three updated vectors.
	m_ViewMatrix = XMMatrixLookAtLH(positionVec, lookAtVec, upVec);

	return;
}

void CameraClass::GetViewMatrix(XMMATRIX &viewMatrix)
{
	viewMatrix = m_ViewMatrix;
}

void CameraClass::RenderBaseViewMatrix()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	upVector = XMLoadFloat3(&up);

	m_Position->GetPosition(position.x, position.y, position.z);
	positionVector = XMLoadFloat3(&position);

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;
	lookAtVector = XMLoadFloat3(&lookAt);

	m_Position->GetRotation(pitch, yaw, roll);
	pitch *= 0.0174532925f;
	yaw *= 0.0174532925f;
	roll *= 0.0174532925f;

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	m_BaseViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

void CameraClass::Frame(InputClass *input)
{
	bool isKeyDown;
	int mouseAddX, mouseAddY;

	if (input->IsMouseRightClick())
	{
		input->GetMouseAddPos(mouseAddX, mouseAddY);
		m_Position->TurnByMouse(mouseAddX, mouseAddY);
	}

	isKeyDown = input->IsWPressed();
	m_Position->MoveForward(isKeyDown);

	isKeyDown = input->IsSPressed();
	m_Position->MoveBackward(isKeyDown);

	isKeyDown = input->IsAPressed();
	m_Position->MoveLeftward(isKeyDown);

	isKeyDown = input->IsDPressed();
	m_Position->MoveRightward(isKeyDown);

	isKeyDown = input->IsQPressed();
	m_Position->MoveUpward(isKeyDown);

	isKeyDown = input->IsEPressed();
	m_Position->MoveDownward(isKeyDown);

	isKeyDown = input->IsUpPressed();
	m_Position->LookUpward(isKeyDown);

	isKeyDown = input->IsLeftPressed();
	m_Position->TurnLeft(isKeyDown);

	isKeyDown = input->IsDownPressed();
	m_Position->LookDownward(isKeyDown);

	isKeyDown = input->IsRightPressed();
	m_Position->TurnRight(isKeyDown);
}

void CameraClass::Shutdown()
{
	if (m_Position)
	{
		delete m_Position;
		m_Position = NULL;
	}
}

void CameraClass::GetBaseViewMatrix(XMMATRIX &viewMatrix)
{
	viewMatrix = m_BaseViewMatrix;
}
