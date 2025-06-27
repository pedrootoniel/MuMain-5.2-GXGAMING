//////////////////////////////////////////////////////////////////////
// NewUIMainFrameWindow.cpp: implementation of the CNewUIMainFrameWindow class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NewUIMainFrameWindow.h"	// self
#include "NewUIOptionWindow.h"
#include "NewUISystem.h"
#include "UIBaseDef.h"
#include "DSPlaySound.h"
#include "ZzzInfomation.h"
#include "ZzzBMD.h"
#include "ZzzObject.h"
#include "ZzzCharacter.h"
#include "ZzzInterface.h"
#include "ZzzInventory.h"
#include "wsclientinline.h"
#include "CSItemOption.h"
#include "CSChaosCastle.h"
#include "MapManager.h"
#include "CharacterManager.h"
#include "SkillManager.h"
#include "GMDoppelGanger1.h"
#include "GMDoppelGanger2.h"
#include "GMDoppelGanger3.h"
#include "GMDoppelGanger4.h"
#include "./Time/CTimCheck.h"
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
#include "MonkSystem.h"
#endif //PBG_ADD_NEWCHAR_MONK_SKILL

#ifdef PBG_ADD_INGAMESHOP_UI_MAINFRAME
#include "GameShop/InGameShopSystem.h"
#endif //PBG_ADD_INGAMESHOP_UI_MAINFRAME
#include "Widescreen.h"
#include "TradeX.h"

extern float g_fScreenRate_x;
extern float g_fScreenRate_y;
extern int  MouseUpdateTime;
extern int  MouseUpdateTimeMax;
extern int SelectedCharacter;
extern int Attacking;


SEASON3B::CNewUIMainFrameWindow::CNewUIMainFrameWindow() 
{
	m_bExpEffect = false;
	m_dwExpEffectTime = 0;
	m_dwPreExp = 0;
	m_dwGetExp = 0;
	m_bButtonBlink = false;
}

SEASON3B::CNewUIMainFrameWindow::~CNewUIMainFrameWindow() 
{ 
	Release(); 
}

void SEASON3B::CNewUIMainFrameWindow::LoadImages()
{
	LoadBitmap("Interface\\newui_menu01.jpg", IMAGE_MENU_1, GL_LINEAR);
	LoadBitmap("Interface\\newui_menu02.jpg", IMAGE_MENU_2, GL_LINEAR);
	LoadBitmap("Interface\\partCharge1\\newui_menu03.jpg", IMAGE_MENU_3, GL_LINEAR);
	LoadBitmap("Interface\\newui_menu02-03.jpg", IMAGE_MENU_2_1, GL_LINEAR);
	LoadBitmap("Interface\\newui_menu_blue.jpg", IMAGE_GAUGE_BLUE, GL_LINEAR);
	LoadBitmap("Interface\\newui_menu_green.jpg", IMAGE_GAUGE_GREEN, GL_LINEAR);
	LoadBitmap("Interface\\newui_menu_red.jpg", IMAGE_GAUGE_RED, GL_LINEAR);
	LoadBitmap("Interface\\newui_menu_ag.jpg", IMAGE_GAUGE_AG, GL_LINEAR);
	LoadBitmap("Interface\\newui_menu_sd.jpg", IMAGE_GAUGE_SD, GL_LINEAR);
	LoadBitmap("Interface\\newui_exbar.jpg", IMAGE_GAUGE_EXBAR, GL_LINEAR);
	LoadBitmap("Interface\\Exbar_Master.jpg", IMAGE_MASTER_GAUGE_BAR, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\btn_shop.jpg", IMAGE_MENU_BTN_CSHOP, GL_LINEAR, GL_CLAMP_TO_EDGE);
	LoadBitmap("Custom\\NewInterface\\main_frame_btn_character.jpg", IMAGE_MENU_BTN_CHAINFO, GL_LINEAR, GL_CLAMP_TO_EDGE);
	LoadBitmap("Custom\\NewInterface\\main_frame_btn_inventory.jpg", IMAGE_MENU_BTN_MYINVEN, GL_LINEAR, GL_CLAMP_TO_EDGE);
	LoadBitmap("Custom\\NewInterface\\main_frame_btn_guild.jpg", IMAGE_MENU_BTN_FRIEND, GL_LINEAR, GL_CLAMP_TO_EDGE);
	LoadBitmap("Custom\\NewInterface\\main_frame_btn_party.jpg", IMAGE_MENU_BTN_WINDOW, GL_LINEAR, GL_CLAMP_TO_EDGE);
	LoadBitmap("Interface\\newui_decor.tga", IMAGE_CUSTOM_ID, GL_LINEAR);
	//
	LoadBitmap("Custom\\NewInterface\\FontTest.tga", IMAGE_CUSTOM_ID - 1, 0x2601, 0x2901, 1, 0);	//lateral party
	LoadBitmap("Custom\\NewInterface\\main_frame_left.tga", IMAGE_CUSTOM_ID + 1, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\main_frame_right.tga", IMAGE_CUSTOM_ID + 2, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\main_frame_mana.tga", IMAGE_CUSTOM_ID + 3, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\main_frame_venom.tga", IMAGE_CUSTOM_ID + 4, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\main_frame_life.tga", IMAGE_CUSTOM_ID + 5, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\main_frame_stamina.jpg", IMAGE_CUSTOM_ID + 6, GL_LINEAR);
}

void SEASON3B::CNewUIMainFrameWindow::UnloadImages()
{
	DeleteBitmap(IMAGE_MENU_1);
	DeleteBitmap(IMAGE_MENU_2);
	DeleteBitmap(IMAGE_MENU_3);
	DeleteBitmap(IMAGE_MENU_2_1);
	DeleteBitmap(IMAGE_GAUGE_BLUE);
	DeleteBitmap(IMAGE_GAUGE_GREEN);
	DeleteBitmap(IMAGE_GAUGE_RED);
	DeleteBitmap(IMAGE_GAUGE_AG);
	DeleteBitmap(IMAGE_GAUGE_SD);
	DeleteBitmap(IMAGE_GAUGE_EXBAR);
	DeleteBitmap(IMAGE_MENU_BTN_CHAINFO);
	DeleteBitmap(IMAGE_MENU_BTN_MYINVEN);
	DeleteBitmap(IMAGE_MENU_BTN_FRIEND);
	DeleteBitmap(IMAGE_MENU_BTN_WINDOW);
	//
	DeleteBitmap(IMAGE_CUSTOM_ID + 1);
	DeleteBitmap(IMAGE_CUSTOM_ID + 2);
	DeleteBitmap(IMAGE_CUSTOM_ID + 3);
	DeleteBitmap(IMAGE_CUSTOM_ID + 4);
	DeleteBitmap(IMAGE_CUSTOM_ID + 5);
	DeleteBitmap(IMAGE_CUSTOM_ID + 6);
}

bool SEASON3B::CNewUIMainFrameWindow::Create(CNewUIManager* pNewUIMng, CNewUI3DRenderMng* pNewUI3DRenderMng)
{
	if(NULL == pNewUIMng || NULL == pNewUI3DRenderMng)
		return false;

	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_MAINFRAME, this);

	m_pNewUI3DRenderMng = pNewUI3DRenderMng;
	m_pNewUI3DRenderMng->Add3DRenderObj(this, ITEMHOTKEYNUMBER_CAMERA_Z_ORDER);

	LoadImages();

	SetButtonInfo();

	Show(true);
	
	return true;
}

void SEASON3B::CNewUIMainFrameWindow::SetButtonInfo()
{
	int frame_cx = GetCenterX(640);
	int x_Next = 489 + GetCenterX(640);
	int y_Next = setPosDown(452);
	int x_Add = 22;
	int y_Add = 22;
	
	// --
	// Button Party
	m_BtnParty.ChangeTextBackColor(RGBA(255, 255, 255, 0));
	m_BtnParty.ChangeButtonImgState(true, IMAGE_MENU_BTN_WINDOW, true);
	m_BtnParty.ChangeButtonInfo(frame_cx + 349, y_Next, x_Add, y_Add);
	m_BtnParty.ChangeImgColor(BUTTON_STATE_UP, RGBA(255, 255, 255, 255));
	m_BtnParty.ChangeImgColor(BUTTON_STATE_DOWN, RGBA(255, 255, 255, 255));
	m_BtnParty.ChangeToolTipText(GlobalText[361], true);
	// --
	// Button Inventory
	m_BtnMyInven.ChangeTextBackColor(RGBA(255, 255, 255, 0));
	m_BtnMyInven.ChangeButtonImgState(true, IMAGE_MENU_BTN_MYINVEN, true);
	m_BtnMyInven.ChangeButtonInfo(frame_cx + 412, y_Next, x_Add, y_Add);
	m_BtnMyInven.ChangeImgColor(BUTTON_STATE_UP, RGBA(255, 255, 255, 255));
	m_BtnMyInven.ChangeImgColor(BUTTON_STATE_DOWN, RGBA(255, 255, 255, 255));
	m_BtnMyInven.ChangeToolTipText(GlobalText[363], true);
	// --
	// Button Character
	m_BtnChaInfo.ChangeTextBackColor(RGBA(255, 255, 255, 0));
	m_BtnChaInfo.ChangeButtonImgState(true, IMAGE_MENU_BTN_CHAINFO, true);
	m_BtnChaInfo.ChangeButtonInfo(frame_cx + 380, y_Next, x_Add, y_Add);
	m_BtnChaInfo.ChangeImgColor(BUTTON_STATE_UP, RGBA(255, 255, 255, 255));
	m_BtnChaInfo.ChangeImgColor(BUTTON_STATE_DOWN, RGBA(255, 255, 255, 255));
	m_BtnChaInfo.ChangeToolTipText(GlobalText[362], true);
	// --
	// Button Guild
	m_BtnGuild.ChangeTextBackColor(RGBA(255, 255, 255, 0));
	m_BtnGuild.ChangeButtonImgState(true, IMAGE_MENU_BTN_FRIEND, true);
	m_BtnGuild.ChangeButtonInfo(frame_cx + 92, y_Next, x_Add, y_Add);
	m_BtnGuild.ChangeImgColor(BUTTON_STATE_UP, RGBA(255, 255, 255, 255));
	m_BtnGuild.ChangeImgColor(BUTTON_STATE_DOWN, RGBA(255, 255, 255, 255));
	m_BtnGuild.ChangeToolTipText(GlobalText[364], true);
	// --
	// Button CashShop
#ifndef PBG_ADD_INGAMESHOP_UI_MAINFRAME
	m_BtnCShop.ChangeTextBackColor(RGBA(255,255,255,0));
	m_BtnCShop.ChangeButtonImgState( true, IMAGE_MENU_BTN_CSHOP, true );
	m_BtnCShop.ChangeButtonInfo(x_Next, y_Next, x_Add, y_Add);
	x_Next += x_Add;
	m_BtnCShop.ChangeImgColor(BUTTON_STATE_UP, RGBA(255, 255, 255, 255));
	m_BtnCShop.ChangeImgColor(BUTTON_STATE_DOWN, RGBA(255, 255, 255, 255));
	m_BtnCShop.ChangeToolTipText(GlobalText[2277], true);
#endif
}

void SEASON3B::CNewUIMainFrameWindow::Release()
{
	UnloadImages();

	if(m_pNewUI3DRenderMng)
	{
		m_pNewUI3DRenderMng->Remove3DRenderObj(this);
		m_pNewUI3DRenderMng = NULL;
	}

	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}
}

bool SEASON3B::CNewUIMainFrameWindow::Render()
{
	EnableAlphaTest();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	RenderFrame();

	m_pNewUI3DRenderMng->RenderUI2DEffect(ITEMHOTKEYNUMBER_CAMERA_Z_ORDER, UI2DEffectCallback, this, 0, 0);
	
	g_pSkillList->RenderCurrentSkillAndHotSkillList();

	EnableAlphaTest();
	RenderLifeMana();
	//RenderGuageSD();
	RenderGuageAG();
	RenderButtons();
	RenderExperience();
	DisableAlphaBlend();

	return true;
}

void SEASON3B::CNewUIMainFrameWindow::Render3D()
{
	m_ItemHotKey.RenderItems();
}

void SEASON3B::CNewUIMainFrameWindow::UI2DEffectCallback(LPVOID pClass, DWORD dwParamA, DWORD dwParamB)
{
	g_pMainFrame->RenderHotKeyItemCount();

}

bool SEASON3B::CNewUIMainFrameWindow::IsVisible() const
{
	return CNewUIObj::IsVisible();
}

void SEASON3B::CNewUIMainFrameWindow::RenderFrame()
{
	//	- EXEMPLO DA FUN��O RenderColorRadius
	// 
	//glColor4f(1.0f, 0.0f, 0.0f, 0.6f);
	//
	//RenderColorRadius(100, 80, 215.0f, 200.0f, 0.0f, 0, 15.0f); // 20.0f � o raio das bordas
	//
	//EndRenderColor();
	//gTradeX.RenderButtomHidden();


	float frame_cx = GetCenterX(640);
	float frame_cy = (float)GetWindowsY - 51.f;
	frame_cy = (float)GetWindowsY - 60.f;

	GWidescreen.RenderImages(IMAGE_CUSTOM_ID + 1, frame_cx, frame_cy, 320.0, 60.0, 0.0, 0.0, 716.f, 134.f);
	frame_cx += 320.f;
	GWidescreen.RenderImages(IMAGE_CUSTOM_ID + 2, frame_cx, frame_cy, 320.0, 60.0, 0.0, 0.0, 717.f, 134.f);
	char szText[100] = { 0 };
	sprintf_s(szText, "FPS: %.1f", FPS);

	EnableAlphaTest();
	glColor3f(0.60000002, 0.60000002, 0.60000002);
	GWidescreen.RenderNumbers(GetCenterX(640) + 55.0, frame_cy + 47, Hero->PositionX, 6.0, 6.0);
	GWidescreen.RenderNumbers(GetCenterX(640) + 76.5 , frame_cy + 47, Hero->PositionY, 6.0, 6.0);
	glColor3f(1.0, 1.0, 1.0);
	EnableAlphaTest(0);
	//--
	frame_cx = GetCenterX(640);
	g_pRenderText->SetBgColor(0);
	g_pRenderText->SetFont(g_hFixFont);
	g_pRenderText->SetTextColor(CLRDW_WHITE);
	g_pRenderText->RenderText(frame_cx + 555, frame_cy + 46, szText, 35, 0, RT3_SORT_CENTER);
}

void SEASON3B::CNewUIMainFrameWindow::RenderLifeMana()
{
	float fLife = 0.f, fMana = 0.f;
	float u[2], v[2], uw[2], vh[2];
	float fY[2], fH[2], fV, X[2], Y[2], width, height;
	float frame_cx = GetCenterX(640);

	if (CharacterAttribute->LifeMax > 0)
	{
		if (CharacterAttribute->Life > 0 && (CharacterAttribute->Life / (float)CharacterAttribute->LifeMax) < 0.2f)
		{
			PlayBuffer(34, 0, 0);
		}
	}

	if (CharacterAttribute->LifeMax > 0)
	{
		fLife = (CharacterAttribute->LifeMax - CharacterAttribute->Life) / (float)CharacterAttribute->LifeMax;
	}
	if (CharacterAttribute->ManaMax > 0)
	{
		fMana = (CharacterAttribute->ManaMax - CharacterAttribute->Mana) / (float)CharacterAttribute->ManaMax;
	}

	height = 43.f, width = 45.5f;
	//--
	int Anim = 0;
	int AnimX = 0;
	int AnimY = 0;
	//-- Life
	X[0] = frame_cx + 144.f; Y[0] = GetWindowsY - 49.f;
	X[1] = frame_cx + 451.f; Y[1] = GetWindowsY - 49.f;

	fY[0] = Y[0] + (fLife * height);
	fH[0] = height - (fLife * height);
	fV = fLife;
	//--
	u[0] = 0.0 + (128.f * AnimX); v[0] = fV * 96.f + (128.f * AnimY);
	uw[0] = 102.f; vh[0] = (1.0f - fV) * 96.f;

	//-- Mana
	fY[1] = Y[1] + (fMana * height);
	fH[1] = height - (fMana * height);
	fV = fMana;

	u[1] = 0.0 + (128.f * AnimX); v[1] = fV * 96.f + (128.f * AnimY);
	uw[1] = 102.f; vh[1] = (1.0f - fV) * 96.f;

	EnableAlphaTest(true);
	glColor4f(1.f, 1.f, 1.f, 1.f);

	if (g_isCharacterBuff((&Hero->Object), eDeBuff_Poison))
	{
		GWidescreen.RenderImages(IMAGE_CUSTOM_ID + 4, X[0], fY[0], width, fH[0], u[0], v[0], uw[0], vh[0]);
	}
	else
	{
		GWidescreen.RenderImages(IMAGE_CUSTOM_ID + 5, X[0], fY[0], width, fH[0], u[0], v[0], uw[0], vh[0]);
	}

	GWidescreen.RenderImages(IMAGE_CUSTOM_ID + 3, X[1], fY[1], width, fH[1], u[1], v[1], uw[1], vh[1]);


	EnableAlphaTest(true);

	glColor3f(0.91000003, 0.81, 0.60000002);

	GWidescreen.RenderNumbers(X[0] + 25, GetWindowsY - 18.f, CharacterAttribute->Life, 6.0, 6.0);
	GWidescreen.RenderNumbers(X[1] + 30, GetWindowsY - 18.f, CharacterAttribute->Mana, 6.0, 7.0);

	glColor4f(1.f, 1.f, 1.f, 1.f);

	char strTipText[256];
	if (SEASON3B::CheckMouseIn(X[0], Y[0], width, height) == true)
	{
		sprintf_s(strTipText, GlobalText[358], CharacterAttribute->Life, CharacterAttribute->LifeMax);
		RenderTipText((int)X[0], (int)Y[0] - 20, strTipText);
		glColor4f(1.f, 1.f, 1.f, 1.f);
	}

	if (SEASON3B::CheckMouseIn((int)X[1], Y[1], width, height) == true)
	{
		sprintf_s(strTipText, GlobalText[359], CharacterAttribute->Mana, CharacterAttribute->ManaMax);
		RenderTipText((int)X[1], (int)Y[1] - 20, strTipText);
		glColor4f(1.f, 1.f, 1.f, 1.f);
	}
}

void SEASON3B::CNewUIMainFrameWindow::RenderGuageAG()
{
	DWORD dwMaxSkillMana = CharacterAttribute->SkillManaMax;
	DWORD dwSkillMana = CharacterAttribute->SkillMana;

	float fSkillMana = 0.0;

	if (dwMaxSkillMana > 0)
	{
		fSkillMana = (dwMaxSkillMana - dwSkillMana) / (float)dwMaxSkillMana;
	}

	float x, y, width, height;
	float fY, fH, fV, u, v, uw, vh;

	float frame_cx = GetCenterX(640);
	float frame_cy = (float)GetWindowsY - 51.f;
	float Sub = 28.f;

	frame_cy = (float)GetWindowsY - 60.f;

	y = frame_cy + 18.f;
	x = frame_cx + 506.f;
	width = 16.0f, height = 38.5f;

	fY = y + (fSkillMana * height);
	fH = height - (fSkillMana * height);
	fV = fSkillMana;

	v = fV * 86.f;
	u = 0.0; uw = 36.f;
	vh = (1.0f - fV) * 86.f;

	Sub = 10.f;

	EnableAlphaTest(true);

	GWidescreen.RenderImages(IMAGE_CUSTOM_ID + 6, x, fY, width, fH, u, v, uw, vh);

	glColor3f(0.91000003, 0.81, 0.60000002);

	GWidescreen.RenderNumbers(x + 12, GetWindowsY - Sub - 4, dwSkillMana, 6.0, 7.0);

	glColor4f(1.f, 1.f, 1.f, 1.f);

	char strTipText[256];

	if (SEASON3B::CheckMouseIn((int)x, (int)y, (int)width, (int)height) == true)
	{
		sprintf_s(strTipText, GlobalText[214], dwSkillMana, dwMaxSkillMana);
		RenderTipText((int)(x - 20), (int)y - 25, strTipText);
		glColor4f(1.f, 1.f, 1.f, 1.f);
	}
}

void SEASON3B::CNewUIMainFrameWindow::RenderGuageSD()
{
	float x, y, width, height;
	float fY, fH, fV;
    DWORD wMaxShield,wShield;

	float frame_cx = GetCenterX(640);
	//Master_Level_Data.wMaxShield
	if(gCharacterManager.IsMasterLevel(Hero->Class) == true)
	{
		wMaxShield = max (1, Master_Level_Data.wMaxShield);
		wShield = min (wMaxShield, CharacterAttribute->Shield);
	}
	else
	{
		wMaxShield = max (1, CharacterAttribute->ShieldMax);
		wShield = min (wMaxShield, CharacterAttribute->Shield);
	}
	
	float fShield = 0.0f;

	if(wMaxShield > 0)
	{
		fShield = (wMaxShield - wShield) / (float)wMaxShield;
	}

	width = 16.f, height = 39.f;
	x = 204 + frame_cx; y = 480.f - 49.f;
	fY = y + (fShield * height);
	fH = height - (fShield * height);
	fV = fShield;

	RenderBitmap(IMAGE_GAUGE_SD, x, fY, width, fH, 0.f, fV*height/64.f, width/16.f, (1.0f - fV)*height/64.f);
	SEASON3B::RenderNumber(x+15, 480-18, (int)wShield);

	height = 39.f;
	y = 480.f - 10.f - 39.f;
	if(SEASON3B::CheckMouseIn(x, y, width, height) == true)
	{	
		char strTipText[256];

        sprintf(strTipText, GlobalText[2037], wShield, wMaxShield);
		RenderTipText((int)x-20, (int)418, strTipText);
    }
}

void SEASON3B::CNewUIMainFrameWindow::RenderExperience()
{
	__int64 wLevel;
	__int64 dwNexExperience;
	__int64 dwExperience;
	double x, y, width, height;

	wLevel = CharacterAttribute->Level;
	dwNexExperience = CharacterAttribute->NextExperince;
	dwExperience = CharacterAttribute->Experience;

	x = 0; y = 470; width = 6; height = 4;

	WORD wPriorLevel = wLevel - 1;
	DWORD dwPriorExperience = 0;

	if (wPriorLevel > 0)
	{
		dwPriorExperience = (9 + wPriorLevel) * wPriorLevel * wPriorLevel * 10;

		if (wPriorLevel > 255)
		{
			int iLevelOverN = wPriorLevel - 255;
			dwPriorExperience += (9 + iLevelOverN) * iLevelOverN * iLevelOverN * 1000;
		}
	}

	float fNeedExp = dwNexExperience - dwPriorExperience;
	float fExp = dwExperience - dwPriorExperience;

	if (dwExperience < dwPriorExperience)
	{
		fExp = 0.f;
	}

	float fExpBarNum = 0.f;
	if (fExp > 0.f && fNeedExp > 0)
	{
		fExpBarNum = (fExp / fNeedExp) * 10.f;
	}

	float fProgress = fExpBarNum;
	fProgress = fProgress - (int)fProgress;

	if (m_bExpEffect == true)
	{
		float fPreProgress = 0.f;
		fExp = m_dwPreExp - dwPriorExperience;
		if (m_dwPreExp < dwPriorExperience)
		{
			x = setPosMidRight(221.f); y = (float)GetWindowsY - 42.f; width = fProgress * 200.f; height = 5.f;
			RenderBitmap(IMAGE_GAUGE_EXBAR, x, y, width, height, 0.f, 0.f, 6.f / 8.f, 4.f / 4.f);
			glColor4f(1.f, 1.f, 1.f, 0.4f);
			RenderColor(x, y, width, height);
			EndRenderColor();
		}
		else
		{
			int iPreExpBarNum = 0;
			int iExpBarNum = 0;
			if (fExp > 0.f && fNeedExp > 0.f)
			{
				fPreProgress = (fExp / fNeedExp) * 10.f;
				iPreExpBarNum = (int)fPreProgress;
				fPreProgress = fPreProgress - (int)fPreProgress;
			}

			iExpBarNum = (int)fExpBarNum;

			if (iExpBarNum > iPreExpBarNum)
			{
				x = setPosMidRight(221.f); y = (float)GetWindowsY - 42.f; width = fProgress * 200.f; height = 5.f;
				RenderBitmap(IMAGE_GAUGE_EXBAR, x, y, width, height, 0.f, 0.f, 6.f / 8.f, 4.f / 4.f);
				glColor4f(1.f, 1.f, 1.f, 0.4f);
				RenderColor(x, y, width, height);
				EndRenderColor();
			}
			else
			{
				float fGapProgress = 0.f;
				fGapProgress = fProgress - fPreProgress;
				x = setPosMidRight(221.f); y = (float)GetWindowsY - 42.f; width = fPreProgress * 200.f; height = 5.f;
				RenderBitmap(IMAGE_GAUGE_EXBAR, x, y, width, height, 0.f, 0.f, 6.f / 8.f, 4.f / 4.f);
				x += width; width = fGapProgress * 200.f;
				RenderBitmap(IMAGE_GAUGE_EXBAR, x, y, width, height, 0.f, 0.f, 6.f / 8.f, 4.f / 4.f);
				glColor4f(1.f, 1.f, 1.f, 0.4f);
				RenderColor(x, y, width, height);
				EndRenderColor();
			}
		}
	}
	else
	{
		x = setPosMidRight(221.f); y = (float)GetWindowsY - 42.f; width = fProgress * 200.f; height = 5.f;
		RenderBitmap(IMAGE_GAUGE_EXBAR, x, y, width, height, 0.f, 0.f, 6.f / 8.f, 4.f / 4.f);
	}

	//int iExp = (int)fExpBarNum;
	int iExp = CharacterAttribute->Level;

	x = setPosMidRight(429.f); y = (float)GetWindowsY - 44.f;

	glColor3f(0.91000003, 0.81, 0.60000002);
	GWidescreen.RenderNumbers(x, y, iExp, 5.0, 6.0);
	glColor3f(1.0, 1.0, 1.0);

	x = setPosMidRight(221.f); y = (float)GetWindowsY - 42.f; width = 200.f; height = 5.f;

	if (SEASON3B::CheckMouseIn(x, y, width, height) == true)
	{
		char strTipText[256];

		sprintf(strTipText, GlobalText[1748], dwExperience, dwNexExperience);
		RenderTipText(280 + GetWindowsCX(640.f), 418 + (float)(GetWindowsY - 480.f), strTipText);
	}
}

void SEASON3B::CNewUIMainFrameWindow::RenderHotKeyItemCount()
{
	m_ItemHotKey.RenderItemCount();
}

void SEASON3B::CNewUIMainFrameWindow::RenderButtons()
{
#ifndef PBG_ADD_INGAMESHOP_UI_MAINFRAME
	m_BtnCShop.Render();
#endif //defined PBG_ADD_INGAMESHOP_UI_MAINFRAME

	m_BtnMyInven.Render();

	m_BtnChaInfo.Render();

	m_BtnGuild.Render();

	m_BtnParty.Render();
}

void SEASON3B::CNewUIMainFrameWindow::RenderCharInfoButton()
{
	if (g_QuestMng.IsQuestIndexByEtcListEmpty())
		return;

	if (g_Time.GetTimeCheck(5, 500))
		m_bButtonBlink = !m_bButtonBlink;

	float frame_cx = GetCenterX(640);

	if (m_bButtonBlink)
	{

	}
}

void SEASON3B::CNewUIMainFrameWindow::RenderFriendButton()
{
	int iBlinkTemp = g_pFriendMenu->GetBlinkTemp();
	BOOL bIsAlertTime = (iBlinkTemp % 24 < 12);

	if (g_pFriendMenu->IsNewChatAlert() && bIsAlertTime)
	{
		RenderFriendButtonState();	
	}
	if (g_pFriendMenu->IsNewMailAlert())
	{
		if (bIsAlertTime)
		{
			RenderFriendButtonState();

			if (iBlinkTemp % 24 == 11) 
			{
				g_pFriendMenu->IncreaseLetterBlink();
			}
		}
	}
	else if (g_pLetterList->CheckNoReadLetter())
	{
		RenderFriendButtonState();
	}

	g_pFriendMenu->IncreaseBlinkTemp();
}

void SEASON3B::CNewUIMainFrameWindow::RenderFriendButtonState()
{
#ifdef PBG_ADD_INGAMESHOP_UI_MAINFRAME

#else //defined PBG_ADD_INGAMESHOP_UI_MAINFRAME
	if(g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_FRIEND) == true)
	{
		RenderImage(IMAGE_MENU_BTN_FRIEND, 488+76, 480-51, 38, 42, 0.0f, 126.f);
	}
	else
	{
		RenderImage(IMAGE_MENU_BTN_FRIEND, 488+76, 480-51, 38, 42, 0.0f, 42.f);
	}
#endif//defined PBG_ADD_INGAMESHOP_UI_MAINFRAME
}

bool SEASON3B::CNewUIMainFrameWindow::UpdateMouseEvent()
{
	if( g_pNewUIHotKey->IsStateGameOver() == true )
	{
		return true;
	}

	if(BtnProcess() == true)
	{
		return false;
	}

	return true;
}

bool SEASON3B::CNewUIMainFrameWindow::BtnProcess()
{
	if(g_pNewUIHotKey->CanUpdateKeyEventRelatedMyInventory() == true)
	{

	}
	else if(g_pNewUIHotKey->CanUpdateKeyEvent() == true)
	{
		if(m_BtnMyInven.UpdateMouseEvent() == true)
		{
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_INVENTORY);
			PlayBuffer(SOUND_CLICK01);
			return true;
		}
		else if(m_BtnChaInfo.UpdateMouseEvent() == true)
		{
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_CHARACTER);

			PlayBuffer(SOUND_CLICK01);

			if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_CHARACTER))
				g_QuestMng.SendQuestIndexByEtcSelection();

			return true;
		}
		else if(m_BtnGuild.UpdateMouseEvent() == true)
		{
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_GUILDINFO);
			PlayBuffer(SOUND_CLICK01);
			return true;
		}
		else if(m_BtnParty.UpdateMouseEvent() == true)
		{
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_PARTY);
			PlayBuffer(SOUND_CLICK01);
			return true;
		}
		if (m_BtnMyInven.UpdateMouseEvent() == true)
		{
			g_pNewUISystem->Toggle(SEASON3B::INTERFACE_INVENTORY);
			PlayBuffer(SOUND_CLICK01);
			return true;
		}

#ifndef PBG_ADD_INGAMESHOP_UI_MAINFRAME
		else if(m_BtnCShop.UpdateMouseEvent() == true)
		{
			if(g_pInGameShop->IsInGameShopOpen() == false)
				return false;

#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
			if( g_InGameShopSystem->IsScriptDownload() == true )
			{
				if( g_InGameShopSystem->ScriptDownload() == false )
					return false;
			}
			
			if( g_InGameShopSystem->IsBannerDownload() == true )
			{
				g_InGameShopSystem->BannerDownload();
			}
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD
			
			if( g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_INGAMESHOP) == false)
			{
				if( g_InGameShopSystem->GetIsRequestShopOpenning() == false )		
				{
					SendRequestIGS_CashShopOpen(0);
					g_InGameShopSystem->SetIsRequestShopOpenning(true);

#ifdef KJH_MOD_SHOP_SCRIPT_DOWNLOAD
					g_pMainFrame->SetBtnState(MAINFRAME_BTN_PARTCHARGE, true);
#endif // KJH_MOD_SHOP_SCRIPT_DOWNLOAD

				}
			}
			else
			{
				SendRequestIGS_CashShopOpen(1);
				g_pNewUISystem->Hide(SEASON3B::INTERFACE_INGAMESHOP);
			}		

			return true;
		}
#endif //PBG_ADD_INGAMESHOP_UI_MAINFRAME
	}

	return false;
}

bool SEASON3B::CNewUIMainFrameWindow::UpdateKeyEvent()
{
	if(m_ItemHotKey.UpdateKeyEvent() == false)
	{
		return false;
	}
	return true;
}

bool SEASON3B::CNewUIMainFrameWindow::Update()
{
	if(m_bExpEffect == true)
	{
		if(timeGetTime() - m_dwExpEffectTime > 2000)
		{
			m_bExpEffect = false;
			m_dwExpEffectTime = 0;
			m_dwGetExp = 0;
		}
	}
	
	return true;
}

float SEASON3B::CNewUIMainFrameWindow::GetLayerDepth()
{
	return 10.6f;
}

float SEASON3B::CNewUIMainFrameWindow::GetKeyEventOrder()
{
	return 2.9f;
}

void SEASON3B::CNewUIMainFrameWindow::SetItemHotKey(int iHotKey, int iItemType, int iItemLevel)
{
	m_ItemHotKey.SetHotKey(iHotKey, iItemType, iItemLevel);	
}

int SEASON3B::CNewUIMainFrameWindow::GetItemHotKey(int iHotKey)
{
	return m_ItemHotKey.GetHotKey(iHotKey);
}

int SEASON3B::CNewUIMainFrameWindow::GetItemHotKeyLevel(int iHotKey)
{
	return m_ItemHotKey.GetHotKeyLevel(iHotKey);
}

void SEASON3B::CNewUIMainFrameWindow::UseHotKeyItemRButton()
{
	m_ItemHotKey.UseItemRButton();
}

void SEASON3B::CNewUIMainFrameWindow::UpdateItemHotKey()
{
	m_ItemHotKey.UpdateKeyEvent();
}

void SEASON3B::CNewUIMainFrameWindow::ResetSkillHotKey()
{
	g_pSkillList->Reset();
}

void SEASON3B::CNewUIMainFrameWindow::SetSkillHotKey(int iHotKey, int iSkillType)
{
	g_pSkillList->SetHotKey(iHotKey, iSkillType);
}

int SEASON3B::CNewUIMainFrameWindow::GetSkillHotKey(int iHotKey)
{
	return g_pSkillList->GetHotKey(iHotKey);
}

int SEASON3B::CNewUIMainFrameWindow::GetSkillHotKeyIndex(int iSkillType)
{
	return g_pSkillList->GetSkillIndex(iSkillType);
}

SEASON3B::CNewUIItemHotKey::CNewUIItemHotKey()
{
	for(int i=0; i<HOTKEY_COUNT; ++i)
	{
		m_iHotKeyItemType[i] = -1;
		m_iHotKeyItemLevel[i] = 0;
	}
}

SEASON3B::CNewUIItemHotKey::~CNewUIItemHotKey()
{

}

bool SEASON3B::CNewUIItemHotKey::UpdateKeyEvent()
{
	int iIndex = -1;

	if(SEASON3B::IsPress('Q') == true)
	{
		iIndex = GetHotKeyItemIndex(HOTKEY_Q);
	}
	else if(SEASON3B::IsPress('W') == true)
	{
		iIndex = GetHotKeyItemIndex(HOTKEY_W);
	}
	else if(SEASON3B::IsPress('E') == true)
	{
		iIndex = GetHotKeyItemIndex(HOTKEY_E);	
	}
	//else if(SEASON3B::IsPress('R') == true)
	//{
	//	iIndex = GetHotKeyItemIndex(HOTKEY_R);
	//}
	
	if(iIndex != -1)
	{
		ITEM* pItem = NULL;
		pItem = g_pMyInventory->FindItem(iIndex);
		if( ( pItem->Type>=ITEM_POTION+78 && pItem->Type<=ITEM_POTION+82 ) )
		{
			std::list<eBuffState> secretPotionbufflist;
			secretPotionbufflist.push_back( eBuff_SecretPotion1 );
			secretPotionbufflist.push_back( eBuff_SecretPotion2 );
			secretPotionbufflist.push_back( eBuff_SecretPotion3 );
			secretPotionbufflist.push_back( eBuff_SecretPotion4 );
			secretPotionbufflist.push_back( eBuff_SecretPotion5 );
			
			if( g_isCharacterBufflist( (&Hero->Object), secretPotionbufflist ) != eBuffNone ) {
				SEASON3B::CreateOkMessageBox(GlobalText[2530], RGBA(255, 30, 0, 255) );	
			}
			else {
				SendRequestUse(iIndex, 0);
			}
		}
		else
		
		{
			SendRequestUse(iIndex, 0);
		}
		return false;
	}

	return true;
}

int SEASON3B::CNewUIItemHotKey::GetHotKeyItemIndex(int iType, bool bItemCount)
{
	int iStartItemType = 0, iEndItemType = 0;
	int i, j;

	switch(iType)
	{
	case HOTKEY_Q:
		if(GetHotKeyCommonItem(iType, iStartItemType, iEndItemType) == false)
		{
			if(m_iHotKeyItemType[iType] >= ITEM_POTION+4 && m_iHotKeyItemType[iType] <= ITEM_POTION+6)
            {
                iStartItemType = ITEM_POTION+6; iEndItemType = ITEM_POTION+4;
            }
			else
			{
				iStartItemType = ITEM_POTION+3; iEndItemType = ITEM_POTION+0;
			}
		}
		break;
	case HOTKEY_W:
		if(GetHotKeyCommonItem(iType, iStartItemType, iEndItemType) == false)
		{
			if(m_iHotKeyItemType[iType] >= ITEM_POTION+0 && m_iHotKeyItemType[iType] <= ITEM_POTION+3)
            {
                iStartItemType = ITEM_POTION+3; iEndItemType = ITEM_POTION+0;
            }
			else
			{
				iStartItemType = ITEM_POTION+6; iEndItemType = ITEM_POTION+4;
			}	
		}
		break;
	case HOTKEY_E:
		if(GetHotKeyCommonItem(iType, iStartItemType, iEndItemType) == false)
		{
			if(m_iHotKeyItemType[iType] >= ITEM_POTION+0 && m_iHotKeyItemType[iType] <= ITEM_POTION+3)
            {
                iStartItemType = ITEM_POTION+3; iEndItemType = ITEM_POTION+0;
            }
			else if(m_iHotKeyItemType[iType] >= ITEM_POTION+4 && m_iHotKeyItemType[iType] <= ITEM_POTION+6)
            {
                iStartItemType = ITEM_POTION+6; iEndItemType = ITEM_POTION+4;
            }
			else
			{
				iStartItemType = ITEM_POTION+8; iEndItemType = ITEM_POTION+8;
			}
		}
		break;
	//case HOTKEY_R:
	//	if(GetHotKeyCommonItem(iType, iStartItemType, iEndItemType) == false)
	//	{
	//		if(m_iHotKeyItemType[iType] >= ITEM_POTION+0 && m_iHotKeyItemType[iType] <= ITEM_POTION+3)
    //        {
    //            iStartItemType = ITEM_POTION+3; iEndItemType = ITEM_POTION+0;
    //        }
	//		else if(m_iHotKeyItemType[iType] >= ITEM_POTION+4 && m_iHotKeyItemType[iType] <= ITEM_POTION+6)
    //        {
    //            iStartItemType = ITEM_POTION+6; iEndItemType = ITEM_POTION+4;
    //        }
	//		else
	//		{
	//			iStartItemType = ITEM_POTION+37; iEndItemType = ITEM_POTION+35;	
	//		}
	//	}
		break;	
	}

	int iItemCount = 0;
	ITEM* pItem = NULL;

	int iNumberofItems = g_pMyInventory->GetInventoryCtrl()->GetNumberOfItems();
	for(i=iStartItemType; i>=iEndItemType; --i)
	{
		if(bItemCount)
		{
			for(j=0; j<iNumberofItems; ++j)
			{
				pItem = g_pMyInventory->GetInventoryCtrl()->GetItem(j);
				if(pItem == NULL)
				{
					continue;
				}

				if( 
					(pItem->Type == i && ((pItem->Level>>3)&15) == m_iHotKeyItemLevel[iType])
				|| (pItem->Type == i && (pItem->Type >= ITEM_POTION+0 && pItem->Type <= ITEM_POTION+3)) 
				)
				{
					if(pItem->Type == ITEM_POTION+9
						|| pItem->Type == ITEM_POTION+10
						|| pItem->Type == ITEM_POTION+20
						)
					{
						iItemCount++;
					}
					else
					{
						iItemCount += pItem->Durability;
					}
				}
			}
		}
		else
		{
			int iIndex = -1;
			if(i >= ITEM_POTION+0 && i <= ITEM_POTION+3)	
			{
				iIndex = g_pMyInventory->FindItemReverseIndex(i);
			}
			else
			{
				iIndex = g_pMyInventory->FindItemReverseIndex(i, m_iHotKeyItemLevel[iType]);
			}
			
			if (-1 != iIndex)
			{
				pItem = g_pMyInventory->FindItem(iIndex);
				if((pItem->Type != ITEM_POTION+7
					&& pItem->Type != ITEM_POTION+10
					&& pItem->Type != ITEM_POTION+20)
					|| ((pItem->Level>>3)&15) == m_iHotKeyItemLevel[iType]
					)
				{
					return iIndex;
				}
			}
		}
	}

	if(bItemCount == true)
	{
		return iItemCount;
	}

	return -1;
}

bool SEASON3B::CNewUIItemHotKey::GetHotKeyCommonItem(IN int iHotKey, OUT int& iStart, OUT int& iEnd)
{
	switch(m_iHotKeyItemType[iHotKey])
	{
	case ITEM_POTION+7:
	case ITEM_POTION+8:
	case ITEM_POTION+9:
	case ITEM_POTION+10:
	case ITEM_POTION+20:
	case ITEM_POTION+46:
	case ITEM_POTION+47:
	case ITEM_POTION+48:
	case ITEM_POTION+49:
	case ITEM_POTION+50:
	case ITEM_POTION+70:
	case ITEM_POTION+71:
	case ITEM_POTION+78:
	case ITEM_POTION+79:
	case ITEM_POTION+80:
	case ITEM_POTION+81:
	case ITEM_POTION+82:
	case ITEM_POTION+94:
	case ITEM_POTION+85:
	case ITEM_POTION+86:
	case ITEM_POTION+87:
	case ITEM_POTION+133:
		if(m_iHotKeyItemType[iHotKey] != ITEM_POTION+20 || m_iHotKeyItemLevel[iHotKey] == 0)
		{
			iStart = iEnd = m_iHotKeyItemType[iHotKey];
			return true;
		}
		break;
	default:
		if(m_iHotKeyItemType[iHotKey] >= ITEM_POTION+35 && m_iHotKeyItemType[iHotKey] <= ITEM_POTION+37)
		{
			iStart = ITEM_POTION+37; iEnd = ITEM_POTION+35;
			return true;
		}
		else if(m_iHotKeyItemType[iHotKey] >= ITEM_POTION+38 && m_iHotKeyItemType[iHotKey] <= ITEM_POTION+40)
		{
			iStart = ITEM_POTION+40; iEnd = ITEM_POTION+38;
			return true;
		}
		break;
	}
	return false;
}

int SEASON3B::CNewUIItemHotKey::GetHotKeyItemCount(int iType)
{
	return 0;
}

void SEASON3B::CNewUIItemHotKey::SetHotKey(int iHotKey, int iItemType, int iItemLevel)
{
	if(iHotKey != -1 && CNewUIMyInventory::CanRegisterItemHotKey(iItemType) == true
		)
	{
		m_iHotKeyItemType[iHotKey] = iItemType;
		m_iHotKeyItemLevel[iHotKey] = iItemLevel;
	}
	else
	{
		m_iHotKeyItemType[iHotKey] = -1;
		m_iHotKeyItemLevel[iHotKey] = 0;
	}
}

int SEASON3B::CNewUIItemHotKey::GetHotKey(int iHotKey)
{
	if(iHotKey != -1)
	{
		return m_iHotKeyItemType[iHotKey];
	}

	return -1;
}

int SEASON3B::CNewUIItemHotKey::GetHotKeyLevel(int iHotKey)
{
	if(iHotKey != -1)
	{
		return m_iHotKeyItemLevel[iHotKey];
	}
	
	return 0;
}

void SEASON3B::CNewUIItemHotKey::RenderItems()
{
	float x, y, width, height;

	for(int i=0; i<HOTKEY_COUNT; ++i)
	{
		int iIndex = GetHotKeyItemIndex(i);
		if(iIndex != -1)
		{
			ITEM* pItem = g_pMyInventory->FindItem(iIndex);
			if(pItem)
			{
				if (i == 0)
				{
					x = 205 + (i * 38); y = GetWindowsY - 27; width = 20; height = 20;
				}
				if (i == 1)
				{
					x = 199 + (i * 38); y = GetWindowsY - 27; width = 20; height = 20;
				}
				if (i == 2)
				{
					x = 192 + (i * 38); y = GetWindowsY - 27; width = 20; height = 20;
				}
				RenderItem3D(GetCenterX(640) + x, y, width, height, pItem->Type, pItem->Level, 0, 0);
			}
		}
	}
}

void SEASON3B::CNewUIItemHotKey::RenderItemCount()
{
	float x, y, width, height;

	glColor4f(1.f, 1.f, 1.f, 1.f);

	for(int i=0; i<HOTKEY_COUNT; ++i)
	{
		int iCount = GetHotKeyItemIndex(i, true);
		if(iCount > 0)
		{
			if (i == 0)
			{
				x = 221 + (i * 38); y = GetWindowsY - 34; width = 20; height = 20;
			}
			if (i == 1)
			{
				x = 214 + (i * 38); y = GetWindowsY - 34; width = 20; height = 20;
			}
			if (i == 2)
			{
				x = 207 + (i * 38); y = GetWindowsY - 34; width = 20; height = 20;
			}

			glColor3f(0.91000003, 0.81, 0.60000002);

			GWidescreen.RenderNumbers(GetCenterX(640) + x, y, iCount, 5.0, 6.0);
		}
	}
}

void SEASON3B::CNewUIItemHotKey::UseItemRButton()
{
	int x, y, width, height;

	for(int i=0; i<HOTKEY_COUNT; ++i)
	{
		if (i == 0)
		{
			x = 227 + (i * 38) - 20; y = GetWindowsY - 34; width = 20; height = 20;
		}
		if (i == 1)
		{
			x = 220 + (i * 38) - 20; y = GetWindowsY - 34; width = 20; height = 20;
		}
		if (i == 2)
		{
			x = 213 + (i * 38) - 20; y = GetWindowsY - 34; width = 20; height = 20;
		}

		if(SEASON3B::CheckMouseIn(GetCenterX(640) + x, y, width, height) == true)
		{
			if(MouseRButtonPush)
			{
				MouseRButtonPush = false;
				int iIndex = GetHotKeyItemIndex(i);
				if(iIndex != -1)
				{
					SendRequestUse(iIndex, 0);
					break;
				}
			}
		}
	}	
}

SEASON3B::CNewUISkillList::CNewUISkillList()
{
	m_pNewUIMng = NULL;
	Reset();
}

SEASON3B::CNewUISkillList::~CNewUISkillList()
{
	Release();
}

bool SEASON3B::CNewUISkillList::Create(CNewUIManager* pNewUIMng, CNewUI3DRenderMng* pNewUI3DRenderMng)
{
	if(NULL == pNewUIMng)
		return false;
	
	m_pNewUIMng = pNewUIMng;
	m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_SKILL_LIST, this);

	m_pNewUI3DRenderMng = pNewUI3DRenderMng;

	LoadImages();

	Show(true);

	return true;
}

void SEASON3B::CNewUISkillList::Release()
{
	if(m_pNewUI3DRenderMng)
	{
		m_pNewUI3DRenderMng->DeleteUI2DEffectObject(UI2DEffectCallback);
	}
	
	UnloadImages();

	if(m_pNewUIMng)
	{
		m_pNewUIMng->RemoveUIObj(this);
		m_pNewUIMng = NULL;
	}
}

void SEASON3B::CNewUISkillList::Reset()
{
	m_bSkillList = false;
	m_bHotKeySkillListUp = false;

	m_bRenderSkillInfo = false;
	m_iRenderSkillInfoType = 0;
	m_iRenderSkillInfoPosX = 0 + GetCenterX(640);
	m_iRenderSkillInfoPosY = 0;

	for(int i=0; i<SKILLHOTKEY_COUNT; ++i)
	{
		m_iHotKeySkillType[i] = -1;
	}

	m_EventState = EVENT_NONE;
}

void SEASON3B::CNewUISkillList::LoadImages()
{
	LoadBitmap("Interface\\newui_skill.jpg", IMAGE_SKILL1, GL_LINEAR);
	LoadBitmap("Interface\\newui_skill2.jpg", IMAGE_SKILL2, GL_LINEAR);
	LoadBitmap("Interface\\newui_command.jpg", IMAGE_COMMAND, GL_LINEAR);
	LoadBitmap("Interface\\newui_skillbox.jpg", IMAGE_SKILLBOX, GL_LINEAR);
	LoadBitmap("Interface\\newui_skillbox2.jpg", IMAGE_SKILLBOX_USE, GL_LINEAR);
	LoadBitmap("Interface\\newui_non_skill.jpg", IMAGE_NON_SKILL1, GL_LINEAR);
	LoadBitmap("Interface\\newui_non_skill2.jpg", IMAGE_NON_SKILL2, GL_LINEAR);
	LoadBitmap("Interface\\newui_non_command.jpg", IMAGE_NON_COMMAND, GL_LINEAR);
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	LoadBitmap("Interface\\newui_skill3.jpg", IMAGE_SKILL3, GL_LINEAR);
	LoadBitmap("Interface\\newui_non_skill3.jpg", IMAGE_NON_SKILL3, GL_LINEAR);
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	LoadBitmap("Custom\\NewInterface\\skill_render.tga", SEASON3B::CNewUIMainFrameWindow::IMAGE_CUSTOM_ID + 7, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\Main_Skillbox.tga", SEASON3B::CNewUIMainFrameWindow::IMAGE_CUSTOM_ID + 8, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\btn_close_v2.jpg", 931306, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\btn_repair_v2.jpg", 931307, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\btn_openstore_v2.jpg", 931308, GL_LINEAR);
	LoadBitmap("Custom\\NewInterface\\btn_circle_v2.jpg", 931350, GL_LINEAR);
}

void SEASON3B::CNewUISkillList::UnloadImages()
{
	DeleteBitmap(931306);
	DeleteBitmap(931307);
	DeleteBitmap(931308);
	DeleteBitmap(931350);

	DeleteBitmap(IMAGE_SKILL1);
	DeleteBitmap(IMAGE_SKILL2);
	DeleteBitmap(IMAGE_COMMAND);
	DeleteBitmap(IMAGE_SKILLBOX);
	DeleteBitmap(IMAGE_SKILLBOX_USE);
	DeleteBitmap(IMAGE_NON_SKILL1);
	DeleteBitmap(IMAGE_NON_SKILL2);
	DeleteBitmap(IMAGE_NON_COMMAND);
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	DeleteBitmap(IMAGE_SKILL3);
	DeleteBitmap(IMAGE_NON_SKILL3);
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	DeleteBitmap(SEASON3B::CNewUIMainFrameWindow::IMAGE_CUSTOM_ID + 7);
	DeleteBitmap(SEASON3B::CNewUIMainFrameWindow::IMAGE_CUSTOM_ID + 8);
}

int JCPageSlotSkill = 0;
int JCSkillScale = 0;

bool SEASON3B::CNewUISkillList::UpdateMouseEvent()
{
#ifdef MOD_SKILLLIST_UPDATEMOUSE_BLOCK
	if(GFxProcess::GetInstancePtr()->GetUISelect() == 1)
	{
		return true;
	}
#endif //MOD_SKILLLIST_UPDATEMOUSE_BLOCK

	int JCResto = GWidescreen.JCWinWidthAdd;

	if(g_isCharacterBuff((&Hero->Object), eBuff_DuelWatch))
	{
		m_bSkillList = false;
		return true;
	}

	BYTE bySkillNumber = CharacterAttribute->SkillNumber;
	BYTE bySkillMasterNumber = CharacterAttribute->SkillMasterNumber;

	float x, y, width, height;

	m_bRenderSkillInfo = false;

	if(bySkillNumber <= 0)
	{
		return true;
	}

	x = 310.0f + JCResto;
	y = setPosDown(447.05);
	width = 20.0;
	height = 28.0;

	if (m_EventState == EVENT_NONE && MouseLButtonPush == false && SEASON3B::CheckMouseIn(x, y, width, height) == true)
	{
		m_EventState = EVENT_BTN_HOVER_CURRENTSKILL;
		return true;
	}
	if (m_EventState == EVENT_BTN_HOVER_CURRENTSKILL && MouseLButtonPush == false && SEASON3B::CheckMouseIn(x, y, width, height) == false)
	{
		m_EventState = EVENT_NONE;
		return true;
	}
	if (m_EventState == EVENT_BTN_HOVER_CURRENTSKILL && (MouseLButtonPush == true || MouseLButtonDBClick == true) && SEASON3B::CheckMouseIn(x, y, width, height) == true)
	{
		m_EventState = EVENT_BTN_DOWN_CURRENTSKILL;
		return false;
	}
	if(m_EventState == EVENT_BTN_DOWN_CURRENTSKILL)
	{
		if(MouseLButtonPush == false && MouseLButtonDBClick == false)
		{
			if(SEASON3B::CheckMouseIn(x, y, width, height) == true)
			{		
				m_bSkillList = !m_bSkillList;
				PlayBuffer(SOUND_CLICK01);
				m_EventState = EVENT_NONE;
				return false;
			}
			m_EventState = EVENT_NONE;
			return true;
		}
		
	}
	
	if(m_EventState == EVENT_BTN_HOVER_CURRENTSKILL)
	{
		m_bRenderSkillInfo = true;
		m_iRenderSkillInfoType = Hero->CurrentSkill;
		m_iRenderSkillInfoPosX = x - 5;
		m_iRenderSkillInfoPosY = y;
		
		return false;
	}
	else if(m_EventState == EVENT_BTN_DOWN_CURRENTSKILL)
	{
		return false;
	}
	
	x = 222.0 + JCResto;
	y = setPosDown(490.0);
	width = 160.f;
	height = 38.f;

	if (m_EventState == EVENT_NONE && MouseLButtonPush == false && SEASON3B::CheckMouseIn(x, y, width, height) == true)
	{
		m_EventState = EVENT_BTN_HOVER_SKILLHOTKEY;
		return true;
	}
	if(m_EventState == EVENT_BTN_HOVER_SKILLHOTKEY && MouseLButtonPush == false
		&& SEASON3B::CheckMouseIn(x, y, width, height) == false)
	{
		m_EventState = EVENT_NONE;
		return true;
	}
	if (m_EventState == EVENT_BTN_HOVER_SKILLHOTKEY && MouseLButtonPush == true && SEASON3B::CheckMouseIn(x, y, width, height) == true)
	{
		m_EventState = EVENT_BTN_DOWN_SKILLHOTKEY;
		return false;
	}
	
	x = 190.0 + JCResto; y = setPosDown(490.0); width = 32.f; height = 0.f;

	int iStartIndex = (m_bHotKeySkillListUp == true) ? 6 : 1;

	for(int i=0, iIndex = iStartIndex; i<0; ++i, iIndex++)
	{
		x += width;

		if(iIndex == 10)
		{
			iIndex = 0;
		}
		if(SEASON3B::CheckMouseIn(x, y, width, height) == true)
		{
			if(m_iHotKeySkillType[iIndex] == -1)
			{
				if(m_EventState == EVENT_BTN_HOVER_SKILLHOTKEY)
				{
					m_bRenderSkillInfo = false;
					m_iRenderSkillInfoType = -1;
				}
				if(m_EventState == EVENT_BTN_DOWN_SKILLHOTKEY && MouseLButtonPush == false)
				{
					m_EventState = EVENT_NONE;
				}
				continue;
			}

			WORD bySkillType = CharacterAttribute->Skill[m_iHotKeySkillType[iIndex]];

			if(bySkillType == 0 || ( bySkillType >= AT_SKILL_STUN && bySkillType <= AT_SKILL_REMOVAL_BUFF ))
				continue;

			BYTE bySkillUseType = SkillAttribute[bySkillType].SkillUseType;

			if(bySkillUseType == SKILL_USE_TYPE_MASTERLEVEL)
			{
				continue;
			}

			if(m_EventState == EVENT_BTN_HOVER_SKILLHOTKEY)
			{
				m_bRenderSkillInfo = true;
				m_iRenderSkillInfoType = m_iHotKeySkillType[iIndex];
				m_iRenderSkillInfoPosX = x - 5;
				m_iRenderSkillInfoPosY = y;
				return true;
			}
			if(m_EventState == EVENT_BTN_DOWN_SKILLHOTKEY)
			{
				if(MouseLButtonPush == false)
				{
					if(m_iRenderSkillInfoType == m_iHotKeySkillType[iIndex])
					{
						m_EventState = EVENT_NONE;
						m_wHeroPriorSkill = CharacterAttribute->Skill[Hero->CurrentSkill];
						Hero->CurrentSkill = m_iHotKeySkillType[iIndex];
						PlayBuffer(SOUND_CLICK01);
						return false;
					}
					else
					{
						m_EventState = EVENT_NONE;
					}
				}
			}
		}
	}
	
	x = 222.f; y =431.f; width = 32.f*5.f; height = 38.f;

	if(m_EventState == EVENT_BTN_DOWN_SKILLHOTKEY)
	{
		if(MouseLButtonPush == false && SEASON3B::CheckMouseIn(x, y, width, height) == false)
		{
			m_EventState = EVENT_NONE;
			return true;	
		}
		return false;
	}
	
	if(m_bSkillList == false)
		return true;
	
	WORD bySkillType = 0;

	int iSkillCount = 0;
	bool bMouseOnSkillList = false;
	
	x = JCResto + 191.0;
	y = setPosDown(349.0);
	width = 24.0;
	height = 29.5;

	float fOrigX = 0;
	
	EVENT_STATE PrevEventState = m_EventState;

	for(int i=0; i<MAX_MAGIC; ++i)
	{
		bySkillType = CharacterAttribute->Skill[i];

		if (bySkillType == 0 || (bySkillType >= AT_SKILL_STUN && bySkillType <= AT_SKILL_REMOVAL_BUFF))
			continue;

		BYTE bySkillUseType = SkillAttribute[bySkillType].SkillUseType;

		if(bySkillUseType == SKILL_USE_TYPE_MASTERLEVEL)
		{
			continue;
		}

		if (iSkillCount == 10)
		{
			y = y + height;
		}

		if (iSkillCount == 20)
		{
			y = y - height;
		}

		if (iSkillCount >= 10 && iSkillCount < 20)
		{
			fOrigX = (iSkillCount - 10) * width + x;
		}
		else if (iSkillCount >= 20)
		{
			fOrigX = (iSkillCount - 20) * width + x;
		}
		else
		{
			fOrigX = (iSkillCount)*width + x;
		}

		iSkillCount++;

		if (JCPageSlotSkill == 0)
		{
			if (iSkillCount >= 21)
				continue;
		}
		else
		{
			if (iSkillCount < 21)
				continue;
		}
		
		if(SEASON3B::CheckMouseIn(fOrigX, y, width, height) == true)
		{
			bMouseOnSkillList = true;
			if(m_EventState == EVENT_NONE && MouseLButtonPush == false)
			{
				m_EventState = EVENT_BTN_HOVER_SKILLLIST;
				break;
			}
		}
		
		if (m_EventState == EVENT_BTN_HOVER_SKILLLIST && MouseLButtonPush == true && SEASON3B::CheckMouseIn(fOrigX, y, width, height) == true)
		{
			m_EventState = EVENT_BTN_DOWN_SKILLLIST;
			break;
		}
		
		if (m_EventState == EVENT_BTN_HOVER_SKILLLIST && MouseLButtonPush == false && SEASON3B::CheckMouseIn(fOrigX, y, width, height) == true)
		{
			m_bRenderSkillInfo = true;
			m_iRenderSkillInfoType = i;
			m_iRenderSkillInfoPosX = fOrigX;
			m_iRenderSkillInfoPosY = y;
		}
		
		if (m_EventState == EVENT_BTN_DOWN_SKILLLIST && MouseLButtonPush == false && m_iRenderSkillInfoType == i && SEASON3B::CheckMouseIn(fOrigX, y, width, height) == true)
		{
			m_EventState = EVENT_NONE;

			m_wHeroPriorSkill = CharacterAttribute->Skill[Hero->CurrentSkill];

			Hero->CurrentSkill = i;
			m_bSkillList = false;
	
			PlayBuffer(SOUND_CLICK01);
			return false;
		}
	}

	if(PrevEventState != m_EventState)
	{
		if(m_EventState == EVENT_NONE || m_EventState == EVENT_BTN_HOVER_SKILLLIST)
			return true;
		return false;
	}

	if(Hero->m_pPet != NULL)
	{
		x = JCResto + 191.0;
		y = setPosDown(379.0);
		width = 24.0;
		height = 38.0;

		for(int i=AT_PET_COMMAND_DEFAULT; i<AT_PET_COMMAND_END; ++i)
		{
			if(SEASON3B::CheckMouseIn(x, y, width, height) == true)
			{
				bMouseOnSkillList = true;
				
				if(m_EventState == EVENT_NONE && MouseLButtonPush == false)
				{
					m_EventState = EVENT_BTN_HOVER_SKILLLIST;
					return true;
				}
				if(m_EventState == EVENT_BTN_HOVER_SKILLLIST && MouseLButtonPush == true)
				{
					m_EventState = EVENT_BTN_DOWN_SKILLLIST;
					return false;
				}
				
				if(m_EventState == EVENT_BTN_HOVER_SKILLLIST)
				{
					m_bRenderSkillInfo = true;
					m_iRenderSkillInfoType = i;
					m_iRenderSkillInfoPosX = x;
					m_iRenderSkillInfoPosY = y;
				}
				if(m_EventState == EVENT_BTN_DOWN_SKILLLIST && MouseLButtonPush == false
					&& m_iRenderSkillInfoType == i)
				{
					m_EventState = EVENT_NONE;

					m_wHeroPriorSkill = CharacterAttribute->Skill[Hero->CurrentSkill];

					Hero->CurrentSkill = i;
					m_bSkillList = false;
					PlayBuffer(SOUND_CLICK01);
					return false;
				}
			}
			x += width;	
		}
	}

	if(bMouseOnSkillList == false && m_EventState == EVENT_BTN_HOVER_SKILLLIST)
	{
		m_EventState = EVENT_NONE;
		return true;
	}
	if(bMouseOnSkillList == false && MouseLButtonPush == false
		&& m_EventState == EVENT_BTN_DOWN_SKILLLIST )
	{
		m_EventState = EVENT_NONE;
		return false;
	}
	if(m_EventState == EVENT_BTN_DOWN_SKILLLIST)
	{
		if(MouseLButtonPush == false)
		{
			m_EventState = EVENT_NONE;
			return true;
		}
		return false;
	}
	
	return true;
}

bool SEASON3B::CNewUISkillList::UpdateKeyEvent()
{
	for(int i=0; i<9; ++i)
	{
		if(SEASON3B::IsPress('1' + i))
		{
			UseHotKey(i+1);
		}
	}

	if(SEASON3B::IsPress('0'))
	{
		UseHotKey(0);
	}

	if(m_EventState == EVENT_BTN_HOVER_SKILLLIST)
	{
		if(SEASON3B::IsRepeat(VK_CONTROL))
		{
			for(int i=0; i<9; ++i)
			{
				if(SEASON3B::IsPress('1' + i))
				{
					SetHotKey(i+1, m_iRenderSkillInfoType);

					return false;
				}
			}

			if(SEASON3B::IsPress('0'))
			{
				SetHotKey(0, m_iRenderSkillInfoType);

				return false;
			}
		}
	}

	if(SEASON3B::IsRepeat(VK_SHIFT))
	{
		for(int i=0; i<4; ++i)
		{
			if(SEASON3B::IsPress('1' + i))
			{
				Hero->CurrentSkill = AT_PET_COMMAND_DEFAULT + i;
				return false;
			}
		}
	}
		
	return true;
}

bool SEASON3B::CNewUISkillList::IsArrayUp(BYTE bySkill)
{
	for(int i=0; i<SKILLHOTKEY_COUNT; ++i)
	{
		if(m_iHotKeySkillType[i] == bySkill)
		{
			if(i == 0 || i > 5)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

bool SEASON3B::CNewUISkillList::IsArrayIn(BYTE bySkill)
{
	for(int i=0; i<SKILLHOTKEY_COUNT; ++i)
	{
		if(m_iHotKeySkillType[i] == bySkill)
		{
			return true;
		}
	}

	return false;
}

void SEASON3B::CNewUISkillList::SetHotKey(int iHotKey, int iSkillType)
{
	for(int i=0; i<SKILLHOTKEY_COUNT; ++i)
	{
		if(m_iHotKeySkillType[i] == iSkillType)
		{
			m_iHotKeySkillType[i] = -1;
			break;
		}
	}	

	m_iHotKeySkillType[iHotKey] = iSkillType;
}

int SEASON3B::CNewUISkillList::GetHotKey(int iHotKey)
{
	return m_iHotKeySkillType[iHotKey];
}

int SEASON3B::CNewUISkillList::GetSkillIndex(int iSkillType)
{
	int iReturn = -1;
	for(int i=0; i<MAX_MAGIC; ++i)
	{
		if(CharacterAttribute->Skill[i] == iSkillType)
		{
			iReturn = i;
			break;
		}
	}

	return iReturn;
}

void SEASON3B::CNewUISkillList::UseHotKey(int iHotKey)
{
	if(m_iHotKeySkillType[iHotKey] != -1)
	{
		if(m_iHotKeySkillType[iHotKey] >= AT_PET_COMMAND_DEFAULT && m_iHotKeySkillType[iHotKey] < AT_PET_COMMAND_END)
		{
			if(Hero->m_pPet == NULL)
			{
				return;
			}
		}

		WORD wHotKeySkill = CharacterAttribute->Skill[m_iHotKeySkillType[iHotKey]];

		if(wHotKeySkill == 0)
		{
			return;
		}

		m_wHeroPriorSkill = CharacterAttribute->Skill[Hero->CurrentSkill];

		Hero->CurrentSkill = m_iHotKeySkillType[iHotKey];

		WORD bySkill = CharacterAttribute->Skill[Hero->CurrentSkill];


        if ( 
			g_pOption->IsAutoAttack() == true
			&& gMapManager.WorldActive != WD_6STADIUM 
			&& gMapManager.InChaosCastle()==false 
			&& ( bySkill == AT_SKILL_TELEPORT || bySkill == AT_SKILL_TELEPORT_B ) )
        {
            SelectedCharacter = -1;
            Attacking = -1;
        }
	}
}

bool SEASON3B::CNewUISkillList::Update()
{
	if(IsArrayIn(Hero->CurrentSkill) == true)
	{
		if(IsArrayUp(Hero->CurrentSkill) == true)
		{
			m_bHotKeySkillListUp = true;
		}
		else
		{
			m_bHotKeySkillListUp = false;
		}
	}

	if(Hero->m_pPet == NULL)
	{
		if(Hero->CurrentSkill >= AT_PET_COMMAND_DEFAULT && Hero->CurrentSkill < AT_PET_COMMAND_END)
		{
			Hero->CurrentSkill = 0;
		}
	}

	return true;
}

void SEASON3B::CNewUISkillList::RenderCurrentSkillAndHotSkillList()
{
	int i;
	float x, y, width, height;
	
	BYTE bySkillNumber = CharacterAttribute->SkillNumber;
	
	if(bySkillNumber > 0)
	{
		int iStartSkillIndex = 1;
		if(m_bHotKeySkillListUp)
		{
			iStartSkillIndex = 6;
		}

		x = setPosMidRight(190.f);; y = setPosDown(431.f); width = 32; height = 38;
		for(i=0; i<0; ++i)
		{
			x += width;
			
			int iIndex = iStartSkillIndex + i;
			if(iIndex == 10)
			{
				iIndex = 0;
			}
			
			if(m_iHotKeySkillType[iIndex] == -1)
			{
				continue;
			}
			
			if(m_iHotKeySkillType[iIndex] >= AT_PET_COMMAND_DEFAULT && m_iHotKeySkillType[iIndex] < AT_PET_COMMAND_END)
			{
				if(Hero->m_pPet == NULL)
				{
					continue;
				}
			}
			
			if(Hero->CurrentSkill == m_iHotKeySkillType[iIndex])
			{
				SEASON3B::RenderImage(IMAGE_SKILLBOX_USE, x, y, width, height);
			}
			RenderSkillIcon(m_iHotKeySkillType[iIndex], x+6, y+6, 20, 28);
		}
		
		x = setPosMidRight(310.5f); y = setPosDown(448.f); width = 20; height = 28;
		RenderSkillIcon(Hero->CurrentSkill, x, y, width, height);
	}
}

bool SEASON3B::CNewUISkillList::Render()
{
	int i;
	float x, y, width, height, x1, y1;
	
	BYTE bySkillNumber = CharacterAttribute->SkillNumber;

	if(bySkillNumber > 0)
	{
		if(m_bSkillList == true)
		{
			int JCResto = GWidescreen.JCWinWidthAdd;

			x = JCResto + 191.0;
			y = setPosDown(349.0);;
			width = 24.0;
			height = 29.5;

			float fOrigX = 0.0;

            int iSkillType  = 0;
			int iSkillCount = 0;

			RenderBitmap(SEASON3B::CNewUIMainFrameWindow::IMAGE_CUSTOM_ID + 7, JCResto + 191.3, setPosDown(350.0), 243.5, 60.0, 0.0, 0.0, 1.0, 1.0, 1, 1, 0);

			for(i=0; i<MAX_MAGIC; ++i)
			{
                iSkillType = CharacterAttribute->Skill[i];
				
				if(iSkillType != 0 && (iSkillType < AT_SKILL_STUN || iSkillType > AT_SKILL_REMOVAL_BUFF))
				{
                    BYTE bySkillUseType = SkillAttribute[iSkillType].SkillUseType;
                  
                    if(bySkillUseType == SKILL_USE_TYPE_MASTER || bySkillUseType == SKILL_USE_TYPE_MASTERLEVEL)
					{
                        continue;
					}

					if(iSkillCount == 10)
					{
						y = y + height;
					}

					if (iSkillCount == 20)
					{
						y = y - height;
					}

					if (iSkillCount >= 10 && iSkillCount < 20)
					{
						fOrigX = (iSkillCount - 10) * width + x;
					}
					else if (iSkillCount >= 20)
					{
						fOrigX = (iSkillCount - 20) * width + x;
					}
					else
					{
						fOrigX = (iSkillCount) * width + x;
					}

					iSkillCount++;

					if (JCPageSlotSkill == 0)
					{
						if (iSkillCount >= 21)
							continue;
					}
					else
					{
						if (iSkillCount < 21)
							continue;
					}

					if(i == Hero->CurrentSkill)
						RenderBitmap(SEASON3B::CNewUIMainFrameWindow::IMAGE_CUSTOM_ID + 8, fOrigX + 4.0, y + 4.0, 20.0f, 24.0f, 0.1600000411f, 0.1000000089f, 0.6397998333f, 0.4179990888f, 1, 1, 0);

					y1 = y + 6.0;
					x1 = fOrigX + 6.0;

					JCSkillScale = 1;
					RenderSkillIcon(i, x1, y1, 20, 28);
					JCSkillScale = 0;
				}
			}
			RenderPetSkill();
		}
	}
	
	if(m_bRenderSkillInfo == true && m_pNewUI3DRenderMng)
	{
		m_pNewUI3DRenderMng->RenderUI2DEffect(INVENTORY_CAMERA_Z_ORDER, UI2DEffectCallback, this, 0, 0);

		m_bRenderSkillInfo = false;
	}

	return true;
}

void SEASON3B::CNewUISkillList::RenderSkillInfo()
{
	::RenderSkillInfo(m_iRenderSkillInfoPosX+15, m_iRenderSkillInfoPosY-40, m_iRenderSkillInfoType);
}

float SEASON3B::CNewUISkillList::GetLayerDepth()
{
	return 5.2f;
}

WORD SEASON3B::CNewUISkillList::GetHeroPriorSkill()
{
	return m_wHeroPriorSkill;
}

void SEASON3B::CNewUISkillList::SetHeroPriorSkill(BYTE bySkill)
{
	m_wHeroPriorSkill = bySkill;
}

void SEASON3B::CNewUISkillList::RenderPetSkill()
{
	if(Hero->m_pPet == NULL)
	{
		return;
	}

	float x, y, width, height, x1, y1;

	int JCResto = GWidescreen.JCWinWidthAdd;

	x = JCResto + 191.0;
	y = setPosDown(379.0);
	width = 24.0;
	height = 38.0;

	for(int i=AT_PET_COMMAND_DEFAULT; i<AT_PET_COMMAND_END; ++i)
	{
		if(i == Hero->CurrentSkill)
			RenderBitmap(SEASON3B::CNewUIMainFrameWindow::IMAGE_CUSTOM_ID + 8, x + 4.0, y + 4.0, 20.0f, 24.0f, 0.1600000411f, 0.1000000089f, 0.6397998333f, 0.4179990888f, 1, 1, 0);

		y1 = y + 6.0;
		x1 = x + 6.0;

		JCSkillScale = 1;
        RenderSkillIcon(i, x1, y1, 20, 28);
		JCSkillScale = 0;
		x = x + width;
	}
}

void SEASON3B::CNewUISkillList::RenderSkillIcon(int iIndex, float x, float y, float width, float height)
{
	WORD bySkillType = CharacterAttribute->Skill[iIndex];

	if(bySkillType == 0)
	{
		return;
	}

	if(iIndex >= AT_PET_COMMAND_DEFAULT)
    {
        bySkillType = iIndex;
    }

	bool bCantSkill = false;

    BYTE bySkillUseType = SkillAttribute[bySkillType].SkillUseType;
	int Skill_Icon = SkillAttribute[bySkillType].Magic_Icon;

 	if( !gSkillManager.DemendConditionCheckSkill(bySkillType))
 	{
		bCantSkill = true;
	}

	if(IsCanBCSkill(bySkillType) == false)
	{
		bCantSkill = true;
	}
	if( g_isCharacterBuff((&Hero->Object), eBuff_AddSkill) && bySkillUseType == SKILL_USE_TYPE_BRAND )
	{
		bCantSkill = true;
	}

	if(bySkillType == AT_SKILL_SPEAR && ( Hero->Helper.Type<MODEL_HELPER+2 || Hero->Helper.Type>MODEL_HELPER+3 ) && Hero->Helper.Type != MODEL_HELPER+37)
	{
		bCantSkill = true;
	}

	if(bySkillType == AT_SKILL_SPEAR && (Hero->Helper.Type == MODEL_HELPER+2 || Hero->Helper.Type == MODEL_HELPER+3	|| Hero->Helper.Type == MODEL_HELPER+37))
	{
		int iTypeL = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
		int iTypeR = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
		if((iTypeL < ITEM_SPEAR || iTypeL >= ITEM_BOW) && (iTypeR < ITEM_SPEAR || iTypeR >= ITEM_BOW))
		{
			bCantSkill = true;
		}
	}

	if (bySkillType >= AT_SKILL_BLOCKING && bySkillType <= AT_SKILL_SWORD5 && (Hero->Helper.Type == MODEL_HELPER + 2 || Hero->Helper.Type == MODEL_HELPER + 3 || Hero->Helper.Type == MODEL_HELPER + 37))
	{
		bCantSkill = true;
	}

	if ((bySkillType == AT_SKILL_ICE_BLADE || (AT_SKILL_POWER_SLASH_UP <= bySkillType && AT_SKILL_POWER_SLASH_UP + 4 >= bySkillType)) && (Hero->Helper.Type == MODEL_HELPER + 2 || Hero->Helper.Type == MODEL_HELPER + 3 || Hero->Helper.Type == MODEL_HELPER + 37))
	{
		bCantSkill = true;
	}
                   
    int iEnergy = CharacterAttribute->Energy+CharacterAttribute->AddEnergy;

    if(g_csItemOption.IsDisableSkill(bySkillType, iEnergy))
	{
		bCantSkill = true;
	}

    if(bySkillType == AT_SKILL_PARTY_TELEPORT && PartyNumber <= 0)
    {
		bCantSkill = true;
    }

	if (bySkillType == AT_SKILL_PARTY_TELEPORT && (IsDoppelGanger1() || IsDoppelGanger2() || IsDoppelGanger3() || IsDoppelGanger4()))
	{
		bCantSkill = true;
	}

	if(bySkillType == AT_SKILL_DARK_HORSE || (AT_SKILL_ASHAKE_UP <= bySkillType && bySkillType <= AT_SKILL_ASHAKE_UP+4))
	{
		BYTE byDarkHorseLife = 0;
		byDarkHorseLife = CharacterMachine->Equipment[EQUIPMENT_HELPER].Durability;
		if(byDarkHorseLife == 0)
		{
			if (Hero->Helper.Type != MODEL_HELPER + 4)
			{
				bCantSkill = true;
			}

			if (!gHelperSystem.CheckHelperType(Hero->Helper.Type, 16))
			{
				bCantSkill = true;
			}

		}
	}
#ifdef PJH_FIX_SPRIT
/*������*/
	if( bySkillType>=AT_PET_COMMAND_DEFAULT && bySkillType<AT_PET_COMMAND_END )
	{
		int iCharisma = CharacterAttribute->Charisma+CharacterAttribute->AddCharisma;
		PET_INFO PetInfo;
		giPetManager::GetPetInfo(PetInfo, 421-PET_TYPE_DARK_SPIRIT);
		int RequireCharisma = (185+(PetInfo.m_wLevel*15));
		if( RequireCharisma > iCharisma ) 
		{
			bCantSkill = true;
		}
	}
#endif //PJH_FIX_SPRIT
	if( (bySkillType == AT_SKILL_INFINITY_ARROW) || (bySkillType == AT_SKILL_SWELL_OF_MAGICPOWER))
	{
		if(g_csItemOption.IsDisableSkill(bySkillType, iEnergy))
		{
			bCantSkill = true;
		}
		if( ( g_isCharacterBuff((&Hero->Object), eBuff_InfinityArrow) )	|| ( g_isCharacterBuff((&Hero->Object), eBuff_SwellOfMagicPower)))
		{
			bCantSkill = true;
		}
	}

	if( bySkillType == AT_SKILL_REDUCEDEFENSE || (AT_SKILL_BLOOD_ATT_UP <= bySkillType && bySkillType <= AT_SKILL_BLOOD_ATT_UP+4))
	{
		DWORD Strength;
		const WORD wRequireStrength = 596;
		Strength = CharacterAttribute->Strength + CharacterAttribute->AddStrength;
		if(Strength < wRequireStrength)
		{
			bCantSkill = true;
		}
		int iTypeL = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
		int iTypeR = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
		
		if ( !( iTypeR!=-1 && ( iTypeR<ITEM_STAFF || iTypeR>=ITEM_STAFF+MAX_ITEM_INDEX ) &&	( iTypeL<ITEM_STAFF || iTypeL>=ITEM_STAFF+MAX_ITEM_INDEX ) ) )
		{
			bCantSkill = true;
		}
	}
	
	switch( bySkillType )
	{
	//case AT_SKILL_PIERCING:
	case AT_SKILL_PARALYZE:
		{
			DWORD  Dexterity;
			const WORD wRequireDexterity = 646;
			Dexterity = CharacterAttribute->Dexterity + CharacterAttribute->AddDexterity;
			if(Dexterity < wRequireDexterity)
			{
				bCantSkill = true;
			}
		}break;
	}

	if( bySkillType == AT_SKILL_WHEEL || (AT_SKILL_TORNADO_SWORDA_UP <= bySkillType && bySkillType <= AT_SKILL_TORNADO_SWORDA_UP+4)	|| (AT_SKILL_TORNADO_SWORDB_UP <= bySkillType && bySkillType <= AT_SKILL_TORNADO_SWORDB_UP+4)
		)
	{
		int iTypeL = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
		int iTypeR = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
		
		if ( !( iTypeR!=-1 && ( iTypeR<ITEM_STAFF || iTypeR>=ITEM_STAFF+MAX_ITEM_INDEX ) && ( iTypeL<ITEM_STAFF || iTypeL>=ITEM_STAFF+MAX_ITEM_INDEX ) ) )
		{
			bCantSkill = true;
		}
	}

	if(gMapManager.InChaosCastle() == true)
	{
		if( bySkillType == AT_SKILL_DARK_HORSE || bySkillType == AT_SKILL_RIDER	|| (bySkillType >= AT_PET_COMMAND_DEFAULT && bySkillType <= AT_PET_COMMAND_TARGET) ||(AT_SKILL_ASHAKE_UP <= bySkillType && bySkillType <= AT_SKILL_ASHAKE_UP+4))
		{
			bCantSkill = true;
		}
	}
	else
	{
		if(bySkillType == AT_SKILL_DARK_HORSE || (AT_SKILL_ASHAKE_UP <= bySkillType && bySkillType <= AT_SKILL_ASHAKE_UP+4))
		{
			BYTE byDarkHorseLife = 0;
			byDarkHorseLife = CharacterMachine->Equipment[EQUIPMENT_HELPER].Durability;
			if(byDarkHorseLife == 0) 
			{
				bCantSkill = true;
			}
		}
	}

	int iCharisma = CharacterAttribute->Charisma+CharacterAttribute->AddCharisma;

	if(g_csItemOption.IsDisableSkill(bySkillType, iEnergy, iCharisma))
	{
		bCantSkill = true;
	}

#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if(!g_CMonkSystem.IsSwordformGlovesUseSkill(bySkillType))
	{
		bCantSkill = true;
	}
	if(g_CMonkSystem.IsRideNotUseSkill(bySkillType, Hero->Helper.Type))
	{
		bCantSkill = true;
	}

	ITEM* pLeftRing = &CharacterMachine->Equipment[EQUIPMENT_RING_LEFT];
	ITEM* pRightRing = &CharacterMachine->Equipment[EQUIPMENT_RING_RIGHT];
	
	if(g_CMonkSystem.IsChangeringNotUseSkill(pLeftRing->Type, pRightRing->Type, pLeftRing->Level, pRightRing->Level)
		&& (GetBaseClass(Hero->Class) == CLASS_RAGEFIGHTER))
	{
		bCantSkill = true;
	}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	
	float fU, fV;
	int iKindofSkill = 0;
	
	if(g_csItemOption.Special_Option_Check() == false && (bySkillType == AT_SKILL_ICE_BLADE||(AT_SKILL_POWER_SLASH_UP <= bySkillType && AT_SKILL_POWER_SLASH_UP+4 >= bySkillType)))
	{
		bCantSkill = true;
	}

	if(g_csItemOption.Special_Option_Check(1) == false && (bySkillType == AT_SKILL_CROSSBOW||(AT_SKILL_MANY_ARROW_UP <= bySkillType && AT_SKILL_MANY_ARROW_UP+4 >= bySkillType)))
		bCantSkill = true;

	if(bySkillType >= AT_PET_COMMAND_DEFAULT && bySkillType <= AT_PET_COMMAND_END)
    {
		fU = ((bySkillType - AT_PET_COMMAND_DEFAULT) % 8) * width / 256.f;
		fV = ((bySkillType - AT_PET_COMMAND_DEFAULT) / 8) * height / 256.f;
		iKindofSkill = KOS_COMMAND;
    }
    else if(bySkillType == AT_SKILL_PLASMA_STORM_FENRIR)
	{
		fU = 4 * width / 256.f;
		fV = 0.f;
		iKindofSkill = KOS_COMMAND;
	}
	else if((bySkillType >= AT_SKILL_ALICE_DRAINLIFE && bySkillType <= AT_SKILL_ALICE_THORNS))
	{
		fU = ((bySkillType - AT_SKILL_ALICE_DRAINLIFE) % 8) * width / 256.f;
		fV = 3 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if(bySkillType >= AT_SKILL_ALICE_SLEEP && bySkillType <= AT_SKILL_ALICE_BLIND)
	{
		fU = ((bySkillType - AT_SKILL_ALICE_SLEEP + 4) % 8) * width / 256.f;
		fV = 3 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if (bySkillType == AT_SKILL_ALICE_BERSERKER)
	{
		fU = 10 * width / 256.f;
		fV = 3 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if (bySkillType >= AT_SKILL_ALICE_WEAKNESS && bySkillType <= AT_SKILL_ALICE_ENERVATION)
	{
		fU = (bySkillType - AT_SKILL_ALICE_WEAKNESS + 8) * width / 256.f;
		fV = 3 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if(bySkillType >= AT_SKILL_SUMMON_EXPLOSION && bySkillType <= AT_SKILL_SUMMON_REQUIEM)
	{
		fU = ((bySkillType - AT_SKILL_SUMMON_EXPLOSION + 6) % 8) * width / 256.f;
		fV = 3 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if (bySkillType == AT_SKILL_SUMMON_POLLUTION)
	{
		fU = 11 * width / 256.f;
		fV = 3 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if (bySkillType == AT_SKILL_BLOW_OF_DESTRUCTION)
	{
		fU = 7 * width / 256.f;
		fV = 2 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if (bySkillType == AT_SKILL_GAOTIC)
	{
		fU = 3 * width / 256.f;
		fV = 8 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if (bySkillType == AT_SKILL_RECOVER)
	{
		fU = 9 * width / 256.f;
		fV = 2 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if (bySkillType == AT_SKILL_MULTI_SHOT)
	{
		if (gCharacterManager.GetEquipedBowType_Skill() == BOWTYPE_NONE)
		{
			bCantSkill = true;
		}

		fU = 0 * width / 256.f;
		fV = 8 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if (bySkillType == AT_SKILL_FLAME_STRIKE)
	{
		int iTypeL = CharacterMachine->Equipment[EQUIPMENT_WEAPON_LEFT].Type;
		int iTypeR = CharacterMachine->Equipment[EQUIPMENT_WEAPON_RIGHT].Type;
		
		if ( !( iTypeR!=-1 && ( iTypeR<ITEM_STAFF || iTypeR>=ITEM_STAFF+MAX_ITEM_INDEX ) &&	( iTypeL<ITEM_STAFF || iTypeL>=ITEM_STAFF+MAX_ITEM_INDEX ) ) )
		{
			bCantSkill = true;
		}

		fU = 1 * width / 256.f;
		fV = 8 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if (bySkillType == AT_SKILL_GIGANTIC_STORM)
	{
		fU = 2 * width / 256.f;
		fV = 8 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if (bySkillType == AT_SKILL_LIGHTNING_SHOCK)
	{
		fU = 2 * width / 256.f;
		fV = 3 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if(AT_SKILL_LIGHTNING_SHOCK_UP <= bySkillType && bySkillType <= AT_SKILL_LIGHTNING_SHOCK_UP+4)
	{
		fU = 6 * width / 256.f;
		fV = 8 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if( bySkillType == AT_SKILL_SWELL_OF_MAGICPOWER )
	{
		fU = 8 * width / 256.f;
		fV = 2 * height / 256.f;
		iKindofSkill = KOS_SKILL2;
	}
	else if(bySkillUseType == 4)
	{
		fU = (width/256.f) * (Skill_Icon%12);
		fV = (height/256.f)*((Skill_Icon/12)+4);
		iKindofSkill = KOS_SKILL2;
	}
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	else if(bySkillType >= AT_SKILL_THRUST)
	{
		fU = ((bySkillType - 260) % 12) * width / 256.f;
		fV = ((bySkillType - 260) / 12) * height / 256.f;
		iKindofSkill = KOS_SKILL3;
	}
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	else if(bySkillType >= 57)
    {
		fU = ((bySkillType - 57) % 8) * width / 256.f;
		fV = ((bySkillType - 57) / 8) * height / 256.f;
		iKindofSkill = KOS_SKILL2;
    }
    else
    {
		fU = ((bySkillType - 1) % 8) * width / 256.f;
		fV = ((bySkillType - 1) / 8) * height / 256.f;
		iKindofSkill = KOS_SKILL1;
    }
	int iSkillIndex = 0;
	switch(iKindofSkill)
	{
	case KOS_COMMAND:
		{
			iSkillIndex = IMAGE_COMMAND;
		}break;
	case KOS_SKILL1:
		{
			iSkillIndex = IMAGE_SKILL1;
		}break;
	case KOS_SKILL2:
		{
			iSkillIndex = IMAGE_SKILL2;
		}break;
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	case KOS_SKILL3:
		{
			iSkillIndex = IMAGE_SKILL3;
		}break;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	}

	if( bCantSkill == true )
	{
#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
		iSkillIndex += 6;
#else //PBG_ADD_NEWCHAR_MONK_SKILL
		iSkillIndex += 5;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL
	}
	
	if( iSkillIndex != 0)
	{
		if (JCSkillScale == 1)
		{
			RenderBitmap(iSkillIndex, x, y, 16.0f, 20.0f, fU, fV, width / 256.f, height / 256.f);
		}
		else
		{
			RenderBitmap(iSkillIndex, x, y, width, height, fU, fV, width / 256.f, height / 256.f);
		}
	}

	int iHotKey = -1;
	for(int i=0; i<SKILLHOTKEY_COUNT; ++i)
	{
		if(m_iHotKeySkillType[i] == iIndex)
		{
			iHotKey = i;
			break;
		}
	}

	if(iHotKey != -1)
	{
		glColor3f(1.f, 0.9f, 0.8f);

		if (JCSkillScale == 1)
		{
			GWidescreen.RenderNumbers(x + 15, y + 15, iHotKey, 6.0, 7.0);
		}
		else
		{
			GWidescreen.RenderNumbers(x + 20, y + 20, iHotKey, 6.0, 7.0);
		}
	}

#ifdef PBG_ADD_NEWCHAR_MONK_SKILL
	if((bySkillType == AT_SKILL_GIANTSWING || bySkillType == AT_SKILL_DRAGON_KICK
		|| bySkillType == AT_SKILL_DRAGON_LOWER) && (bCantSkill))
		return;
#endif //PBG_ADD_NEWCHAR_MONK_SKILL

	if( (bySkillType != AT_SKILL_INFINITY_ARROW) && (bySkillType != AT_SKILL_SWELL_OF_MAGICPOWER))
	{
		if (JCSkillScale == 1)
		{
			RenderSkillDelay(iIndex, x, y, 16.0f, 20.0f);
		}
		else
		{
			RenderSkillDelay(iIndex, x, y, width, height);
		}
	}
}

void SEASON3B::CNewUISkillList::RenderSkillDelay(int iIndex, float x, float y, float width, float height)
{
    int iSkillDelay = CharacterAttribute->SkillDelay[iIndex];
    if ( iSkillDelay > 0 )
    {
        int iSkillType  = CharacterAttribute->Skill[iIndex];
		
		if(iSkillType == AT_SKILL_PLASMA_STORM_FENRIR)
		{
			if(!CheckAttack())
			{
				return;
			}
		}

        int iSkillMaxDelay = SkillAttribute[iSkillType].Delay;
		
        float fPersent = (float)(iSkillDelay/(float)iSkillMaxDelay);
        
		EnableAlphaTest();
        glColor4f(1.f, 0.5f, 0.5f, 0.5f);
        float fdeltaH = height * fPersent;
        RenderColor(x, y+height-fdeltaH, width, fdeltaH);
		EndRenderColor();
    }
}

bool SEASON3B::CNewUISkillList::IsSkillListUp()
{
	return m_bHotKeySkillListUp;
}

void SEASON3B::CNewUISkillList::ResetMouseLButton()
{
	MouseLButton = false;
	MouseLButtonPop = false;
	MouseLButtonPush = false;
}

void SEASON3B::CNewUISkillList::UI2DEffectCallback(LPVOID pClass, DWORD dwParamA, DWORD dwParamB)
{
	if(pClass)
	{
		CNewUISkillList* pSkillList= (CNewUISkillList*)(pClass);
		pSkillList->RenderSkillInfo();
	}
}

void SEASON3B::CNewUIMainFrameWindow::SetPreExp_Wide(__int64 dwPreExp)
{
	m_loPreExp = dwPreExp;
}

void SEASON3B::CNewUIMainFrameWindow::SetGetExp_Wide(__int64 dwGetExp)
{
	m_loGetExp = dwGetExp;

	if(m_loGetExp > 0)
	{
		m_bExpEffect = true;
		m_dwExpEffectTime = timeGetTime();
	}
}

void SEASON3B::CNewUIMainFrameWindow::SetPreExp(DWORD dwPreExp)
{
	m_dwPreExp = dwPreExp;
}

void SEASON3B::CNewUIMainFrameWindow::SetGetExp(DWORD dwGetExp)
{
	m_dwGetExp = dwGetExp;

	if(m_dwGetExp > 0)
	{
		m_bExpEffect = true;
		m_dwExpEffectTime = timeGetTime();
	}
}

void SEASON3B::CNewUIMainFrameWindow::SetBtnState(int iBtnType, bool bStateDown)
{
	switch(iBtnType)
	{
#ifndef PBG_ADD_INGAMESHOP_UI_MAINFRAME
	case MAINFRAME_BTN_PARTCHARGE:
		{
			if(bStateDown) 
			{
				m_BtnCShop.UnRegisterButtonState();
				m_BtnCShop.RegisterButtonState(BUTTON_STATE_UP, IMAGE_MENU_BTN_CSHOP, 2);
				m_BtnCShop.RegisterButtonState(BUTTON_STATE_OVER, IMAGE_MENU_BTN_CSHOP, 3);
				m_BtnCShop.RegisterButtonState(BUTTON_STATE_DOWN, IMAGE_MENU_BTN_CSHOP, 2);
				m_BtnCShop.ChangeImgIndex(IMAGE_MENU_BTN_CSHOP, 2);
			}
			else 
			{
				m_BtnCShop.UnRegisterButtonState();
				m_BtnCShop.RegisterButtonState(BUTTON_STATE_UP, IMAGE_MENU_BTN_CSHOP, 0);
				m_BtnCShop.RegisterButtonState(BUTTON_STATE_OVER, IMAGE_MENU_BTN_CSHOP, 1);
				m_BtnCShop.RegisterButtonState(BUTTON_STATE_DOWN, IMAGE_MENU_BTN_CSHOP, 2);
				m_BtnCShop.ChangeImgIndex(IMAGE_MENU_BTN_CSHOP, 0);
			}
		}
		break;
#endif //defined defined PBG_ADD_INGAMESHOP_UI_MAINFRAME
	case MAINFRAME_BTN_CHAINFO:
		{
			if(bStateDown)
			{
				m_BtnChaInfo.UnRegisterButtonState();
				m_BtnChaInfo.RegisterButtonState(BUTTON_STATE_UP, IMAGE_MENU_BTN_CHAINFO, 2);
				m_BtnChaInfo.RegisterButtonState(BUTTON_STATE_OVER, IMAGE_MENU_BTN_CHAINFO, 3);
				m_BtnChaInfo.RegisterButtonState(BUTTON_STATE_DOWN, IMAGE_MENU_BTN_CHAINFO, 2);
				m_BtnChaInfo.ChangeImgIndex(IMAGE_MENU_BTN_CHAINFO, 2);
				
			}
			else
			{
				m_BtnChaInfo.UnRegisterButtonState();
				m_BtnChaInfo.RegisterButtonState(BUTTON_STATE_UP, IMAGE_MENU_BTN_CHAINFO, 0);
				m_BtnChaInfo.RegisterButtonState(BUTTON_STATE_OVER, IMAGE_MENU_BTN_CHAINFO, 1);
				m_BtnChaInfo.RegisterButtonState(BUTTON_STATE_DOWN, IMAGE_MENU_BTN_CHAINFO, 2);
				m_BtnChaInfo.ChangeImgIndex(IMAGE_MENU_BTN_CHAINFO, 0);
			}
		}
		break;
	case MAINFRAME_BTN_MYINVEN:
		{
			if(bStateDown)
			{
				m_BtnMyInven.UnRegisterButtonState();
				m_BtnMyInven.RegisterButtonState(BUTTON_STATE_UP, IMAGE_MENU_BTN_MYINVEN, 2);
				m_BtnMyInven.RegisterButtonState(BUTTON_STATE_OVER, IMAGE_MENU_BTN_MYINVEN, 3);
				m_BtnMyInven.RegisterButtonState(BUTTON_STATE_DOWN, IMAGE_MENU_BTN_MYINVEN, 2);
				m_BtnMyInven.ChangeImgIndex(IMAGE_MENU_BTN_MYINVEN, 2);
			}
			else
			{
				m_BtnMyInven.UnRegisterButtonState();
				m_BtnMyInven.RegisterButtonState(BUTTON_STATE_UP, IMAGE_MENU_BTN_MYINVEN, 0);
				m_BtnMyInven.RegisterButtonState(BUTTON_STATE_OVER, IMAGE_MENU_BTN_MYINVEN, 1);
				m_BtnMyInven.RegisterButtonState(BUTTON_STATE_DOWN, IMAGE_MENU_BTN_MYINVEN, 2);
				m_BtnMyInven.ChangeImgIndex(IMAGE_MENU_BTN_MYINVEN, 0);
			}
		}
		break;
	case MAINFRAME_BTN_FRIEND:
		{
			if(bStateDown)
			{
				m_BtnGuild.UnRegisterButtonState();
				m_BtnGuild.RegisterButtonState(BUTTON_STATE_UP, IMAGE_MENU_BTN_FRIEND, 2);
				m_BtnGuild.RegisterButtonState(BUTTON_STATE_OVER, IMAGE_MENU_BTN_FRIEND, 3);
				m_BtnGuild.RegisterButtonState(BUTTON_STATE_DOWN, IMAGE_MENU_BTN_FRIEND, 2);
				m_BtnGuild.ChangeImgIndex(IMAGE_MENU_BTN_FRIEND, 2);
			}
			else
			{
				m_BtnGuild.UnRegisterButtonState();
				m_BtnGuild.RegisterButtonState(BUTTON_STATE_UP, IMAGE_MENU_BTN_FRIEND, 0);
				m_BtnGuild.RegisterButtonState(BUTTON_STATE_OVER, IMAGE_MENU_BTN_FRIEND, 1);
				m_BtnGuild.RegisterButtonState(BUTTON_STATE_DOWN, IMAGE_MENU_BTN_FRIEND, 2);
				m_BtnGuild.ChangeImgIndex(IMAGE_MENU_BTN_FRIEND, 0);
			}
		}
		break;
	case MAINFRAME_BTN_WINDOW:
		{
			if(bStateDown)
			{
				m_BtnParty.UnRegisterButtonState();
				m_BtnParty.RegisterButtonState(BUTTON_STATE_UP, IMAGE_MENU_BTN_WINDOW, 2);
				m_BtnParty.RegisterButtonState(BUTTON_STATE_OVER, IMAGE_MENU_BTN_WINDOW, 3);
				m_BtnParty.RegisterButtonState(BUTTON_STATE_DOWN, IMAGE_MENU_BTN_WINDOW, 2);
				m_BtnParty.ChangeImgIndex(IMAGE_MENU_BTN_WINDOW, 2);
			}
			else
			{
				m_BtnParty.UnRegisterButtonState();
				m_BtnParty.RegisterButtonState(BUTTON_STATE_UP, IMAGE_MENU_BTN_WINDOW, 0);
				m_BtnParty.RegisterButtonState(BUTTON_STATE_OVER, IMAGE_MENU_BTN_WINDOW, 1);
				m_BtnParty.RegisterButtonState(BUTTON_STATE_DOWN, IMAGE_MENU_BTN_WINDOW, 2);
				m_BtnParty.ChangeImgIndex(IMAGE_MENU_BTN_WINDOW, 0);
			}
		}
		break;
	}
}
