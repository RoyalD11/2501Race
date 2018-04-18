#include "Sound.h"

void Sound::playersound(float playerspeed) {
	if(playerspeed > 0){
		PlaySound(TEXT("Sounds/viper.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);
	}
	if (playerspeed == 0) {
		PlaySound(NULL, NULL, 0);
	}

}

void Sound::playSound(int state) {


	switch (state) {
	case 0:
		PlaySound(TEXT("Sounds/MenuMusic.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);
		break;
	case 1:
		PlaySound(NULL, NULL, 0);
		break;
	case 2:
		break;
	case 3:
		PlaySound(TEXT("Sounds/pew.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 4:
		PlaySound(TEXT("Sounds/Cha-Ching-[AudioTrimmer.com].wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	}
	
}