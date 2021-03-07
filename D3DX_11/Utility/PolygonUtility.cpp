#include "stdafx.h"
#include "PolygonUtility.h"

Mesh * PolygonUtility::CreateBox(DirectX::XMFLOAT3 scale)
{
	DirectX::XMFLOAT3 value = DirectX::XMFLOAT3(scale.x, scale.y, scale.z);

	MeshValue::VertexValue v[24];

	// Fill in the front face vertex data.
	v[0] = MeshValue::VertexValue(-value.x, -value.y, -value.z, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = MeshValue::VertexValue(-value.x, +value.y, -value.z, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = MeshValue::VertexValue(+value.x, +value.y, -value.z, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[3] = MeshValue::VertexValue(+value.x, -value.y, -value.z, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	v[4] = MeshValue::VertexValue(-value.x, -value.y, +value.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	v[5] = MeshValue::VertexValue(+value.x, -value.y, +value.z, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[6] = MeshValue::VertexValue(+value.x, +value.y, +value.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[7] = MeshValue::VertexValue(-value.x, +value.y, +value.z, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	v[8]  = MeshValue::VertexValue(-value.x, +value.y, -value.z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	v[9]  = MeshValue::VertexValue(-value.x, +value.y, +value.z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[10] = MeshValue::VertexValue(+value.x, +value.y, +value.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	v[11] = MeshValue::VertexValue(+value.x, +value.y, -value.z, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	v[12] = MeshValue::VertexValue(-value.x, -value.y, -value.z, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	v[13] = MeshValue::VertexValue(+value.x, -value.y, -value.z, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	v[14] = MeshValue::VertexValue(+value.x, -value.y, +value.z, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	v[15] = MeshValue::VertexValue(-value.x, -value.y, +value.z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	v[16] = MeshValue::VertexValue(-value.x, -value.y, +value.z, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[17] = MeshValue::VertexValue(-value.x, +value.y, +value.z, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[18] = MeshValue::VertexValue(-value.x, +value.y, -value.z, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[19] = MeshValue::VertexValue(-value.x, -value.y, -value.z, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	v[20] = MeshValue::VertexValue(+value.x, -value.y, -value.z, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[21] = MeshValue::VertexValue(+value.x, +value.y, -value.z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[22] = MeshValue::VertexValue(+value.x, +value.y, +value.z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[23] = MeshValue::VertexValue(+value.x, -value.y, +value.z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Create the indices.
	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	return new Mesh(MeshValue(v, 24, i, 36));
}
