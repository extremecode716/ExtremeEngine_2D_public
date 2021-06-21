#pragma once

#include "global.h"

// Vec3
struct Vec3 : XMFLOAT3
{
	Vec3()
		: XMFLOAT3(0.f, 0.f, 0.f)
	{}

	Vec3(FXMVECTOR _xmvec)
		: XMFLOAT3(0.f, 0.f, 0.f)
	{
		XMStoreFloat3(this, _xmvec);
	}

	Vec3(float _x, float _y, float _z)
		: XMFLOAT3(_x, _y, _z)
	{}

	XMVECTOR Convert()
	{
		return XMLoadFloat3((XMFLOAT3*)this);
	}

	float Distance()
	{
		return sqrt(x * x + y * y + z * z);
	}

	void Normalize()
	{
		float fDist = Distance();

		if (fDist == 0.f)
			return;

		x /= fDist;
		y /= fDist;
		z /= fDist;
	}

	float Dot(const Vec3& _vOther)
	{
		return (x * _vOther.x) + (y * _vOther.y) + (z * _vOther.z);
	}

	Vec3 Cross(const Vec3& _vOther)
	{
		return Vec3(y * _vOther.z - z * _vOther.y, z * _vOther.x - x * _vOther.z, x * _vOther.y - y * _vOther.x);
	}

	Vec3 rotateX(float _fDegree)
	{
		float fTheta = _fDegree / 180.f * XM_PI;
		return Vec3(x, cos(fTheta) * y + sin(fTheta) * z, cos(fTheta) * z - sin(fTheta) * y);
	}

	Vec3 rotateY(float _fDegree)
	{
		float fTheta = _fDegree / 180.f * XM_PI;
		return Vec3(cos(fTheta) * x + sin(fTheta) * z,  y,  cos(fTheta) * z - sin(fTheta) * x);
	}

	const Vec3& operator = (FXMVECTOR _xmvec)
	{
		XMStoreFloat3(this, _xmvec);
		return (*this);
	}

	float& operator[](int _iIdx)
	{
		switch (_iIdx)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			assert(NULL);
		}
		// temp
		return z;
	}

	const Vec3 operator + (FXMVECTOR _other)
	{
		Vec3 vRet(x + _other.vector4_f32[0], y + _other.vector4_f32[1], z + _other.vector4_f32[2]);
		return vRet;
	}

	const Vec3 operator - (FXMVECTOR _other)
	{
		Vec3 vRet(x - _other.vector4_f32[0], y - _other.vector4_f32[1], z - _other.vector4_f32[2]);
		return vRet;
	}

	const Vec3 operator * (FXMVECTOR _other)
	{
		Vec3 vRet(x * _other.vector4_f32[0], y * _other.vector4_f32[1], z * _other.vector4_f32[2]);
		return vRet;
	}

	const Vec3 operator / (FXMVECTOR _other)
	{
		Vec3 vRet(_other.vector4_f32[0] == 0.f ? 0.f : x / _other.vector4_f32[0]
			, _other.vector4_f32[1] == 0.f ? 0.f : y / _other.vector4_f32[1]
			, _other.vector4_f32[2] == 0.f ? 0.f : z / _other.vector4_f32[2]);

		return vRet;
	}

	const Vec3 operator + (const Vec3& _other)
	{
		Vec3 vRet(x + _other.x, y + _other.y, z + _other.z);
		return vRet;
	}

	const Vec3 operator - (const Vec3& _other)
	{
		Vec3 vRet(x - _other.x, y - _other.y, z - _other.z);
		return vRet;
	}

	const Vec3 operator * (const Vec3& _other)
	{
		Vec3 vRet(x * _other.x, y * _other.y, z * _other.z);
		return vRet;
	}

	const Vec3 operator / (const Vec3& _other)
	{
		Vec3 vRet(_other.x == 0.f ? 0.f : x / _other.x
			, _other.y == 0.f ? 0.f : y / _other.y
			, _other.z == 0.f ? 0.f : z / _other.z);

		return vRet;
	}

	const Vec3& operator += (const Vec3& _other)
	{
		x += _other.x;
		y += _other.y;
		z += _other.z;
		return (*this);
	}

	const Vec3& operator *= (const Vec3& _other)
	{
		x *= _other.x;
		y *= _other.y;
		z *= _other.z;
		return (*this);
	}

	const Vec3& operator -= (const Vec3& _other)
	{
		x -= _other.x;
		y -= _other.y;
		z -= _other.z;
		return (*this);
	}

	const Vec3& operator /= (const Vec3& _other)
	{
		_other.x == 0.f ? x = 0.f : x /= _other.x;
		_other.y == 0.f ? y = 0.f : y /= _other.y;
		_other.z == 0.f ? z = 0.f : z /= _other.z;

		return (*this);
	}

	// 허용오차 범위
	bool operator == (const Vec3& _other)
	{
		float fTolerance = 0.000001f;
		if (fabsf(x - _other.x) <= fTolerance)
			if (fabsf(y - _other.y) <= fTolerance)
				if (fabsf(z - _other.z) <= fTolerance)
					return true;

		return false;
	}
};

// Vec2
struct Vec2 : XMFLOAT2
{
	Vec2()
		: XMFLOAT2(0.f, 0.f)
	{}

	Vec2(FXMVECTOR _xmvec)
		: XMFLOAT2(0.f, 0.f)
	{
		XMStoreFloat2(this, _xmvec);
	}

	Vec2(float _x, float _y)
		: XMFLOAT2(_x, _y)
	{}

	XMVECTOR Convert()
	{
		return XMLoadFloat2((XMFLOAT2*)this);
	}

	float Distance()
	{
		return sqrt(x * x + y * y);
	}

	const Vec2& Normalize()
	{
		float fDist = Distance();

		if (fDist == 0.f)
			return *this;

		x /= fDist;
		y /= fDist;
		
		return (*this);
	}

	float Dot(const Vec2& _vOther)
	{
		return (x * _vOther.x) + (y * _vOther.y);
	}

	float Cross(const Vec2& _vOther)
	{
		return (x * _vOther.y) - (y * _vOther.x);
	}

	void rotate(float _fDegree)
	{
		float fTheta = _fDegree / 180.f * XM_PI;
		float fC = cos(fTheta);
		float fS = sin(fTheta);
		float fTx = x * fC - y * fS;
		float fTy = x * fS + y * fC;
		x = fTx;
		y = fTy;
	}

	float Angle()
	{
		float fAngle = atan2f(y, x) * 180.f / XM_PI;

		//fAngle = (fAngle >= 0) ? fAngle : fAngle + 360.f;
		return fAngle;
	}

	void truncate(float _fLength)
	{
		float fTheta = atan2f(y, x);
		x = _fLength * cos(fTheta);
		y = _fLength * sin(fTheta);
	}

	Vec2 ortho() const
	{
		return Vec2(y, -x);
	}

	const Vec2& operator = (FXMVECTOR _xmvec)
	{
		XMStoreFloat2(this, _xmvec);
		return (*this);
	}

	float& operator[](int _iIdx)
	{
		switch (_iIdx)
		{
		case 0:
			return x;
		case 1:
			return y;
		default:
			assert(NULL);
		}

		// temp
		return y; 
	}

	const Vec2 operator + (FXMVECTOR _other)
	{
		Vec2 vRet(x + _other.vector4_f32[0], y + _other.vector4_f32[1]);
		return vRet;
	}

	const Vec2 operator - (FXMVECTOR _other)
	{
		Vec2 vRet(x - _other.vector4_f32[0], y - _other.vector4_f32[1]);
		return vRet;
	}

	const Vec2 operator * (FXMVECTOR _other)
	{
		Vec2 vRet(x * _other.vector4_f32[0], y * _other.vector4_f32[1]);
		return vRet;
	}

	const Vec2 operator / (FXMVECTOR _other)
	{
		Vec2 vRet(_other.vector4_f32[0] == 0.f ? 0.f : x / _other.vector4_f32[0]
			, _other.vector4_f32[1] == 0.f ? 0.f : y / _other.vector4_f32[1]);

		return vRet;
	}

	const Vec2 operator + (const Vec2& _other)
	{
		Vec2 vRet(x + _other.x, y + _other.y);
		return vRet;
	}

	const Vec2 operator - (const Vec2& _other)
	{
		Vec2 vRet(x - _other.x, y - _other.y);
		return vRet;
	}

	const Vec2 operator * (const Vec2& _other)
	{
		Vec2 vRet(x * _other.x, y * _other.y);
		return vRet;
	}

	const Vec2 operator / (const Vec2& _other)
	{
		Vec2 vRet(_other.x == 0.f ? 0.f : x / _other.x
			, _other.y == 0.f ? 0.f : y / _other.y);

		return vRet;
	}

	const Vec2 operator / (float _other)
	{
		Vec2 vRet(_other == 0.f ? 0.f : x / _other
			, _other == 0.f ? 0.f : y / _other);

		return vRet;
	}

	const Vec2& operator += (const Vec2& _other)
	{
		x += _other.x;
		y += _other.y;
		return (*this);
	}

	const Vec2& operator *= (const Vec2& _other)
	{
		x *= _other.x;
		y *= _other.y;
		return (*this);
	}

	const Vec2& operator -= (const Vec2& _other)
	{
		x -= _other.x;
		y -= _other.y;
		return (*this);
	}

	const Vec2& operator /= (const Vec2& _other)
	{
		_other.x == 0.f ? x = 0.f : x /= _other.x;
		_other.y == 0.f ? y = 0.f : y /= _other.y;

		return (*this);
	}

	// 허용오차 범위
	bool operator == (const Vec2& _other)
	{
		float fTolerance = 0.000001f;
		if (fabsf(x - _other.x) <= fTolerance)
			if (fabsf(y - _other.y) <= fTolerance)
				return true;

		return false;
	}
};

typedef struct _tagVTX
{
	Vec3 vPos;
	Vec2 vUV;
	Vec4 vColor;
}VTX;

typedef struct _tagIndex16
{
	WORD	_1, _2, _3;
	_tagIndex16()
		: _1(0), _2(0), _3(0)
	{}
	_tagIndex16(WORD __1, WORD __2, WORD __3)
		: _1(__1), _2(__2), _3(__3)
	{}

	static UINT size() { return sizeof(WORD); }
	static DXGI_FORMAT format() { return DXGI_FORMAT_R16_UINT; }
}INDEX16;

typedef struct _tagIndex32
{
	DWORD	_1, _2, _3;
	_tagIndex32()
		: _1(0), _2(0), _3(0)
	{}
	_tagIndex32(DWORD __1, DWORD __2, DWORD __3)
		: _1(__1), _2(__2), _3(__3)
	{}
	static UINT size() { return sizeof(DWORD); }
	static DXGI_FORMAT format() { return DXGI_FORMAT_R32_UINT; }
}INDEX32;

struct CBUFFER
{
	ID3D11Buffer*	pBuffer;
	UINT			iRegister;
	UINT			iSize;
};

struct tShaderParam
{
	SHADER_PARAM eShaderParam;
	UINT		 iRegister;
	UINT		 iTiming;
};

//==========
// 상수 버퍼
//==========
typedef struct _tagTransform
{
	XMMATRIX	matWorld;
	XMMATRIX	matView;
	XMMATRIX	matProj;
}tTransform;

///////////////////////////
// 애니메이션_2D 상수 버퍼
//////////////////////////
struct tAnimInfo
{
	Vec4 vUV;
	Vec4 vAnim;
};

///////////////////////
// 텍스트 정보
///////////////////////
typedef struct _tDrawStringInfo
{
	wstring strKey;
	bool	bShow;
	wstring strText;
	float	fFontSize;
	float	fPositionX;
	float	fPositionY;
	UINT32	iColor;

	_tDrawStringInfo() {};
	_tDrawStringInfo(const wstring& _strKey, bool _bShow, const wstring& _strText, float _fFontSize, float _fPositionX, float _fPositionY, UINT32 _iColor)
		: strKey(_strKey), bShow(_bShow), strText(_strText), fFontSize(_fFontSize), fPositionX(_fPositionX), fPositionY(_fPositionY), iColor(_iColor)
	{}

	void SetDrawInfo(const wstring& _strKey, bool _bShow, const wstring& _strText, float _fFontSize, float _fPositionX, float _fPositionY, UINT32 _iColor)
	{
		strKey = _strKey;
		bShow = _bShow;
		strText = _strText;
		fFontSize = _fFontSize;
		fPositionX = _fPositionX;
		fPositionY = _fPositionY;
		iColor = _iColor;
	}
	const wstring& GetKey() { return strKey; }

	void SetShow(bool _bShow) { bShow = _bShow; }
	void SetFontSize(float _fSize) { fFontSize = _fSize; }
	void SetPos(const Vec2& _vPos) { 
		fPositionX = (_vPos.x + WINSIZE_X / 2.f);
		fPositionY = -(_vPos.y - WINSIZE_Y / 2.f);
	}
	void SetPos(const Vec2& _vPos, const Vec2& _vCameraPos)
	{
		fPositionX = (_vPos.x - (_vCameraPos.x - WINSIZE_X / 2.f));
		fPositionY = -(_vPos.y - (_vCameraPos.y + WINSIZE_Y / 2.f));
	}
	void SetColor(UINT32 _iColor) { iColor = _iColor; }

}tDrawStringInfo;