#pragma once

#include "irrKlang.h"
#include "pch.h"

namespace Sound
{
	class SoundEngine
	{
	public:
		SoundEngine();

		irrklang::ISoundSource* ambientMusic;
		irrklang::ISoundSource* walkSound;
		irrklang::ISoundSource* keysound;
		irrklang::ISoundSource* DoorKnocking;
		irrklang::ISoundSource* grappleSound; 
		irrklang::ISoundSource* torchLight;
		irrklang::ISoundSource* themeSound;

		irrklang::ISoundEngine* engine;

		~SoundEngine() = default;
	};
}