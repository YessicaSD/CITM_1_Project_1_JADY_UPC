#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_MUSICS 10
#define MAX_SOUNDEFECTS 100


typedef struct _Mix_Music Mix_Music;

enum Audio_State {
	PLAY_AUDIO,
	STOP_AUDIO, 
};

struct Music {
	int  id;
	Mix_Music * audio = nullptr;
	bool hasPlayed = false;
	const char* name = nullptr;
	
};

struct Sfx {
	int  id;
	Mix_Chunk *audio = nullptr;
	bool hasPlayed = false;
	const char* name = nullptr;

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

	bool ControlAudio (Music* music, Audio_State state);
	bool ControlAudio(Sfx* chunk, Audio_State state);

	bool UnloadMUS(Music* music);
	bool UnloadSFX(Sfx* chunk);

private: 

	Music* musics[MAX_MUSICS];//Set to nullptr at the constructor
	Sfx* sfx[MAX_SOUNDEFECTS];//Set to nullptr at the constructor
	int volumeMUS = GENERAL_MUSIC_VOLUME;
	int volumeSFX= GENERAL_SFX_VOLUME;
	int sfxID =0;
	int musicID = 0;
};


#endif // __ModuleAudio_H__
