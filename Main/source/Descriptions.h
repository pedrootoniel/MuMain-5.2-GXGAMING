#pragma once

#include "Lua.h"
#include "LuaUser.h"
#include <unordered_map>
#include "_struct.h"

struct NEWCOLOR_3f {
	float R;
	float G;
	float B;
};

struct NEW_COLOR_FULL {
	int fR;
	int fG;
	int fB;
	int fA;
	int bR;
	int bG;
	int bB;
	int bA;
};

class CDescriptions {
public:
	CDescriptions();
	~CDescriptions();

	void SetDescriptionsItem(int Line, ITEM* itemObject);
	int DescriptionsCall(int Line, ITEM* itemObject);
	void Init();

public:
	Lua m_Lua;
	CLuaUser m_LuaUser;
	std::unordered_map<int, NEWCOLOR_3f> m_Color3f;
	std::unordered_map<int, NEW_COLOR_FULL> m_ColorFull;
};

extern CDescriptions gDescriptions;