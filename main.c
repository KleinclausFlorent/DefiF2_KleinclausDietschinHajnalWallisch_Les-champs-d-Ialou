#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

void initIntro(SDL_Renderer *renderer,SDL_Texture** bg,SDL_Texture** txt );
void afficheIntro(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt );
void initRectEnigm1(SDL_Rect* reinit, SDL_Rect* vaseNephtys, SDL_Rect* vaseNeith, SDL_Rect* vaseIsis, SDL_Rect* vaseSerket, SDL_Rect* rect_estomac,SDL_Rect* rect_foie,SDL_Rect* rect_poumons,SDL_Rect*  rect_intestins);
void initImgEnigm1(SDL_Renderer *renderer,SDL_Texture** bg,SDL_Texture** reinit_button,SDL_Texture** vase1,SDL_Texture** vase2,SDL_Texture** vase3,SDL_Texture** vase4,SDL_Texture** estomac,SDL_Texture** foie,SDL_Texture** poumons,SDL_Texture** intestins);
void afficheEnigm1(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Rect* reinit,SDL_Texture* reinit_button,SDL_Rect* vaseNephtys, SDL_Rect* vaseNeith, SDL_Rect* vaseIsis, SDL_Rect* vaseSerket, SDL_Rect* rect_estomac,SDL_Rect* rect_foie,SDL_Rect* rect_poumons,SDL_Rect*  rect_intestins
    ,SDL_Texture* vase1,SDL_Texture* vase2,SDL_Texture* vase3,SDL_Texture* vase4,SDL_Texture* estomac,SDL_Texture* foie,SDL_Texture* poumons,SDL_Texture* intestins);
void initIntroLVL2(SDL_Renderer *renderer,SDL_Texture** bg,SDL_Texture** txt );
void afficheIntroLVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt );
void initRectEnigm2(SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3);
void initE1LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1 );
void afficheE1LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1, SDL_Rect* proposition2 );
void initE2LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1,SDL_Texture** E2T2,SDL_Texture** E2T3 );
void afficheE2LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1,SDL_Texture* E2T2,SDL_Texture* E2T3, SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3 );
void initE3LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1,SDL_Texture** E2T2,SDL_Texture** E2T3 );
void afficheE3LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1,SDL_Texture* E2T2,SDL_Texture* E2T3, SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3 );
void initE4LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1,SDL_Texture** E2T2,SDL_Texture** E2T3 );
void afficheE4LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1,SDL_Texture* E2T2,SDL_Texture* E2T3, SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3 );
void initE5LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1,SDL_Texture** E2T2,SDL_Texture** E2T3 );
void afficheE5LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1,SDL_Texture* E2T2,SDL_Texture* E2T3, SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3 );
void initE6LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1,SDL_Texture** E2T2,SDL_Texture** E2T3 );
void afficheE6LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1,SDL_Texture* E2T2,SDL_Texture* E2T3, SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3 );
void initE7LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T2);
void afficheE7LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T2, SDL_Rect* proposition2);

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

    SDL_Rect proposition1;
    SDL_Rect proposition2;
    SDL_Rect proposition3;

    SDL_Texture* E2T1;
    SDL_Texture* E2T2;
    SDL_Texture* E2T3;

    int enigmeLVL2 = 0;


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
            if(intro == 0){
                if (enigmeLVL2 == 0)
                {
                    initIntroLVL2(renderer,&bg,&txt);
                    afficheIntroLVL2(renderer,bg,txt);
                    initRectEnigm2(&proposition1,&proposition2,&proposition3);
                    intro = 1;
                }
                else if (enigmeLVL2 == 1)
                {
                    initE1LVL2(renderer,&txt,&E2T1);
                    afficheE1LVL2(renderer,bg,txt,E2T1,&proposition2);
                    intro = 1;
                }
                else if (enigmeLVL2 == 2)
                {
                    initE2LVL2(renderer,&txt,&E2T1,&E2T2,&E2T3);
                    afficheE2LVL2(renderer,bg,txt,E2T1,E2T2,E2T3,&proposition1,&proposition2,&proposition3);
                    intro = 1;
                }
                else if (enigmeLVL2 == 3)
                {
                    initE3LVL2(renderer,&txt,&E2T1,&E2T2,&E2T3);
                    afficheE3LVL2(renderer,bg,txt,E2T1,E2T2,E2T3,&proposition1,&proposition2,&proposition3);
                    intro = 1;
                }
                else if (enigmeLVL2 == 4)
                {
                    initE4LVL2(renderer,&txt,&E2T1,&E2T2,&E2T3);
                    afficheE4LVL2(renderer,bg,txt,E2T1,E2T2,E2T3,&proposition1,&proposition2,&proposition3);
                    intro = 1;
                }
                else if (enigmeLVL2 == 5)
                {
                    initE5LVL2(renderer,&txt,&E2T1,&E2T2,&E2T3);
                    afficheE5LVL2(renderer,bg,txt,E2T1,E2T2,E2T3,&proposition1,&proposition2,&proposition3);
                    intro = 1;
                }
                else if (enigmeLVL2 == 6)
                {
                    initE6LVL2(renderer,&txt,&E2T1,&E2T2,&E2T3);
                    afficheE6LVL2(renderer,bg,txt,E2T1,E2T2,E2T3,&proposition1,&proposition2,&proposition3);
                    intro = 1;
                }
                else if (enigmeLVL2 == 7)
                {
                    initE7LVL2(renderer,&txt,&E2T2);
                    afficheE7LVL2(renderer,bg,txt,E2T2,&proposition2);
                    intro = 1;
                }
                else if (enigmeLVL2 == 8)
                {
                    printf("fin des enigmes codees. Merci d'avoir teste !!");
                    stop = 1;
                }

            }
        }
        uint32_t start = SDL_GetTicks();

        while(SDL_PollEvent(&event)){
            // -------------------- LORSQUE LE CLIC EST PRESSÉ --------------------
            if(event.type == SDL_MOUSEBUTTONDOWN){
                if (layout == 0){
                    layout = 1;
                    intro = 0;
                }
                else if ((layout == 1)&&(intro==1)){
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
                else if ((layout == 2)&&(intro==1))
                {
                    if (enigmeLVL2==0){
                        enigmeLVL2 = 1;
                        intro = 0;
                    } else if (enigmeLVL2==1){
                        if(event.button.x >= proposition2.x && event.button.x <= proposition2.x + 200){
                            if(event.button.y >= proposition2.y && event.button.y <= proposition2.y + 50){
                                enigmeLVL2 = 2;
                                intro = 0;
                            }
                        }
                    } else if (enigmeLVL2==2){
                        if(event.button.x >= proposition1.x && event.button.x <= proposition1.x + 200){
                            if(event.button.y >= proposition1.y && event.button.y <= proposition1.y + 50){
                                enigmeLVL2 = 3;
                                intro = 0;
                            }
                        }
                        if(event.button.x >= proposition2.x && event.button.x <= proposition2.x + 200){
                            if(event.button.y >= proposition2.y && event.button.y <= proposition2.y + 50){
                                enigmeLVL2 = 0;
                                intro = 0;
                            }
                        }
                        if(event.button.x >= proposition3.x && event.button.x <= proposition3.x + 200){
                            if(event.button.y >= proposition3.y && event.button.y <= proposition3.y + 50){
                                enigmeLVL2 = 0;
                                intro = 0;
                            }
                        }
                    }  else if (enigmeLVL2==3){
                        if(event.button.x >= proposition1.x && event.button.x <= proposition1.x + 200){
                            if(event.button.y >= proposition1.y && event.button.y <= proposition1.y + 50){
                                enigmeLVL2 = 0;
                                intro = 0;
                            }
                        }
                        if(event.button.x >= proposition2.x && event.button.x <= proposition2.x + 200){
                            if(event.button.y >= proposition2.y && event.button.y <= proposition2.y + 50){
                                enigmeLVL2 = 4;
                                intro = 0;
                            }
                        }
                        if(event.button.x >= proposition3.x && event.button.x <= proposition3.x + 200){
                            if(event.button.y >= proposition3.y && event.button.y <= proposition3.y + 50){
                                enigmeLVL2 = 0;
                                intro = 0;
                            }
                        }
                    } else if (enigmeLVL2==4){
                        if(event.button.x >= proposition1.x && event.button.x <= proposition1.x + 200){
                            if(event.button.y >= proposition1.y && event.button.y <= proposition1.y + 50){
                                enigmeLVL2 = 5;
                                intro = 0;
                            }
                        }
                        if(event.button.x >= proposition2.x && event.button.x <= proposition2.x + 200){
                            if(event.button.y >= proposition2.y && event.button.y <= proposition2.y + 50){
                                enigmeLVL2 = 0;
                                intro = 0;
                            }
                        }
                        if(event.button.x >= proposition3.x && event.button.x <= proposition3.x + 200){
                            if(event.button.y >= proposition3.y && event.button.y <= proposition3.y + 50){
                                enigmeLVL2 = 0;
                                intro = 0;
                            }
                        }
                    }  else if (enigmeLVL2==5){
                        if(event.button.x >= proposition1.x && event.button.x <= proposition1.x + 200){
                            if(event.button.y >= proposition1.y && event.button.y <= proposition1.y + 50){
                                enigmeLVL2 = 0;
                                intro = 0;
                            }
                        }
                        if(event.button.x >= proposition2.x && event.button.x <= proposition2.x + 200){
                            if(event.button.y >= proposition2.y && event.button.y <= proposition2.y + 50){
                                enigmeLVL2 = 0;
                                intro = 0;
                            }
                        }
                        if(event.button.x >= proposition3.x && event.button.x <= proposition3.x + 200){
                            if(event.button.y >= proposition3.y && event.button.y <= proposition3.y + 50){
                                enigmeLVL2 = 6;
                                intro = 0;
                            }
                        }
                    } else if (enigmeLVL2==6){
                        if(event.button.x >= proposition1.x && event.button.x <= proposition1.x + 200){
                            if(event.button.y >= proposition1.y && event.button.y <= proposition1.y + 50){
                                enigmeLVL2 = 7;
                                intro = 0;
                            }
                        }
                        if(event.button.x >= proposition2.x && event.button.x <= proposition2.x + 200){
                            if(event.button.y >= proposition2.y && event.button.y <= proposition2.y + 50){
                                enigmeLVL2 = 0;
                                intro = 0;
                            }
                        }
                        if(event.button.x >= proposition3.x && event.button.x <= proposition3.x + 200){
                            if(event.button.y >= proposition3.y && event.button.y <= proposition3.y + 50){
                                enigmeLVL2 = 0;
                                intro = 0;
                            }
                        }
                    } else if (enigmeLVL2==7){
                        if(event.button.x >= proposition2.x && event.button.x <= proposition2.x + 200){
                            if(event.button.y >= proposition2.y && event.button.y <= proposition2.y + 50){
                                enigmeLVL2 = 8;
                                intro = 0;
                            }
                        }
                    }
                }
            }

            // -------------------- DEPLACEMENTS ORGANES ET BOUTON RÉINITIALISER --------------------
            if(event.type == SDL_MOUSEMOTION){
                if ((layout == 1)&&(intro==1)){
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
            }
            // -------------------- LORSQUE LE CLIC EST LÂCHÉ --------------------
            if(event.type == SDL_MOUSEBUTTONUP){

                if ((layout == 1)&&(intro == 1)){
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
        if (layout==2){
            //SDL_RenderClear(renderer);
        }
        SDL_RenderPresent(renderer);
        uint32_t total = SDL_GetTicks() - start;
        if (total < 16) {
            SDL_Delay(16 - total);
        }
        if(layout==1){
            if(enigme == 4){
                layout = 2;
                intro = 0;
            }
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

void initIntroLVL2(SDL_Renderer *renderer,SDL_Texture** bg,SDL_Texture** txt ){

    //Affichage BG pré-Niveau 2
    SDL_Surface* temp = IMG_Load("./img/LVL3bgIntro.jpg");
    (*bg) = SDL_CreateTextureFromSurface(renderer, temp);


    //Affichage texte pré-Niveau 2
    temp = IMG_Load("./img/LVL3txtIntro.png");
    (*txt) = SDL_CreateTextureFromSurface(renderer, temp);


}

void afficheIntroLVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt ){
    SDL_Rect dest = (SDL_Rect){0, 0, 1000, 700};
    SDL_RenderCopy(renderer, bg, NULL, &dest);

    dest = (SDL_Rect){50, 100, 850, 50};
    SDL_RenderCopy(renderer, txt, NULL, &dest);
}

void initRectEnigm2(SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3){

        proposition1->x = 150;
        proposition1->y = 600;
        proposition1->w = 200;
        proposition1->h = 50;

        proposition2->x = 400;
        proposition2->y = 600;
        proposition2->w = 200;
        proposition2->h = 50;

        proposition3->x = 650;
        proposition3->y = 600;
        proposition3->w = 200;
        proposition3->h = 50;

}

void initE1LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1 ){

    //Affichage texte pré-Niveau 2
    SDL_Surface* temp = IMG_Load("./img/LVL3enigmeIntro.png");
    (*txt) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/continuer.png");
    (*E2T1) = SDL_CreateTextureFromSurface(renderer, temp);


}

void afficheE1LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1, SDL_Rect* proposition2 ){
    SDL_Rect dest = (SDL_Rect){0, 0, 1000, 700};
    SDL_RenderCopy(renderer, bg, NULL, &dest);

    dest = (SDL_Rect){50, 50, 900, 500};
    SDL_RenderCopy(renderer, txt, NULL, &dest);

    proposition2->y=650;
    SDL_RenderCopy(renderer, E2T1, NULL, proposition2);
}

void initE2LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1,SDL_Texture** E2T2,SDL_Texture** E2T3 ){

    //Affichage texte pré-Niveau 2
    SDL_Surface* temp = IMG_Load("./img/LVL3test1.png");
    (*txt) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test1P1.png");
    (*E2T1) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test1P2.png");
    (*E2T2) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test1P3.png");
    (*E2T3) = SDL_CreateTextureFromSurface(renderer, temp);


}

void afficheE2LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1,SDL_Texture* E2T2,SDL_Texture* E2T3, SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3 ){
    SDL_Rect dest = (SDL_Rect){0, 0, 1000, 700};
    SDL_RenderCopy(renderer, bg, NULL, &dest);

    dest = (SDL_Rect){50, 50, 900, 500};
    SDL_RenderCopy(renderer, txt, NULL, &dest);

    proposition1->y=600;
    SDL_RenderCopy(renderer, E2T1, NULL, proposition1);
    proposition2->y=600;
    SDL_RenderCopy(renderer, E2T2, NULL, proposition2);
    proposition3->y=600;
    SDL_RenderCopy(renderer, E2T3, NULL, proposition3);
}

void initE3LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1,SDL_Texture** E2T2,SDL_Texture** E2T3 ){

    //Affichage texte pré-Niveau 2
    SDL_Surface* temp = IMG_Load("./img/LVL3test2.png");
    (*txt) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test2P1.png");
    (*E2T1) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test2P2.png");
    (*E2T2) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test2P3.png");
    (*E2T3) = SDL_CreateTextureFromSurface(renderer, temp);


}

void afficheE3LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1,SDL_Texture* E2T2,SDL_Texture* E2T3, SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3 ){
    SDL_Rect dest = (SDL_Rect){0, 0, 1000, 700};
    SDL_RenderCopy(renderer, bg, NULL, &dest);

    dest = (SDL_Rect){50, 50, 900, 400};
    SDL_RenderCopy(renderer, txt, NULL, &dest);

    proposition1->y=650;
    SDL_RenderCopy(renderer, E2T1, NULL, proposition1);
    proposition2->y=650;
    SDL_RenderCopy(renderer, E2T2, NULL, proposition2);
    proposition3->y=650;
    SDL_RenderCopy(renderer, E2T3, NULL, proposition3);
}

void initE4LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1,SDL_Texture** E2T2,SDL_Texture** E2T3 ){

    //Affichage texte pré-Niveau 2
    SDL_Surface* temp = IMG_Load("./img/LVL3test3.png");
    (*txt) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test3P1.png");
    (*E2T1) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test3P2.png");
    (*E2T2) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test3P3.png");
    (*E2T3) = SDL_CreateTextureFromSurface(renderer, temp);


}

void afficheE4LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1,SDL_Texture* E2T2,SDL_Texture* E2T3, SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3 ){
    SDL_Rect dest = (SDL_Rect){0, 0, 1000, 700};
    SDL_RenderCopy(renderer, bg, NULL, &dest);

    dest = (SDL_Rect){50, 50, 900, 150};
    SDL_RenderCopy(renderer, txt, NULL, &dest);

    proposition1->y=600;
    SDL_RenderCopy(renderer, E2T1, NULL, proposition1);
    proposition2->y=600;
    SDL_RenderCopy(renderer, E2T2, NULL, proposition2);
    proposition3->y=600;
    SDL_RenderCopy(renderer, E2T3, NULL, proposition3);
}


void initE5LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1,SDL_Texture** E2T2,SDL_Texture** E2T3 ){

    //Affichage texte pré-Niveau 2
    SDL_Surface* temp = IMG_Load("./img/LVL3test4.png");
    (*txt) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test4P1.png");
    (*E2T1) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test4P2.png");
    (*E2T2) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test4P3.png");
    (*E2T3) = SDL_CreateTextureFromSurface(renderer, temp);


}

void afficheE5LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1,SDL_Texture* E2T2,SDL_Texture* E2T3, SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3 ){
    SDL_Rect dest = (SDL_Rect){0, 0, 1000, 700};
    SDL_RenderCopy(renderer, bg, NULL, &dest);

    dest = (SDL_Rect){50, 50, 900, 150};
    SDL_RenderCopy(renderer, txt, NULL, &dest);

    proposition1->y=650;
    SDL_RenderCopy(renderer, E2T1, NULL, proposition1);
    proposition2->y=650;
    SDL_RenderCopy(renderer, E2T2, NULL, proposition2);
    proposition3->y=650;
    SDL_RenderCopy(renderer, E2T3, NULL, proposition3);
}

void initE6LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T1,SDL_Texture** E2T2,SDL_Texture** E2T3 ){

    //Affichage texte pré-Niveau 2
    SDL_Surface* temp = IMG_Load("./img/LVL3test5.png");
    (*txt) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test5P1.png");
    (*E2T1) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test5P2.png");
    (*E2T2) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/LVL3test5P3.png");
    (*E2T3) = SDL_CreateTextureFromSurface(renderer, temp);


}

void afficheE6LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T1,SDL_Texture* E2T2,SDL_Texture* E2T3, SDL_Rect* proposition1, SDL_Rect* proposition2, SDL_Rect* proposition3 ){
    SDL_Rect dest = (SDL_Rect){0, 0, 1000, 700};
    SDL_RenderCopy(renderer, bg, NULL, &dest);

    dest = (SDL_Rect){50, 50, 900, 150};
    SDL_RenderCopy(renderer, txt, NULL, &dest);

    proposition1->y=600;
    SDL_RenderCopy(renderer, E2T1, NULL, proposition1);
    proposition2->y=600;
    SDL_RenderCopy(renderer, E2T2, NULL, proposition2);
    proposition3->y=600;
    SDL_RenderCopy(renderer, E2T3, NULL, proposition3);
}
void initE7LVL2(SDL_Renderer *renderer,SDL_Texture** txt,SDL_Texture** E2T2){

    //Affichage texte pré-Niveau 2
    SDL_Surface* temp = IMG_Load("./img/LVL3test6.png");
    (*txt) = SDL_CreateTextureFromSurface(renderer, temp);

    temp = IMG_Load("./img/continuer.png");
    (*E2T2) = SDL_CreateTextureFromSurface(renderer, temp);

}

void afficheE7LVL2(SDL_Renderer *renderer,SDL_Texture* bg,SDL_Texture* txt,SDL_Texture* E2T2, SDL_Rect* proposition2){
    SDL_Rect dest = (SDL_Rect){0, 0, 1000, 700};
    SDL_RenderCopy(renderer, bg, NULL, &dest);

    dest = (SDL_Rect){50, 50, 900, 50};
    SDL_RenderCopy(renderer, txt, NULL, &dest);

    proposition2->y=650;
    SDL_RenderCopy(renderer, E2T2, NULL, proposition2);
}


