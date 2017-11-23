#include "PickingToolClass.h"

void PickingToolClass::InitPick(D3DClass *direct3D, 
	CameraClass *camera,
	int screenWidth, 
	int screenHeight, 
	int mousePosX,
	int mousePosY)
{
	m_Ray.SetRay(direct3D, camera, screenWidth, screenHeight, mousePosX, mousePosY);
}

void PickingToolClass::Picking(D3DClass *direct3D, TerrainClass *terrain, XMVECTOR &pickPos)
{	
	const int nCell = terrain->GetCellCount();
	int pickVertex = -1;
	XMVECTOR v0, v1, v2;

	for (int cellIndex = 0; cellIndex < nCell; ++cellIndex)
	{
		const int nVertexDividedByThree = terrain->GetTerrainCellObj()[cellIndex].GetVertexCount() / 3;
		XMFLOAT3 *tempVertexList;
		float minDist = INT_MAX;

		pickVertex = -1;
		tempVertexList = &(terrain->GetTerrainCellObj()[cellIndex].m_vertexList->position);

		for (int i = 0; i < nVertexDividedByThree; ++i)
		{
			v0 = XMLoadFloat3(&tempVertexList[i * 3 + 0]);
			v1 = XMLoadFloat3(&tempVertexList[i * 3 + 1]);
			v2 = XMLoadFloat3(&tempVertexList[i * 3 + 2]);

			float currentDist = 0.0f;
			bool result = DirectX::TriangleTests::Intersects(m_Ray.GetOriginal(),
				m_Ray.GetDirection(),
				v0, v1, v2,
				currentDist);
			if (result)
			{
				if (currentDist < minDist)
				{
					minDist = currentDist;
					pickVertex = i * 3;
					pickPos = m_Ray.GetOriginal() + m_Ray.GetDirection() * minDist;
				}
			}
		}

		if (pickVertex != -1)
		{
			terrain->GetTerrainCellObj()[cellIndex].m_vertexList[pickVertex + 0].position.y += 1.0f;
			terrain->GetTerrainCellObj()[cellIndex].m_vertexList[pickVertex + 1].position.y += 1.0f;
			terrain->GetTerrainCellObj()[cellIndex].m_vertexList[pickVertex + 2].position.y += 1.0f;
			terrain->GetTerrainCellObj()[cellIndex].TranslateVertex(direct3D->GetDeviceContext());
		}
	}
}

//bool PickingToolClass::IsCursorInWindow(HWND hwnd)
//{
//	POINT cursor;
//	RECT rc;
//
//	// InitPick함수 파라미터로 받은 커서 포지션 값은 DirectXViewHwnd 기준이기 때문에
//	// 못쓰고, 전체 화면에서의 포지션 값으로 받아와야 함.
//	GetCursorPos(&cursor);
//	GetWindowRect(hwnd, &rc);
//	if ((rc.left   > cursor.x || rc.right < cursor.x) ||
//		(rc.bottom < cursor.y || rc.top   > cursor.y))
//		return false;
//
//	return true;
//}