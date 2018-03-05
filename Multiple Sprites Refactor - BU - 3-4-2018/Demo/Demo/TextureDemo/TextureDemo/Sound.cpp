#include "Sound.h"

void Sound::playersound(float playerspeed) {
	if(playerspeed > 0){
		PlaySound(TEXT("Sounds/viper.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);
	}
	if (playerspeed == 0) {
		PlaySound(NULL, NULL, 0);
	}

}
