#include "Sound.h"
#include <string>
#include <SimpleAudioEngine.h>

Sound::Sound(void)
{

}

void Sound::PlayEffect(const char* a) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(a);
}

void Sound::PlayBackground(string audio) {

}