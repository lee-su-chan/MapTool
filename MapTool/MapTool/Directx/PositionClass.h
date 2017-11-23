#pragma once

#include <math.h>

class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass &) = default;
	~PositionClass() = default;

public:
	inline void SetPosition(float x, float y, float z) { m_posX = x; m_posY = y; m_posZ = z; }
	inline void SetRotation(float x, float y, float z) { m_rotX = x; m_rotY = y; m_rotZ = z; }

	inline void GetPosition(float &x, float &y, float &z) { x = m_posX; y = m_posY; z = m_posZ; }
	inline void GetRotation(float &x, float &y, float &z) { x = m_rotX; y = m_rotY; z = m_rotZ; }

	inline void SetFrameTime(float time) { m_frameTime = time; }

	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void MoveLeftward(bool);
	void MoveRightward(bool);
	void TurnLeft(bool);
	void TurnRight(bool);
	void LookUpward(bool);
	void LookDownward(bool);
	void TurnByMouse(int, int);

private:
	float m_posX, m_posY, m_posZ;
	float m_rotX, m_rotY, m_rotZ;

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftwardSpeed, m_rightwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;
	float m_mouseSpeed;
};