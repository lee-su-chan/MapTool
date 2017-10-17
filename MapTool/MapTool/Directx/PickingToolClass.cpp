#include "PickingToolClass.h"

bool PickingToolClass::InitPick(D3DClass *direct3D, 
	CameraClass *camera, 
	HWND hwnd, 
	int screenWidth, 
	int screenHeight, 
	int cursorX, 
	int cursorY)
{
	bool result;

	result = IsCursorInWindow(hwnd);
	if (!result)
		return false;

	m_Ray.SetRay(direct3D, camera, hwnd, screenWidth, screenHeight, cursorX, cursorY);

	return true;
}

void PickingToolClass::Picking(D3DClass *direct3D, TerrainClass *terrain, XMVECTOR &pickPos)
{	
	int pickVertex = -1;
	XMVECTOR v0, v1, v2;

	for (int cellIndex = 0; cellIndex < terrain->GetCellCount(); ++cellIndex)
	{
		const int nVertex = terrain->GetTerrainCellObj()[cellIndex].GetVertexCount();
		XMFLOAT3 *tempVertexList = new XMFLOAT3[nVertex];
		float minDist = INT_MAX;

		pickVertex = -1;

		for (int i = 0; i < nVertex; ++i)
		{
			tempVertexList[i].x = terrain->GetTerrainCellObj()[cellIndex].m_vertexList[i].position.x;
			tempVertexList[i].y = terrain->GetTerrainCellObj()[cellIndex].m_vertexList[i].position.y;
			tempVertexList[i].z = terrain->GetTerrainCellObj()[cellIndex].m_vertexList[i].position.z;
		}
		for (int i = 0; i < nVertex / 3; ++i)
		{
			v0 = XMLoadFloat3(&tempVertexList[i * 3 + 0]);
			v1 = XMLoadFloat3(&tempVertexList[i * 3 + 1]);
			v2 = XMLoadFloat3(&tempVertexList[i * 3 + 2]);

			float currentDist = 0.0f;
			if (DirectX::TriangleTests::Intersects(m_Ray.GetOriginal(),
				m_Ray.GetDirection(),
				v0, v1, v2,
				currentDist))
			{
				if (currentDist < minDist)
				{
					minDist = currentDist;
					pickVertex = i * 3;
					pickPos = m_Ray.GetOriginal() + m_Ray.GetDirection() * minDist;
				}

				// TODO: 마우스 포인터에 따른 원 그리기

			}
		}

		if (pickVertex != -1)
		{
			terrain->GetTerrainCellObj()[cellIndex].m_vertexList[pickVertex + 0].position.y += 0.016f;
			terrain->GetTerrainCellObj()[cellIndex].m_vertexList[pickVertex + 1].position.y += 0.016f;
			terrain->GetTerrainCellObj()[cellIndex].m_vertexList[pickVertex + 2].position.y += 0.016f;
			terrain->GetTerrainCellObj()[cellIndex].TranslateVertex(direct3D->GetDeviceContext());
		}
	}
}

void PickingToolClass::RenderPickingCircle(ID3D11DeviceContext *deviceContext)
{
}

bool PickingToolClass::IsCursorInWindow(HWND hwnd)
{
	POINT cursor;
	RECT rc;

	// InitPick함수 파라미터로 받은 커서 포지션 값은 DirectXViewHwnd 기준이기 때문에
	// 못쓰고, 전체 화면에서의 포지션 값으로 받아와야 함.
	GetCursorPos(&cursor);
	GetWindowRect(hwnd, &rc);
	if ((rc.left   > cursor.x || rc.right < cursor.x) ||
		(rc.bottom < cursor.y || rc.top   > cursor.y))
	{
		return false;
	}

	return true;
}