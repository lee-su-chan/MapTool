#include "PositionClass.h"

PositionClass::PositionClass()
{
	m_posX = m_posY = m_posZ = 0.0f;
	m_rotX = m_rotY = m_rotZ = 0.0f;

	m_frameTime = 0.0f;

	m_forwardSpeed = m_backwardSpeed = 0.0f;
	m_upwardSpeed = m_downwardSpeed = 0.0f;
	m_leftwardSpeed = m_rightwardSpeed = 0.0f;
	m_leftTurnSpeed = m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed = m_lookDownSpeed = 0.0f;
}

PositionClass::PositionClass(const PositionClass &other)
{
}

PositionClass::~PositionClass()
{
}

void PositionClass::SetPosition(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;

	return;
}

void PositionClass::SetRotation(float x, float y, float z)
{
	m_rotX = x;
	m_rotY = y;
	m_rotZ = z;

	return;
}

void PositionClass::GetPosition(float &x, float &y, float &z)
{
	x = m_posX;
	y = m_posY;
	z = m_posZ;

	return;
}

void PositionClass::GetRotation(float &x, float &y, float &z)
{
	x = m_rotX;
	y = m_rotY;
	z = m_rotZ;

	return;
}


void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;

	return;
}

void PositionClass::MoveForward(bool keydown)
{
	float radians;
	
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_forwardSpeed += m_frameTime * 1.0f;

		if (m_forwardSpeed > m_frameTime * 50.0f)
			m_forwardSpeed = m_frameTime * 50.0f;
	}
	else
	{
		m_forwardSpeed -= m_frameTime * 0.5f;

		if (m_forwardSpeed < 0.0f)
			m_forwardSpeed = 0.0f;
	}

	// Convert degrees to radians.
	radians = m_rotY * 0.0174532925f;

	// Update the position.
	m_posX += sinf(radians) * m_forwardSpeed;
	m_posZ += cosf(radians) * m_forwardSpeed;

	return;
}


void PositionClass::MoveBackward(bool keydown)
{
	float radians;

	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_backwardSpeed += m_frameTime * 1.0f;

		if (m_backwardSpeed > m_frameTime * 50.0f)
			m_backwardSpeed = m_frameTime * 50.0f;
	}
	else
	{
		m_backwardSpeed -= m_frameTime * 0.5f;

		if (m_backwardSpeed < 0.0f)
			m_backwardSpeed = 0.0f;
	}

	// Convert degrees to radians.
	radians = m_rotY * 0.0174532925f;

	// Update the position.
	m_posX -= sinf(radians) * m_backwardSpeed;
	m_posZ -= cosf(radians) * m_backwardSpeed;

	return;

}

void PositionClass::MoveUpward(bool keydown)
{
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_upwardSpeed += m_frameTime * 1.5f;

		if (m_upwardSpeed > m_frameTime * 15.0f)
			m_upwardSpeed = m_frameTime * 15.0f;
	}
	else
	{
		m_upwardSpeed -= m_frameTime * 0.5f;

		if (m_upwardSpeed < 0.0f)
			m_upwardSpeed = 0.0f;
	}

	// Update the height position.
	m_posY += m_upwardSpeed;

	return;
}

void PositionClass::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_downwardSpeed += m_frameTime * 1.5f;

		if (m_downwardSpeed > m_frameTime * 15.0f)
			m_downwardSpeed = m_frameTime * 15.0f;
	}
	else
	{
		m_downwardSpeed -= m_frameTime * 0.5f;

		if (m_downwardSpeed < 0.0f)
			m_downwardSpeed = 0.0f;
	}

	// Update the height position.
	m_posY -= m_downwardSpeed;

	return;
}

void PositionClass::MoveLeftward(bool keydown)
{
	float radians;

	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_leftwardSpeed += m_frameTime * 1.0f;

		if (m_leftwardSpeed > m_frameTime * 50.0f)
			m_leftwardSpeed = m_frameTime * 50.0f;
	}
	else
	{
		m_leftwardSpeed -= m_frameTime * 0.5f;

		if (m_leftwardSpeed < 0.0f)
			m_leftwardSpeed = 0.0f;
	}

	// Convert degrees to radians.
	radians = m_rotY * 0.0174532925f;

	// Update the position.
	m_posX -= cosf(radians) * m_leftwardSpeed;
	m_posZ += sinf(radians) * m_leftwardSpeed;

	return;
}

void PositionClass::MoveRightward(bool keydown)
{
	float radians;

	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_rightwardSpeed += m_frameTime * 1.0f;

		if (m_rightwardSpeed > m_frameTime * 50.0f)
			m_rightwardSpeed = m_frameTime * 50.0f;
	}
	else
	{
		m_rightwardSpeed -= m_frameTime * 0.5f;

		if (m_rightwardSpeed < 0.0f)
			m_rightwardSpeed = 0.0f;
	}

	// Convert degrees to radians.
	radians = m_rotY * 0.0174532925f;

	// Update the position.
	m_posX += cosf(radians) * m_rightwardSpeed;
	m_posZ -= sinf(radians) * m_rightwardSpeed;

	return;
}

void PositionClass::TurnLeft(bool keydown)
{
	//Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_leftTurnSpeed += m_frameTime * 5.0f;

		if (m_leftTurnSpeed > m_frameTime * 150.0f)
			m_leftTurnSpeed = m_frameTime * 150.0f;
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime * 3.5f;

		if (m_leftTurnSpeed < 0.0f)
			m_leftTurnSpeed = 0.0f;
	}

	// Update the rotation.
	m_rotY -= m_leftTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if (m_rotY < 0.0f)
		m_rotY += 360.0f;

	return;
}

void PositionClass::TurnRight(bool keydown)
{
	//Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_rightTurnSpeed += m_frameTime * 5.0f;

		if (m_rightTurnSpeed > m_frameTime * 150.0f)
			m_rightTurnSpeed = m_frameTime * 150.0f;
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime * 3.5f;

		if (m_rightTurnSpeed < 0.0f)
			m_rightTurnSpeed = 0.0f;
	}

	// Update the rotation.
	m_rotY += m_rightTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if (m_rotY > 360.0f)
		m_rotY -= 360.0f;

	return;
}

void PositionClass::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookUpSpeed += m_frameTime * 7.5f;

		if (m_lookUpSpeed > m_frameTime * 75.0f)
			m_lookUpSpeed = m_frameTime * 75.0f;
	}
	else
	{
		m_lookUpSpeed -= m_frameTime * 2.0f;

		if (m_lookUpSpeed < 0.0f)
			m_lookUpSpeed = 0.0f;
	}

	// Update the rotation.
	m_rotX -= m_lookUpSpeed;

	// Keep the rotation maximun 90 degrees.
	if (m_rotX > 90.0f)
		m_rotX = 90.0f;

	return;
}

void PositionClass::LookDownward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_lookDownSpeed += m_frameTime * 7.5f;

		if (m_lookDownSpeed > m_frameTime * 75.0f)
			m_lookDownSpeed = m_frameTime * 75.0f;
	}
	else
	{
		m_lookDownSpeed -= m_frameTime * 2.0f;

		if (m_lookDownSpeed < 0.0f)
			m_lookDownSpeed = 0.0f;
	}

	// Update the rotation.
	m_rotX += m_lookDownSpeed;

	// Keep the rotation maximun 90 degrees.
	if (m_rotX < -90.0f)
		m_rotX = -90.0f;

	return;
}