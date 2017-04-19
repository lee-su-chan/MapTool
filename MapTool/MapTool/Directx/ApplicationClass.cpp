#include "ApplicationClass.h"

ApplicationClass::ApplicationClass()
{
	m_Input = NULL;
	m_Direct3D = NULL;
	m_Timer = NULL;
	m_Fps = NULL;
	m_ShaderManager = NULL;
	m_TextureManager = NULL;
	m_Zone = NULL;
}

ApplicationClass::ApplicationClass(const ApplicationClass &other)
{
}

ApplicationClass::~ApplicationClass()
{
}

// hwnd[0] = DirectXView->Hwnd, hwnd[1] = MainFrm->Hwnd
bool ApplicationClass::Initialize(HINSTANCE hinstance,
	HWND hwnd[],
	int screenWidth, 
	int screenHeight)
{
	bool result;

	m_Input = new InputClass;
	if (!m_Input)
		return false;

	result = m_Input->initialze(hinstance, hwnd[1], screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd[1], L"Could not initialize the input object.", L"Error", MB_OK);
		
		return false;
	}
	
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
		return false;

	result = m_Direct3D->Initialize(screenWidth,
		screenHeight,
		VSYNC_ENABLED,
		hwnd[0],
		FULL_SCREEN,
		SCREEN_DEPTH,
		SCREEN_NEAR);

	if (!result)
	{
		MessageBox(hwnd[0], L"Could not initialize Direct3D.", L"Error", MB_OK);

		return false;
	}

	m_ShaderManager = new ShaderManagerClass;
	if (!m_ShaderManager)
		return false;

	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd[0]);
	if (!result)
	{
		MessageBox(hwnd[0], L"Could not initialize the shader manager object.", L"Error", MB_OK);

		return false;
	}

	m_TextureManager = new TextureManagerClass;
	if (!m_TextureManager)
		return false;

	result = m_TextureManager->Initialize(10);
	if (!result)
	{
		MessageBox(hwnd[0], L"Could not initialize manager object.", L"Error", MB_OK);

		return false;
	}

	//result = m_TextureManager->LoadTexture(m_Direct3D->GetDevice(),
	//	m_Direct3D->GetDeviceContext(),
	//	"Data/textures/dirt01d.tga",
	//	0);

	//if (!result)
	//	return false;

	// For TerrainShader
	result = m_TextureManager->LoadTexture(m_Direct3D->GetDevice(),
		m_Direct3D->GetDeviceContext(),
		"Data/Textures/Rock.tga",
		0);
	
	if (!result)
		return false;
	
	result = m_TextureManager->LoadTexture(m_Direct3D->GetDevice(),
		m_Direct3D->GetDeviceContext(),
		"Data/Textures/NormalMap/nRock.tga",
		1);
	
	if (!result)
		return false;
	
	result = m_TextureManager->LoadTexture(m_Direct3D->GetDevice(),
		m_Direct3D->GetDeviceContext(),
		"Data/Textures/NormalMap/nSnow.tga",
		2);
	
	if (!result)
		return false;
	
	result = m_TextureManager->LoadTexture(m_Direct3D->GetDevice(),
		m_Direct3D->GetDeviceContext(),
		"Data/Textures/NormalMap/nDistance.tga",
		3);
	
	if (!result)
		return false;

	m_Timer = new TimerClass;
	if (!m_Timer)
		return false;

	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd[0], L"Could not initialize the timer object.", L"Error", MB_OK);

		return false;
	}

	m_Fps = new FpsClass;
	if (!m_Fps)
		return false;

	m_Fps->Initialize();

	m_Zone = new ZoneClass;
	if (!m_Zone)
		return false;

	result = m_Zone->Initialize(m_Direct3D,
		hwnd[0],
		screenWidth,
		screenHeight,
		SCREEN_DEPTH);
	
	if (!result)
	{
		MessageBox(hwnd[0], L"Could not initialize the zone object.", L"Error", MB_OK);

		return false;
	}

	return true;
}

void ApplicationClass::Shutdown()
{
	if (m_Zone)
	{
		m_Zone->Shutdown();
		delete m_Zone;
		m_Zone = NULL;
	}

	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = NULL;
	}

	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = NULL;
	}

	if (m_TextureManager)
	{
		m_TextureManager->Shutdown();
		delete m_TextureManager;
		m_TextureManager = 0;
	}

	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = NULL;
	}

	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = NULL;
	}

	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = NULL;
	}

	return;
}

bool ApplicationClass::Frame()
{
	bool result;

	m_Fps->Frame();
	m_Timer->Frame();

	result = m_Input->Frame();
	if (!result)
		return false;

	if (m_Input->IsEscapePressed() == true)
		return false;

	result = m_Zone->Frame(m_Direct3D,
		m_Input,
		m_ShaderManager,
		m_TextureManager,
		m_Timer->GetTime(),
		m_Fps->GetFps());
	
	if (!result)
		return false;

	return result;
}