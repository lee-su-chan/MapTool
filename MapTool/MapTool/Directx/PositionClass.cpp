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
	m_mouseSpeed = 0.0f;
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

	radians = m_rotX * 0.0174532925f;
	m_posY -= sinf(radians) * m_forwardSpeed;
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

	radians = m_rotX * 0.0174532925f;
	m_posY += sinf(radians) * m_backwardSpeed;
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
}

void PositionClass::TurnByMouse(int mouseAddX, int mouseAddY)
{
	const float SPEED = 4.0f;

	if (mouseAddX > 0)
		m_rotY += mouseAddX * 0.016 * SPEED;
	else if (mouseAddX < 0)
		m_rotY += mouseAddX * 0.016 * SPEED;

	if (mouseAddY > 0)
		m_rotX += mouseAddY * 0.016 * SPEED;
	else if (mouseAddY < 0)
		m_rotX += mouseAddY * 0.016 * SPEED;
}
