#include "Sound.h"

void Sound::playersound() {
	PlaySound(TEXT("Sounds/viper.wav"), NULL, SND_FILENAME |SND_NOSTOP| SND_ASYNC);

}
