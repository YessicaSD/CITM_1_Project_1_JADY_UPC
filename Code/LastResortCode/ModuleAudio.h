#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_MUSICS 3
#define MAX_SOUNDEFECTS 20

typedef struct _Mix_Music Mix_Music;

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
	bool CleanUp();

	Mix_Chunk* const LoadSFX(const char* path);
	Mix_Music* const LoadMUS(const char* path);
	bool ControlMUS (Mix_Music* music, Audio_State state);
	bool ControlSFX(Mix_Chunk* chunk, Audio_State state);
	bool UnloadMUS(Mix_Music* music);
	bool UnloadSFX(Mix_Chunk* chunk);
private: 

	Mix_Music* musics[MAX_MUSICS];
	Mix_Chunk* sfx[MAX_SOUNDEFECTS];
	uint last_chunk = 0;
	uint last_music = 0;
};


#endif // __ModuleAudio_H__
