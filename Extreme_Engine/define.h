#pragma once

#include "global.h"

#define WINSIZE_X 1600
#define WINSIZE_Y 900

#define SINGLE(Type) public:\
					static Type* GetInst()\
					{\
						static Type mgr;\
						return &mgr;\
					}\
					private:\
						Type();\
						~Type();

#define RET_FAILED -1
#define RET_SUCCESS 1

#define SAFE_RELEASE(p) if(NULL != p){ p->Release(); }
#define SAFE_DELETE(p) if(NULL != p){ delete p; p = NULL; }
#define SAFE_DELETE_ARR(p) if( NULL != p){ delete [] p; p = NULL; }

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

#define CLONE(type) virtual type* Clone(){return new type (*this);}

#define MAX_LAYER 32

#define LOWORD(_dw)     ((WORD)(((DWORD_PTR)(_dw)) & 0xffff))
#define HIWORD(_dw)     ((WORD)((((DWORD_PTR)(_dw)) >> 16) & 0xffff))
#define LODWORD(_qw)    ((DWORD)(_qw))
#define HIDWORD(_qw)    ((DWORD)(((_qw) >> 32) & 0xffffffff))

// TooL Àü¿ë
////////////////////////////
//#define _EXTREME_TOOL
//////////////////////////////

typedef XMMATRIX Matrix;
typedef XMFLOAT4 Vec4;
//typedef XMFLOAT2 Vec2;


enum class COMPONENT_TYPE
{
	TRANSFORM,
	MESHRENDER,
	COLLIDER,
	ANIMATOR,
	CAMERA,
	SCRIPT,
	END,
	COLLIDER_2D,
	COLLIDER_3D,
};

enum class SHADER_TYPE
{
	ST_VERTEX = 0x01,
	ST_HULL = 0x02,
	ST_DOMAIN = 0x04,
	ST_GEOMETRY = 0x08,
	ST_COMPUTE = 0x10,
	ST_PIXEL = 0x20,
};

enum class RASTERIZE_TYPE
{
	RT_WIREFRAME,
	RT_FRONT,
	RT_BACK,
	RT_NONE,
	RT_END,
};

enum class SHADER_PARAM
{
	SP_INT_0,
	SP_INT_1,
	SP_INT_2,
	SP_INT_3,
	SP_INT_END,
	SP_FLOAT_0,
	SP_FLOAT_1,
	SP_FLOAT_2,
	SP_FLOAT_3,
	SP_FLOAT_END,
	SP_VEC4_0,
	SP_VEC4_1,
	SP_VEC4_2,
	SP_VEC4_3,
	SP_VEC4_END,
	SP_TEX_0,
	SP_TEX_1,
	SP_TEX_2,
	SP_TEX_3,
	SP_TEX_END,
	SP_END,
};