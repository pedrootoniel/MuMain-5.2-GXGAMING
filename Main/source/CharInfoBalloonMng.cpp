//*****************************************************************************
// File: CharInfoBalloonMng.cpp
//
// Desc: implementation of the CCharInfoBalloonMng class.
//
// producer: Ahn Sang-Kyu
//*****************************************************************************

#include "stdafx.h"
#include "CharInfoBalloonMng.h"
#include "CharacterList.h"
#include "CharInfoBalloon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCharInfoBalloonMng::CCharInfoBalloonMng() : m_pCharInfoBalloon(NULL)
{

}

CCharInfoBalloonMng::~CCharInfoBalloonMng()
{
	Release();
}

void CCharInfoBalloonMng::Release()
{
	SAFE_DELETE_ARRAY(m_pCharInfoBalloon);
}

//*****************************************************************************
// �Լ� �̸� : Create()
// �Լ� ���� : ĳ���� ���� ǳ�� �Ŵ��� ����.
//			   (ĳ���� ���þ����� ����. ǳ�� 5�� ����.)
//*****************************************************************************
void CCharInfoBalloonMng::Create()
{
	if (NULL == m_pCharInfoBalloon)
		m_pCharInfoBalloon = new CCharInfoBalloon[gCharacterList.MaxCharacters];

	for (int i = 0; i < gCharacterList.MaxCharacters; ++i)
		m_pCharInfoBalloon[i].Create(&CharactersClient[i]);
}

//*****************************************************************************
// �Լ� �̸� : Render()
// �Լ� ���� : ĳ���� ���� ǳ���� ����.
//*****************************************************************************
void CCharInfoBalloonMng::Render()
{
	if (NULL == m_pCharInfoBalloon)
		return;

	for (int i = 0; i < gCharacterList.MaxCharacters; ++i)
		m_pCharInfoBalloon[i].Render();
}

//*****************************************************************************
// �Լ� �̸� : UpdateDisplay()
// �Լ� ���� : ĳ���� ������ ������Ʈ.
//*****************************************************************************
void CCharInfoBalloonMng::UpdateDisplay()
{
	if (NULL == m_pCharInfoBalloon)
		return;

	for (int i = 0; i < gCharacterList.MaxCharacters; ++i)
		m_pCharInfoBalloon[i].SetInfo();
}