#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_MUSICS 8
#define MAX_SOUNDEFECTS 50


typedef struct _Mix_Music Mix_Music;

//This struct makes not repeating sfx easier
struct SFX
{
	int position = 0;
	Mix_Chunk * sfx = nullptr;
	bool hasPlayed = false;
};

enum Audio_State {
	PLAY_AUDIO,
	STOP_AUDIO, 
};

//struct Music {
//	Mix_Music * music;
//	char *name;
//};
//
//struct Sfx {
//	Mix_Chunk *chunk;
//	char *name;
//};

class ModuleAudio : public Module {
public:
	ModuleAudio();
	~ModuleAudio();
	
	bool Init();
	update_status LogicUpdate();
	bool CleanUp();

	Mix_Chunk*  LoadSFX(const char* path);
	Mix_Music*  LoadMUS(const char* path);

	void ControlAudio (Mix_Music* music, Audio_State state);
	void ControlAudio(Mix_Chunk* chunk, Audio_State state);

	void UnloadMUS(Mix_Music* music);
	void UnloadSFX(Mix_Chunk* chunk);

private: 

	Mix_Music* musics[MAX_MUSICS];
	Mix_Chunk* sfx[MAX_SOUNDEFECTS];
	int volumeMUS = GENERAL_MUSIC_VOLUME;
	int volumeSFX= GENERAL_SFX_VOLUME;

};


#endif // __ModuleAudio_H__
