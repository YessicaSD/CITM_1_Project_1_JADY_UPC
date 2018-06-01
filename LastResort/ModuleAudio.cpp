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
			musics[i]->id = musicID;
			++musicID;
			musics[i]->name = path;
			musics[i]->audio = music;
			return musics[i];
		}
	}

	LOG("Cannot load music Mix Error: %s\n", Mix_GetError());
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

			sfx[i]->id = sfxID;
			++sfxID;
			sfx[i]->name = path;
			sfx[i]->audio = chunk;
	
		
			return sfx[i];
		}
	}
	
	LOG("Cannot load music Mix Error: %s\n", Mix_GetError());
	return nullptr;
}


bool ModuleAudio::UnloadMUS(Music * music) {

	if (music == nullptr) {
		return false;
	}

	for ( int i = 0; i < MAX_MUSICS; ++i)
	{
		if (musics[i] != nullptr  && musics[i]->id == music->id )
		{
			LOG(" Unload music ID  %i name: :  %s ", music->id, music->name);
			Mix_FreeMusic(musics[i]->audio);
			delete musics[i];
			musics[i] = nullptr;
			return true;
		}
	}

	if (music != nullptr) {
		LOG("Cannot unload music ID  %i name: :  %s ", music->id, music->name);
	}
	else
		LOG("Cannot unload music Error:  Music* is nullptr");

	return false;
}
	
	


bool ModuleAudio::UnloadSFX(Sfx * sound_fx) {

	if (sound_fx == nullptr) {
		return false;
	}

	for (int i = 0; i < MAX_SOUNDEFECTS; ++i)
	{
		if (sfx[i] != nullptr  && sfx[i] == sound_fx)
		{
			LOG(" Unload sfx ID  %i name: :  %s ", sound_fx->id, sound_fx->name);
			Mix_FreeChunk(sfx[i]->audio);
			delete sfx[i];
			sfx[i] = nullptr;
			return true;
		}

	}

	LOG("Cannot unload sfx Error:	Sfx* is nullptr");

	return false;
}


bool ModuleAudio::ControlAudio(Music* music, Audio_State state) {

	if (music == nullptr) {
		return false;
	}

	for (uint i = 0; i < MAX_MUSICS; ++i) {

		if (musics[i] != nullptr && musics[i]->id == music->id ) {

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

bool ModuleAudio::ControlAudio(Sfx* SFX, Audio_State state) {

	if (SFX == nullptr) {
		return false;
	}

	for (uint i = 0; i < MAX_SOUNDEFECTS; ++i) {

		if (sfx[i] != nullptr && sfx[i]->id == SFX->id) {

			switch (state)
			{
			case PLAY_AUDIO:

				Mix_VolumeChunk(sfx[i]->audio, volumeSFX);
				if (Mix_PlayChannel(-1, sfx[i]->audio, 0) == -1) {
					LOG("Cannot play SFX ID: %i name:  %s  Mix Error: %s\n", sfx[i]->id, sfx[i]->name,  Mix_GetError());
				}

				break;

			case STOP_AUDIO:

				break;
			}
		}
	}
	return true;
}
