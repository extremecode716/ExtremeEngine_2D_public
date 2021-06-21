#include "value.fx"


struct PS_OUTPUT
{
    float4 vCol : SV_Target;
};


//====================
// Vertex Color Shader
//====================
struct VS_COL_INPUT
{
    float3 vPos : POSITION;
    float4 vCol : COLOR;
};

struct VS_COL_OUTPUT
{
    float4 vPos : SV_POSITION;
    float4 vCol : COLOR;
};

VS_COL_OUTPUT VS_Color(VS_COL_INPUT _input)
{
    VS_COL_OUTPUT output = (VS_COL_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);

    output.vPos = vProjPos;
    output.vCol = _input.vCol;

    return output;
}


PS_OUTPUT PS_Color(VS_COL_OUTPUT _input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0.f;
    output.vCol = _input.vCol;
    return output;
}

//================
// Texture Shader
// g_tex_0
// g_float_0     : alpha
//================

struct VS_TEX_INPUT
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_TEX_OUTPUT
{
    float4 vPos : SV_POSITION;
    float2 vUV : TEXCOORD;
};

VS_TEX_OUTPUT VS_Tex(VS_TEX_INPUT _input)
{
    VS_TEX_OUTPUT output = (VS_TEX_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);

    output.vPos = vProjPos;
    output.vUV = _input.vUV;

    return output;
}

PS_OUTPUT PS_Tex(VS_TEX_OUTPUT _input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0.f;

    float4 vCol = g_tex_0.Sample(g_default_sam, _input.vUV);

    float fAlph = (g_float_0 / 100.f);
    //fAlph = (fAlph > 1.0f) ? 1.0f : fAlph;

    vCol.a = vCol.a - fAlph;

    if (vCol.a <= 0.f)
        clip(-1);

    output.vCol = vCol;
    return output;
}

//================
// Collider Shader
// g_int_0
//================
struct VS_COLLIDER_OUTPUT
{
    float4 vPos : SV_POSITION;
};

VS_COLLIDER_OUTPUT VS_Collider(float3 vPos : POSITION)
{
    VS_COLLIDER_OUTPUT output = (VS_COLLIDER_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);

    output.vPos = vProjPos;

    return output;
}

PS_OUTPUT PS_Collider(VS_COLLIDER_OUTPUT _input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0.f;

    if (g_int_0)
    {
        output.vCol = float4(1.f, 0.f, 0.f, 1.f);
    }
    else
    {
        output.vCol = float4(0.f, 1.f, 0.f, 1.f);
    }

    return output;
}



//===================
// Split 2D Shader
// g_tex_0 : Texture
// g_vec4_0 : xy(uv) z(width) w(height)
// g_int_0  : Color change on/off (1 : on / 0 : off) 
// g_vec4_1 : Color
//===================

struct VS_SPLIT_INPUT
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_SPLIT_OUTPUT
{
    float4 vPos : SV_POSITION;
    float2 vUV : TEXCOORD;
};

float4 ChangeSplitColor(const float4 _vScrColor, const float4 _vDestColor)
{
    const float MIN_COLOR = 0.3f;
    float4 vColor = _vScrColor;

    if (vColor.x > MIN_COLOR)
    {
        vColor.x = _vDestColor.x;
    }
    if (vColor.y > MIN_COLOR)
    {
        vColor.y = _vDestColor.y;
    }
    if (vColor.z > MIN_COLOR)
    {
        vColor.z = _vDestColor.z;
    }

    return vColor;
}


VS_SPLIT_OUTPUT VS_SPLIT_2D(VS_SPLIT_INPUT _input)
{
    VS_SPLIT_OUTPUT output = (VS_SPLIT_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);

    output.vPos = vProjPos;
    output.vUV = _input.vUV;

    return output;
}

PS_OUTPUT PS_SPLIT_2D(VS_SPLIT_OUTPUT _input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0.f;

    float4 vCol = (float4) 0.f;

   // float2 vUV = float2(g_vec4_0.x + (g_vec4_0.z * _input.vUV.x)
			//, g_vec4_0.y + (g_vec4_0.w * _input.vUV.y));


    vCol = g_tex_0.Sample(g_default_sam, _input.vUV);

    if (_input.vUV.x < g_vec4_0.x || _input.vUV.y < g_vec4_0.y)
    {
        vCol.a = 0.f;
    }
    else if (_input.vUV.x > g_vec4_0.z || _input.vUV.y > g_vec4_0.w)
    {
        vCol.a = 0.f;
    }

    if (g_int_0 == 1)
    {
        vCol = ChangeSplitColor(vCol, g_vec4_1);
    }

    if (vCol.a <= 0.f)
        clip(-1);

    output.vCol = vCol;

    return output;
}

//===================
// DAMAGE 2D Shader
// g_tex_0 : Texture
// g_vec4_0 : xy(uv) z(width) w(height)
// g_vec4_1 : color
// g_float_0 : alpha
// g_int_0 : Damage;
// g_int_1 : DamageCount;
//===================

struct VS_DAMAGE_INPUT
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_DAMAGE_OUTPUT
{
    float4 vPos : SV_POSITION;
    float2 vUV : TEXCOORD;
};

VS_DAMAGE_OUTPUT VS_DAMAGE_2D(VS_DAMAGE_INPUT _input)
{
    VS_DAMAGE_OUTPUT output = (VS_DAMAGE_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);

    output.vPos = vProjPos;
    output.vUV = _input.vUV;

    return output;
}


// 현재 픽셀의 Damage index를 리턴한다.
int CalIndexDamage(int _count, float _uvx)
{
    float fOffset = 1.f / _count;

    int iIndex = _uvx / fOffset;
    return iIndex;
}


// 해당 인덱스 번호에 있는 한 자리수 데미지를 UV값을 리턴한다.
float2 CalUVDamage(int _damage, int _count, int _iIndex)
{
    float2 vUV = { 0.f, 0.f };

    float fOffset = 0.1f;

    int iNumber = _damage / pow(10, _count - _iIndex - 1);
    iNumber = iNumber % 10;

    // 시작 위치 , 너비
    vUV = float2(fOffset * iNumber - _iIndex * fOffset, fOffset);
    
    return vUV;
}

// g_int_0 : Damage;
// g_int_1 : DamageCount;
PS_OUTPUT PS_DAMAGE_2D(VS_DAMAGE_OUTPUT _input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0.f;

    float4 vCol = (float4) 0.f;
    int iIndex = CalIndexDamage(g_int_1, _input.vUV.x);
    float2 vDamageUV = CalUVDamage(g_int_0, g_int_1, iIndex);

   // float2 vUV = float2(g_vec4_0.x + (g_vec4_0.z * _input.vUV.x)
			//, g_vec4_0.y + (g_vec4_0.w * _input.vUV.y));

    float2 vUV;

    vUV = float2((vDamageUV.x + vDamageUV.y * _input.vUV.x * g_int_1), _input.vUV.y);

    vCol = g_tex_0.Sample(g_default_sam, vUV);
 

    vCol.a = vCol.a - (g_float_0 / 100.f);

    if (vCol.a <= 0.f)
        clip(-1);

    output.vCol = vCol;
    return output;
}





//===================
// Standard 2D Shader
// g_tex_0 : Texture
// g_vec4_uv : xy(uv) z(width) w(height)
// g_vec4_anim : Animation Exit
//===================

struct VS_STD_INPUT
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;

    row_major matrix matWorld : WORLD;
    row_major matrix matWV : WV;
    row_major matrix matWVP : WVP;

    uint iInstanceID : SV_InstanceID;
};

struct VS_STD_OUTPUT
{
    float4 vPos : SV_POSITION;
    float2 vUV : TEXCOORD;
};

VS_STD_OUTPUT VS_Std_2D(VS_STD_INPUT _input)
{
    VS_STD_OUTPUT output = (VS_STD_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);

    output.vPos = vProjPos;
    output.vUV = _input.vUV;

    return output;
}

VS_STD_OUTPUT VS_Std_2D_Instancing(VS_STD_INPUT _input)
{
    VS_STD_OUTPUT output = (VS_STD_OUTPUT) 0.f;
    
    output.vPos = mul(float4(_input.vPos, 1.f), _input.matWVP);
    output.vUV = _input.vUV;

    return output;
}

float ToonColorConvert(float _fCol)
{
    const float4 vToonCol = { 0.2f, 0.4f, 0.6f, 0.8f };

    if (_fCol == 0.f)
    {
        _fCol = 0.0f;
    }
    else if (_fCol <= vToonCol.x)
    {
        _fCol = vToonCol.x;
    }
    else if (_fCol <= vToonCol.y)
    {
        _fCol = vToonCol.x;
    }
    else if (_fCol <= vToonCol.z)
    {
        _fCol = vToonCol.y;
    }
    else if (_fCol <= vToonCol.w)
    {
        _fCol = vToonCol.z;
    }
    else
    {
        _fCol = 1.f;
    }

    return _fCol;
}

PS_OUTPUT PS_Std_2D(VS_STD_OUTPUT _input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0.f;

    float4 vCol = (float4) 0.f;

    if (g_vec4_anim.x)
    {
        float2 vUV = float2(g_vec4_uv.x + (g_vec4_uv.z * _input.vUV.x)
			, g_vec4_uv.y + (g_vec4_uv.w * _input.vUV.y));
        vCol = g_tex_anim.Sample(g_default_sam, vUV);
    }
    else
    {
        vCol = g_tex_0.Sample(g_default_sam, _input.vUV);
    }

   
	//vCol.x = ToonColorConvert(vCol.x);
	//vCol.y = ToonColorConvert(vCol.y);
	//vCol.z = ToonColorConvert(vCol.z);

    if (vCol.a <= 0.0f)
        clip(-1);

    output.vCol = vCol;

    return output;
}


//===================
// Flow Standard 2D Shader
// g_tex_0 : Texture
// g_int_0 : flow type
// g_float_0 : DT
// g_vec4_uv : xy(uv) z(width) w(height)
// g_vec4_anim : Animation Exit
//===================
PS_OUTPUT PS_Flow_Std_2D(VS_STD_OUTPUT _input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0.f;

    float4 vCol = (float4) 0.f;

    if (g_vec4_anim.x)
    {
        float2 vUV = float2(g_vec4_uv.x + (g_vec4_uv.z * _input.vUV.x)
			, g_vec4_uv.y + (g_vec4_uv.w * _input.vUV.y));
        vCol = g_tex_anim.Sample(g_default_sam, vUV);
    }
    else
    {
        float UVX = sin(_input.vUV.y * 3.28f + 1.14f * g_float_0) * 0.008f + _input.vUV.x - g_float_0 * 0.01f;
        float UVY = cos(_input.vUV.x * 3.28f + 1.14f * g_float_0) * 0.008f + _input.vUV.y;
        float2 vUV = float2(UVX, UVY);
        vCol = g_tex_0.Sample(g_default_sam, vUV);

       // vCol = g_tex_0.Sample(g_default_sam, _input.vUV);
    }

   
	//vCol.x = ToonColorConvert(vCol.x);
	//vCol.y = ToonColorConvert(vCol.y);
	//vCol.z = ToonColorConvert(vCol.z);

    if (vCol.a <= 0.0f)
        clip(-1);

    output.vCol = vCol;

    return output;
}