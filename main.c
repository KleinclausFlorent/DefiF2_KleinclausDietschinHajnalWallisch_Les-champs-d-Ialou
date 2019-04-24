#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

void initIntro(SDL_Renderer *renderer,SDL_Texture** bg,SDL_Texture** txt );
void afficheIntro(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt );

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){ // Démarrage de la SDL. Si erreur :
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    SDL_Window* fnt = NULL;

    fnt = SDL_CreateWindow("Sortez les rames !", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 700, SDL_WINDOW_SHOWN);

    if( fnt == NULL ){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        getchar();
        SDL_Quit();
    }

    if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) == -1){
        printf("Mix_OpenAudio : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    Mix_Music *music = Mix_LoadMUS("./audio/egypte.wav");
    if(music == NULL){
        printf("Mix_LoadMUS : %s\n", Mix_GetError());
    }
    Mix_VolumeMusic(128);
    if(Mix_PlayMusic(music, -1) == -1){
        printf("Mix_PlayMusic : %s\n", SDL_GetError());
    }

    SDL_Event event;
    int stop = 0;
    int layout = 0;
    int intro = 0;
    SDL_Renderer* renderer = SDL_CreateRenderer(fnt, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* bg;
    SDL_Texture* txt;

    // ----- Création du bouton Réinitialisation -----
    SDL_Rect reinit;
    // ----- Création des SDL_Rect des vases canopes -----
    SDL_Rect vaseNephtys;
    SDL_Rect vaseNeith;
    SDL_Rect vaseIsis;
    SDL_Rect vaseSerket;
    // ----- Création des SDL_Rect des membres -----
    SDL_Rect rect_estomac;
    SDL_Rect rect_foie;
    SDL_Rect rect_poumons;
    SDL_Rect rect_intestins;

    SDL_Texture* reinit_button;
    SDL_Texture* vase1;
    SDL_Texture* vase2;
    SDL_Texture* vase3;
    SDL_Texture* vase4;
    SDL_Texture* estomac;
    SDL_Texture* foie;
    SDL_Texture* poumons;
    SDL_Texture* intestins;

    int enigme = 0;
    int testclique = 0;

    int testVaseNephtys = 0;
    int testVaseNeith = 0;
    int testVaseIsis = 0;
    int testVaseSerket = 0;

    int move_estomac = 0;
    int move_foie = 0;
    int move_poumons = 0;
    int move_intestins = 0;



    while(stop == 0){
        if (layout == 0){
            if(intro == 0){
                initIntro(renderer,&bg,&txt);
                afficheIntro(renderer,bg,txt);
                intro = 1;
            }
        }
        else if(layout==1){
            if(intro == 0){
                initRectEnigm1(&reinit,&vaseNephtys,&vaseNeith,&vaseIsis,&vaseSerket,&rect_estomac,&rect_foie,&rect_poumons,&rect_intestins);
                initImgEnigm1(renderer,&bg,&reinit_button,&vase1,&vase2,&vase3,&vase4,&estomac,&foie,&poumons,&intestins);
                testVaseNephtys = 0;
                testVaseNeith = 0;
                testVaseIsis = 0;
                testVaseSerket = 0;
                move_estomac = 0;
                move_foie = 0;
                move_poumons = 0;
                move_intestins = 0;
                enigme = 0;
                intro = 1;


            }
        }
        else if(layout == 2){
            printf("Niveau 2!");
            SDL_RenderClear(renderer);
            int enigmeLVL2 = 0;
            layout = 3;
        }
        uint32_t start = SDL_GetTicks();

        while(SDL_PollEvent(&event)){
            // -------------------- LORSQUE LE CLIC EST PRESSÉ --------------------
            if(event.type == SDL_MOUSEBUTTONDOWN){
                if (layout == 0){
                    layout = 1;
                    intro = 0;
                }
                else if ((layout = 1)&&(intro=1)){
                    if(event.button.x >= rect_estomac.x && event.button.x <= rect_estomac.x + 75 && move_estomac == 0){ //si clique sur estomac...
                        if(event.button.y >= rect_estomac.y && event.button.y <= rect_estomac.y + 75){
                            testclique = 1;
                        }
                    }
                    if(event.button.x >= rect_foie.x && event.button.x <= rect_foie.x + 75  && move_foie == 0){ //si clique sur foie...
                        if(event.button.y >= rect_foie.y && event.button.y <= rect_foie.y + 75){
                            testclique = 2;
                        }
                    }
                    if(event.button.x >= rect_poumons.x && event.button.x <= rect_poumons.x + 75 && move_poumons == 0){ //si clique sur poumons...
                        if(event.button.y >= rect_poumons.y && event.button.y <= rect_poumons.y + 75){
                            testclique = 3;
                        }
                    }
                    if(event.button.x >= rect_intestins.x && event.button.x <= rect_intestins.x + 75 && move_intestins == 0){ //si clique sur intestins...
                        if(event.button.y >= rect_intestins.y && event.button.y <= rect_intestins.y + 75){
                            testclique = 4;
                        }
                    }
                }
            }

            // -------------------- DEPLACEMENTS ORGANES ET BOUTON RÉINITIALISER --------------------
            if(event.type == SDL_MOUSEMOTION){
                    if(testclique == 1){ //déplacement estomac
                        rect_estomac.x = event.motion.x - 37;
                        rect_estomac.y = event.motion.y - 37;
                    }
                    else if(testclique == 2){ //déplacement foie
                        rect_foie.x = event.motion.x - 37;
                        rect_foie.y = event.motion.y - 37;
                    }
                    else if(testclique == 3){ //déplacement poumons
                        rect_poumons.x = event.motion.x - 37;
                        rect_poumons.y = event.motion.y - 37;
                    }
                    else if(testclique == 4){ //déplacement intestins
                        rect_intestins.x = event.motion.x - 37;
                        rect_intestins.y = event.motion.y - 37;
                    }
                    else{
                        continue;
                    }
            }
            // -------------------- LORSQUE LE CLIC EST LÂCHÉ --------------------
            if(event.type == SDL_MOUSEBUTTONUP){

                if ((layout = 1)&&(intro=1)){
                    testclique = 0;

                    if(event.button.x >= reinit.x && event.button.x <= reinit.x + 200){ //si clique sur intestins...
                        if(event.button.y >= reinit.y && event.button.y <= reinit.y + 50){
                            SDL_Delay(100);
                            intro = 0;
                            layout = 0;
                        }
                    }

                    // -------------------- SI ORGANE RENTRE DANS VASE NEPHTYS --------------------
                    if(testVaseNephtys == 0){
                        if(rect_estomac.x + 37 >= vaseNephtys.x && rect_estomac.x + 37 <= vaseNephtys.x + 100){ //si ESTOMAC est dans VASE NEPTHYS
                            if(rect_estomac.y + 37 >= vaseNephtys.y && rect_estomac.y + 37 <= vaseNephtys.y + 200){
                                SDL_DestroyTexture(estomac);
                                testVaseNephtys = 1;
                                move_estomac = 1;
                            }
                        }
                        if(rect_foie.x + 37 >= vaseNephtys.x && rect_foie.x + 37 <= vaseNephtys.x + 100){ //si FOIE est dans VASE NEPTHYS
                            if(rect_foie.y + 37 >= vaseNephtys.y && rect_foie.y + 37 <= vaseNephtys.y + 200){
                                SDL_DestroyTexture(foie);
                                testVaseNephtys = 1;
                                move_foie = 1;
                            }
                        }
                        if(rect_poumons.x + 37 >= vaseNephtys.x && rect_poumons.x + 37 <= vaseNephtys.x + 100){ //si POUMONS est dans VASE NEPTHYS
                            if(rect_poumons.y + 37 >= vaseNephtys.y && rect_poumons.y + 37 <= vaseNephtys.y + 200){
                                SDL_DestroyTexture(poumons);
                                testVaseNephtys = 1;
                                move_poumons = 1;
                                enigme += 1;
                            }
                        }
                        if(rect_intestins.x + 37 >= vaseNephtys.x && rect_intestins.x + 37 <= vaseNephtys.x + 100){ //si INTESTINS est dans VASE NEPTHYS
                            if(rect_intestins.y + 37 >= vaseNephtys.y && rect_intestins.y + 37 <= vaseNephtys.y + 200){
                                SDL_DestroyTexture(intestins);
                                testVaseNephtys = 1;
                                move_intestins = 1;
                            }
                        }
                    }

                    // -------------------- SI ORGANE RENTRE DANS VASE NEITH --------------------
                    if(testVaseNeith == 0){
                        if(rect_estomac.x + 37 >= vaseNeith.x && rect_estomac.x + 37 <= vaseNeith.x + 100){ //si ESTOMAC est dans VASE NEITH
                            if(rect_estomac.y + 37 >= vaseNeith.y && rect_estomac.y + 37 <= vaseNeith.y + 200){
                                SDL_DestroyTexture(estomac);
                                testVaseNeith = 1;
                                move_estomac = 1;
                                enigme += 1;
                            }
                        }
                        if(rect_foie.x + 37 >= vaseNeith.x && rect_foie.x + 37 <= vaseNeith.x + 100){ //si FOIE est dans VASE NEITH
                            if(rect_foie.y + 37 >= vaseNeith.y && rect_foie.y + 37 <= vaseNeith.y + 200){
                                SDL_DestroyTexture(foie);
                                testVaseNeith = 1;
                                move_foie = 1;
                            }
                        }
                        if(rect_poumons.x + 37 >= vaseNeith.x && rect_poumons.x + 37 <= vaseNeith.x + 100){ //si POUMONS est dans VASE NEITH
                            if(rect_poumons.y + 37 >= vaseNeith.y && rect_poumons.y + 37 <= vaseNeith.y + 200){
                                SDL_DestroyTexture(poumons);
                                testVaseNeith = 1;
                                move_poumons = 1;
                            }
                        }
                        if(rect_intestins.x + 37 >= vaseNeith.x && rect_intestins.x + 37 <= vaseNeith.x + 100){ //si INTESTINS est dans VASE NEITH
                            if(rect_intestins.y + 37 >= vaseNeith.y && rect_intestins.y + 37 <= vaseNeith.y + 200){
                                SDL_DestroyTexture(intestins);
                                testVaseNeith = 1;
                                move_intestins = 1;
                            }
                        }
                    }

                    // -------------------- SI ORGANE RENTRE DANS VASE ISIS --------------------
                    if(testVaseIsis == 0){
                        if(rect_estomac.x + 37 >= vaseIsis.x && rect_estomac.x + 37 <= vaseIsis.x + 100){ //si ESTOMAC est dans VASE ISIS
                            if(rect_estomac.y + 37 >= vaseIsis.y && rect_estomac.y + 37 <= vaseIsis.y + 200){
                                SDL_DestroyTexture(estomac);
                                testVaseIsis = 1;
                                move_estomac = 1;
                            }
                        }
                        if(rect_foie.x + 37 >= vaseIsis.x && rect_foie.x + 37 <= vaseIsis.x + 100){ //si FOIE est dans VASE ISIS
                            if(rect_foie.y + 37 >= vaseIsis.y && rect_foie.y + 37 <= vaseIsis.y + 200){
                                SDL_DestroyTexture(foie);
                                testVaseIsis = 1;
                                move_foie = 1;
                                enigme += 1;
                            }
                        }
                        if(rect_poumons.x + 37 >= vaseIsis.x && rect_poumons.x + 37 <= vaseIsis.x + 100){ //si POUMONS est dans VASE ISIS
                            if(rect_poumons.y + 37 >= vaseIsis.y && rect_poumons.y + 37 <= vaseIsis.y + 200){
                                SDL_DestroyTexture(poumons);
                                testVaseIsis = 1;
                                move_poumons = 1;
                            }
                        }
                        if(rect_intestins.x + 37 >= vaseIsis.x && rect_intestins.x + 37 <= vaseIsis.x + 100){ //si INTESTINS est dans VASE ISIS
                            if(rect_intestins.y + 37 >= vaseIsis.y && rect_intestins.y + 37 <= vaseIsis.y + 200){
                                SDL_DestroyTexture(intestins);
                                testVaseIsis = 1;
                                move_intestins = 1;
                            }
                        }
                    }

                    // -------------------- SI ORGANE RENTRE DANS VASE SERKET --------------------
                    if(testVaseSerket == 0){
                        if(rect_estomac.x + 37 >= vaseSerket.x && rect_estomac.x + 37 <= vaseSerket.x + 100){ //si ESTOMAC est dans VASE SERKET
                            if(rect_estomac.y + 37 >= vaseSerket.y && rect_estomac.y + 37 <= vaseSerket.y + 200){
                                SDL_DestroyTexture(estomac);
                                testVaseSerket = 1;
                                move_estomac = 1;
                            }
                        }
                        if(rect_foie.x + 37 >= vaseSerket.x && rect_foie.x + 37 <= vaseSerket.x + 100){ //si FOIE est dans VASE SERKET
                            if(rect_foie.y + 37 >= vaseSerket.y && rect_foie.y + 37 <= vaseSerket.y + 200){
                                SDL_DestroyTexture(foie);
                                testVaseSerket = 1;
                                move_foie = 1;
                            }
                        }
                        if(rect_poumons.x + 37 >= vaseSerket.x && rect_poumons.x + 37 <= vaseSerket.x + 100){ //si POUMONS est dans VASE SERKET
                            if(rect_poumons.y + 37 >= vaseSerket.y && rect_poumons.y + 37 <= vaseSerket.y + 200){
                                SDL_DestroyTexture(poumons);
                                testVaseSerket = 1;
                                move_poumons = 1;
                            }
                        }
                        if(rect_intestins.x + 37 >= vaseSerket.x && rect_intestins.x + 37 <= vaseSerket.x + 100){ //si INTESTINS est dans VASE SERKET
                            if(rect_intestins.y + 37 >= vaseSerket.y && rect_intestins.y + 37 <= vaseSerket.y + 200){
                                SDL_DestroyTexture(intestins);
                                testVaseSerket = 1;
                                enigme += 1;
                                move_intestins = 1;
                            }
                        }
                    }
                }

            }
            if(event.type == SDL_QUIT){
                SDL_Quit();
                break;
            }
        }
        //Update de l'affichage
        if((layout==1)&&(intro==1)){
            afficheEnigm1(renderer,bg,&reinit,reinit_button,&vaseNephtys,&vaseNeith,&vaseIsis,&vaseSerket,&rect_estomac,&rect_foie,&rect_poumons,&rect_intestins,vase1,vase2,vase3,vase4,estomac,foie,poumons,intestins);
        }
        SDL_RenderPresent(renderer);
        uint32_t total = SDL_GetTicks() - start;
        if (total < 16) {
            SDL_Delay(16 - total);
        }
        if(enigme == 4){
            layout += 1;
        }
    }

    SDL_Quit();

    return 0;
}


void initIntro(SDL_Renderer *renderer,SDL_Texture** bg,SDL_Texture** txt ){
    //Affichage BG pré-Niveau 2
    SDL_Surface* temp = IMG_Load("./img/bgMot.jpg");
    (*bg) = SDL_CreateTextureFromSurface(renderer, temp);


    //Affichage texte pré-Niveau 2
    temp = IMG_Load("./img/txt.png");
    (*txt) = SDL_CreateTextureFromSurface(renderer, temp);


}

void afficheIntro(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt ){
    SDL_Rect dest = (SDL_Rect){0, 0, 1000, 700};
    SDL_RenderCopy(renderer, bg, NULL, &dest);

    dest = (SDL_Rect){125, 200, 650, 300};
    SDL_RenderCopy(renderer, txt, NULL, &dest);
}

void initRectEnigm1(SDL_Rect* reinit, SDL_Rect* vaseNephtys, SDL_Rect* vaseNeith, SDL_Rect* vaseIsis, SDL_Rect* vaseSerket, SDL_Rect* rect_estomac,SDL_Rect* rect_foie,SDL_Rect* rect_poumons,SDL_Rect*  rect_intestins){

        reinit->x = 780;
        reinit->y = 20;
        reinit->w = 200;
        reinit->h = 50;

        vaseNephtys->x = 450;
        vaseNephtys->y = 0;
        vaseNephtys->w = 100;
        vaseNephtys->h = 200;

        vaseNeith->x = 600;
        vaseNeith->y = 150;
        vaseNeith->w = 100;
        vaseNeith->h = 200;

        vaseIsis->x = 450;
        vaseIsis->y = 300;
        vaseIsis->w = 100;
        vaseIsis->h = 200;

        vaseSerket->x = 300;
        vaseSerket->y = 150;
        vaseSerket->w = 100;
        vaseSerket->h = 200;

        rect_estomac->x = 120;
        rect_estomac->y = 600;
        rect_estomac->w = 75;
        rect_estomac->h = 75;

        rect_foie->x = 340;
        rect_foie->y = 600;
        rect_foie->w = 75;
        rect_foie->h = 75;

        rect_poumons->x = 560;
        rect_poumons->y = 600;
        rect_poumons->w = 75;
        rect_poumons->h = 75;

        rect_intestins->x = 780;
        rect_intestins->y = 600;
        rect_intestins->w = 75;
        rect_intestins->h = 75;



}

void initImgEnigm1(SDL_Renderer *renderer,SDL_Texture** bg,SDL_Texture** reinit_button,SDL_Texture** vase1,SDL_Texture** vase2,SDL_Texture** vase3,SDL_Texture** vase4,SDL_Texture** estomac,SDL_Texture** foie,SDL_Texture** poumons,SDL_Texture** intestins){
        //Affichage BG Niveau 2
        SDL_Surface* temp = IMG_Load("./img/bgLvl2.jpg");
        (*bg) = SDL_CreateTextureFromSurface(renderer, temp);

        //Affichage bouton réinitialiser
        temp = IMG_Load("./img/reinit.png");
        (*reinit_button) = SDL_CreateTextureFromSurface(renderer, temp);

        //Affichage vase canope Nephtys (haut)
        temp = IMG_Load("./img/VCNepthys.png");
        (*vase1) = SDL_CreateTextureFromSurface(renderer, temp);

        //Affichage vase canope Neith (droite)
        temp = IMG_Load("./img/VCNeith.png");
        (*vase2) = SDL_CreateTextureFromSurface(renderer, temp);

        //Affichage vase canope Isis (bas)
        temp = IMG_Load("./img/VCIsis.png");
        (*vase3) = SDL_CreateTextureFromSurface(renderer, temp);

        //Affichage vase canope Serket (gauche)
        temp = IMG_Load("./img/VCSerket.png");
        (*vase4) = SDL_CreateTextureFromSurface(renderer, temp);

        //Affichage estomac
        temp = IMG_Load("./img/VCEstomac.png");
        (*estomac) = SDL_CreateTextureFromSurface(renderer, temp);

         //Affichage foie
        temp = IMG_Load("./img/VCFoie.png");
        (*foie) = SDL_CreateTextureFromSurface(renderer, temp);

        //Affichage poumons
        temp = IMG_Load("./img/VCPoumons.png");
        (*poumons) = SDL_CreateTextureFromSurface(renderer, temp);

        //Affichage intestins
        temp = IMG_Load("./img/VCIntestins.png");
        (*intestins) = SDL_CreateTextureFromSurface(renderer, temp);
}

void afficheEnigm1(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Rect* reinit,SDL_Texture* reinit_button,SDL_Rect* vaseNephtys, SDL_Rect* vaseNeith, SDL_Rect* vaseIsis, SDL_Rect* vaseSerket, SDL_Rect* rect_estomac,SDL_Rect* rect_foie,SDL_Rect* rect_poumons,SDL_Rect*  rect_intestins
    ,SDL_Texture* vase1,SDL_Texture* vase2,SDL_Texture* vase3,SDL_Texture* vase4,SDL_Texture* estomac,SDL_Texture* foie,SDL_Texture* poumons,SDL_Texture* intestins){

        SDL_RenderClear(renderer);
        SDL_Rect dest = (SDL_Rect){0, 0, 1000, 700};
        SDL_RenderCopy(renderer, bg, NULL, &dest);

        SDL_RenderCopy(renderer, reinit_button, NULL, reinit);

        SDL_RenderCopy(renderer, vase1, NULL, vaseNephtys);

        SDL_RenderCopy(renderer, vase2, NULL, vaseNeith);

        SDL_RenderCopy(renderer, vase3, NULL, vaseIsis);

        SDL_RenderCopy(renderer, vase4, NULL, vaseSerket);

        SDL_RenderCopy(renderer, estomac, NULL, rect_estomac);

        SDL_RenderCopy(renderer, foie, NULL, rect_foie);

        SDL_RenderCopy(renderer, poumons, NULL, rect_poumons);

        SDL_RenderCopy(renderer, intestins, NULL, rect_intestins);
}
