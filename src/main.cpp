/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Keyboard.h"
#include "Generique.h"

SDL_Surface* init(bool* etire) // initialise SDL
{             
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) 
    {
        printf("Could not load SDL : %s\n", SDL_GetError());
        exit(-1);
    }
    atexit(SDL_Quit);

    SDL_WM_SetCaption("Time to Triumph",NULL);
    SDL_Surface* icon = SDL_LoadBMP("data/images/logos/ocarina.ico");
    SDL_SetColorKey(icon,SDL_SRCCOLORKEY,SDL_MapRGB(icon->format,0,0,0));
    SDL_WM_SetIcon(icon,NULL);

    SDL_ShowCursor(SDL_DISABLE);

#ifdef SDL_TRIPLEBUF
    return SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE|SDL_TRIPLEBUF);
#else
    return SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
#endif
}

int main(int argc, char** argv) 
{
    if (argc && argv); //pour éviter un warning.....
    
    std::srand(std::time(NULL));
    SDL_Surface* gpScreen = NULL;
    
    int mode = 2; //mode=1;
    
    bool etire = false;
    
    gpScreen = init(&etire);
    /*SDL_Surface* gpScreen2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    SDL_Surface* gpScreen3 = NULL;*/
    
    Audio* gpAudio = new Audio();
    Jeu* gpJeu = new Jeu(gpAudio);
    Carte* gpCarte = new Carte(gpJeu);
    Encyclopedie* gpEncyclopedie = new Encyclopedie(gpJeu);
    Poissons* gpPoissons = new Poissons(gpJeu);
    Keyboard* gpKeyboard = new Keyboard(gpJeu, gpCarte, gpEncyclopedie, gpPoissons, 
        gpScreen, mode, etire);
    gpJeu->setKeyboard(gpKeyboard);
    Generique* gpGenerique = new Generique(gpJeu);
    gpJeu->setGenerique(gpGenerique);
    gpGenerique->initLogo();
    
    bool gLoop = true;
    #ifndef GCW0
    Uint32 lastAnimTime = SDL_GetTicks();
    #endif
    
    while (gLoop) {
        
        if (gpKeyboard->gererClavier() == -1) {gLoop = false;}
        
        switch (gpKeyboard->getMode()) {
            case 0 : //jeu normal
                gpJeu->draw(gpScreen); break;
            case 1 : //disclamer
            case 2 : //logo
            case 3 : //titre
            case 14 : //générique score
            case 17 : //menu d'aide 1
            case 18 : //menu d'aide 2
            case 24 : //menu d'aide 3
            case 25 : //items de troc
            case 28 : //image de fin
                gpGenerique->draw(gpScreen); break;
            case 4 : //selection
                gpGenerique->drawSelection(gpScreen, gpKeyboard->getLigne(), 
                    gpKeyboard->getColonne()); break;
            case 6 : //options
                gpGenerique->drawOption(gpScreen, gpKeyboard->getLigneOption(),
                gpKeyboard->getVolume()/8, gpKeyboard->getVolson()/8); break;
            case 7 : //charger partie
                gpGenerique->drawCharger(gpScreen, gpKeyboard->getLigne(), 
                    gpKeyboard->getLigneVal()); break;
            case 8 : //générique intro
                gpGenerique->drawIntro(gpScreen, gpKeyboard->getIntro()); break;
            case 9 : //effacer partie
                gpGenerique->drawEffacerSave(gpScreen, gpKeyboard->getLigne(), 
                    gpKeyboard->getLigneVal()); break;
            case 10 : //générique début chez link
                gpGenerique->drawDebut(gpScreen); break;
            case 11 : //générique fin
                gpGenerique->drawFin(gpScreen); break;
            case 12 : //carte
            case 22 : //carte téléportation
                gpCarte->draw(gpScreen); break;
            case 13 : //encyclopédie des monstres
                gpEncyclopedie->draw(gpScreen); break;
            case 15 : //records
            case 19 : //rang 100%
            case 20 : //rang ultime
            case 21 : //rang de rapidité
                gpGenerique->drawRecord(gpScreen, gpKeyboard->getLigneRecord(),
                    gpKeyboard->getColonneRecord()); break;
            case 16 : //effacer record
                gpGenerique->drawEffacer(gpScreen, gpKeyboard->getLigneVal()); break;
            case 23 : //encyclopédie des poissons
                gpPoissons->draw(gpScreen); break;
            case 26 : //générique vers présent
            case 27 : //générique vers passé
                gpGenerique->drawToPresent(gpScreen); break;
            default : break;
        }

        SDL_Flip(gpScreen);
        
        #ifndef GCW0
		if (SDL_GetTicks() < lastAnimTime + 20) SDL_Delay(lastAnimTime+20-SDL_GetTicks());
        lastAnimTime = SDL_GetTicks();
        #endif
    
    }
    
   /*SDL_FreeSurface(gpScreen2);
    SDL_FreeSurface(gpScreen3);*/
    
    delete gpPoissons;
    delete gpEncyclopedie;
    delete gpGenerique;
    delete gpKeyboard;
    delete gpCarte;
    delete gpJeu;
    delete gpAudio;
	SDL_ShowCursor(SDL_ENABLE);
    if (gpScreen) SDL_FreeSurface(gpScreen);
    SDL_Quit();
    
    return 0;
}
