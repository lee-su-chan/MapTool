#pragma once

#include "D3DClass.h"
#include "TextClass.h"
#include "MinimapClass.h"

class UserInterfaceClass
{
public:
	UserInterfaceClass();
	UserInterfaceClass(const UserInterfaceClass &);
	~UserInterfaceClass();

	bool Initialize(D3DClass *, int, int);
	void Shutdown();

	bool Frame(ID3D11DeviceContext *, int, float, float, float, float, float, float, XMFLOAT4, XMFLOAT4, int, int);
	bool Render(D3DClass *, ShaderManagerClass *, XMMATRIX, XMMATRIX, XMMATRIX);

	bool UpdateRenderCounts(ID3D11DeviceContext *, int, int, int);

private:
	bool UpdateFpsString(ID3D11DeviceContext *, int);
	bool UpdatePositionStrings(ID3D11DeviceContext *, float, float, float, float, float, float);
	bool UpdateSkyColorStrings(ID3D11DeviceContext *, XMFLOAT4, XMFLOAT4);
	bool UpdateMousePositionStrings(ID3D11DeviceContext *, int, int);

private:
	FontClass *m_font1;
	
	TextClass *m_fpsString;
	TextClass *m_videoStrings;
	TextClass *m_positionStrings;
	TextClass *m_skyColorTypeStrings;
	TextClass *m_skyColorStrings;
	TextClass *m_renderCountStrings;
	TextClass *m_mousePositionStrings;
	
	int m_previousFps;
	int m_previousPosition[6];
	int m_previousSkyColor[8];
	int m_previousMousePosition[2];

	MiniMapClass *m_MiniMap;
};