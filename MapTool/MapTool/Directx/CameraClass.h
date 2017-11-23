#pragma once

#include "D3D_Core.h"
#include "PositionClass.h"
#include "InputClass.h"

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass &) = default;
	~CameraClass() = default;

	void Render();
	void RenderBaseViewMatrix();
	void Frame(InputClass *);
	void Shutdown();

public:
	inline void SetPosition(float x, float y, float z)		{ m_Position->SetPosition(x, y, z); }
	inline void SetRotation(float x, float y, float z)		{ m_Position->SetRotation(x, y, z); }

	inline void GetPosition(float &x, float &y, float &z)	{ m_Position->GetPosition(x, y, z); }
	inline void GetRotation(float &x, float &y, float &z)	{ m_Position->GetRotation(x, y, z); }

	inline void SetFrameTime(float time) { m_Position->SetFrameTime(time); }

	void GetViewMatrix(XMMATRIX &);
	void GetBaseViewMatrix(XMMATRIX &);

private:
	XMMATRIX m_ViewMatrix;
	XMMATRIX m_BaseViewMatrix;

	PositionClass *m_Position;
};