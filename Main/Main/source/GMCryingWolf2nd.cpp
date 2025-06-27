
#include "stdafx.h"
#include "UIWindows.h"
#include "ZzzOpenglUtil.h"
#include "zzztexture.h"
#include "ZzzBMD.h"
#include "zzzlodterrain.h"
#include "ZzzScene.h"
#include "zzzEffect.h"
#include "zzzAi.h"
#include "zzzOpenData.h"
#include "MapManager.h"
#include "GMCryingWolf2nd.h"
#include "BoneManager.h"

bool M34CryingWolf2nd::IsCyringWolf2nd()
{ 
	return (gMapManager.WorldActive == WD_35CRYWOLF_2ND) ? true : false; 
}

bool M34CryingWolf2nd::CreateCryingWolf2ndObject(OBJECT* pObject)
{
	if(!IsCyringWolf2nd())
		return false;

	return true;
}
bool M34CryingWolf2nd::MoveCryingWolf2ndObject(OBJECT* pObject)
{
	if(!IsCyringWolf2nd())
		return false;
	
	float Luminosity;
	vec3_t Light;
	
	switch(pObject->Type)
	{
	case 2:
	case 5:
		pObject->HiddenMesh = -2;
		break;
	case 3:
		Luminosity = (float)(rand()%4+3)*0.1f;
		Vector(Luminosity,Luminosity*0.6f,Luminosity*0.2f,Light);
		AddTerrainLight(pObject->Position[0], pObject->Position[1],Light,3,PrimaryTerrainLight);
		pObject->HiddenMesh = -2;
		break;	
	}
	
	return true;
}

bool M34CryingWolf2nd::RenderCryingWolf2ndObjectVisual(OBJECT* pObject, BMD* pModel)
{
	//Select Server
	if (gMapManager.WorldActive == 94)
	{
		switch (pObject->Type)
		{
		case 1:
		{
			pModel->BeginRender(1.0f);
			pObject->HiddenMesh = -2;
			pModel->StreamMesh = 0;
			float v552 = 4000;
			float v551 = ((int)(v552 - timeGetTime() * 0.75f) % 4001) * 0.0002500000118743628;
			pModel->RenderMesh(0, 66, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, v551, -1);
			pModel->StreamMesh = -1;
			pModel->EndRender();
		}
		break;
		case 5:
		{
			pModel->BeginRender(1.0f);
			pModel->StreamMesh = 0;
			pModel->BodyLight[0] = 0.80000001;
			pModel->BodyLight[1] = 0.69999999;
			pModel->BodyLight[2] = 0.30000001;
			pModel->RenderMesh(0, 68, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, BITMAP_CHROME);
			pModel->RenderMesh(23, 66, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, -1);
			pModel->RenderMesh(23, 68, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, BITMAP_CHROME);
			pModel->RenderMesh(24, 66, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, -1);
			pModel->RenderMesh(24, 68, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, BITMAP_CHROME);
			pModel->RenderMesh(25, 66, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, -1);
			pModel->RenderMesh(25, 68, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, BITMAP_CHROME);
			pModel->RenderMesh(26, 66, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, -1);
			pModel->RenderMesh(26, 68, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, BITMAP_CHROME);
			pModel->RenderMesh(27, 66, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, -1);
			pModel->RenderMesh(27, 68, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, BITMAP_CHROME);
			pModel->RenderMesh(28, 66, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, -1);
			pModel->RenderMesh(28, 68, pObject->Alpha, pObject->BlendMesh, pObject->BlendMeshLight, pObject->BlendMeshTexCoordU, pObject->BlendMeshTexCoordV, BITMAP_CHROME);
			pModel->StreamMesh = -1;
			pModel->EndRender();
		}
		break;
		}
	}

	if(!IsCyringWolf2nd())
		return false;

	vec3_t Light;

	switch(pObject->Type)
	{
	case 2:
        if (rand_fps_check(3))
		{
			Vector ( 1.f, 1.f, 1.f, Light );
			CreateParticle ( BITMAP_SMOKE, pObject->Position, pObject->Angle, Light, 21 , pObject->Scale);
		}
		break;
	case 3:
        if (rand_fps_check(2)) {
			Vector ( 1.f, 1.f, 1.f, Light );
			CreateParticle ( BITMAP_TRUE_FIRE, pObject->Position, pObject->Angle, Light, 5, pObject->Scale);
		}
		break;
	case 5:
		{
			Vector ( 1.f, 1.f, 1.f, Light );
        if (rand_fps_check(2)) {
            if ((int)((pObject->Timer += FPS_ANIMATION_FACTOR) + 2) % 4 == 0)
				{
					CreateParticle ( BITMAP_ADV_SMOKE+1, pObject->Position, pObject->Angle, Light );
					CreateParticle ( BITMAP_ADV_SMOKE, pObject->Position, pObject->Angle, Light, 0 );
				}
			}
        if (rand_fps_check(2)) {
            if ((int)(pObject->Timer += FPS_ANIMATION_FACTOR) % 4 == 0)
				{
					CreateParticle ( BITMAP_CLOUD, pObject->Position, pObject->Angle, Light, 6 );
					CreateParticle ( BITMAP_ADV_SMOKE, pObject->Position, pObject->Angle, Light, 1 );
				}
			}
		}
		break;
	case 6:
		{
			Vector ( 1.f, 1.f, 1.f, Light );
			Vector ( 0.2f, 0.2f, 0.2f, Light );

			//CreateParticle ( BITMAP_CLOUD, o->Position, o->Angle, Light, 8, o->Scale);
			if(pObject->HiddenMesh != -2) 
			{
            CreateParticleFpsChecked(BITMAP_CLOUD, pObject->Position, pObject->Angle, Light, 1, pObject->Scale, pObject);
            CreateParticleFpsChecked(BITMAP_CLOUD, pObject->Position, pObject->Angle, Light, 2, pObject->Scale, pObject);
            CreateParticleFpsChecked(BITMAP_CLOUD, pObject->Position, pObject->Angle, Light, 3, pObject->Scale, pObject);
            CreateParticleFpsChecked(BITMAP_CLOUD, pObject->Position, pObject->Angle, Light, 4, pObject->Scale, pObject);
			}
			pObject->HiddenMesh = -2;
			//}
		}
		break;
	}
	
	return true;
}

bool M34CryingWolf2nd::RenderCryingWolf2ndObjectMesh(OBJECT* pObject, BMD* pModel)
{
	if(!IsCyringWolf2nd())
		return false;

	return RenderCryingWolf2ndMonsterObjectMesh(pObject, pModel);
}

CHARACTER* M34CryingWolf2nd::CreateCryingWolf2ndMonster(int iType, int PosX, int PosY, int Key)
{
	if(!IsCyringWolf2nd())
		return false;
	CHARACTER* pCharacter = NULL;
	
	switch(iType)
	{
	case 315:
		{
			OpenMonsterModel(95);
			pCharacter = CreateCharacter(Key,MODEL_MONSTER01+95,PosX,PosY);
			pCharacter->Object.Scale = 1.25f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;

			BoneManager::RegisterBone(pCharacter, "Monster95_Head", 6);
		}
		break;
	case 316:
		{
			OpenMonsterModel(96);
			pCharacter = CreateCharacter(Key,MODEL_MONSTER01+96,PosX,PosY);
			pCharacter->Object.Scale = 1.2f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;

			BoneManager::RegisterBone(pCharacter, "Monster96_Top", 27);
			BoneManager::RegisterBone(pCharacter, "Monster96_Center", 28);
			BoneManager::RegisterBone(pCharacter, "Monster96_Bottom", 29);
		}
		break;
	case 317:
		{
			OpenMonsterModel(97);
			pCharacter = CreateCharacter(Key,MODEL_MONSTER01+97,PosX,PosY);
			pCharacter->Object.Scale = 1.2f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;
		}
		break;
	case 318:
		{
			OpenMonsterModel(98);
			pCharacter = CreateCharacter(Key,MODEL_MONSTER01+98,PosX,PosY);
			pCharacter->Object.Scale = 1.2f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;
		}
		break;
	case 310:
		{
			OpenMonsterModel(91);
			pCharacter = CreateCharacter(Key,MODEL_MONSTER01+91,PosX,PosY);
			pCharacter->Object.Scale = 1.25f;
			pCharacter->Weapon[0].Type = -1;
			pCharacter->Weapon[1].Type = -1;
		}
		break;
	}
	
	return pCharacter;
}

bool M34CryingWolf2nd::MoveCryingWolf2ndMonsterVisual(OBJECT* pObject, BMD* pModel)
{
	if(!IsCyringWolf2nd())
		return false;
	switch(pObject->Type)
	{
	case MODEL_MONSTER01+95:
		{
			vec3_t Position, Light;
			
			if(pObject->CurrentAction != MONSTER01_DIE) {
				Vector ( 0.9f, 0.2f, 0.1f, Light );
				BoneManager::GetBonePosition(pObject, "Monster95_Head", Position);
				CreateSprite(BITMAP_LIGHT,Position,3.5f,Light,pObject);
			}

			Vector ( 0.9f, 0.2f, 0.1f, Light );
			//. Walking & Running Scene Processing
			if(pObject->CurrentAction == MONSTER01_WALK || pObject->CurrentAction == MONSTER01_RUN)
			{
            if (rand_fps_check(10)) {
					CreateParticle ( BITMAP_SMOKE+1, pObject->Position, pObject->Angle, Light );
				}
			}
		}
		break;
	case MODEL_MONSTER01+97:
		{
			vec3_t Position, Position2, Light;
			Vector(0.f, 0.f, 0.f, Position);
			
			if(pObject->CurrentAction == MONSTER01_ATTACK2 && pObject->AnimationFrame >= 4.0f && pObject->AnimationFrame <= 6.0f)
			{
				float Matrix[3][4];
				AngleMatrix(pObject->Angle,Matrix);
				VectorRotate(pObject->Direction,Matrix,Position2);
				VectorAdd(Position,Position2,Position);

				Vector ( 1.f, 0.0f, 0.5f, Light );
                CreateEffect ( MODEL_PIERCING2, pObject->Position, pObject->Angle, Light, 1);
			}
		}
		break;
	case MODEL_MONSTER01+96:
		{
			vec3_t Position, Light;

        auto Rotation = (float)(rand() % 360);
			float Luminosity = sinf(WorldTime*0.0012f)*0.8f+1.3f;
            
			float fScalePercent = 1.f;
			if(pObject->CurrentAction == MONSTER01_ATTACK1 || pObject->CurrentAction == MONSTER01_ATTACK2)
				fScalePercent = .5f;

			BoneManager::GetBonePosition(pObject, "Monster96_Center", Position);
            Vector ( Luminosity*0.f, Luminosity*0.5f, Luminosity*0.1f, Light );
			CreateSprite(BITMAP_LIGHT,Position,fScalePercent,Light,pObject);

            Vector ( 0.5f, 0.5f, 0.5f, Light );
            
			BoneManager::GetBonePosition(pObject, "Monster96_Top", Position);
			CreateSprite(BITMAP_SHINY+1,Position,0.5f*fScalePercent,Light,pObject, Rotation );
            CreateSprite(BITMAP_SHINY+1,Position,0.5f*fScalePercent,Light,pObject, 360.f-Rotation );

			BoneManager::GetBonePosition(pObject, "Monster96_Bottom", Position);
			CreateSprite(BITMAP_SHINY+1,Position,0.5f*fScalePercent,Light,pObject, Rotation );
            CreateSprite(BITMAP_SHINY+1,Position,0.5f*fScalePercent,Light,pObject, 360.f-Rotation );
		}
		break;
	}
	return false;
}
bool M34CryingWolf2nd::RenderCryingWolf2ndMonsterObjectMesh(OBJECT* pObject, BMD* pModel)
{
	return false;
}

bool M34CryingWolf2nd::RenderCryingWolf2ndMonsterVisual(CHARACTER* pCharacter, OBJECT* pObject, BMD* pModel)
{
	return false;
}

void M34CryingWolf2nd::MoveCryingWolf2ndBlurEffect(CHARACTER* pCharacter, OBJECT* pObject, BMD* pModel)
{
	switch(pObject->Type)
	{
	case MODEL_MONSTER01+95:
		{
			if(pObject->CurrentAction == MONSTER01_ATTACK2)
			{
				vec3_t  Light;
				Vector(1.f,1.f,1.f,Light);

				vec3_t StartPos, StartRelative;
				vec3_t EndPos, EndRelative;
				
            float fActionSpeed = pModel->Actions[pObject->CurrentAction].PlaySpeed * static_cast<float>(FPS_ANIMATION_FACTOR);
				float fSpeedPerFrame = fActionSpeed/10.f;
				float fAnimationFrame = pObject->AnimationFrame - fActionSpeed;
				for(int i=0; i<10; i++) {
					pModel->Animation(BoneTransform,fAnimationFrame,pObject->PriorAnimationFrame,pObject->PriorAction, pObject->Angle, pObject->HeadAngle);

					Vector(0.f, 0.f, -90.f, StartRelative);
					Vector(0.f, 0.f, 0.f, EndRelative);
					pModel->TransformPosition(BoneTransform[80],StartRelative,StartPos,false);
					pModel->TransformPosition(BoneTransform[80],EndRelative,EndPos,false);

					CreateBlur(pCharacter,StartPos,EndPos,Light,3,true,80);

					Vector(0.f, 0.f, 90.f, StartRelative);
					Vector(0.f, 0.f, 0.f, EndRelative);
					pModel->TransformPosition(BoneTransform[82],StartRelative,StartPos,false);
					pModel->TransformPosition(BoneTransform[82],EndRelative,EndPos,false);
					
					CreateBlur(pCharacter,StartPos,EndPos,Light,3,true,84);
					
					fAnimationFrame += fSpeedPerFrame;
				}
			}
		}
		break;
	case MODEL_MONSTER01+97:
		{
			if(pObject->CurrentAction == MONSTER01_ATTACK1)
			{
				vec3_t  Light;
				Vector(1.f,1.f,1.f,Light);

				vec3_t StartPos, StartRelative;
				vec3_t EndPos, EndRelative;
				
            float fActionSpeed = pModel->Actions[pObject->CurrentAction].PlaySpeed * static_cast<float>(FPS_ANIMATION_FACTOR);
				float fSpeedPerFrame = fActionSpeed/10.f;
				float fAnimationFrame = pObject->AnimationFrame - fActionSpeed;
				for(int i=0; i<10; i++) {
					pModel->Animation(BoneTransform,fAnimationFrame,pObject->PriorAnimationFrame,pObject->PriorAction, pObject->Angle, pObject->HeadAngle);

					Vector(0.f, 0.f, 120.f, StartRelative);
					Vector(0.f, 0.f, 0.f, EndRelative);
					pModel->TransformPosition(BoneTransform[25],StartRelative,StartPos,false);
					pModel->TransformPosition(BoneTransform[25],EndRelative,EndPos,false);

					CreateBlur(pCharacter,StartPos,EndPos,Light,3,true,25);
					
					fAnimationFrame += fSpeedPerFrame;
				}
			}
		}
		break;
	}
}

bool M34CryingWolf2nd::AttackEffectCryingWolf2ndMonster(CHARACTER* pCharacter, OBJECT* pObject, BMD* pModel)
{
	if(!IsCyringWolf2nd())
		return false;
	
	switch(pObject->Type)
	{
	case MODEL_MONSTER01+96:
		{
        if (pCharacter->CheckAttackTime(14))
			{
				CreateEffect(MODEL_ARROW_NATURE,pObject->Position,pObject->Angle,pObject->Light,1,pObject,pObject->PKKey);
            pCharacter->SetLastAttackEffectTime();
				return true;
			}
		}
		break;
	case MODEL_MONSTER01+91:
		{
        if (pCharacter->CheckAttackTime(14))
			{
				CreateEffect(MODEL_ARROW_HOLY,pObject->Position,pObject->Angle,pObject->Light,1,pObject,pObject->PKKey);
            pCharacter->SetLastAttackEffectTime();
				return true;
			}
		}
		break;
	}
	return false;
}
