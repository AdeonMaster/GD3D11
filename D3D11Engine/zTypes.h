#pragma once
#include "pch.h"

enum zTCam_ClipType {
	ZTCAM_CLIPTYPE_IN, 
	ZTCAM_CLIPTYPE_OUT, 
	ZTCAM_CLIPTYPE_CROSSING 
};

enum zTCam_ClipFlags {
	CLIP_FLAGS_FULL		= 63, 
	CLIP_FLAGS_NO_FAR	= 15 
};

#pragma pack (push, 1)	
struct zTBBox3D {
	D3DXVECTOR3	Min;	
	D3DXVECTOR3	Max;

	enum zTPlaneClass {
		zPLANE_INFRONT, 
		zPLANE_BEHIND, 
		zPLANE_ONPLANE, 
		zPLANE_SPANNING 
	};

	int ClassifyToPlane (float planeDist, int axis) const {
		if (planeDist>=((float *)&Max)[axis])	
			return zPLANE_BEHIND;	
		else if (planeDist<=((float *)&Max)[axis])	
			return zPLANE_INFRONT;	
		else return zPLANE_SPANNING;
	}
};

struct zTPlane {
	float Distance;
	D3DXVECTOR3 Normal;
};
#pragma pack (pop)

class zCWorld;
class zCVob;
class zCCamera;

struct zTRenderContext {
	int ClipFlags;
	zCVob * Vob;
	zCWorld * world;
	zCCamera * cam;
	float distVobToCam;
	
	// More not needed stuff here
};

struct zCRenderLight {
	int	LightType;            
	D3DXVECTOR3	ColorDiffuse;			
	D3DXVECTOR3	Position;				
	D3DXVECTOR3	Direction;				
	float Range;						
	float RangeInv;
	D3DXVECTOR3 PositionLS;				
	D3DXVECTOR3 DirectionLS;			
	float Dir_approxFalloff;			
};

struct zCRenderLightContainer {
	zCRenderLight			LightList[8];
	int						NumLights;

private:
	int	DoPrelight;
	int	DoSmoothPrelit;
	float PreLightDist;
	D3DXMATRIX MatObjToCam;
};

enum zTRnd_AlphaBlendFunc {	
	zRND_ALPHA_FUNC_MAT_DEFAULT = 0,	
	zRND_ALPHA_FUNC_NONE = 1,				
	zRND_ALPHA_FUNC_BLEND = 2,				
	zRND_ALPHA_FUNC_ADD = 3,				
	zRND_ALPHA_FUNC_SUB = 4,				
	zRND_ALPHA_FUNC_MUL = 5,				
	zRND_ALPHA_FUNC_MUL2 = 6,				
	zRND_ALPHA_FUNC_TEST = 7,				
	zRND_ALPHA_FUNC_BLEND_TEST = 8			
};


struct zColor {
	union {
		struct bgra {
		  unsigned char b;
		  unsigned char g;
		  unsigned char r;
		  unsigned char alpha;
		} bgra;
		unsigned long dword;
	};
	zColor() {}
	zColor(uint8_t b, uint8_t g, uint8_t r, uint8_t a = 255) {
		bgra.b = b;
		bgra.g = g;
		bgra.r = r;
		bgra.alpha = a;
	}
	bool IsWhite() {
		return dword == 4294967295;
	}
};
static zColor zCOLOR_WHITE = zColor(255, 255, 255, 255);

struct zTRndSimpleVertex {
	float2 pos;
	float z;
	float2 uv;
	zColor color;
};

struct zVEC2 {
public:
	float v[2];
};
