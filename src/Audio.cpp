/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "Audio.h"

Mix_Chunk* sfx_id[45];
Mix_Music* music;

Audio::Audio() : volume(0), musiqueId(0), specialId(0) {
    //SOUND = FSOUND_Init(44100, 32, 0);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) 
	{
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	Mix_AllocateChannels(16);
    music = NULL;
    
    if (SOUND) {
        previous_volume = -1;
       // previous_volson = FSOUND_GetSFXMasterVolume();
        loadSounds();
    }
}

Audio::~Audio() {
    if (SOUND) {
        freeSounds();
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		Mix_CloseAudio();
        /*FMUSIC_StopSong(music);
        FMUSIC_SetMasterVolume(music, previous_volume);
        FMUSIC_FreeSong(music);
        FSOUND_SetSFXMasterVolume(previous_volson);
        FSOUND_Close();*/
    }
}

void Audio::setVolume(int vol) {volume=vol*4;
   // if (previous_volume == -1) previous_volume = FMUSIC_GetMasterVolume(music);
   // FMUSIC_SetMasterVolume(music, volume);
    }
void Audio::setVolson(int volson) {
	//FSOUND_SetSFXMasterVolume(volson*4);
	}

void Audio::loadSounds() {
    //sons = new FSOUND_SAMPLE*[44];
    
    sfx_id[0] = Mix_LoadWAV("data/sound/text.ogg"); // lettres
    sfx_id[1] = Mix_LoadWAV("data/sound/menu1.ogg"); // menu 1
    sfx_id[2] = Mix_LoadWAV("data/sound/menu2.ogg"); // menu 2
    sfx_id[3] = Mix_LoadWAV("data/sound/menu3.ogg"); // menu 3
    sfx_id[4] = Mix_LoadWAV("data/sound/menu4.ogg"); // menu 4
    sfx_id[5] = Mix_LoadWAV("data/sound/timewarp.ogg"); // time retour
    sfx_id[6] = Mix_LoadWAV("data/sound/tombe.ogg"); // tombe (ennemi)
    sfx_id[7] = Mix_LoadWAV("data/sound/hitenemy.ogg"); //shot 1
    sfx_id[8] = Mix_LoadWAV("data/sound/killenemy.ogg"); // shot 2
    sfx_id[9] = Mix_LoadWAV("data/sound/surprise.ogg"); // surprise
    sfx_id[10] = Mix_LoadWAV("data/sound/monte.ogg"); // monte
    sfx_id[11] = Mix_LoadWAV("data/sound/descend.ogg"); // descend
    sfx_id[12] = Mix_LoadWAV("data/sound/chute.ogg"); // chute
    sfx_id[13] = Mix_LoadWAV("data/sound/item.ogg"); // item
    sfx_id[14] = Mix_LoadWAV("data/sound/rupee.ogg"); // rubis
    sfx_id[15] = Mix_LoadWAV("data/sound/heart.ogg"); // coeur
    sfx_id[16] = Mix_LoadWAV("data/sound/bomb.ogg"); // bombe
    sfx_id[17] = Mix_LoadWAV("data/sound/textnext.ogg"); // suite texte
    sfx_id[18] = Mix_LoadWAV("data/sound/textend.ogg"); // fin texte
    sfx_id[19] = Mix_LoadWAV("data/sound/happy.ogg"); // trouve objet
    sfx_id[20] = Mix_LoadWAV("data/sound/door.ogg"); // ouvre porte
    sfx_id[21] = Mix_LoadWAV("data/sound/pics.ogg"); // pics contre mur
    sfx_id[22] = Mix_LoadWAV("data/sound/sword.ogg"); // épée
    sfx_id[23] = Mix_LoadWAV("data/sound/SwordCharging.ogg"); // chargée
    sfx_id[24] = Mix_LoadWAV("data/sound/Sword360.ogg"); // spin
    sfx_id[25] = Mix_LoadWAV("data/sound/shoot.ogg"); // flèche
    sfx_id[26] = Mix_LoadWAV("data/sound/hookshot.ogg"); // grappin
    sfx_id[27] = Mix_LoadWAV("data/sound/stamp.ogg"); // pose bombe
    sfx_id[28] = Mix_LoadWAV("data/sound/magic.ogg"); // magie
    sfx_id[29] = Mix_LoadWAV("data/sound/burn.ogg"); // brûle
    sfx_id[30] = Mix_LoadWAV("data/sound/hammer.ogg"); // marteau
    sfx_id[31] = Mix_LoadWAV("data/sound/plouf.ogg"); // plouf
    sfx_id[32] = Mix_LoadWAV("data/sound/danger.ogg"); // danger
    sfx_id[33] = Mix_LoadWAV("data/sound/hurt.ogg"); // link se blesse
    sfx_id[34] = Mix_LoadWAV("data/sound/porte.ogg"); // porte objet
    sfx_id[35] = Mix_LoadWAV("data/sound/lance.ogg"); // lance objet
    sfx_id[36] = Mix_LoadWAV("data/sound/casse.ogg"); // casse objet
    sfx_id[37] = Mix_LoadWAV("data/sound/charge.ogg"); // charge magie
    sfx_id[38] = Mix_LoadWAV("data/sound/buisson.ogg"); // coupe buisson
    sfx_id[39] = Mix_LoadWAV("data/sound/pousse.ogg"); // pousse caisse
    sfx_id[40] = Mix_LoadWAV("data/sound/envol.ogg"); // chant envol
    sfx_id[41] = Mix_LoadWAV("data/sound/inverse.ogg"); // inversé
    sfx_id[42] = Mix_LoadWAV("data/sound/accelere.ogg"); // accéléré
    sfx_id[43] = Mix_LoadWAV("data/sound/splash.ogg"); // ...
    Mix_PlayChannel(-1, sfx_id[0], 0);
}

void Audio::freeSounds() {
	unsigned char i;
	for (i=0;i<44;i++)
	{
		if (sfx_id[i])
		{
			Mix_FreeChunk(sfx_id[i]);
			sfx_id[i] = NULL;
		}
	}
}

void Audio::playSound(int id, int chl) {
    if (SOUND) //Mix_PlayChannel(chl,sfx_id[id],0);
         Mix_PlayChannel(-1, sfx_id[id], 0);
}

void Audio::stopSound() {
    if (SOUND) {Mix_HaltChannel(-1); musiqueId=0;}
}

void Audio::playMusic(int id) {
    if (SOUND) {
        if (id == 2 || id == 5 || id == 7 || id == 8 || id == 9 || id == 14) id = 1;
        if (id == 20 || id == 22 || id == 24) id = 17;
        if (id == 29) id = 19;
        if (id == 32 || id == 34 || id == 35 || id == 39 || id == 44) id = 31;
        if (id >= 61 && id <= 78) id = 61;
        if (id == 82 || id == 84 || id == 94 || id == 98 || id == 99
        || id == 101 || id == 107 || id == 108 || id == 109 || id == 112 
        || id == 117 || id == 118 || id == 122 || id == 128 || id == 129
        || id == 142 || id == 143 || id == 148 || id == 149) id = 81; //magasins
        if (id == 91 || id == 120 || id == 132) id = 85; //potions
        if (id == 102 || id == 136) id = 80; //bar
        if (id == 105 || id == 106 || id == 131 || id == 139 || id == 147) id = 95; //maire
        if (id == 152 || id == 153) id = 151; //temple temps
        if (musiqueId != id) {
            musiqueId = id;            
            if (specialId == 0) {
                Mix_HaltMusic();
				Mix_FreeMusic(music);
                music = choixMusique(id);
               // if (previous_volume == -1) previous_volume = FMUSIC_GetMasterVolume(music);
                Mix_PlayMusic(music, -1);
                specialId = 0;
            }
        }
    }
}

bool Audio::isSpecial() {return (specialId>0);}

void Audio::stopMusic() {
    if (SOUND) Mix_HaltMusic();
}

void Audio::replayMusic() {
    if (SOUND) Mix_PlayMusic(music, -1);
}

Mix_Music* Audio::choixMusique(int id) {
    switch (id) {
        case 1 : case 2 : case 7 : return Mix_LoadMUS("data/music/PlaineP.ogg");
        case 3 : return Mix_LoadMUS("data/music/VilleCP.ogg");
        case 4 : return Mix_LoadMUS("data/music/TerresS.ogg");
        case 6 : return Mix_LoadMUS("data/music/BoisPerdus.ogg");
        case 8 : return Mix_LoadMUS("data/music/CimetiereP.ogg");
        case 10 : return Mix_LoadMUS("data/music/VillageMP.ogg");
        case 11 : return Mix_LoadMUS("data/music/LacP.ogg");
        case 12 : return Mix_LoadMUS("data/music/DesertP.ogg");
        case 13 : return Mix_LoadMUS("data/music/Cocorico.ogg");
        case 15 : return Mix_LoadMUS("data/music/MontP.ogg");
        case 16 : return Mix_LoadMUS("data/music/Foret.ogg");
        case 17 : return Mix_LoadMUS("data/music/Plaine.ogg");
        case 18 : return Mix_LoadMUS("data/music/Cite.ogg");
        case 19 : return Mix_LoadMUS("data/music/Chateau.ogg");
        case 21 : return Mix_LoadMUS("data/music/Lanelle.ogg");
        case 23 : return Mix_LoadMUS("data/music/Cimetiere.ogg");
        case 25 : return Mix_LoadMUS("data/music/VillageM.ogg");
        case 26 : return Mix_LoadMUS("data/music/Lac.ogg");
        case 27 : return Mix_LoadMUS("data/music/Desert.ogg");
        case 28 : return Mix_LoadMUS("data/music/VillageO.ogg");
        case 30 : return Mix_LoadMUS("data/music/Mont.ogg");
        case 31 : case 32 : case 34 : case 35 :
            return Mix_LoadMUS("data/music/Ombre.ogg");
        case 33 : return Mix_LoadMUS("data/music/VilleF.ogg");
        case 36 : return Mix_LoadMUS("data/music/BoisPerdusF.ogg");
        case 37 : return Mix_LoadMUS("data/music/Cascades.ogg");
        case 38 : return Mix_LoadMUS("data/music/CimetiereF.ogg");
        case 40 : return Mix_LoadMUS("data/music/VillageMF.ogg");
        case 41 : return Mix_LoadMUS("data/music/LacF.ogg");
        case 42 : return Mix_LoadMUS("data/music/DesertF.ogg");
        case 43 : return Mix_LoadMUS("data/music/VillageOF.ogg");
        case 45 : return Mix_LoadMUS("data/music/MontF.ogg");
        case 46 : return Mix_LoadMUS("data/music/Courage.ogg");
        case 47 : return Mix_LoadMUS("data/music/Sagesse.ogg");
        case 48 : return Mix_LoadMUS("data/music/Force.ogg");
        case 49 : return Mix_LoadMUS("data/music/Abysses.ogg");
        case 50 : return Mix_LoadMUS("data/music/PyramideF.ogg");
        case 51 : return Mix_LoadMUS("data/music/PyramideP.ogg");
        case 52 : return Mix_LoadMUS("data/music/Ordinn.ogg");
        case 53 : return Mix_LoadMUS("data/music/Air.ogg");
        case 54 : return Mix_LoadMUS("data/music/Glace.ogg");
        case 55 : return Mix_LoadMUS("data/music/Feu.ogg");
        case 56 : return Mix_LoadMUS("data/music/Titre.ogg");
        case 57 : return Mix_LoadMUS("data/music/DFinal.ogg");
        case 58 : return Mix_LoadMUS("data/music/Casino.ogg");
        case 59 : return Mix_LoadMUS("data/music/Gemme.ogg");
        case 60 : return Mix_LoadMUS("data/music/DestinationF.ogg");
        case 61 : return Mix_LoadMUS("data/music/Cave.ogg");
        case 79 : return Mix_LoadMUS("data/music/Home.ogg");
        case 80 : return Mix_LoadMUS("data/music/Bar.ogg");
        case 81 : return Mix_LoadMUS("data/music/Magasin.ogg");
        case 83 : return Mix_LoadMUS("data/music/Maison.ogg");
        case 85 : return Mix_LoadMUS("data/music/Potion.ogg");
        case 89 : return Mix_LoadMUS("data/music/Jeu.ogg");
        case 95 : return Mix_LoadMUS("data/music/Maire.ogg");
        case 119 : return Mix_LoadMUS("data/music/Cafe.ogg");
        case 144 : return Mix_LoadMUS("data/music/Sages.ogg");
        case 150 : return Mix_LoadMUS("data/music/Opera.ogg");
        case 151 : return Mix_LoadMUS("data/music/Epee.ogg");
        case 154 : return Mix_LoadMUS("data/music/Prison.ogg");
        case 155 : return Mix_LoadMUS("data/music/ChateauF.ogg");
        case 218 : return Mix_LoadMUS("data/music/probleme.ogg");
        case 219 : return Mix_LoadMUS("data/music/Epee.ogg");
        case 180 : return Mix_LoadMUS("data/music/Titre.ogg");
        case 190 : return Mix_LoadMUS("data/music/Selection.ogg");
        case 199 : return Mix_LoadMUS("data/music/Nuit.ogg");
        case 200 : return Mix_LoadMUS("data/music/Debut.ogg");
        default : return Mix_LoadMUS("data/music/Maison.ogg");
    }
}

void Audio::playSpecial(int id) {
    if (SOUND) {
        if (specialId != id) {
			Mix_HaltMusic();
			Mix_FreeMusic(music);
            music = choixSpecial(id);
            //if (previous_volume == -1) previous_volume = FMUSIC_GetMasterVolume(music);
			Mix_PlayMusic(music, -1);
            specialId=id;
        }    
    }
}

void Audio::stopSpecial() {
    if (!specialId) return;
    int tmp = musiqueId;
    musiqueId = 0;
    specialId = 0;
    playMusic(tmp);
}

Mix_Music* Audio::choixSpecial(int id) {
    switch (id) {
        case 1 : return Mix_LoadMUS("data/music/Boss.ogg");
        case 2 : return Mix_LoadMUS("data/music/Mort.ogg");
        case 3 : return Mix_LoadMUS("data/music/Epee.ogg");
        case 4 : return Mix_LoadMUS("data/music/BossF.ogg");
        case 5 : return Mix_LoadMUS("data/music/Fin.ogg");
        case 6 : return Mix_LoadMUS("data/music/BossM.ogg");
        case 7 : return Mix_LoadMUS("data/music/Area81.ogg");
        case 8 : return Mix_LoadMUS("data/music/OniLink.ogg");
        case 9 : return Mix_LoadMUS("data/music/probleme.ogg");
        case 10 : return Mix_LoadMUS("data/music/Harpie.ogg");
        case 11 : return Mix_LoadMUS("data/music/Crabe.ogg");
        case 12 : return Mix_LoadMUS("data/music/Imp.ogg");
        case 13 : return Mix_LoadMUS("data/music/Masamune.ogg");
        case 14 : return Mix_LoadMUS("data/music/ZoraS.ogg");
        case 15 : return Mix_LoadMUS("data/music/Marlag.ogg");
        case 16 : return Mix_LoadMUS("data/music/Fantomas.ogg");
        case 17 : return Mix_LoadMUS("data/music/Vampire.ogg");
        case 18 : return Mix_LoadMUS("data/music/Araignee.ogg");
        case 19 : return Mix_LoadMUS("data/music/Plumes.ogg");
        case 20 : return Mix_LoadMUS("data/music/Garuda.ogg");
        case 21 : return Mix_LoadMUS("data/music/Heckran.ogg");
        case 22 : return Mix_LoadMUS("data/music/Sun.ogg");
        case 23 : return Mix_LoadMUS("data/music/Orcus.ogg");
        case 24 : return Mix_LoadMUS("data/music/Agahnim.ogg");
        case 25 : return Mix_LoadMUS("data/music/Zelda.ogg");
        case 26 : return Mix_LoadMUS("data/music/AgahnimFinal.ogg");
        case 27 : return Mix_LoadMUS("data/music/GanondorfFinal.ogg");
        case 28 : return Mix_LoadMUS("data/music/Quizz.ogg");
        case 29 : return Mix_LoadMUS("data/music/FinalBattle.ogg");
        default : return Mix_LoadMUS("data/music/Boss.ogg");
    }
}
