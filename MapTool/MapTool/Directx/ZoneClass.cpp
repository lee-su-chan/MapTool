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
	m_PosX = 0;
	m_PosY = 0;
	m_PosZ = 0;
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
	const MyStruct::TERRAIN_DESC &terrainDesc)
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
	m_Light->SetDirection(0.5f, -1.0f, -0.5f);

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

	result = m_Terrain->Initialize(direct3D->GetDevice(), terrainDesc);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);

		return false;
	}
	
	m_Position = new PositionClass;
	if (!m_Position)
		return false;
	
	m_Terrain->GetTerrainCellObj()->GetEdgePosition(m_PosX, m_PosY, m_PosZ);

	m_Position->SetPosition(m_PosX, m_PosY + 5.0f, m_PosZ);
	m_Position->SetRotation(36.0f, 136.0f, 0.0f);
	
	m_IsDisplayUI		= true;
	m_IsWireFrame		= false;
	m_IsPlay			= false;
	m_IsCellLines		= true;
	m_IsHeightLocked	= false;

	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;

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
	int fps,
	const MyStruct::TERRAIN_DESC &terrainDesc)
{
	bool result, foundHeight;
	float posX, posY, posZ, rotX, rotY, rotZ, height;
	int mousePosX, mousePosY;

	HandleMovementInput(direct3D, input, frameTime);

	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	input->GetMouseWindowPosition(mousePosX, mousePosY);

	if(m_IsPlay)
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
	
	if (m_IsHeightLocked)
	{
		foundHeight = m_Terrain->GetHeightAtPosition(posX, posZ, height);
		if (foundHeight)
		{
			m_Position->SetPosition(posX, height + 1.0f, posZ);
			m_Camera->SetPosition(posX, height + 1.0f, posZ);
		}
	}

	result = Render(direct3D, shaderManager, textureManager, terrainDesc);
	if (!result)
		return false;

	return true;
}

void ZoneClass::HandleMovementInput(D3DClass *direct3D, InputClass *input, float frameTime)
{
	bool isKeyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;
	int mouseAddX, mouseAddY;
	int mouseWinX, mouseWinY;

	m_Position->SetFrameTime(frameTime);

	if (input->IsMouseLightClick())
	{
		input->GetMouseWindowPosition(mouseWinX, mouseWinY);
		m_Ray.SetRay(direct3D, m_Camera, m_ScreenWidth, m_ScreenHeight, mouseWinX, mouseWinY);
		PickingToolSingletonClass::GetInstance()->Picking(direct3D, m_Terrain, &m_Ray);
	}

	if (input->IsMouseRightClick())
	{
		isKeyDown = input->IsMouseMoved();
		input->GetMouseAddPos(mouseAddX, mouseAddY);
		m_Position->TurnByMouse(mouseAddX, mouseAddY);
	}

	isKeyDown = input->IsWPressed();
	m_Position->MoveForward(isKeyDown);

	isKeyDown = input->IsSPressed();
	m_Position->MoveBackward(isKeyDown);

	isKeyDown = input->IsAPressed();
	m_Position->MoveLeftward(isKeyDown);

	isKeyDown = input->IsDPressed();
	m_Position->MoveRightward(isKeyDown);

	isKeyDown = input->IsQPressed();
	m_Position->MoveUpward(isKeyDown);

	isKeyDown = input->IsEPressed();
	m_Position->MoveDownward(isKeyDown);

	isKeyDown = input->IsUpPressed();
	m_Position->LookUpward(isKeyDown);

	isKeyDown = input->IsLeftPressed();
	m_Position->TurnLeft(isKeyDown);

	isKeyDown = input->IsDownPressed();
	m_Position->LookDownward(isKeyDown);

	isKeyDown = input->IsRightPressed();
	m_Position->TurnRight(isKeyDown);

	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	if (input->IsF1Toggled())
		m_IsDisplayUI = !m_IsDisplayUI;

	if (input->IsF2Toggled())
		m_IsWireFrame = !m_IsWireFrame;

	if (input->IsF3Toggled())
		m_IsPlay = !m_IsPlay;

	if (input->IsF4Toggled())
		m_IsCellLines = !m_IsCellLines;

	if (input->IsF5Toggled())
		m_IsHeightLocked = !m_IsHeightLocked;

	return;
}

bool ZoneClass::Render(D3DClass *direct3D, 
	ShaderManagerClass *shaderManager,
	TextureManagerClass *textureManager,
	const MyStruct::TERRAIN_DESC &terrainDesc)
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

	if (m_IsWireFrame)
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
				textureManager->GetTexture(terrainDesc.textureCurSel),
				m_Light->GetDirection(),
				m_Light->GetDiffuseColor());
			if (!result)
				return false;

			if (m_IsCellLines)
			{
				m_Terrain->RenderCellLines(direct3D->GetDeviceContext(), i);
				result = shaderManager->RenderColorShader(direct3D->GetDeviceContext(),
					m_Terrain->GetCellLinesIndexCount(i),
					worldMatrix,
					viewMatrix,
					projectionMatrix);
				if (!result)
					return false;
			}
		}
	}

	if (m_IsWireFrame)
		direct3D->DisableWireframe();

	result = m_UserInterface->UpdateRenderCounts(direct3D->GetDeviceContext(),
		m_Terrain->GetRenderCount(),
		m_Terrain->GetCellsDrawn(),
		m_Terrain->GetCellsCulled());
	if (!result)
		return false;

	if (m_IsDisplayUI)
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
