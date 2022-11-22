#include "SoundManager.h"
#include <iostream>

using namespace sf;
using namespace gm;

SoundManager::SoundManager() {
    if (!bounce.loadFromFile("Assets/bounce.wav")) {
        // error...
        std::cerr << "Error: Failed to load bounce.wav" << std::endl;
        exit(-1);
    }
    if (!button.loadFromFile("Assets/button.wav")) {
        // error...
        std::cerr << "Error: Failed to load button.wav" << std::endl;
        exit(-1);
    }
    if (!goal.loadFromFile("Assets/goal.wav")) {
        // error...
        std::cerr << "Error: Failed to load goal.wav" << std::endl;
        exit(-1);
    }
}
void SoundManager::PlaySFX(SFX sfx) {
    switch (sfx) {
    case SFX::bounce:
        sound.setBuffer(bounce);
        sound.play();
        break;
    case SFX::button:
        sound.setBuffer(button);
        sound.play();
        break;
    case SFX::goal:
        sound.setBuffer(goal);
        sound.play();
        break;
    }
}
SoundManager::~SoundManager() {

}