#include "SoundManager.h"

#include <cassert>
#include "fmod.hpp"
#include <cstdio>
#include "MyUtility.h"
#include "logmanager.h"
#include <string>

SoundManager* SoundManager::sm_pInstance = 0;


void SoundManager::PlaySoundGoreHit()
{
	int rand = MyUtility::RandomInt(0, 3);
	switch (rand)
	{
	case 0:result = soundSystem->playSound(gore_hit_1, 0, false, &channel);
		break;
	case 1:result = soundSystem->playSound(gore_hit_2, 0, false, &channel);
		break;
	case 2:result = soundSystem->playSound(gore_hit_3, 0, false, &channel);
		break;
	case 3:result = soundSystem->playSound(gore_hit_4, 0, false, &channel);
		break;
	default: result = soundSystem->playSound(pistol_handling, 0, false, &channel);
		break;
	}
}

void SoundManager::PlaySoundImpact()
{
	int rand = MyUtility::RandomInt(0, 2);
	switch (rand)
	{
	case 0:result = soundSystem->playSound(impact_1, 0, false, &channel);
		break;
	case 1:result = soundSystem->playSound(impact_2, 0, false, &channel);
		break;
	case 2:result = soundSystem->playSound(impact_3, 0, false, &channel);
		break;
	default: result = soundSystem->playSound(pistol_handling, 0, false, &channel);
		break;
	}
}

void SoundManager::PlaySoundPistolHandling()
{
	result = soundSystem->playSound(pistol_handling, 0, false, &channel);
}

void SoundManager::PlaySoundPistolShoot()
{
	result = soundSystem->playSound(pistol_shoot, 0, false, &channel);
}

void SoundManager::PlayCasingSound()
{
	int rand = MyUtility::RandomInt(0, 3);
	switch (rand)
	{
	case 0:result = soundSystem->playSound(casing_1, 0, false, &channel);
		break;
	case 1:result = soundSystem->playSound(casing_2, 0, false, &channel);
		break;
	case 2:result = soundSystem->playSound(casing_3, 0, false, &channel);
		break;
	case 3:result = soundSystem->playSound(casing_4, 0, false, &channel);
		break;
	default: result = soundSystem->playSound(casing_4, 0, false, &channel);
		break;
	}
}

SoundManager::SoundManager()
{

}


SoundManager & SoundManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new SoundManager();
	}

	return (*sm_pInstance);
}

SoundManager::~SoundManager()
{

	// TODO: Release sounds
	result = gore_hit_1->release();
	result = gore_hit_2->release();
	result = gore_hit_3->release();
	result = gore_hit_4->release();
	result = impact_1->release();
	result = impact_2->release();
	result = impact_3->release();
	result = pistol_handling->release();
	result = pistol_shoot->release();
	result = casing_1->release();
	result = casing_2->release();
	result = casing_3->release();
	result = casing_4->release();
	result = soundSystem->close();
	result = soundSystem->release();
}

void SoundManager::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

void SoundManager::Initialise()
{
	result = FMOD::System_Create(&soundSystem);      // Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error!");
		//exit(-1);
	}

	result = soundSystem->init(32, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error!");
		//exit(-1);
	}

	// --- CREATE SOUNDS --- //
	result = soundSystem->createSound("..\\bin\\assets\\sound\\gore_hit_1.wav",
		FMOD_CREATESAMPLE, NULL, &gore_hit_1);
	result = soundSystem->createSound("..\\bin\\assets\\sound\\gore_hit_2.wav",
		FMOD_CREATESAMPLE, NULL, &gore_hit_2);
	result = soundSystem->createSound("..\\bin\\assets\\sound\\gore_hit_3.wav",
		FMOD_CREATESAMPLE, NULL, &gore_hit_3);
	result = soundSystem->createSound("..\\bin\\assets\\sound\\gore_hit_4.wav",
		FMOD_CREATESAMPLE, NULL, &gore_hit_4);

	result = soundSystem->createSound("..\\bin\\assets\\sound\\impact_1.wav",
		FMOD_CREATESAMPLE, NULL, &impact_1);
	result = soundSystem->createSound("..\\bin\\assets\\sound\\impact_2.wav",
		FMOD_CREATESAMPLE, NULL, &impact_2);
	result = soundSystem->createSound("..\\bin\\assets\\sound\\impact_3.wav",
		FMOD_CREATESAMPLE, NULL, &impact_3);

	result = soundSystem->createSound("..\\bin\\assets\\sound\\pistol_handling.wav",
		FMOD_CREATESAMPLE, NULL, &pistol_handling);
	result = soundSystem->createSound("..\\bin\\assets\\sound\\pistol_shoot.wav",
		FMOD_CREATESAMPLE, NULL, &pistol_shoot);

	result = soundSystem->createSound("..\\bin\\assets\\sound\\casing_1.wav",
		FMOD_CREATESAMPLE, NULL, &casing_1);
	result = soundSystem->createSound("..\\bin\\assets\\sound\\casing_2.wav",
		FMOD_CREATESAMPLE, NULL, &casing_2);
	result = soundSystem->createSound("..\\bin\\assets\\sound\\casing_3.wav",
		FMOD_CREATESAMPLE, NULL, &casing_3);
	result = soundSystem->createSound("..\\bin\\assets\\sound\\casing_4.wav",
		FMOD_CREATESAMPLE, NULL, &casing_4);
}

void SoundManager::Update()
{
	result = soundSystem->update();
}
