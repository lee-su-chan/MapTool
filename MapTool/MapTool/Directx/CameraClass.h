#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

#include <DirectXMath.h>
using namespace DirectX;

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass &);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX &);

private:
	float m_posX, m_posY, m_posZ;
	float m_rotX, m_rotY, m_rotZ;
	XMMATRIX m_viewMatrix;
};

#endif