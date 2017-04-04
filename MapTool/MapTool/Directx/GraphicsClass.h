#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "D3DClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "TextureShaderClass.h"

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass &);
	~GraphicsClass();

	bool Initialize(D3DClass *, HWND, int, int, float);
	void Shutdown();
	bool Frame(D3DClass *);

private:
	bool Render(D3DClass *);

private:
	D3DClass *m_Direct3D;
	CameraClass *m_Camera;
	ModelClass *m_Model;
	TextureShaderClass *m_TextureShader;
};

#endif