#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_

#include <fstream>
#include <stdio.h>

#include "Resources\MyResource.h"

#include "TerrainCellClass.h"
#include "FrustumClass.h"

using namespace std;

class TerrainClass
{
private:
	struct HeightMapType
	{
		float x, y, z;
		float nx, ny, nz;
		float r, g, b;
	};

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

	struct VectorType
	{
		float x, y, z;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};
	
public:
	TerrainClass();
	TerrainClass(const TerrainClass &);
	~TerrainClass();

	bool Initialize(ID3D11Device *, char *, MyStruct::TERRAIN_DESC &);
	void Shutdown();
	
	void Frame();

	bool RenderCell(ID3D11DeviceContext *, int, FrustumClass *);
	void RenderCellLines(ID3D11DeviceContext *, int);

	int GetCellIndexCount(int);
	int GetCellLinesIndexCount(int);
	int GetCellCount();
	int GetRenderCount();
	int GetCellsDrawn();
	int GetCellsCulled();
	bool GetHeightAtPosition(float, float, float &);
	TerrainCellClass *GetTerrainCellObj();

private:
	bool LoadSetupFile(char *);
	bool LoadTerrainDesc(MyStruct::TERRAIN_DESC &);
	bool LoadBitmapHeightMap();
	bool LoadRawHeightMap();
	void ShutdownHeightMap();
	void SetTerrainCoordinates();
	bool CalculateNormals();
	bool LoadColorMap();
	bool BuildTerrainModel();
	void ShutdownTerrainModel();
	void CalculateTerrainVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType &, VectorType &);
	bool LoadTerrainCells(ID3D11Device *, MyStruct::TERRAIN_DESC &);
	void ShutdownTerrainCells();
	bool CheckHeightOfTriangle(float, float, float &, float[3], float[3], float[3]);

private:
	int m_terrainHeight, m_terrainWidth, m_vertexCount;
	float m_heightScale;
	char *m_terrainFilename, *m_colorMapFilename;
	HeightMapType *m_heightMap;
	ModelType *m_terrainModel;
	TerrainCellClass *m_TerrainCells;
	int m_cellCount, m_renderCount, m_cellsDrawn, m_cellsCulled;
};

#endif