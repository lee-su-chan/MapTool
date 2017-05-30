#include "UserInterfaceClass.h"

UserInterfaceClass::UserInterfaceClass()
{
	m_font1 = 0;
	m_fpsString = 0;
	m_videoStrings = 0;
	m_positionStrings = 0;
	m_skyColorStrings = 0;
	m_renderCountStrings = 0;
	m_MiniMap = 0;
	m_mousePositionStrings = 0;
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

	m_font1 = new FontClass;
	if (!m_font1)
		return false;

	result = m_font1->Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		"Data/font/",
		"font01.txt",
		"font01.tga",
		32.0f,
		3);

	if (!result)
		return false;

	m_fpsString = new TextClass;
	if (!m_fpsString)
		return false;

	result = m_fpsString->Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"Fps: 0",
		10,
		-50,
		0.0f,
		1.0f,
		0.0f);

	if (!result)
		return false;

	m_previousFps = -1;

	Direct3D->GetVideoCardInfo(videoCard, videoMemory);
	strcpy_s(videoString, "Video Card: ");
	strcat_s(videoString, videoCard);

	_itoa_s(videoMemory, tempString, 10);

	strcpy_s(memoryString, "Video Memory: ");
	strcat_s(memoryString, tempString);
	strcat_s(memoryString, " MB");

	m_videoStrings = new TextClass[2];
	if (!m_videoStrings)
		return false;

	result = m_videoStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		256,
		false,
		m_font1,
		videoString,
		10,
		-10,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_videoStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		32,
		false,
		m_font1,
		memoryString,
		10,
		-30,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	m_positionStrings = new TextClass[6];
	if (!m_positionStrings)
		return false;

	result = m_positionStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"X: 0",
		10,
		-310,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_positionStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"Y: 0",
		10,
		-330,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_positionStrings[2].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"Z: 0",
		10,
		-350,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_positionStrings[3].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"rX: 0",
		10,
		-370,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_positionStrings[4].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"rY: 0",
		10,
		-390,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_positionStrings[5].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"rZ: 0",
		10,
		-410,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	for (i = 0; i < 6; ++i)
		m_previousPosition[i] = -1;

	m_skyColorTypeStrings = new TextClass[2];
	if (!m_skyColorTypeStrings)
		return false;

	result = m_skyColorTypeStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"ApexColor",
		10,
		-270,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_skyColorTypeStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"CenterColor",
		10,
		-380,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	m_skyColorStrings = new TextClass[8];
	if (!m_skyColorStrings)
		return false;

	result = m_skyColorStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"R: 0",
		10,
		-290,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_skyColorStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"G: 0",
		10,
		-310,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;


	result = m_skyColorStrings[2].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"B: 0",
		10,
		-330,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_skyColorStrings[3].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"A: 0",
		10,
		-350,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_skyColorStrings[4].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"R: 0",
		10,
		-400,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_skyColorStrings[5].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"G: 0",
		10,
		-420,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_skyColorStrings[6].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"B: 0",
		10,
		-440,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_skyColorStrings[7].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"A: 0",
		10,
		-460,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	for (i = 0; i < 8; ++i)
		m_previousSkyColor[i] = -1;

	m_renderCountStrings = new TextClass[3];
	if (!m_renderCountStrings)
		return false;

	result = m_renderCountStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		32,
		false,
		m_font1,
		"Polys Drawn: 0",
		10,
		-490,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_renderCountStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		32,
		false,
		m_font1,
		"Cells Drawn: 0",
		10,
		-510,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	result = m_renderCountStrings[2].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		32,
		false,
		m_font1,
		"Cells Culled: 0",
		10,
		-530,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	m_mousePositionStrings = new TextClass[2];
	if (!m_mousePositionStrings)
		return false;

	result = m_mousePositionStrings[0].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"X: 0",
		5,
		-560,
		1.0f,
		1.0f,
		1.0f);
	
	if (!result)
		return false;

	result = m_mousePositionStrings[1].Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		16,
		false,
		m_font1,
		"Y: 0",
		5,
		-580,
		1.0f,
		1.0f,
		1.0f);

	if (!result)
		return false;

	for (i = 0; i < 2; ++i)
		m_previousMousePosition[i] = -1;

	m_MiniMap = new MiniMapClass;
	if (!m_MiniMap)
		return false;

	result = m_MiniMap->Initialize(Direct3D->GetDevice(),
		Direct3D->GetDeviceContext(),
		screenWidth,
		screenHeight,
		1025,
		1025);

	if (!result)
		return false;

	return true;
}

void UserInterfaceClass::Shutdown()
{
	if (m_MiniMap)
	{
		m_MiniMap->Shutdown();
		delete m_MiniMap;
		m_MiniMap = NULL;
	}

	if (m_mousePositionStrings)
	{
		m_mousePositionStrings[0].Shutdown();
		m_mousePositionStrings[1].Shutdown();

		delete[] m_mousePositionStrings;
		m_mousePositionStrings = NULL;
	}

	if (m_renderCountStrings)
	{
		m_renderCountStrings[0].Shutdown();
		m_renderCountStrings[1].Shutdown();
		m_renderCountStrings[2].Shutdown();

		delete[] m_renderCountStrings;
		m_renderCountStrings = NULL;
	}

	if (m_positionStrings)
	{
		m_positionStrings[0].Shutdown();
		m_positionStrings[1].Shutdown();
		m_positionStrings[2].Shutdown();
		m_positionStrings[3].Shutdown();
		m_positionStrings[4].Shutdown();
		m_positionStrings[5].Shutdown();

		delete[] m_positionStrings;
		m_positionStrings = NULL;
	}

	if (m_skyColorStrings)
	{
		m_skyColorStrings[0].Shutdown();
		m_skyColorStrings[1].Shutdown();
		m_skyColorStrings[2].Shutdown();
		m_skyColorStrings[3].Shutdown();
		m_skyColorStrings[4].Shutdown();
		m_skyColorStrings[5].Shutdown();
		m_skyColorStrings[6].Shutdown();
		m_skyColorStrings[7].Shutdown();

		delete[] m_skyColorStrings;
		m_skyColorStrings = NULL;
	}

	if (m_skyColorTypeStrings)
	{
		m_skyColorTypeStrings[0].Shutdown();
		m_skyColorTypeStrings[1].Shutdown();

		delete[] m_skyColorTypeStrings;
		m_skyColorTypeStrings = NULL;
	}

	if (m_videoStrings)
	{
		m_videoStrings[0].Shutdown();
		m_videoStrings[1].Shutdown();

		delete[] m_videoStrings;
		m_videoStrings = NULL;
	}

	if (m_fpsString)
	{
		m_fpsString->Shutdown();
		delete m_fpsString;
		m_fpsString = NULL;
	}

	if (m_font1)
	{
		m_font1->Shutdown();
		delete m_font1;
		m_font1 = NULL;
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

	m_MiniMap->PositionUpdate(posX, posZ);

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

	m_fpsString->Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_font1->GetTexture());

	m_videoStrings[0].Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_font1->GetTexture());
	m_videoStrings[1].Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_font1->GetTexture());

	for (i = 0; i < 6; ++i)
		m_positionStrings[i].Render(Direct3D->GetDeviceContext(),
			shaderManager,
			worldMatrix,
			viewMatrix,
			orthoMatrix,
			m_font1->GetTexture());

	m_skyColorTypeStrings[0].Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_font1->GetTexture());
	m_skyColorTypeStrings[1].Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_font1->GetTexture());

	for (i = 0; i < 8; ++i)
		m_skyColorStrings[i].Render(Direct3D->GetDeviceContext(),
			shaderManager,
			worldMatrix,
			viewMatrix,
			orthoMatrix,
			m_font1->GetTexture());

	for (i = 0; i < 3; ++i)
		m_renderCountStrings[i].Render(Direct3D->GetDeviceContext(),
			shaderManager,
			worldMatrix,
			viewMatrix,
			orthoMatrix,
			m_font1->GetTexture());

	for (i = 0; i < 2; ++i)
		m_mousePositionStrings[i].Render(Direct3D->GetDeviceContext(),
			shaderManager,
			worldMatrix,
			viewMatrix,
			orthoMatrix,
			m_font1->GetTexture());

	Direct3D->DisableAlphaBlending();

	result = m_MiniMap->Render(Direct3D->GetDeviceContext(),
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMatrix);

	if (!result)
		return false;

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

	result = m_renderCountStrings[0].UpdateSentence(deviceContext,
		m_font1,
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

	result = m_renderCountStrings[1].UpdateSentence(deviceContext,
		m_font1,
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

	result = m_renderCountStrings[2].UpdateSentence(deviceContext,
		m_font1,
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

	if (m_previousFps == fps)
		return true;

	m_previousFps = fps;

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

	result = m_fpsString->UpdateSentence(deviceContext,
		m_font1,
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

	if (positionX != m_previousPosition[0])
	{
		m_previousPosition[0] = positionX;
		_itoa_s(positionX, tempString, 10);
		strcpy_s(finalString, "X: ");
		strcat_s(finalString, tempString);
		result = m_positionStrings[0].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-100,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (positionY != m_previousPosition[1])
	{
		m_previousPosition[1] = positionY;
		_itoa_s(positionY, tempString, 10);
		strcpy_s(finalString, "Y: ");
		strcat_s(finalString, tempString);
		result = m_positionStrings[1].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-120,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (positionZ != m_previousPosition[2])
	{
		m_previousPosition[2] = positionZ;
		_itoa_s(positionZ, tempString, 10);
		strcpy_s(finalString, "Z: ");
		strcat_s(finalString, tempString);
		result = m_positionStrings[2].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-140,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}

	if (rotationX != m_previousPosition[3])
	{
		m_previousPosition[3] = rotationX;
		_itoa_s(rotationX, tempString, 10);
		strcpy_s(finalString, "rX: ");
		strcat_s(finalString, tempString);
		result = m_positionStrings[3].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-180,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (rotationY != m_previousPosition[4])
	{
		m_previousPosition[4] = rotationY;
		_itoa_s(rotationY, tempString, 10);
		strcpy_s(finalString, "rY: ");
		strcat_s(finalString, tempString);
		result = m_positionStrings[4].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-200,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (rotationZ != m_previousPosition[5])
	{
		m_previousPosition[5] = rotationZ;
		_itoa_s(rotationZ, tempString, 10);
		strcpy_s(finalString, "rZ: ");
		strcat_s(finalString, tempString);
		result = m_positionStrings[5].UpdateSentence(deviceContext,
			m_font1,
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

	if (apexR != m_previousSkyColor[0])
	{
		m_previousSkyColor[0] = apexR;
		sprintf_s(tempString, "%.3f", apexR);
		strcpy_s(finalString, "R: ");
		strcat_s(finalString, tempString);
		result = m_skyColorStrings[0].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-290,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (apexG != m_previousSkyColor[1])
	{
		m_previousSkyColor[1] = apexG;
		sprintf_s(tempString, "%.3f", apexG);
		strcpy_s(finalString, "G: ");
		strcat_s(finalString, tempString);
		result = m_skyColorStrings[1].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-310,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (apexB != m_previousSkyColor[2])
	{
		m_previousSkyColor[2] = apexB;
		sprintf_s(tempString, "%.3f", apexB);
		strcpy_s(finalString, "B: ");
		strcat_s(finalString, tempString);
		result = m_skyColorStrings[2].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-330,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (apexA != m_previousSkyColor[3])
	{
		m_previousSkyColor[3] = apexA;
		sprintf_s(tempString, "%.3f", apexA);
		strcpy_s(finalString, "A: ");
		strcat_s(finalString, tempString);
		result = m_skyColorStrings[3].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-350,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}

	if (centerR != m_previousSkyColor[4])
	{
		m_previousSkyColor[4] = centerR;
		sprintf_s(tempString, "%.3f", centerR);
		strcpy_s(finalString, "R: ");
		strcat_s(finalString, tempString);
		result = m_skyColorStrings[4].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-400,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (centerG != m_previousSkyColor[5])
	{
		m_previousSkyColor[5] = centerG;
		sprintf_s(tempString, "%.3f", centerG);
		strcpy_s(finalString, "G: ");
		strcat_s(finalString, tempString);
		result = m_skyColorStrings[5].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-420,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (centerB != m_previousSkyColor[6])
	{
		m_previousSkyColor[6] = centerB;
		sprintf_s(tempString, "%.3f", centerB);
		strcpy_s(finalString, "B: ");
		strcat_s(finalString, tempString);
		result = m_skyColorStrings[6].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			10,
			-440,
			1.0f,
			1.0f,
			1.0f);

		if (!result)
			return false;
	}
	if (centerA != m_previousSkyColor[7])
	{
		m_previousSkyColor[7] = centerA;
		sprintf_s(tempString, "%.3f", centerA);
		strcpy_s(finalString, "A: ");
		strcat_s(finalString, tempString);
		result = m_skyColorStrings[7].UpdateSentence(deviceContext,
			m_font1,
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

	if (posX != m_previousMousePosition[0])
	{
		m_previousMousePosition[0] = posX;
		_itoa_s(posX, tempString, 10);
		strcpy_s(finalString, "X: ");
		strcat_s(finalString, tempString);
		result = m_mousePositionStrings[0].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			5,
			-560,
			1.0f,
			1.0f,
			1.0f);
	}
	if (posY != m_previousMousePosition[1])
	{
		m_previousMousePosition[1] = posY;
		_itoa_s(posY, tempString, 10);
		strcpy_s(finalString, "Y: ");
		strcat_s(finalString, tempString);
		result = m_mousePositionStrings[1].UpdateSentence(deviceContext,
			m_font1,
			finalString,
			5,
			-580,
			1.0f,
			1.0f,
			1.0f);
	}

	return true;
}
