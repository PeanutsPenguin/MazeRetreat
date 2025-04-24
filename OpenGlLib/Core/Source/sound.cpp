#include "Core/sound.h"

namespace Sound
{
	SoundEngine::SoundEngine()
	{
		this->engine = irrklang::createIrrKlangDevice();

		this->ambientMusic = engine->addSoundSourceFromFile("Assets/Sound/ambiance.wav");
		this->keysound = engine->addSoundSourceFromFile("Assets/Sound/broken_light.wav");
		this->walkSound = engine->addSoundSourceFromFile("Assets/Sound/footStep.wav");
		this->DoorKnocking = engine->addSoundSourceFromFile("Assets/Sound/door_knocking.wav");
		this->grappleSound = engine->addSoundSourceFromFile("Assets/Sound/enderpearl.wav");
		this->torchLight = engine->addSoundSourceFromFile("Assets/Sound/torchLight.wav");
		this->themeSound = engine->addSoundSourceFromFile("Assets/Sound/horrortheme.wav");

		this->ambientMusic->setDefaultVolume(0.5f);
		this->keysound->setDefaultVolume(6.f);
		this->walkSound->setDefaultVolume(6.f);
	}

}

