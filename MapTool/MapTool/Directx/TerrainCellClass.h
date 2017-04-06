#ifndef _TERRAINCELLCLASS_H_
#define _TERRAINCELLCLASS_H_

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class TerrainCellClass
{
private:
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float tu2, tv2;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
		float r, g, b;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT3 binormal;
		XMFLOAT3 color;
		XMFLOAT2 texture2;
	};

	struct VectorType
	{
		float x, y, z;
	};

	struct ColorVertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	TerrainCellClass();
	TerrainCellClass(const TerrainCellClass &);
	~TerrainCellClass();

	bool Initialize(ID3D11Device *, void *, int, int, int, int, int);
	void Shutdown();
	void Render(ID3D11DeviceContext *);
	void RenderLineBuffers(ID3D11DeviceContext *);

	int GetVertexCount();
	int GetIndexCount();
	int GetLineBuffersIndexCount();
	void GetCellDimensions(float &, float &, float &, float &, float &, float &);

private:
	bool InitializeBuffers(ID3D11Device *, int, int, int, int, int, ModelType *);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext *);
	void CalculateCellDemensions();
	bool BuildLineBuffers(ID3D11Device *);
	void ShutdownLineBuffers();

public:
	VectorType *m_vertexList;

private:
	int m_vertexCount, m_indexCount, m_lineIndexCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_lineVertexBuffer, *m_lineIndexBuffer;
	float m_maxWidth, m_maxHeight, m_maxDepth, m_minWidth, m_minHeight, m_minDepth;
	float m_positionX, m_positionY, m_positionZ;
};

#endif