#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "fmod.hpp"

class SoundManager
{
public:
	static SoundManager& GetInstance();
	~SoundManager();
	static void DestroyInstance();

	void Initialise();

	void Update();

	void PlaySoundGoreHit();
	void PlaySoundImpact();
	void PlaySoundPistolHandling();
	void PlaySoundPistolShoot();
	void PlayCasingSound();

private:
	SoundManager();
	SoundManager(const SoundManager& soundManager);
	SoundManager& operator=(const SoundManager& soundManager);

protected:
	static SoundManager* sm_pInstance;

	FMOD_RESULT result;
	FMOD::System* soundSystem = 0;
	FMOD::Channel* channel = 0;
	void* extradriverdata = 0;

	FMOD::Sound *gore_hit_1, *gore_hit_2, *gore_hit_3, *gore_hit_4,
		*impact_1, *impact_2, *impact_3,
		*pistol_handling, *pistol_shoot,
		*casing_1, *casing_2, *casing_3, *casing_4;

};

#endif

