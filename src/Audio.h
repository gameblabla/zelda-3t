/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#define FSOUND_FREE 1

class Audio {
    public :
        Audio();
        ~Audio();
        void playSound(int id, int chl = FSOUND_FREE);
        void stopSound();
        void playMusic(int id);
        void stopMusic();
        void replayMusic();
        void playSpecial(int id);
        void stopSpecial();
        void setVolume(int vol);
        void setVolson(int volson);
        bool isSpecial();
    private :
        void loadSounds();
        void freeSounds();
        Mix_Music* choixMusique(int id);
        Mix_Music* choixSpecial(int id);
        
        bool SOUND;
        int previous_volume;
        int previous_volson;
        int volume;
        int musiqueId;
        int specialId;

};

#endif  // Audio.h
