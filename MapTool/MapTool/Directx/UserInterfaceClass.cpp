#include "UserInterfaceClass.h"

UserInterfaceClass::UserInterfaceClass()
{
	m_Font1 = 0;
	m_FpsString = 0;
	m_VideoStrings = 0;
	m_PositionStrings = 0;
	m_SkyColorStrings = 0;
	m_RenderCountStrings = 0;
	m_MiniMap = 0;
	m_MousePositionStrings = 0;
}

UserInterfaceClass::UserInterfaceClass(const UserInterfaceClass &other)
{
}

UserInterfaceClass::~UserInterfaceClass()
{
}

bool UserInterfaceClass::Initialize(D3DClass *Direct3D, 
	int screenHeight, 
	int screenWidth)
{
	bool result;
	char videoCard[128];
	int videoMemory;
	char videoString[144];
	char memoryString[32];
	char tempString[16];
	int i;

	m_Font1 = new FontClass;
	if (!m_Font1)
		return false;

	result = m_Font1->Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		"Data/font/",
		"font01.txt",
		"font01.tga",
		32.0f,
		3);
	if (!result)
		return false;

	m_FpsString = new TextClass;
	if (!m_FpsString)
		return false;

	result = m_FpsString->Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"Fps: 0",
		10,
		-50,
		0.0f,
		1.0f,
		0.0f);
	if (!result)
		return false;

	m_PreviousFps = -1;

	Direct3D->GetVideoCardInfo(videoCard, videoMemory);
	strcpy_s(videoString, "Video Card: ");
	strcat_s(videoString, videoCard);

	_itoa_s(videoMemory, tempString, 10);

	strcpy_s(memoryString, "Video Memory: ");
	strcat_s(memoryString, tempString);
	strcat_s(memoryString, " MB");

	m_VideoStrings = new TextClass[2];
	if (!m_VideoStrings)
		return false;

	result = m_VideoStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		256,
		false,
		m_Font1,
		videoString,
		10,
		-10,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_VideoStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		32,
		false,
		m_Font1,
		memoryString,
		10,
		-30,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	m_PositionStrings = new TextClass[6];
	if (!m_PositionStrings)
		return false;

	result = m_PositionStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"X: 0",
		10,
		-310,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_PositionStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"Y: 0",
		10,
		-330,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_PositionStrings[2].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"Z: 0",
		10,
		-350,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_PositionStrings[3].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"rX: 0",
		10,
		-370,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_PositionStrings[4].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"rY: 0",
		10,
		-390,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_PositionStrings[5].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"rZ: 0",
		10,
		-410,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	for (i = 0; i < 6; ++i)
		m_PreviousPosition[i] = -1;

	m_SkyColorTypeStrings = new TextClass[2];
	if (!m_SkyColorTypeStrings)
		return false;

	result = m_SkyColorTypeStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"ApexColor",
		10,
		-270,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_SkyColorTypeStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"CenterColor",
		10,
		-380,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	m_SkyColorStrings = new TextClass[8];
	if (!m_SkyColorStrings)
		return false;

	result = m_SkyColorStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"R: 0",
		10,
		-290,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_SkyColorStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"G: 0",
		10,
		-310,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;


	result = m_SkyColorStrings[2].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"B: 0",
		10,
		-330,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_SkyColorStrings[3].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"A: 0",
		10,
		-350,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_SkyColorStrings[4].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"R: 0",
		10,
		-400,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_SkyColorStrings[5].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"G: 0",
		10,
		-420,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_SkyColorStrings[6].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"B: 0",
		10,
		-440,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_SkyColorStrings[7].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"A: 0",
		10,
		-460,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	for (i = 0; i < 8; ++i)
		m_PreviousSkyColor[i] = -1;

	m_RenderCountStrings = new TextClass[3];
	if (!m_RenderCountStrings)
		return false;

	result = m_RenderCountStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		32,
		false,
		m_Font1,
		"Polys Drawn: 0",
		10,
		-490,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_RenderCountStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		32,
		false,
		m_Font1,
		"Cells Drawn: 0",
		10,
		-510,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;
	result = m_RenderCountStrings[2].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		32,
		false,
		m_Font1,
		"Cells Culled: 0",
		10,
		-530,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	m_MousePositionStrings = new TextClass[2];
	if (!m_MousePositionStrings)
		return false;
	result = m_MousePositionStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"X: 0",
		5,
		-560,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	result = m_MousePositionStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_Font1,
		"Y: 0",
		5,
		-580,
		1.0f,
		1.0f,
		1.0f);
	if (!result)
		return false;

	for (i = 0; i < 2; ++i)
		m_PreviousMousePosition[i] = -1;

	//m_MiniMap = new MiniMapClass;
	//if (!m_MiniMap)
	//	return false;
	//result = m_MiniMap->Initialize(Direct3D->GetDevice(),
	//	Direct3D->GetDeviceContext(),
	//	screenWidth,
	//	screenHeight,
	//	1025,
	//	1025);
	//if (!result)
	//	return false;

	return true;
}

void UserInterfaceClass::Shutdown()
{
	//if (m_MiniMap)
	//{
	//	m_MiniMap->Shutdown();
	//	delete m_MiniMap;
	//	m_MiniMap = NULL;
	//}

	if (m_MousePositionStrings)
	{
		m_MousePositionStrings[0].Shutdown();
		m_MousePositionStrings[1].Shutdown();

		delete[] m_MousePositionStrings;
		m_MousePositionStrings = NULL;
	}

	if (m_RenderCountStrings)
	{
		m_RenderCountStrings[0].Shutdown();
		m_RenderCountStrings[1].Shutdown();
		m_RenderCountStrings[2].Shutdown();

		delete[] m_RenderCountStrings;
		m_RenderCountStrings = NULL;
	}

	if (m_PositionStrings)
	{
		m_PositionStrings[0].Shutdown();
		m_PositionStrings[1].Shutdown();
		m_PositionStrings[2].Shutdown();
		m_PositionStrings[3].Shutdown();
		m_PositionStrings[4].Shutdown();
		m_PositionStrings[5].Shutdown();

		delete[] m_PositionStrings;
		m_PositionStrings = NULL;
	}

	if (m_SkyColorStrings)
	{
		m_SkyColorStrings[0].Shutdown();
		m_SkyColorStrings[1].Shutdown();
		m_SkyColorStrings[2].Shutdown();
		m_SkyColorStrings[3].Shutdown();
		m_SkyColorStrings[4].Shutdown();
		m_SkyColorStrings[5].Shutdown();
		m_SkyColorStrings[6].Shutdown();
		m_SkyColorStrings[7].Shutdown();

		delete[] m_SkyColorStrings;
		m_SkyColorStrings = NULL;
	}

	if (m_SkyColorTypeStrings)
	{
		m_SkyColorTypeStrings[0].Shutdown();
		m_SkyColorTypeStrings[1].Shutdown();

		delete[] m_SkyColorTypeStrings;
		m_SkyColorTypeStrings = NULL;
	}

	if (m_VideoStrings)
	{
		m_VideoStrings[0].Shutdown();
		m_VideoStrings[1].Shutdown();

		delete[] m_VideoStrings;
		m_VideoStrings = NULL;
	}

	if (m_FpsString)
	{
		m_FpsString->Shutdown();
		delete m_FpsString;
		m_FpsString = NULL;
	}

	if (m_Font1)
	{
		m_Font1->Shutdown();
		delete m_Font1;
		m_Font1 = NULL;
	}

	return;
}

bool UserInterfaceClass::Frame(ID3D11DeviceContext *deviceContext,
	int fps,
	float posX, 
	float posY,
	float posZ,
	float rotX,
	float rotY,
	float rotZ,
	XMFLOAT4 apexColor,
	XMFLOAT4 centerColor,
	int mousePosX,
	int mousePosY)
{
	bool result;

	result = UpdateFpsString(deviceContext, fps);
	if (!result)
		return false;

	result = UpdatePositionStrings(deviceContext,
		posX,
		posY,
		posZ,
		rotX,
		rotY,
		rotZ);

	if (!result)
		return false;

	result = UpdateSkyColorStrings(deviceContext,
		apexColor,
		centerColor);

	if (!result)
		return false;

	result = UpdateMousePositionStrings(deviceContext,
		mousePosX,
		mousePosY);

	if (!result)
		return false;

	//m_MiniMap->PositionUpdate(posX, posZ);

	return true;
}

bool UserInterfaceClass::Render(D3DClass *Direct3D,
	ShaderManagerClass *shaderManager,
	XMMATRIX worldMatrix,
	XMMATRIX viewMatrix,
	XMMATRIX orthoMatrix)
{
	int i;
	bool result;

	Direct3D->TurnZBufferOff();
	Direct3D->EnableAlphaBlending();

	m_FpsString->Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_Font1->GetTexture());

	m_VideoStrings[0].Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_Font1->GetTexture());
	m_VideoStrings[1].Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_Font1->GetTexture());

	for (i = 0; i < 6; ++i)
		m_PositionStrings[i].Render(Direct3D->GetDeviceContext(),
			shaderManager,
			worldMatrix,
			viewMatrix,
			orthoMatrix,
			m_Font1->GetTexture());

	m_SkyColorTypeStrings[0].Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_Font1->GetTexture());
	m_SkyColorTypeStrings[1].Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_Font1->GetTexture());

	for (i = 0; i < 8; ++i)
		m_SkyColorStrings[i].Render(Direct3D->GetDeviceContext(),
			shaderManager,
			worldMatrix,
			viewMatrix,
			orthoMatrix,
			m_Font1->GetTexture());

	for (i = 0; i < 3; ++i)
		m_RenderCountStrings[i].Render(Direct3D->GetDeviceContext(),
			shaderManager,
			worldMatrix,
			viewMatrix,
			orthoMatrix,
			m_Font1->GetTexture());

	for (i = 0; i < 2; ++i)
		m_MousePositionStrings[i].Render(Direct3D->GetDeviceContext(),
			shaderManager,
			worldMatrix,
			viewMatrix,
			orthoMatrix,
			m_Font1->GetTexture());

	Direct3D->DisableAlphaBlending();

	//result = m_MiniMap->Render(Direct3D->GetDeviceContext(),
	//	shaderManager,
	//	worldMatrix,
	//	viewMatrix,
	//	orthoMatrix);
	//if (!result)
	//	return false;

	Direct3D->TurnZBufferOn();

	return true;
}

bool UserInterfaceClass::UpdateRenderCounts(ID3D11DeviceContext *deviceContext,
	int renderCount,
	int nodesDrawn,
	int nodeCulled)
{
	char tempString[32];
	char finalString[32];
	bool result;

	_itoa_s(renderCount, tempString, 10);

	strcpy_s(finalString, "Polys Drawn: ");
	strcat_s(finalString, tempString);

	result = m_RenderCountStrings[0].UpdateSentence(deviceContext,
		m_Font1,
		finalString,
		10,
		-490,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	_itoa_s(nodesDrawn, tempString, 10);

	strcpy_s(finalString, "Cells Drawn: ");
	strcat_s(finalString, tempString);

	result = m_RenderCountStrings[1].UpdateSentence(deviceContext,
		m_Font1,
		finalString,
		10,
		-510,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	_itoa_s(nodeCulled, tempString, 10);

	strcpy_s(finalString, "Cells Culled: ");
	strcat_s(finalString, tempString);

	result = m_RenderCountStrings[2].UpdateSentence(deviceContext,
		m_Font1,
		finalString,
		10,
		-530,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	return true;
}

bool UserInterfaceClass::UpdateFpsString(ID3D11DeviceContext *deviceContext, int fps)
{
	char tempString[16];
	char finalString[16];
	float red, green, blue;
	bool result;

	if (m_PreviousFps == fps)
		return true;

	m_PreviousFps = fps;

	if (fps > 99999)
		fps = 99999;

	_itoa_s(fps, tempString, 10);

	strcpy_s(finalString, "Fps: ");
	strcat_s(finalString, tempString);

	if (fps >= 60)
	{
		red = 0.0f;
		green = 1.0f;
		blue = 0.0;
	}
	if (fps < 60)
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0;
	}
	if (fps < 30)
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}

	result = m_FpsString->UpdateSentence(deviceContext,
		m_Font1,
		finalString,
		10,
		-50,
		red,
		green,
		blue);
	
	if (!result)
		return false;

	return true;
}

bool UserInterfaceClass::UpdatePositionStrings(ID3D11DeviceContext *deviceContext,
	float posX,
	float posY,
	float posZ,
	float rotX,
	float rotY,
	float rotZ)
{
	int positionX, positionY, positionZ, rotationX, rotationY, rotationZ;
	char tempString[16];
	char finalString[16];
	bool result;

	positionX = (int)posX;
	positionY = (int)posY;
	positionZ = (int)posZ;
	rotationX = (int)rotX;
	rotationY = (int)rotY;
	rotationZ = (int)rotZ;

	if (positionX != m_PreviousPosition[0])
	{
		m_PreviousPosition[0] = positionX;
		_itoa_s(positionX, tempString, 10);
		strcpy_s(finalString, "X: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[0].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-100,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (positionY != m_PreviousPosition[1])
	{
		m_PreviousPosition[1] = positionY;
		_itoa_s(positionY, tempString, 10);
		strcpy_s(finalString, "Y: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[1].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-120,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (positionZ != m_PreviousPosition[2])
	{
		m_PreviousPosition[2] = positionZ;
		_itoa_s(positionZ, tempString, 10);
		strcpy_s(finalString, "Z: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[2].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-140,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}

	if (rotationX != m_PreviousPosition[3])
	{
		m_PreviousPosition[3] = rotationX;
		_itoa_s(rotationX, tempString, 10);
		strcpy_s(finalString, "rX: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[3].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-180,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (rotationY != m_PreviousPosition[4])
	{
		m_PreviousPosition[4] = rotationY;
		_itoa_s(rotationY, tempString, 10);
		strcpy_s(finalString, "rY: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[4].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-200,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (rotationZ != m_PreviousPosition[5])
	{
		m_PreviousPosition[5] = rotationZ;
		_itoa_s(rotationZ, tempString, 10);
		strcpy_s(finalString, "rZ: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[5].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-220,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}

	return true;
}

bool UserInterfaceClass::UpdateSkyColorStrings(ID3D11DeviceContext *deviceContext, 
	XMFLOAT4 apexColor,
	XMFLOAT4 centerColor)
{
	float apexR, apexG, apexB, apexA;
	float centerR, centerG, centerB, centerA;
	char tempString[16];
	char finalString[16];
	bool result;

	apexR = apexColor.x;
	apexG = apexColor.y;
	apexB = apexColor.z;
	apexA = apexColor.w;

	centerR = centerColor.x;
	centerG = centerColor.y;
	centerB = centerColor.z;
	centerA = centerColor.w;

	if (apexR != m_PreviousSkyColor[0])
	{
		m_PreviousSkyColor[0] = apexR;
		sprintf_s(tempString, "%.3f", apexR);
		strcpy_s(finalString, "R: ");
		strcat_s(finalString, tempString);
		result = m_SkyColorStrings[0].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-290,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (apexG != m_PreviousSkyColor[1])
	{
		m_PreviousSkyColor[1] = apexG;
		sprintf_s(tempString, "%.3f", apexG);
		strcpy_s(finalString, "G: ");
		strcat_s(finalString, tempString);
		result = m_SkyColorStrings[1].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-310,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (apexB != m_PreviousSkyColor[2])
	{
		m_PreviousSkyColor[2] = apexB;
		sprintf_s(tempString, "%.3f", apexB);
		strcpy_s(finalString, "B: ");
		strcat_s(finalString, tempString);
		result = m_SkyColorStrings[2].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-330,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (apexA != m_PreviousSkyColor[3])
	{
		m_PreviousSkyColor[3] = apexA;
		sprintf_s(tempString, "%.3f", apexA);
		strcpy_s(finalString, "A: ");
		strcat_s(finalString, tempString);
		result = m_SkyColorStrings[3].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-350,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}

	if (centerR != m_PreviousSkyColor[4])
	{
		m_PreviousSkyColor[4] = centerR;
		sprintf_s(tempString, "%.3f", centerR);
		strcpy_s(finalString, "R: ");
		strcat_s(finalString, tempString);
		result = m_SkyColorStrings[4].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-400,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (centerG != m_PreviousSkyColor[5])
	{
		m_PreviousSkyColor[5] = centerG;
		sprintf_s(tempString, "%.3f", centerG);
		strcpy_s(finalString, "G: ");
		strcat_s(finalString, tempString);
		result = m_SkyColorStrings[5].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-420,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (centerB != m_PreviousSkyColor[6])
	{
		m_PreviousSkyColor[6] = centerB;
		sprintf_s(tempString, "%.3f", centerB);
		strcpy_s(finalString, "B: ");
		strcat_s(finalString, tempString);
		result = m_SkyColorStrings[6].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-440,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (centerA != m_PreviousSkyColor[7])
	{
		m_PreviousSkyColor[7] = centerA;
		sprintf_s(tempString, "%.3f", centerA);
		strcpy_s(finalString, "A: ");
		strcat_s(finalString, tempString);
		result = m_SkyColorStrings[7].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			10,
			-460,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}

	return true;
}

bool UserInterfaceClass::UpdateMousePositionStrings(ID3D11DeviceContext *deviceContext, 
	int posX, 
	int posY)
{
	char tempString[16];
	char finalString[16];
	bool result;

	if (posX != m_PreviousMousePosition[0])
	{
		m_PreviousMousePosition[0] = posX;
		_itoa_s(posX, tempString, 10);
		strcpy_s(finalString, "X: ");
		strcat_s(finalString, tempString);
		result = m_MousePositionStrings[0].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			5,
			-560,
			1.0f,
			1.0f,
			1.0f);
	}
	if (posY != m_PreviousMousePosition[1])
	{
		m_PreviousMousePosition[1] = posY;
		_itoa_s(posY, tempString, 10);
		strcpy_s(finalString, "Y: ");
		strcat_s(finalString, tempString);
		result = m_MousePositionStrings[1].UpdateSentence(deviceContext,
			m_Font1,
			finalString,
			5,
			-580,
			1.0f,
			1.0f,
			1.0f);
	}

	return true;
}
