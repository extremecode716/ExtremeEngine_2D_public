#pragma once

#define _XM_NO_INTRINSICS_

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

// Texture 
#include "..\External\DirectXTex.h"
#pragma comment(lib, "DirectXTex")

// Font
#include "..\External\FontEngine\FW1CompileSettings.h"
#include "..\External\FontEngine\FW1FontWrapper.h"

// STL
#include <typeinfo>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

#include "define.h"
#include "func.h"
#include "struct.h"

extern tTransform g_Transform;
extern UINT g_SPRegister[(UINT)SHADER_PARAM::SP_END];
extern wchar_t* g_SPName[(UINT)SHADER_PARAM::SP_END];
