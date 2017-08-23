#pragma once

#include "D3D_Defines.h"

class TerrainCellClass
{
public:
	TerrainCellClass();
	TerrainCellClass(const TerrainCellClass &);
	~TerrainCellClass();

	bool Initialize(ID3D11Device *, void *, int, int, int, int, int);
	void Shutdown();
	void Render(ID3D11DeviceContext *);
	void RenderLineBuffers(ID3D11DeviceContext *);

public:
	int GetVertexCount();
	int GetIndexCount();
	int GetLineBuffersIndexCount();
	void GetCellDimensions(float &, float &, float &, float &, float &, float &);
	void GetEdgePosition(float &, float &, float &);

public:
	bool TranslateVertex(ID3D11DeviceContext *);

private:
	bool InitializeBuffers(ID3D11Device *, int, int, int, int, int, const MyStruct::ModelType *);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext *);
	void CalculateCellDemensions();
	bool BuildLineBuffers(ID3D11Device *);
	void ShutdownLineBuffers();

public:
	MyStruct::TerrainVertexType *m_vertexList;

private:
	int m_vertexCount, m_indexCount, m_lineIndexCount;
	float m_maxWidth, m_maxHeight, m_maxDepth, m_minWidth, m_minHeight, m_minDepth;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_lineVertexBuffer, *m_lineIndexBuffer;
};