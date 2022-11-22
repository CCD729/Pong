#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "GameObject.h"

namespace gm {
	enum SFX {
		goal = 0,
		button = 1,
		bounce = 2
	};
	class SoundManager
	{
	protected:
		sf::SoundBuffer goal, button, bounce;
		sf::Sound sound;
	public:
		SoundManager();
		void PlaySFX(SFX sfx);
		~SoundManager();
	};
}
#endif