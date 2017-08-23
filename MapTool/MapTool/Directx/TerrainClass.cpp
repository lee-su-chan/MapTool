#include "TerrainClass.h"

TerrainClass::TerrainClass()
{
	m_terrainFilename = 0;
	m_colorMapFilename = 0;
	m_heightMap = 0;
	m_terrainModel = 0;
	m_TerrainCells = 0;
}

TerrainClass::TerrainClass(const TerrainClass &other)
{
}

TerrainClass::~TerrainClass()
{
}

bool TerrainClass::Initialize(ID3D11Device *device, const MyStruct::TERRAIN_DESC &terrainDesc)
{
	bool result;

	result = LoadTerrainDesc(terrainDesc);
	if (!result)
		return false;

	SetTerrainCoordinates();

	result = CalculateNormals();
	if (!result)
		return false;

	result = BuildTerrainModel();
	if (!result)
		return false;

	ShutdownHeightMap();

	CalculateTerrainVectors();
	
	result = LoadTerrainCells(device, terrainDesc);
	if (!result)
		return false;

	ShutdownTerrainModel();

	return true;
}

void TerrainClass::Shutdown()
{
	ShutdownTerrainCells();
	ShutdownTerrainModel();
	ShutdownHeightMap();

	return;
}

void TerrainClass::Frame()
{
	m_renderCount = 0;
	m_cellsDrawn = 0;
	m_cellsCulled = 0;

	return;
}

bool TerrainClass::RenderCell(ID3D11DeviceContext *deviceContext, 
	int cellId,
	FrustumClass *Frustum)
{
	float maxWidth, maxHeight, maxDepth, minWidth, minHeight, minDepth;
	bool result;

	m_TerrainCells[cellId].GetCellDimensions(maxWidth,
		maxHeight,
		maxDepth,
		minWidth,
		minHeight,
		minDepth);

	result = Frustum->CheckRectangle2(maxWidth,
		maxHeight,
		maxDepth,
		minWidth,
		minHeight,
		minDepth);

	if (!result)
	{
		++m_cellsCulled;

		return false;
	}

	m_TerrainCells[cellId].Render(deviceContext);

	m_renderCount += m_TerrainCells[cellId].GetVertexCount() / 3;
	
	++m_cellsDrawn;

	return true;
}

void TerrainClass::RenderCellLines(ID3D11DeviceContext *deviceContext, int cellId)
{
	m_TerrainCells[cellId].RenderLineBuffers(deviceContext);

	return;
}

int TerrainClass::GetCellIndexCount(int cellId)
{
	return m_TerrainCells[cellId].GetIndexCount();
}

int TerrainClass::GetCellLinesIndexCount(int cellId)
{
	return m_TerrainCells[cellId].GetLineBuffersIndexCount();
}

int TerrainClass::GetCellCount()
{
	return m_cellCount;
}

int TerrainClass::GetRenderCount()
{
	return m_renderCount;
}

int TerrainClass::GetCellsDrawn()
{
	return m_cellsDrawn;
}

int TerrainClass::GetCellsCulled()
{
	return m_cellsCulled;
}

bool TerrainClass::GetHeightAtPosition(float inputX, float inputZ, float &height)
{
	int i, cellId, index;
	float vertex1[3], vertex2[3], vertex3[3];
	bool foundHeight;
	float maxWidth, maxHeight, maxDepth, minWidth, minHeight, minDepth;

	cellId = -1;
	for (i = 0; i < m_cellCount; ++i)
	{
		m_TerrainCells[i].GetCellDimensions(maxWidth,
			maxHeight,
			maxDepth,
			minWidth,
			minHeight,
			minDepth);

		if (inputX < maxWidth &&
			inputX > minWidth &&
			inputZ < maxDepth &&
			inputZ > minDepth)
		{
			cellId = i;
			i = m_cellCount;
		}
	}

	if (cellId == -1)
		return false;

	for (i = 0; i < m_TerrainCells[cellId].GetVertexCount() / 3; ++i)
	{
		index = i * 3;

		vertex1[0] = m_TerrainCells[cellId].m_vertexList[index].position.x;
		vertex1[1] = m_TerrainCells[cellId].m_vertexList[index].position.y;
		vertex1[2] = m_TerrainCells[cellId].m_vertexList[index].position.z;
		++index;

		vertex2[0] = m_TerrainCells[cellId].m_vertexList[index].position.x;
		vertex2[1] = m_TerrainCells[cellId].m_vertexList[index].position.y;
		vertex2[2] = m_TerrainCells[cellId].m_vertexList[index].position.z;
		++index;

		vertex3[0] = m_TerrainCells[cellId].m_vertexList[index].position.x;
		vertex3[1] = m_TerrainCells[cellId].m_vertexList[index].position.y;
		vertex3[2] = m_TerrainCells[cellId].m_vertexList[index].position.z;

		foundHeight = CheckHeightOfTriangle(inputX,
			inputZ,
			height,
			vertex1,
			vertex2,
			vertex3);

		if (foundHeight)
			return true;
	}

	return false;
}
TerrainCellClass *TerrainClass::GetTerrainCellObj()
{
	return m_TerrainCells;
}

//bool TerrainClass::LoadSetupFile(char *filename)
//{
//	int stringLength;
//	ifstream fin;
//	char input;
//
//	stringLength = 256;
//	
//	m_terrainFilename = new char[stringLength];
//	if (!m_terrainFilename)
//		return false;
//
//	m_colorMapFilename = new char[stringLength];
//	if (!m_colorMapFilename)
//		return false;
//
//	fin.open(filename);
//	if (fin.fail())
//		return false;
//
//	fin.get(input);
//	while (input != ':')
//		fin.get(input);
//	fin >> m_terrainFilename;
//
//	fin.get(input);
//	while (input != ':')
//		fin.get(input);
//	fin >> m_terrainHeight;
//
//	fin.get(input);
//	while (input != ':')
//		fin.get(input);
//	fin >> m_terrainWidth;
//
//	fin.get(input);
//	while (input != ':')
//		fin.get(input);
//	fin >> m_heightScale;
//
//	fin.get(input);
//	while (input != ':')
//		fin.get(input);
//	fin >> m_colorMapFilename;
//
//	fin.close();
//
//	return true;
//}

bool TerrainClass::LoadTerrainDesc(const MyStruct::TERRAIN_DESC &terrainDesc)
{
	int i, j, index;
	const int stringLength	= 256;
	m_terrainWidth			= terrainDesc.nCell * terrainDesc.nTile + 1;
	m_terrainHeight			= m_terrainWidth;
	m_heightScale			= 12.0f;

	m_heightMap = new MyStruct::HeightMapType[m_terrainWidth * m_terrainHeight];
	if (!m_heightMap)
		return false;

	for (i = 0; i < m_terrainHeight; ++i)
	{
		for (j = 0; j < m_terrainWidth; ++j)
		{
			index = m_terrainWidth * j + i;

			m_heightMap[index].y = 1.0f;
		}
	}

	return true;
}


bool TerrainClass::LoadBitmapHeightMap()
{
	int error, imageSize, i, j, k, index;
	FILE *filePtr;
	unsigned long long count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char *bitmapImage;
	unsigned char height;

	m_heightMap = new MyStruct::HeightMapType[m_terrainWidth * m_terrainHeight];
	if (!m_heightMap)
		return false;

	error = fopen_s(&filePtr, m_terrainFilename, "rb");
	if (error != 0)
		return false;

	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if (count != 1)
		return false;

	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if (count != 1)
		return false;

	if (bitmapInfoHeader.biHeight != m_terrainHeight ||
		bitmapInfoHeader.biWidth != m_terrainWidth)
		return false;

	imageSize = m_terrainHeight * (m_terrainWidth * 3 + 1);

	bitmapImage = new unsigned char[imageSize];
	if (!bitmapImage)
		return false;

	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	count = fread(bitmapImage, 1, imageSize, filePtr);
	if (count != imageSize)
		return false;

	error = fclose(filePtr);
	if (error != 0)
		return false;

	k = 0;

	for (j = 0; j < m_terrainHeight; ++j)
	{
		for (i = 0; i < m_terrainWidth; ++i)
		{
			// Bitmaps are upside down so load bottom to top into the height map array.
			index = m_terrainWidth * (m_terrainHeight - 1 - j) + i;

			height = bitmapImage[k];

			m_heightMap[index].y = (float)height;

			k += 3;
		}

		++k;
	}

	delete[] bitmapImage;
	bitmapImage = NULL;

	delete[] m_terrainFilename;
	m_terrainFilename = NULL;

	return true;
}

bool TerrainClass::LoadRawHeightMap()
{
	if (!m_terrainFilename)
		return true;

	int error, i, j, index;
	FILE *filePtr;
	unsigned long long imageSize, count;
	unsigned short *rawImage;

	m_heightMap = new MyStruct::HeightMapType[m_terrainWidth * m_terrainHeight];
	if (!m_heightMap)
		return false;

	error = fopen_s(&filePtr, m_terrainFilename, "rb");
	if (error != 0)
		return false;

	imageSize = m_terrainHeight * m_terrainWidth;

	rawImage = new unsigned short[imageSize];
	if (!rawImage)
		return false;

	count = fread(rawImage, sizeof(unsigned short), imageSize, filePtr);
	if (!count)
		return false;

	error = fclose(filePtr);
	if (error != 0)
		return false;

	for (j = 0; j < m_terrainHeight; ++j)
	{
		for (i = 0; i < m_terrainWidth; ++i)
		{
			index = m_terrainWidth * j + i;

			m_heightMap[index].y = (float)rawImage[index];
		}
	}

	delete[] rawImage;
	rawImage = NULL;

	delete[] m_terrainFilename;
	m_terrainFilename = NULL;

	return true;
}

void TerrainClass::ShutdownHeightMap()
{
	if (m_heightMap)
	{
		delete[] m_heightMap;
		m_heightMap = NULL;
	}

	return;
}

void TerrainClass::SetTerrainCoordinates()
{
	if (!m_heightMap)
		return;

	int i, j, index;

	for (j = 0; j < m_terrainHeight; ++j)
	{
		for (i = 0; i < m_terrainWidth; ++i)
		{
			index = m_terrainWidth * j + i;

			m_heightMap[index].x = (float)i;
			m_heightMap[index].z = -(float)j;

			m_heightMap[index].z += (float)(m_terrainHeight - 1);

			m_heightMap[index].y /= m_heightScale;
		}
	}

	return;
}

bool TerrainClass::CalculateNormals()
{
	int i, j, index1, index2, index3, index;
	float vertex1[3], vertex2[3], vertex3[3], vector1[3], vector2[3], sum[3], length;
	MyStruct::VectorType *normals;

	normals = new MyStruct::VectorType[(m_terrainHeight - 1) * (m_terrainWidth - 1)];
	if (!normals)
		return false;

	for (j = 0; j < m_terrainHeight - 1; ++j)
	{
		for (i = 0; i < m_terrainWidth - 1; ++i)
		{
			index1 = (j + 1) * m_terrainWidth + i;			// Bottom left vertex.
			index2 = (j + 1) * m_terrainWidth + (i + 1);	// Bottom right vertex.
			index3 = j * m_terrainWidth + i;				// Upper left vertex.

			vertex1[0] = m_heightMap[index1].x;
			vertex1[1] = m_heightMap[index1].y;
			vertex1[2] = m_heightMap[index1].z;

			vertex2[0] = m_heightMap[index2].x;
			vertex2[1] = m_heightMap[index2].y;
			vertex2[2] = m_heightMap[index2].z;

			vertex3[0] = m_heightMap[index3].x;
			vertex3[1] = m_heightMap[index3].y;
			vertex3[2] = m_heightMap[index3].z;

			vector1[0] = vertex1[0] - vertex3[0];
			vector1[1] = vertex1[1] - vertex3[1];
			vector1[2] = vertex1[2] - vertex3[2];
			vector2[0] = vertex3[0] - vertex2[0];
			vector2[1] = vertex3[1] - vertex2[1];
			vector2[2] = vertex3[2] - vertex2[2];

			index = j * (m_terrainWidth - 1) + i;

			normals[index].x = vector1[1] * vector2[2] - vector1[2] * vector2[1];
			normals[index].y = vector1[2] * vector2[0] - vector1[0] * vector2[2];
			normals[index].z = vector1[0] * vector2[1] - vector1[1] * vector2[0];

			length = (float)sqrt(normals[index].x * normals[index].x +
				normals[index].y * normals[index].y +
				normals[index].z * normals[index].z);

			normals[index].x = normals[index].x / length;
			normals[index].y = normals[index].y / length;
			normals[index].z = normals[index].z / length;
		}
	}

	for (j = 0; j < m_terrainHeight; ++j)
	{
		for (i = 0; i < m_terrainWidth; ++i)
		{
			sum[0] = 0.0f;
			sum[1] = 0.0f;
			sum[2] = 0.0f;

			// Bottom left face.
			if (i - 1 >= 0 && j - 1 >= 0)
			{
				index = (j - 1) * (m_terrainWidth - 1) + (i - 1);

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
			}

			// Bottom right face.
			if (i < m_terrainWidth - 1 && j - 1 >= 0)
			{
				index = (j - 1) * (m_terrainWidth - 1) + i;

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
			}

			// Upper left face.
			if (i - 1 >= 0 && j < m_terrainHeight - 1)
			{
				index = j * (m_terrainWidth - 1) + (i - 1);

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
			}

			// Upper right face.
			if (i < m_terrainWidth - 1 && j < m_terrainHeight - 1)
			{
				index = j * (m_terrainWidth - 1) + i;

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
			}

			length = (float)sqrt(sum[0] * sum[0] + sum[1] * sum[1] + sum[2] * sum[2]);
			index = j * m_terrainWidth + i;

			m_heightMap[index].nx = sum[0] / length;
			m_heightMap[index].ny = sum[1] / length;
			m_heightMap[index].nz = sum[2] / length;
		}
	}

	delete[] normals;
	normals = NULL;

	return true;
}

bool TerrainClass::LoadColorMap()
{
	if (!m_colorMapFilename)
		return true;

	int error, imageSize, i, j, k, index;
	FILE *filePtr;
	unsigned long long count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char *bitmapImage;

	error = fopen_s(&filePtr, m_colorMapFilename, "rb");
	if (error != 0)
		return false;

	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if (count != 1)
		return false;

	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if (count != 1)
		return false;

	if (bitmapInfoHeader.biWidth != m_terrainWidth ||
		bitmapInfoHeader.biHeight != m_terrainHeight)
		return false;

	imageSize = m_terrainHeight * (m_terrainWidth * 3 + 1);

	bitmapImage = new unsigned char[imageSize];
	if (!bitmapImage)
		return false;

	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	count = fread(bitmapImage, 1, imageSize, filePtr);
	if (count != imageSize)
		return false;

	error = fclose(filePtr);
	if (error != 0)
		return false;

	k = 0;
	for (j = 0; j < m_terrainHeight; ++j)
	{
		for (i = 0; i < m_terrainWidth; ++i)
		{
			// Bitmaps are upside down so load bottom to top into the array.
			index = m_terrainWidth * (m_terrainHeight - 1 - j) + i;

			m_heightMap[index].b = (float)bitmapImage[k] / 255.0f;
			m_heightMap[index].g = (float)bitmapImage[k + 1] / 255.0f;
			m_heightMap[index].r = (float)bitmapImage[k + 2] / 255.0f;

			k += 3;
		}

		++k;
	}

	delete[] bitmapImage;
	bitmapImage = NULL;

	delete[] m_colorMapFilename;
	m_colorMapFilename = NULL;

	return true;
}

bool TerrainClass::BuildTerrainModel()
{
	int i, j, index, index1, index2, index3, index4;
	float quadsCovered, incrementSize, tu2Left, tu2Right, tv2Bottom, tv2Top;

	m_vertexCount = (m_terrainHeight - 1) * (m_terrainWidth - 1) * 6;

	m_terrainModel = new MyStruct::ModelType[m_vertexCount];
	if (!m_terrainModel)
		return false;

	quadsCovered = 32.0f;
	incrementSize = 1.0f / quadsCovered;

	tu2Left = 0.0f;
	tu2Right = incrementSize;
	tv2Top = 0.0f;
	tv2Bottom = incrementSize;

	index = 0;

	for (j = 0; j < m_terrainHeight - 1; ++j)
	{
		for (i = 0; i < m_terrainWidth - 1; ++i)
		{
			// Get the indexes to the four points of the quad.
			index1 = m_terrainWidth * j + i;				// Upper left.
			index2 = m_terrainWidth * j + (i + 1);			// Upper right.
			index3 = m_terrainWidth * (j + 1) + i;			// Bottom left.
			index4 = m_terrainWidth * (j + 1) + (i + 1);	// Bottom right.

			// Now create two triangles for that quad.
			// Triangle 1 - Upper left.
			m_terrainModel[index].x = m_heightMap[index1].x;
			m_terrainModel[index].y = m_heightMap[index1].y;
			m_terrainModel[index].z = m_heightMap[index1].z;
			m_terrainModel[index].tu = 0.0f;
			m_terrainModel[index].tv = 0.0f;
			m_terrainModel[index].tu2 = tu2Left;
			m_terrainModel[index].tv2 = tv2Top;
			m_terrainModel[index].nx = m_heightMap[index1].nx;
			m_terrainModel[index].ny = m_heightMap[index1].ny;
			m_terrainModel[index].nz = m_heightMap[index1].nz;
			m_terrainModel[index].r = m_heightMap[index1].r;
			m_terrainModel[index].g = m_heightMap[index1].g;
			m_terrainModel[index].b = m_heightMap[index1].b;
			++index;

			// Triangle 1 - Upper right.
			m_terrainModel[index].x = m_heightMap[index2].x;
			m_terrainModel[index].y = m_heightMap[index2].y;
			m_terrainModel[index].z = m_heightMap[index2].z;
			m_terrainModel[index].tu = 1.0f;
			m_terrainModel[index].tv = 0.0f;
			m_terrainModel[index].tu2 = tu2Right;
			m_terrainModel[index].tv2 = tv2Top;
			m_terrainModel[index].nx = m_heightMap[index2].nx;
			m_terrainModel[index].ny = m_heightMap[index2].ny;
			m_terrainModel[index].nz = m_heightMap[index2].nz;
			m_terrainModel[index].r = m_heightMap[index2].r;
			m_terrainModel[index].g = m_heightMap[index2].g;
			m_terrainModel[index].b = m_heightMap[index2].b;
			++index;

			// Triangle 1 - Bottom left.
			m_terrainModel[index].x = m_heightMap[index3].x;
			m_terrainModel[index].y = m_heightMap[index3].y;
			m_terrainModel[index].z = m_heightMap[index3].z;
			m_terrainModel[index].tu = 0.0f;
			m_terrainModel[index].tv = 1.0f;
			m_terrainModel[index].tu2 = tu2Left;
			m_terrainModel[index].tv2 = tv2Bottom;
			m_terrainModel[index].nx = m_heightMap[index3].nx;
			m_terrainModel[index].ny = m_heightMap[index3].ny;
			m_terrainModel[index].nz = m_heightMap[index3].nz;
			m_terrainModel[index].r = m_heightMap[index3].r;
			m_terrainModel[index].g = m_heightMap[index3].g;
			m_terrainModel[index].b = m_heightMap[index3].b;
			++index;

			// Triangle 2 - Bottom left.
			m_terrainModel[index].x = m_heightMap[index3].x;
			m_terrainModel[index].y = m_heightMap[index3].y;
			m_terrainModel[index].z = m_heightMap[index3].z;
			m_terrainModel[index].tu = 0.0f;
			m_terrainModel[index].tv = 1.0f;
			m_terrainModel[index].tu2 = tu2Left;
			m_terrainModel[index].tv2 = tv2Bottom;
			m_terrainModel[index].nx = m_heightMap[index3].nx;
			m_terrainModel[index].ny = m_heightMap[index3].ny;
			m_terrainModel[index].nz = m_heightMap[index3].nz;
			m_terrainModel[index].r = m_heightMap[index3].r;
			m_terrainModel[index].g = m_heightMap[index3].g;
			m_terrainModel[index].b = m_heightMap[index3].b;
			++index;

			// Triangle 2 - Upper right.
			m_terrainModel[index].x = m_heightMap[index2].x;
			m_terrainModel[index].y = m_heightMap[index2].y;
			m_terrainModel[index].z = m_heightMap[index2].z;
			m_terrainModel[index].tu = 1.0f;
			m_terrainModel[index].tv = 0.0f;
			m_terrainModel[index].tu2 = tu2Right;
			m_terrainModel[index].tv2 = tv2Top;
			m_terrainModel[index].nx = m_heightMap[index2].nx;
			m_terrainModel[index].ny = m_heightMap[index2].ny;
			m_terrainModel[index].nz = m_heightMap[index2].nz;
			m_terrainModel[index].r = m_heightMap[index2].r;
			m_terrainModel[index].g = m_heightMap[index2].g;
			m_terrainModel[index].b = m_heightMap[index2].b;
			++index;

			// Triangle 2 - Bottom right.
			m_terrainModel[index].x = m_heightMap[index4].x;
			m_terrainModel[index].y = m_heightMap[index4].y;
			m_terrainModel[index].z = m_heightMap[index4].z;
			m_terrainModel[index].tu = 1.0f;
			m_terrainModel[index].tv = 1.0f;
			m_terrainModel[index].tu2 = tu2Right;
			m_terrainModel[index].tv2 = tv2Bottom;
			m_terrainModel[index].nx = m_heightMap[index4].nx;
			m_terrainModel[index].ny = m_heightMap[index4].ny;
			m_terrainModel[index].nz = m_heightMap[index4].nz;
			m_terrainModel[index].r = m_heightMap[index4].r;
			m_terrainModel[index].g = m_heightMap[index4].g;
			m_terrainModel[index].b = m_heightMap[index4].b;
			++index;

			tu2Left += incrementSize;
			tu2Right += incrementSize;

			if (tu2Right > 1.0f)
			{
				tu2Left = 0.0f;
				tu2Right = incrementSize;
			}
		}

		tv2Top += incrementSize;
		tv2Bottom += incrementSize;

		if (tv2Bottom > 1.0f)
		{
			tv2Top = 0.0f;
			tv2Bottom = incrementSize;
		}
	}

	return true;
}

void TerrainClass::ShutdownTerrainModel()
{
	if (m_terrainModel)
	{
		delete[] m_terrainModel;
		m_terrainModel = NULL;
	}

	return;
}

void TerrainClass::CalculateTerrainVectors()
{
	int faceCount, i, index;
	MyStruct::TempVertexType vertex1, vertex2, vertex3;
	MyStruct::VectorType tangent, binormal;

	faceCount = m_vertexCount / 3;
	index = 0;

	for (i = 0; i < faceCount; ++i)
	{
		vertex1.x = m_terrainModel[index].x;
		vertex1.y = m_terrainModel[index].y;
		vertex1.z = m_terrainModel[index].z;
		vertex1.tu = m_terrainModel[index].tu;
		vertex1.tv = m_terrainModel[index].tv;
		vertex1.nx = m_terrainModel[index].nx;
		vertex1.ny = m_terrainModel[index].ny;
		vertex1.nz = m_terrainModel[index].nz;
		++index;

		vertex2.x = m_terrainModel[index].x;
		vertex2.y = m_terrainModel[index].y;
		vertex2.z = m_terrainModel[index].z;
		vertex2.tu = m_terrainModel[index].tu;
		vertex2.tv = m_terrainModel[index].tv;
		vertex2.nx = m_terrainModel[index].nx;
		vertex2.ny = m_terrainModel[index].ny;
		vertex2.nz = m_terrainModel[index].nz;
		++index;

		vertex3.x = m_terrainModel[index].x;
		vertex3.y = m_terrainModel[index].y;
		vertex3.z = m_terrainModel[index].z;
		vertex3.tu = m_terrainModel[index].tu;
		vertex3.tv = m_terrainModel[index].tv;
		vertex3.nx = m_terrainModel[index].nx;
		vertex3.ny = m_terrainModel[index].ny;
		vertex3.nz = m_terrainModel[index].nz;
		++index;

		CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, binormal);

		m_terrainModel[index - 1].tx = tangent.x;
		m_terrainModel[index - 1].ty = tangent.y;
		m_terrainModel[index - 1].tz = tangent.z;
		m_terrainModel[index - 1].bx = binormal.x;
		m_terrainModel[index - 1].by = binormal.y;
		m_terrainModel[index - 1].bz = binormal.z;

		m_terrainModel[index - 2].tx = tangent.x;
		m_terrainModel[index - 2].ty = tangent.y;
		m_terrainModel[index - 2].tz = tangent.z;
		m_terrainModel[index - 2].bx = binormal.x;
		m_terrainModel[index - 2].by = binormal.y;
		m_terrainModel[index - 2].bz = binormal.z;

		m_terrainModel[index - 3].tx = tangent.x;
		m_terrainModel[index - 3].ty = tangent.y;
		m_terrainModel[index - 3].tz = tangent.z;
		m_terrainModel[index - 3].bx = binormal.x;
		m_terrainModel[index - 3].by = binormal.y;
		m_terrainModel[index - 3].bz = binormal.z;
	}

	return;
}

void TerrainClass::CalculateTangentBinormal(
	const MyStruct::TempVertexType vertex1,
	const MyStruct::TempVertexType vertex2,
	const MyStruct::TempVertexType vertex3,
	MyStruct::VectorType &tangent,
	MyStruct::VectorType &binormal)
{
	float vector1[3], vector2[3];
	float tuVector[2], tvVector[2];
	float den;
	float length;

	vector1[0] = vertex2.x - vertex1.x;
	vector1[1] = vertex2.y - vertex1.y;
	vector1[2] = vertex2.z - vertex1.z;

	vector2[0] = vertex3.x - vertex1.x;
	vector2[1] = vertex3.y - vertex1.y;
	vector2[2] = vertex3.z - vertex1.z;

	tvVector[0] = vertex2.tu - vertex1.tu;
	tvVector[0] = vertex2.tv - vertex1.tv;

	tvVector[1] = vertex3.tu - vertex1.tu;
	tvVector[1] = vertex3.tv - vertex1.tv;

	den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

	tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
	tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
	tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

	binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
	binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
	binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

	length = (float)sqrt(tangent.x * tangent.x +
		tangent.y * tangent.y +
		tangent.z * tangent.z);

	tangent.x = tangent.x / length;
	tangent.y = tangent.y / length;
	tangent.z = tangent.z / length;

	length = (float)sqrt(binormal.x * binormal.x +
		binormal.y * binormal.y +
		binormal.z * binormal.z);

	binormal.x = binormal.x / length;
	binormal.y = binormal.y / length;
	binormal.z = binormal.z / length;

	return;
}

bool TerrainClass::LoadTerrainCells(ID3D11Device *device, const MyStruct::TERRAIN_DESC &terrainDesc)
{
	int tileHeight, tileWidth, cellRowCount, i, j, index;
	bool result;

	tileHeight = terrainDesc.nTile + 1;
	tileWidth = terrainDesc.nTile + 1;

	cellRowCount = terrainDesc.nCell;
	m_cellCount = cellRowCount * cellRowCount;

	m_TerrainCells = new TerrainCellClass[m_cellCount];
	if (!m_TerrainCells)
		return false;

	for (j = 0; j < cellRowCount; ++j)
	{
		for (i = 0; i < cellRowCount; ++i)
		{
			index = cellRowCount * j + i;
			
			result = m_TerrainCells[index].Initialize(device,
				m_terrainModel,
				i,
				j,
				tileHeight,
				tileWidth,
				m_terrainWidth);
			if (!result)
				return false;
		}
	}

	return true;
}

void TerrainClass::ShutdownTerrainCells()
{
	int i;

	if (m_TerrainCells)
	{
		for (i = 0; i < m_cellCount; ++i)
			m_TerrainCells[i].Shutdown();

		delete[] m_TerrainCells;
		m_TerrainCells = NULL;
	}

	return;
}

bool TerrainClass::CheckHeightOfTriangle(float x,
	float z,
	float &height,
	float v0[3], 
	float v1[3], 
	float v2[3])
{
	float startVector[3], directionVector[3], edge1[3], edge2[3], normal[3];
	float Q[3], e1[3], e2[3], e3[3], edgeNormal[3], temp[3];
	float magnitude, D, denominator, numerator, t, determinant;

	startVector[0] = x;
	startVector[1] = 0.0f;
	startVector[2] = z;

	directionVector[0] = 0.0f;
	directionVector[1] = -1.0f;
	directionVector[2] = 0.0f;

	edge1[0] = v1[0] - v0[0];
	edge1[1] = v1[1] - v0[1];
	edge1[2] = v1[2] - v0[2];

	edge2[0] = v2[0] - v0[0];
	edge2[1] = v2[1] - v0[1];
	edge2[2] = v2[2] - v0[2];

	normal[0] = edge1[1] * edge2[2] - edge1[2] * edge2[1];
	normal[1] = edge1[2] * edge2[0] - edge1[0] * edge2[2];
	normal[2] = edge1[0] * edge2[1] - edge1[1] * edge2[0];

	magnitude = (float)sqrt(normal[0] * normal[0] +
		normal[1] * normal[1] +
		normal[2] * normal[2]);

	normal[0] = normal[0] / magnitude;
	normal[1] = normal[1] / magnitude;
	normal[2] = normal[2] / magnitude;

	// distance
	D = -normal[0] * v0[0] + -normal[1] * v0[1] + -normal[2] * v0[2];

	denominator = normal[0] * directionVector[0] +
		normal[1] * directionVector[1] +
		normal[2] * directionVector[2];

	if (fabs(denominator) < 0.0001f)
		return false;

	numerator = -1.0f * ((normal[0] * startVector[0] +
		normal[1] * startVector[1] +
		normal[2] * startVector[2]) + D);

	// intersect the triangle
	t = numerator / denominator;

	// intersect vector
	Q[0] = startVector[0] + directionVector[0] * t;
	Q[1] = startVector[1] + directionVector[1] * t;
	Q[2] = startVector[2] + directionVector[2] * t;

	e1[0] = v1[0] - v0[0];
	e1[1] = v1[1] - v0[1];
	e1[2] = v1[2] - v0[2];

	e2[0] = v2[0] - v1[0];
	e2[1] = v2[1] - v1[1];
	e2[2] = v2[2] - v1[2];

	e3[0] = v0[0] - v2[0];
	e3[1] = v0[1] - v2[1];
	e3[2] = v0[2] - v2[2];

	edgeNormal[0] = e1[1] * normal[2] - e1[2] * normal[1];
	edgeNormal[1] = e1[2] * normal[0] - e1[0] * normal[2];
	edgeNormal[2] = e1[0] * normal[1] - e1[1] * normal[0];

	temp[0] = Q[0] - v0[0];
	temp[1] = Q[1] - v0[1];
	temp[2] = Q[2] - v0[2];

	determinant = edgeNormal[0] * temp[0] +
		edgeNormal[1] * temp[1] +
		edgeNormal[2] * temp[2];

	if (determinant > 0.001f)
		return false;

	edgeNormal[0] = e2[1] * normal[2] - e2[2] * normal[1];
	edgeNormal[1] = e2[2] * normal[0] - e2[0] * normal[2];
	edgeNormal[2] = e2[0] * normal[1] - e2[1] * normal[0];

	temp[0] = Q[0] - v1[0];
	temp[1] = Q[1] - v1[1];
	temp[2] = Q[2] - v1[2];

	determinant = edgeNormal[0] * temp[0] +
		edgeNormal[1] * temp[1] +
		edgeNormal[2] * temp[2];

	if (determinant > 0.001f)
		return false;

	edgeNormal[0] = e3[1] * normal[2] - e3[2] * normal[1];
	edgeNormal[1] = e3[2] * normal[0] - e3[0] * normal[2];
	edgeNormal[2] = e3[0] * normal[1] - e3[1] * normal[0];

	temp[0] = Q[0] - v2[0];
	temp[1] = Q[1] - v2[1];
	temp[2] = Q[2] - v2[2];

	determinant = edgeNormal[0] * temp[0] +
		edgeNormal[1] * temp[1] +
		edgeNormal[2] * temp[2];

	if (determinant > 0.001f)
		return false;

	height = Q[1];

	return true;
}

bool TerrainClass::BuildBrushCircleBuffers(ID3D11Device *device, int nVertex, XMFLOAT3 color)
{
	

	return true;
}
