#pragma once
#include "stdafx.h"
#include "System/Renderer/DXRenderer.h"

#include "_Components/Base/Component.h"

template <typename IType>
__interface IRenderer
{
	void Release() = 0;

	HRESULT ChangeVariable(ID3D11Device* device, const IType& type) = 0;
	HRESULT IASet(ID3D11Device* device) = 0;
};