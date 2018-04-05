#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


ModuleAudio::ModuleAudio() : Module()
{
	
	//for (uint i = 0; i < MAX_MUSICS; ++i)
	//	musics[i] = nullptr;
	//for (uint i = 0; i < MAX_SOUNDEFECTS; ++i)
	//	sfx[i] = nullptr;

	musics = new Music[MAX_MUSICS];
	sfx = new Sfx[MAX_SOUNDEFECTS];
}

ModuleAudio::~ModuleAudio() {}

bool ModuleAudio::Init()
{
	LOG("Init Image library");
	bool ret = true;
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//LoadMUS("Assets/stage1.ogg", "stage1");
	//ControlMUS("stage1", PLAY);

	return ret;
}

bool ModuleAudio::CleanUp()
{
	LOG("Freeing audios and Mixer library and shutdown mixer");

	//for (uint i = 0; i < MAX_SOUNDEFECTS; ++i)
	//	if (sfx[i].chunk != nullptr) {
	//		Mix_FreeChunk(sfx[i].chunk);
	//	}

	//for (uint i = 0; i < MAX_MUSICS; ++i)
	//	if (musics[i].music != nullptr) {
	//		Mix_FreeMusic(musics[i].music);
	//	}
	//

	delete[] musics;
	delete[] sfx;

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

Mix_Chunk* const ModuleAudio::LoadSfx(const char* path, char *name) {

	Mix_Chunk *chunk;

	chunk = Mix_LoadWAV(path);

	if (chunk == NULL)
	{
		LOG("Unable to load sfx Mix Error: %s\n", Mix_GetError());
	}
	else
	{
		sfx[last_chunk].name = name;
		sfx[last_chunk].chunk = chunk;
	}
	return chunk;
}

Mix_Music* const ModuleAudio::LoadMUS(const char* path, char* name) {

	Mix_Music *music = nullptr;

	music = Mix_LoadMUS(path);

	if (music == nullptr)
	{
		LOG("Unable to load music Mix Error: %s\n", Mix_GetError());
	}
	else
	{
		
		musics[last_music].music = music;
		musics[last_music++].name = name;
	}
	return music;
}

void ModuleAudio::ControlMUS(char* name, Audio_State state) {
	
	Mix_Music *music= nullptr;

	for (uint i = 0; i <= last_music; ++i) {
		if (musics[i].name = name) {
			music = musics[i].music;
		}
	}
	

	if (music == nullptr) {
		LOG("Music not found ControlMUS : %s\n", name);
	}
	else {
		switch (state)
		{
		case PLAY:
			if (!Mix_PlayingMusic())
				Mix_PlayMusic(music, 3);
			else
				LOG("Music is already played : %s\n", name);
			break;
		case STOP:
			if (!Mix_PausedMusic())
				Mix_PauseMusic();
			else
				LOG("Music is already stoped : %s\n", name);
			break;

		default:
			break;
		}
	}

}
