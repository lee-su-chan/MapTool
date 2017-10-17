#pragma once

#include "D3D_Core.h"
#include "PositionClass.h"

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass &) = default;
	~CameraClass() = default;

	void Render();
	void RenderBaseViewMatrix();
	void Shutdown();

public:
	inline void SetPosition(float x, float y, float z)		{ m_position->SetPosition(x, y, z); }
	inline void SetRotation(float x, float y, float z)		{ m_position->SetRotation(x, y, z); }

	PositionClass * GetPosition()							{ return m_position; }
	inline void GetPosition(float &x, float &y, float &z)	{ m_position->GetPosition(x, y, z); }
	inline void GetRotation(float &x, float &y, float &z)	{ m_position->GetRotation(x, y, z); }

	void GetViewMatrix(XMMATRIX &);
	void GetBaseViewMatrix(XMMATRIX &);

private:
	XMMATRIX m_viewMatrix;
	XMMATRIX m_baseViewMatrix;

	PositionClass *m_position;
};