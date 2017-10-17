#pragma once

#include "TerrainCellClass.h"
#include "FrustumClass.h"

class TerrainClass
{
public:
	TerrainClass();
	TerrainClass(const TerrainClass &);
	~TerrainClass();

	bool Initialize(ID3D11Device *, const MyStruct::TERRAIN_DESC &);
	void Shutdown();
	
	void Frame();

	bool RenderCell(ID3D11DeviceContext *, int, FrustumClass *);
	void RenderCellLines(ID3D11DeviceContext *, int);

public:
	int GetCellIndexCount(int);
	int GetCellLinesIndexCount(int);
	int GetCellCount();
	int GetRenderCount();
	int GetCellsDrawn();
	int GetCellsCulled();
	bool GetHeightAtPosition(float, float, float &);
	TerrainCellClass *GetTerrainCellObj();

private:
	//bool LoadSetupFile(char *);
	bool LoadTerrainDesc(const MyStruct::TERRAIN_DESC &);
	bool LoadBitmapHeightMap();
	bool LoadRawHeightMap();
	bool LoadTerrainCells(ID3D11Device *, const MyStruct::TERRAIN_DESC &);
	bool LoadColorMap();

private:
	void ShutdownHeightMap();
	void ShutdownTerrainCells();
	void ShutdownTerrainModel();

private:
	bool CalculateNormals();
	void CalculateTerrainVectors();
	void CalculateTangentBinormal(const MyStruct::TempVertexType, const MyStruct::TempVertexType, const MyStruct::TempVertexType, MyStruct::VectorType &, MyStruct::VectorType &);
	
	bool CheckHeightOfTriangle(float, float, float &, float[3], float[3], float[3]);

private:
	void SetTerrainCoordinates();

	bool BuildTerrainModel();

private:
	int m_terrainHeight, m_terrainWidth, m_vertexCount;
	float m_heightScale;
	char *m_terrainFilename, *m_colorMapFilename;
	MyStruct::HeightMapType *m_heightMap;
	MyStruct::ModelType *m_terrainModel;
	TerrainCellClass *m_TerrainCells;
	int m_cellCount, m_renderCount, m_cellsDrawn, m_cellsCulled;
};