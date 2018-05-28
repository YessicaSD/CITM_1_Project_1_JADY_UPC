#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_MUSICS 8
#define MAX_SOUNDEFECTS 60


typedef struct _Mix_Music Mix_Music;


//This struct makes not repeating sfx easier

enum Audio_State {
	PLAY_AUDIO,
	STOP_AUDIO, 
};

struct Music {
	int id = 0;
	Mix_Music * audio = nullptr;
	bool hasPlayed = false;
	
};

struct Sfx {
	int id = 0;
	Mix_Chunk *audio = nullptr;
	bool hasPlayed = false;
};


class ModuleAudio : public Module {
public:
	ModuleAudio();
	~ModuleAudio();
	
	bool Init();
	update_status LogicUpdate();
	bool CleanUp();

	Sfx*  LoadSFX(const char* path);
	Music*  LoadMUS(const char* path);

	void ControlAudio (Music* music, Audio_State state);
	void ControlAudio(Sfx* chunk, Audio_State state);

	void UnloadMUS(Music* music);
	void UnloadSFX(Sfx* chunk);

private: 

	Music* musics[MAX_MUSICS];
	Sfx* sfx[MAX_SOUNDEFECTS];
	int volumeMUS = GENERAL_MUSIC_VOLUME;
	int volumeSFX= GENERAL_SFX_VOLUME;

};


#endif // __ModuleAudio_H__
