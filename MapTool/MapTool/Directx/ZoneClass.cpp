#include "ZoneClass.h"

ZoneClass::ZoneClass()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Light = 0;
	m_Position = 0;
	m_Frustum = 0;
	m_SkyDome = 0;
	m_Terrain = 0;
	m_posX = 0;
	m_posY = 0;
	m_posZ = 0;
}

ZoneClass::ZoneClass(const ZoneClass &other)
{
}

ZoneClass::~ZoneClass()
{
}

bool ZoneClass::Initialize(D3DClass *direct3D, 
	HWND hwnd, 
	int screenWidth, 
	int screenHeight, 
	float screenDepth,
	TERRAIN_DESC *terrainDesc)
{
	bool result;

	m_UserInterface = new UserInterfaceClass;
	if (!m_UserInterface)
		return false;

	result = m_UserInterface->Initialize(direct3D, screenHeight, screenWidth);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the user interface object.", L"Error", MB_OK);
		
		return false;
	}

	m_Camera = new CameraClass;
	if (!m_Camera)
		return false;

	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();

	m_Light = new LightClass;
	if (!m_Light)
		return false;

	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-0.5f, -1.0f, -0.5f);

	m_Frustum = new FrustumClass;
	if (!m_Frustum)
		return false;

	m_Frustum->Initialize(screenDepth);

	m_SkyDome = new SkyDomeClass;
	if (!m_SkyDome)
		return false;

	result = m_SkyDome->Initialize(direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);

		return false;
	}

	m_Terrain = new TerrainClass;
	if (!m_Terrain)
		return false;

	result = m_Terrain->Initialize(direct3D->GetDevice(), "Data/Setup.txt", terrainDesc);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);

		return false;
	}
	
	m_Position = new PositionClass;
	if (!m_Position)
		return false;
	
	m_Terrain->GetTerrainCellObj()->GetEdgePosition(m_posX, m_posY, m_posZ);

	m_Position->SetPosition(m_posX, m_posY + 5.0f, m_posZ);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);
	
	m_displayUI		= true;
	m_wireFrame		= false;
	m_play			= false;
	m_cellLines		= true;
	m_heightLocked	= false;

	return true;
}

void ZoneClass::Shutdown()
{
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = NULL;
	}

	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = NULL;
	}

	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = NULL;
	}

	if (m_Position)
	{
		delete m_Position;
		m_Position = NULL;
	}

	if (m_Light)
	{
		delete m_Light;
		m_Light = NULL;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = NULL;
	}

	if (m_UserInterface)
	{
		m_UserInterface->Shutdown();
		delete m_UserInterface;
		m_UserInterface = NULL;
	}

	return;
}

bool ZoneClass::Frame(D3DClass *direct3D, 
	InputClass *input,
	ShaderManagerClass *shaderManager, 
	TextureManagerClass *textureManager,
	float frameTime,
	int fps)
{
	bool result, foundHeight;
	float posX, posY, posZ, rotX, rotY, rotZ, height;
	int mousePosX, mousePosY;

	HandleMovementInput(input, frameTime);

	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	input->GetMouseLocation(mousePosX, mousePosY);

	if(m_play)
		PushedF3Button(frameTime);
	
	result = m_UserInterface->Frame(direct3D->GetDeviceContext(),
		fps,
		posX,
		posY,
		posZ,
		rotX,
		rotY,
		rotZ,
		m_SkyDome->GetApexColor(),
		m_SkyDome->GetCenterColor(),
		mousePosX,
		mousePosY);
	
	if (!result)
		return false;

	m_Terrain->Frame();

	if (m_heightLocked)
	{
		foundHeight = m_Terrain->GetHeightAtPosition(posX, posZ, height);
		if (foundHeight)
		{
			m_Position->SetPosition(posX, height + 1.0f, posZ);
			m_Camera->SetPosition(posX, height + 1.0f, posZ);
		}
	}

	result = Render(direct3D, shaderManager, textureManager);
	if (!result)
		return false;

	return true;
}

void ZoneClass::HandleMovementInput(InputClass *input, float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;
	int mouseAddX, mouseAddY;

	m_Position->SetFrameTime(frameTime);

	if (input->IsMouseRightClick())
	{
		keyDown = input->IsMouseMoved();
		input->GetMouseAddPos(mouseAddX, mouseAddY);
		m_Position->TurnByMouse(mouseAddX, mouseAddY);
	}

	keyDown = input->IsWPressed();
	m_Position->MoveForward(keyDown);

	keyDown = input->IsSPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = input->IsAPressed();
	m_Position->MoveLeftward(keyDown);

	keyDown = input->IsDPressed();
	m_Position->MoveRightward(keyDown);

	keyDown = input->IsQPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = input->IsEPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = input->IsUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = input->IsDownPressed();
	m_Position->LookDownward(keyDown);

	keyDown = input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	if (input->IsF1Toggled())
		m_displayUI = !m_displayUI;

	if (input->IsF2Toggled())
		m_wireFrame = !m_wireFrame;

	if (input->IsF3Toggled())
		m_play = !m_play;

	if (input->IsF4Toggled())
		m_cellLines = !m_cellLines;

	if (input->IsF5Toggled())
		m_heightLocked = !m_heightLocked;

	return;
}

bool ZoneClass::Render(D3DClass *direct3D, 
	ShaderManagerClass *shaderManager,
	TextureManagerClass *textureManager)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;
	bool result;
	XMFLOAT3 cameraPosition;
	int i;

	m_Camera->Render();

	direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	direct3D->GetProjectionMatrix(projectionMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	direct3D->GetOrthoMatrix(orthoMatrix);

	cameraPosition = m_Camera->GetPosition();

	m_Frustum->ConstructFrustum(projectionMatrix, viewMatrix);

	direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	direct3D->TurnOffCulling();
	direct3D->TurnZBufferOff();

	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	m_SkyDome->Render(direct3D->GetDeviceContext());
	
	result = shaderManager->RenderSkyDomeShader(direct3D->GetDeviceContext(),
		m_SkyDome->GetIndexCount(),
		worldMatrix,
		viewMatrix,
		projectionMatrix,
		m_SkyDome->GetApexColor(),
		m_SkyDome->GetCenterColor());

	if (!result)
		return false;

	direct3D->GetWorldMatrix(worldMatrix);
	
	direct3D->TurnZBufferOn();
	direct3D->TurnOnCulling();

	if (m_wireFrame)
		direct3D->EnableWireframe();

	for (i = 0; i < m_Terrain->GetCellCount(); ++i)
	{
		result = m_Terrain->RenderCell(direct3D->GetDeviceContext(), i, m_Frustum);
		if (result)
		{			
			result = shaderManager->RenderLightShader(direct3D->GetDeviceContext(),
				m_Terrain->GetCellIndexCount(i),
				worldMatrix,
				viewMatrix,
				projectionMatrix,
				textureManager->GetTexture(0),
				m_Light->GetDirection(),
				m_Light->GetDiffuseColor());

			if (!result)
				return false;

			if (m_cellLines)
			{
				m_Terrain->RenderCellLines(direct3D->GetDeviceContext(), i);
				shaderManager->RenderColorShader(direct3D->GetDeviceContext(),
					m_Terrain->GetCellLinesIndexCount(i),
					worldMatrix,
					viewMatrix,
					projectionMatrix);

				if (!result)
					return false;
			}
		}
	}

	if (m_wireFrame)
		direct3D->DisableWireframe();

	result = m_UserInterface->UpdateRenderCounts(direct3D->GetDeviceContext(),
		m_Terrain->GetRenderCount(),
		m_Terrain->GetCellsDrawn(),
		m_Terrain->GetCellsCulled());

	if (!result)
		return false;

	if (m_displayUI)
	{
		result = m_UserInterface->Render(direct3D,
			shaderManager,
			worldMatrix,
			baseViewMatrix,
			orthoMatrix);	

		if (!result)
			return false;
	}

	direct3D->EndScene();

	return true;
}

// 0 - 257 : 129
void ZoneClass::PushedF3Button(float frameTime)
{
	XMFLOAT3 dir;
	
	dir = m_Light->GetDirection();
	
	if (dir.x >= 360) dir.x -= 360;
	if (dir.y >= 360) dir.y -= 360;
	if (dir.z >= 360) dir.z -= 360;
	
	dir.z -= frameTime / 5;
	
	m_Light->SetDirection(dir.x, dir.y, dir.z);

	//XMFLOAT4 tempColor;
	//
	//tempColor = m_SkyDome->GetApexColor();
	//
	//tempColor.x -= frameTime / 5; // R
	//tempColor.y -= frameTime / 5; // G
	//tempColor.z -= frameTime / 5; // B
	//
	//m_SkyDome->SetApexColor(tempColor);

	return;
}
