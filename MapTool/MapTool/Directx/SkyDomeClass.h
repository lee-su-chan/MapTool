#pragma once

#include "D3D_Defines.h"

class SkyDomeClass
{
private:

public:
	SkyDomeClass();
	SkyDomeClass(const SkyDomeClass &);
	~SkyDomeClass();

	bool Initialize(ID3D11Device *);
	void Shutdown();
	void Render(ID3D11DeviceContext *);

	int GetIndexCount();
	XMFLOAT4 GetApexColor();
	XMFLOAT4 GetCenterColor();

	void SetApexColor(XMFLOAT4);
	void SetCenterColor(XMFLOAT4);

private:
	bool LoadSkyDomeModel(char *);
	void ReleaseSkyDomeModel();

	bool InitializeBuffers(ID3D11Device *);
	void ReleaseBuffers();
	void RenderBuffers(ID3D11DeviceContext *);

private:
	MyStruct::SkyModelType *m_model;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	XMFLOAT4 m_apexColor, m_centerColor;
};