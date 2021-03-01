#include "MeshUtility.h"
#include "stdafx.h"

Mesh* MeshUtility::CreateBox(DirectX::XMFLOAT3 scale)
{
	DirectX::XMFLOAT3 v = DirectX::XMFLOAT3(scale.x, scale.y, scale.z);

	std::vector<MeshValue::VertexValue> vertices = std::vector<MeshValue::VertexValue>(8);
	vertices[0] = MeshValue::VertexValue(DirectX::XMFLOAT3(-scale.x, -scale.y, -scale.z), DirectX::XMFLOAT3(0, 1, 0), DirectX::XMFLOAT2());
	vertices[1] = MeshValue::VertexValue(DirectX::XMFLOAT3(-scale.x, +scale.y, -scale.z), DirectX::XMFLOAT3(0, 1, 0), DirectX::XMFLOAT2());
	vertices[2] = MeshValue::VertexValue(DirectX::XMFLOAT3(+scale.x, +scale.y, -scale.z), DirectX::XMFLOAT3(0, 1, 0), DirectX::XMFLOAT2());
	vertices[3] = MeshValue::VertexValue(DirectX::XMFLOAT3(+scale.x, -scale.y, -scale.z), DirectX::XMFLOAT3(0, 1, 0), DirectX::XMFLOAT2());
	vertices[4] = MeshValue::VertexValue(DirectX::XMFLOAT3(-scale.x, -scale.y, +scale.z), DirectX::XMFLOAT3(0, 1, 0), DirectX::XMFLOAT2());
	vertices[5] = MeshValue::VertexValue(DirectX::XMFLOAT3(-scale.x, +scale.y, +scale.z), DirectX::XMFLOAT3(0, 1, 0), DirectX::XMFLOAT2());
	vertices[6] = MeshValue::VertexValue(DirectX::XMFLOAT3(+scale.x, +scale.y, +scale.z), DirectX::XMFLOAT3(0, 1, 0), DirectX::XMFLOAT2());
	vertices[7] = MeshValue::VertexValue(DirectX::XMFLOAT3(+scale.x, -scale.y, +scale.z), DirectX::XMFLOAT3(0, 1, 0), DirectX::XMFLOAT2());

	std::vector<UINT> i = std::vector<UINT>(36);

	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	i[6] = 4; i[7] = 6;	i[8] = 5;
	i[9] = 4; i[10] = 7; i[11] = 6;

	i[12] = 4; i[13] = 5; i[14] = 1;
	i[15] = 4; i[16] = 1; i[17] = 0;

	i[18] = 3; i[19] = 2; i[20] = 6;
	i[21] = 3; i[22] = 6; i[23] = 7;

	i[24] = 1; i[25] = 5; i[26] = 6;
	i[27] = 1; i[28] = 6; i[29] = 2;

	i[30] = 4; i[31] = 0; i[32] = 3;
	i[33] = 4; i[34] = 3; i[35] = 7;

	return new Mesh(MeshValue(vertices, i));
}
