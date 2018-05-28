#include "Globals.h"
#include "Application.h"
#include "Module.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


ModuleAudio::ModuleAudio() : Module()
{
	for (uint i = 0; i < MAX_MUSICS; ++i)
		musics[i] = nullptr;
	for (uint i = 0; i < MAX_SOUNDEFECTS; ++i)
		sfx[i] = nullptr;
}

ModuleAudio::~ModuleAudio() {
	Mix_CloseAudio();
	Mix_Quit();
}

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

	else {
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		Mix_VolumeMusic(GENERAL_MUSIC_VOLUME);
		
	}


	return ret;
}

update_status ModuleAudio::LogicUpdate() {

	if (App->input->keyboard[SDL_SCANCODE_KP_PLUS] == KEY_STATE::KEY_DOWN) {
		volumeMUS += 5;
		if (volumeMUS > 180) {
			volumeMUS = 180;
		}	
		Mix_VolumeMusic(volumeMUS);
	}
	if (App->input->keyboard[SDL_SCANCODE_KP_MINUS] == KEY_STATE::KEY_DOWN) {
		volumeMUS -= 5;
		if (volumeMUS < 0) {
			volumeMUS = 0;
		}
		Mix_VolumeMusic(volumeMUS);
	}
	return UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp()
{
	LOG("Freeing audios and Mixer library and shutdown mixer");

	for (uint i = 0; i < MAX_SOUNDEFECTS; ++i) {
		if (sfx[i] != nullptr) {

			Mix_FreeChunk(sfx[i]->audio);
			delete sfx[i];
			sfx[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_MUSICS; ++i) {
		if (musics[i] != nullptr) {

			Mix_FreeMusic(musics[i]->audio);
			delete musics[i];
			musics[i] = nullptr;
		}
	}


	return true;
}


Music*  ModuleAudio::LoadMUS(const char* path) {

	Mix_Music *music = nullptr;

	music = Mix_LoadMUS(path);

	for (int i = 0; i < MAX_MUSICS; ++i)
	{
		if (musics[i] == nullptr)
		{
			musics[i] = new Music;
			musics[i]->audio = music;
			return musics[i];
		}
	}

	LOG("Unable to load music Mix Error: %s\n", Mix_GetError());
	return nullptr;
}

Sfx*  ModuleAudio::LoadSFX(const char* path) {

	Mix_Chunk *chunk = nullptr;
	chunk = Mix_LoadWAV(path);


	for (int i = 0; i < MAX_SOUNDEFECTS; ++i)
	{
		if (sfx[i] == nullptr)
		{
			sfx[i] = new Sfx;
			sfx[i]->audio = chunk;
			Mix_VolumeChunk(sfx[i]->audio, volumeSFX);
			return sfx[i];
		}
	}

	LOG("Unable to load music Mix Error: %s\n", Mix_GetError());
	return nullptr;
}


void ModuleAudio::UnloadMUS(Music * music) {


	bool unloaded = false;

	for (int i = 0; i < MAX_MUSICS; ++i)
	{
		if (musics[i] == music && music != nullptr)
		{
			Mix_FreeMusic(musics[i]->audio);
			delete musics[i];
			musics[i] = nullptr;
			unloaded = true;
			break;
		}
	}

	if (unloaded == false) {
		LOG("Cannot unload music Error: Music Not Found");
	}

}

void ModuleAudio::UnloadSFX(Sfx * sound_fx) {

	bool unloaded = false;

	for (int i = 0; i < MAX_MUSICS; ++i)
	{
		if (sfx[i] == sound_fx && sound_fx != nullptr)
		{
			Mix_FreeChunk(sfx[i]->audio);
			delete sfx[i];
			sfx[i] = nullptr;
			unloaded = true;
			break;
		}
	}

	if (unloaded == false) {
		LOG("Cannot unload sfx Error: Music Not Found");
	}
}


void ModuleAudio::ControlAudio(Music* music, Audio_State state) {


	for (uint i = 0; i < MAX_MUSICS; ++i) {

		if (musics[i] == music && music != nullptr) {

			switch (state)
			{
			case PLAY_AUDIO:
				if (!Mix_PlayingMusic())
					Mix_PlayMusic(musics[i]->audio, 3);
				else
					LOG("Music is already playing");
				break;
			case STOP_AUDIO:
				if (!Mix_PausedMusic())
					Mix_PauseMusic();
				break;
			}
			break;
		}
		
	}
}

void ModuleAudio::ControlAudio(Sfx* chunk, Audio_State state) {


	for (uint i = 0; i < MAX_SOUNDEFECTS; ++i) {

		if (sfx[i] == chunk && chunk != nullptr) {

			switch (state)
			{
			case PLAY_AUDIO:

				if (Mix_PlayChannel(-1, sfx[i]->audio, 0) == -1) {
					LOG("Unable to play SFX Mix Error: %s\n", Mix_GetError());
				}

				break;

			case STOP_AUDIO:

				break;
			}
			break;
		}
	}
}
