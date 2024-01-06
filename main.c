#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CELL_SIZE 20
int ps = 0;
int level = 0 ;
typedef struct Snake {
    float x, y;
    int dir;
    struct Snake* next;
} Snake;
typedef struct {
    int x, y, w, h;
} SDL_Rectangle;
typedef struct food {
    float x;
    float y;
}food ;
food Food ;
int score = 0 ;
SDL_Rectangle buttonret = {482, 340, 200, 105};
SDL_Rectangle buttonexit = {174, 347, 195, 110};
SDL_Rectangle buttonnext = {570, 360, 200, 90};
SDL_Rectangle buttonplay = {480, 292, 207, 110};

enum Direction {
    SNAKC_UP,
    SNAKC_DOWN,
    SNAKC_LEFT,
    SNAKC_RIGHT
};
enum Direction currentdir = SNAKC_RIGHT ;
Snake* snake_head = NULL;
Snake* tail = NULL;
int quit = 0;


SDL_Event event;


void init_snake() {
    currentdir = SNAKC_RIGHT ;
    Snake* new_s = malloc(sizeof(Snake));
    new_s->x = 220;
    new_s->y = 520 ;
    new_s->dir = SNAKC_RIGHT;
    new_s->next = NULL;
    snake_head = new_s;
    tail = new_s;
}

void gen_food(){
    if (level == 1){
    do {
    Food.x = rand() % (WINDOW_WIDTH/CELL_SIZE) ;
    Food.y = rand() % (WINDOW_HEIGHT/CELL_SIZE) ;
    }while ((((Food.x) >= 19) && ((Food.x) <= 20) &&((Food.y) >= 10)&&((Food.y) <=19)) ||
         (((Food.y)<=8) && ((Food.x)<= 1)) ||
          ((Food.y<=1)) || ((Food.y >= 28)) || ((Food.y <= 15) && (Food.y >= 14) && (Food.x <= 7)) ||
                (((Food.x)<= 1)&&((Food.y >= 21))) ||((Food.y <= 15) && (Food.y >= 14) && (Food.x >= 32)) ||
                 (((Food.y)<=8) && ((Food.x)>= 38)) || (((Food.x)>= 38)&&((Food.y >= 21)))
                  );}
    else  {
        do {
    Food.x = rand() % (WINDOW_WIDTH/CELL_SIZE) ;
    Food.y = rand() % (WINDOW_HEIGHT/CELL_SIZE) ;
    }while ((Food.y<=1) || (Food.y >=28) || ((Food.x <=3) && (Food.y<=5)) ||
           ((Food.x <= 1) && (Food.y<= 7)) || ((Food.y>= 14) && (Food.y <= 15) && (Food.x <= 7)) ||
           ((Food.x<=3) && (Food.y >=24)) || ((Food.x <= 1) && (Food.y >= 22)) ||
           ((Food.x>=36) && (Food.y >=24)) || ((Food.x >= 38) && (Food.y >= 22)) ||
           ((Food.y >= 14) && (Food.y <= 15) && (Food.x >= 32)) ||
           ((Food.x>=36) && (Food.y <=5)) || ((Food.x >= 38) && (Food.y<= 7)) ||
           ((Food.x >= 18) && (Food.y >= 5) && (Food.x <= 20) && (Food.y <= 12)) ||
           ((Food.x >= 11) && (Food.y>= 8) && (Food.x <= 28) && (Food.y <= 9)) ||
           ((Food.x >= 11) && (Food.y >= 8) && (Food.x <= 12) && (Food.y <= 14)) ||
           ((Food.x >= 11) && (Food.y >= 18) && (Food.x <= 28) && (Food.y <= 19)) ||
           ((Food.x>= 16) && (Food.y >= 17) && (Food.x<= 20) && (Food.y <= 24)) ||
           ((Food.x >= 27) && (Food.y >= 13) && (Food.x <= 28) && (Food.y <= 19))
                  );
    }
}
void gen_foor(){
    Food.x = 9 ;
    Food.y = 18 ;
}
void ate_food(){
    if (snake_head->x == (Food.x*CELL_SIZE) && snake_head->y == (Food.y*CELL_SIZE)){
         create_segment();
         gen_food();
         score++;
    }
}
void render_score(SDL_Renderer* renderer, TTF_Font* font, int score) {
    SDL_Color textColor = {255, 255, 255, 255};
    char scoreText[50];
    snprintf(scoreText, sizeof(scoreText), " Score : %d", score);

    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    SDL_Rect scoreRect = {332, 0, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);
}

void render_scorefinal(SDL_Renderer* renderer, TTF_Font* font, int score) {
    SDL_Color textColor = {0, 0, 0, 255};
    char scoreText[50];
    snprintf(scoreText, sizeof(scoreText), "   GAME OVER");
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {50, -40, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);

}

void render_sco (SDL_Renderer* renderer, TTF_Font* font, int score) {
    SDL_Color textColor = {0, 0, 0, 255};
    char scoreText[50];
    snprintf(scoreText, sizeof(scoreText), "Score : %d",score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {240, 95, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);
}

void render_pause (SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color textColor = {255, 255, 255, 255};
    char scoreText[50];
    snprintf(scoreText, sizeof(scoreText), "PAUSE");
    SDL_Surface* scoreSurface_2 = TTF_RenderText_Solid(font, scoreText, textColor);
    SDL_Texture* scoreTexture_2 = SDL_CreateTextureFromSurface(renderer, scoreSurface_2);
    SDL_Rect pauserect = {240, 240, scoreSurface_2->w, scoreSurface_2->h};
    SDL_RenderCopy(renderer, scoreTexture_2, NULL, &pauserect);
    SDL_FreeSurface(scoreSurface_2);
    SDL_DestroyTexture(scoreTexture_2);
    SDL_RenderPresent(renderer);
}

void render_food(SDL_Renderer *renderer , int x , int y, SDL_Surface* mouses){
    SDL_Rect fod;
    fod.w = 20 ;
    fod.h = 20 ;
    fod.x = x*CELL_SIZE;
    fod.y = y*CELL_SIZE;
    SDL_RenderCopy(renderer, mouses, NULL, &fod);

}

void create_segment() {
    Snake* new_s = malloc(sizeof(Snake));
    new_s->x = tail->x;
    new_s->y = tail->y;
    new_s->dir = tail->dir ;
    new_s->next = NULL;
    tail->next = new_s;
    tail = new_s;
}
void render_head(SDL_Renderer* renderer,SDL_Surface* hardelTexture) {
    SDL_Rect segment;
    segment.x = snake_head->x;
    segment.y = snake_head->y;
    SDL_Rect hardelRect = {segment.x, segment.y,20 , 20};
    SDL_RenderCopy(renderer, hardelTexture, NULL, &hardelRect);
}
void render_snake(SDL_Renderer* renderer, SDL_Surface* hardelTexture_4, SDL_Surface* hardelTexture_5,SDL_Surface* hardelTexture_6,
                  SDL_Surface* hardelTexture_7,SDL_Surface* hardelTexture_8,SDL_Surface* hardelTexture_9,
                  SDL_Surface* hardelTexture_11 , SDL_Surface* hardelTexture_12 , SDL_Surface* hardelTexture_13,SDL_Surface* hardelTexture_14
                  ){
        SDL_Rect segment;
        SDL_Rect hardelRect ;
        segment.w = CELL_SIZE;
        segment.h = CELL_SIZE;
        Snake* track = snake_head->next;
        Snake* prev = snake_head ;
        while (track != NULL){
        segment.x = track->x;
        segment.y = track->y;
        hardelRect.x = segment.x;
        hardelRect.y = segment.y;
        hardelRect.w = segment.w;
        hardelRect.h = segment.h;
        if ((prev->dir != track->dir) && (prev->dir == SNAKC_DOWN) && (track->dir == SNAKC_RIGHT)){
            SDL_RenderCopy(renderer, hardelTexture_6, NULL, &hardelRect);}
        else if  ((prev->dir != track->dir) && (prev->dir == SNAKC_LEFT) && (track->dir == SNAKC_UP)){
              SDL_RenderCopy(renderer, hardelTexture_6, NULL, &hardelRect);}


        else if ((prev->dir != track->dir) && (prev->dir == SNAKC_LEFT) && (track->dir == SNAKC_DOWN)){
               SDL_RenderCopy(renderer, hardelTexture_8, NULL, &hardelRect);
                 }
        else if ((prev->dir != track->dir) && (prev->dir == SNAKC_UP) && (track->dir == SNAKC_RIGHT)){
               SDL_RenderCopy(renderer, hardelTexture_8, NULL, &hardelRect);
                 }

        else if ((prev->dir != track->dir) && (prev->dir == SNAKC_RIGHT) && (track->dir == SNAKC_UP) ){
            SDL_RenderCopy(renderer, hardelTexture_7, NULL, &hardelRect);
        }
        else if ((prev->dir != track->dir) && (prev->dir == SNAKC_DOWN) && (track->dir == SNAKC_LEFT) ){
            SDL_RenderCopy(renderer, hardelTexture_7, NULL, &hardelRect);
        }
        else if ((prev->dir != track->dir) && (prev->dir == SNAKC_RIGHT) && (track->dir == SNAKC_DOWN) ){
             SDL_RenderCopy(renderer, hardelTexture_9, NULL, &hardelRect);
        }
        else if ((prev->dir != track->dir) && (prev->dir == SNAKC_UP) && (track->dir == SNAKC_LEFT) ){
             SDL_RenderCopy(renderer, hardelTexture_9, NULL, &hardelRect);
        } else if (track == tail){
             if (track->dir == SNAKC_UP){
          SDL_RenderCopy(renderer, hardelTexture_11, NULL, &hardelRect);}
         else if (track->dir == SNAKC_DOWN){
          SDL_RenderCopy(renderer, hardelTexture_12, NULL, &hardelRect);
       } else if (track->dir == SNAKC_LEFT){
          SDL_RenderCopy(renderer, hardelTexture_13, NULL, &hardelRect);
        } else if (track->dir == SNAKC_RIGHT){
        SDL_RenderCopy(renderer, hardelTexture_14, NULL, &hardelRect);
      }
        }
        else if (track->dir == SNAKC_DOWN || track->dir == SNAKC_UP){
           SDL_RenderCopy(renderer, hardelTexture_5, NULL, &hardelRect);}
        else if (track->dir == SNAKC_LEFT || track->dir == SNAKC_RIGHT){
            SDL_RenderCopy(renderer, hardelTexture_4, NULL, &hardelRect);}
        track = track->next;
        prev = prev->next;
    }
}
int update_game() {
    int prev_x = snake_head->x;
    int prev_y = snake_head->y;
    int prev_dir = snake_head->dir ;
    switch (currentdir) {
    case SNAKC_UP:
        snake_head->y -= CELL_SIZE;
        snake_head->dir = SNAKC_UP ;
        break;
    case SNAKC_DOWN:
        snake_head->y += CELL_SIZE;
        snake_head->dir = SNAKC_DOWN ;
        break;
    case SNAKC_LEFT:
        snake_head->x -= CELL_SIZE;
        snake_head->dir = SNAKC_LEFT ;
        break;
    case SNAKC_RIGHT:
        snake_head->x += CELL_SIZE;
        snake_head->dir = SNAKC_RIGHT ;
        break;
    }
     if (snake_head->x < 0)
        snake_head->x = WINDOW_WIDTH;
     else if (snake_head->x >= WINDOW_WIDTH)
        snake_head->x = 0;

     if (snake_head->y < 0)
        snake_head->y = WINDOW_HEIGHT;
     else if (snake_head->y >= WINDOW_HEIGHT)
        snake_head->y = 0;
    Snake* track = snake_head->next;
    while (track != NULL) {
        int save_x = track->x;
        int save_y = track->y;
        int save_dir = track->dir ;
        track->x = prev_x;
        track->y = prev_y;
        track->dir = prev_dir ;
        prev_x = save_x;
        prev_y = save_y;
        prev_dir = save_dir ;
        track = track->next;
    }
    if (level == 1){
    if ((((snake_head->x) >= 380) && ((snake_head->x) <= 400) &&((snake_head->y) >= 200)&&((snake_head->y) <=380)) ||
         (((snake_head->y)<=160) && ((snake_head->x)<= 20)) ||
          ((snake_head->y<=20)) || ((snake_head->y >= 560)) || ((snake_head->y <= 300) && (snake_head->y >= 280) && (snake_head->x <= 140)) ||
                (((snake_head->x)<= 20)&&((snake_head->y >= 420))) ||((snake_head->y <= 300) && (snake_head->y >= 280) && (snake_head->x >= 640)) ||
                 (((snake_head->y)<=160) && ((snake_head->x)>= 760)) || (((snake_head->x)>= 760)&&((snake_head->y >= 420)) || collision())
                  ){
        return 0;
    }
    } else {
        if ((snake_head->y<=20) || (snake_head->y>=560) || ((snake_head->x<=60) && (snake_head->y <=100)) ||
           ((snake_head->x <= 20) && (snake_head-> y<= 140)) || ((snake_head->y >= 280) && (snake_head-> y <= 300) && (snake_head->x <= 140)) ||
           ((snake_head->x<=60) && (snake_head->y >=480)) || ((snake_head->x <= 20) && (snake_head-> y >= 440)) ||
           ((snake_head->x>=720) && (snake_head->y >=480)) || ((snake_head->x >= 760) && (snake_head-> y >= 440)) ||
           ((snake_head->y >= 280) && (snake_head-> y <= 300) && (snake_head->x >= 640)) ||
           ((snake_head->x>=720) && (snake_head->y <=100)) || ((snake_head->x >= 760) && (snake_head-> y<= 140)) ||
           ((snake_head->x >= 380) && (snake_head-> y >= 100) && (snake_head->x <= 400) && (snake_head->y <= 240)) ||
           ((snake_head->x >= 220) && (snake_head-> y >= 160) && (snake_head->x <= 560) && (snake_head->y <= 180)) ||
           ((snake_head->x >= 220) && (snake_head-> y >= 160) && (snake_head->x <= 240) && (snake_head->y <= 280)) ||
           ((snake_head->x >= 220) && (snake_head-> y >= 360) && (snake_head->x <= 560) && (snake_head->y <= 380)) ||
           ((snake_head->x >= 380) && (snake_head-> y >= 340) && (snake_head->x <= 400) && (snake_head->y <= 480)) ||
           ((snake_head->x >= 540) && (snake_head-> y >= 260) && (snake_head->x <= 560) && (snake_head->y <= 380)) || collision() ){
return 0;
    }
    }
    return 1;
}

int collision(){
    Snake *Check = snake_head->next;
    while (Check != NULL){
        if ((Check->x == snake_head->x) && ((Check->y == snake_head->y)))
            return 1;

            Check = Check->next ;
    }
    return 0 ;

}

int pointInRectangle(int x, int y, SDL_Rectangle* rect) {
    return (x >= rect->x && x <= rect->x + rect->w && y >= rect->y && y <= rect->y + rect->h);
}

int pointInRectangleplay (int x, int y, SDL_Rectangle* rectplay) {
    return (x >= rectplay->x && x <= rectplay->x + rectplay->w && y >= rectplay->y && y <= rectplay->y + rectplay->h);
}
int pointInRectanglenext(int x, int y, SDL_Rectangle* recnex) {
    return (x >= recnex->x && x <= recnex->x + recnex->w && y >= recnex->y && y <= recnex->y + recnex->h);
}
int buttonexitrectangle(int x, int y, SDL_Rectangle* rectangle){
    return (x >= rectangle->x && x <= rectangle->x + rectangle->w && y >= rectangle->y && y <= rectangle->y + rectangle->h);
}
void pause(SDL_Renderer *renderer, TTF_Font* font2){
    while (ps==1) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                SDL_Quit ();
                exit(0);
                case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
            case SDLK_SPACE:
                 ps = 0 ;
                 break ;
 }
}
}    render_pause(renderer, font2);
    }
}

int main(int argc, char* argv[]) {
    SDL_Window* window;
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "Error creating the window window: %s\n", SDL_GetError());
        SDL_Quit();
    }
    int varnext = 0 ;
    DEBUT:
    init_snake();
    create_segment();
    gen_foor();
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture = NULL;
    SDL_Texture* backgroundgameover = NULL;
    SDL_Surface* hardelTexture = NULL;
    SDL_Surface* hardelTexture_1 = NULL ;
    SDL_Surface* hardelTexture_2 = NULL ;
    SDL_Surface* hardelTexture_3 = NULL ;
    SDL_Surface* hardelTexture_4 = NULL ;
    SDL_Surface* hardelTexture_5 = NULL ;
    SDL_Surface* hardelTexture_6 = NULL ;
    SDL_Surface* hardelTexture_7 = NULL ;
    SDL_Surface* hardelTexture_8 = NULL ;
    SDL_Surface* hardelTexture_9 = NULL ;
    SDL_Surface* hardelTexture_11 = NULL ;
    SDL_Surface* hardelTexture_12 = NULL ;
    SDL_Surface* hardelTexture_13 = NULL ;
    SDL_Surface* hardelTexture_14 = NULL ;
    SDL_Surface* hardelTexture_10 = NULL ;
    SDL_Surface* backgroundnext = NULL ;
    SDL_Surface* mousef = NULL ;
    SDL_Surface* youwin = NULL ;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "error initializing SDL: %s\n", SDL_GetError());
        exit (0);
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "error creating SDL renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    if (level == 0){
        SDL_Surface* backgroundSurface = IMG_Load("begun.png");
    if (!backgroundSurface) {
        fprintf(stderr, "error loading background image for the play: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture) {
        fprintf(stderr, "error creating background texture for play image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }

    }else if (level == 1){
    SDL_Surface* backgroundSurface = IMG_Load("myimageback4.png");
    if (!backgroundSurface) {
        fprintf(stderr, "error loading background image for the level 1: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture) {
        fprintf(stderr, "error creating background texture for the level 1: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    } } else {
         SDL_Surface* backgroundSurface = IMG_Load("secondboard.png");
    if (!backgroundSurface) {
        fprintf(stderr, "error loading background image for sec level: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture) {
        fprintf(stderr, "error creating background texture for sec level: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }

    }
    SDL_Surface* backgroundSurfacegameover = IMG_Load("exitretry.png");
    if (!backgroundSurfacegameover) {
        fprintf(stderr, "error loading background image for game over exitretry: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }
    backgroundgameover = SDL_CreateTextureFromSurface(renderer, backgroundSurfacegameover);
    SDL_FreeSurface(backgroundSurfacegameover);
    if (!backgroundgameover) {
        fprintf(stderr, "error creating background texture for game over exitretry: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }


    SDL_Surface* backgroundSurfacenext = IMG_Load("levelcomplited.png");
    if (!backgroundSurfacenext) {
        fprintf(stderr, "error loading background image forlevel complited levelcomplited: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }
    backgroundnext = SDL_CreateTextureFromSurface(renderer, backgroundSurfacenext);
    SDL_FreeSurface(backgroundSurfacenext);
    if (!backgroundnext) {
        fprintf(stderr, "error creating background texture for level complited levelcomplited: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }


    if (TTF_Init() != 0) {
    fprintf(stderr, "error initializing SDL_ttf: %s\n", TTF_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
   }
    TTF_Font* font = TTF_OpenFont("Premier2019-rPv9.ttf", 40);
if (!font) {
    fprintf(stderr, "error loading font Arial: %s\n", TTF_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

    SDL_Surface* hardelSurface = IMG_Load("headup.png");
    if (!hardelSurface) {
        fprintf(stderr, "error loading  image headup: %s\n", IMG_GetError());
    }

    hardelTexture = SDL_CreateTextureFromSurface(renderer, hardelSurface);
    SDL_FreeSurface(hardelSurface);

    if (!hardelTexture) {
        fprintf(stderr, "error creating  texture headup: %s\n", SDL_GetError());

    }

    SDL_Surface* hardelSurface_4 = IMG_Load("horizontal.png");
    if (!hardelSurface_4) {
        fprintf(stderr, "error loading  image horizontal: %s\n", IMG_GetError());
    }

    hardelTexture_4 = SDL_CreateTextureFromSurface(renderer, hardelSurface_4);
    SDL_FreeSurface(hardelSurface_4);

    if (!hardelTexture_4) {
        fprintf(stderr, "error creating  texture horizontal: %s\n", SDL_GetError());
    }

    SDL_Surface* hardelSurface_5 = IMG_Load("vertical.png");
    if (!hardelSurface_5) {
        fprintf(stderr, "error loading  image vertical: %s\n", IMG_GetError());
    }

    hardelTexture_5 = SDL_CreateTextureFromSurface(renderer, hardelSurface_5);
    SDL_FreeSurface(hardelSurface_5);

    if (!hardelTexture_5) {
        fprintf(stderr, "error creating texture vertical: %s\n", SDL_GetError());

    }
    SDL_Surface* hardelSurface_2 = IMG_Load("headleft.png");
    if (!hardelSurface_2) {
        fprintf(stderr, "error loading  image headleft: %s\n", IMG_GetError());
    }

    hardelTexture_2 = SDL_CreateTextureFromSurface(renderer, hardelSurface_2);
    SDL_FreeSurface(hardelSurface_2);

    if (!hardelTexture_2) {
        fprintf(stderr, "error creating  texture headleft: %s\n", SDL_GetError());

    }
    SDL_Surface* hardelSurface_1 = IMG_Load("headdown.png");
    if (!hardelSurface_1) {
        fprintf(stderr, "error loading  image headdown: %s\n", IMG_GetError());
    }

    hardelTexture_1 = SDL_CreateTextureFromSurface(renderer, hardelSurface_1);
    SDL_FreeSurface(hardelSurface_1);

    if (!hardelTexture_1) {
        fprintf(stderr, "error creating texture headdown: %s\n", SDL_GetError());

    }

    SDL_Surface* hardelSurface_3 = IMG_Load("headright.png");
    if (!hardelSurface_3) {
        fprintf(stderr, "error loading Hardel image headright: %s\n", IMG_GetError());
    }

    hardelTexture_3 = SDL_CreateTextureFromSurface(renderer, hardelSurface_3);
    SDL_FreeSurface(hardelSurface_3);

    if (!hardelTexture_3) {
        fprintf(stderr, "error creating  texture headright: %s\n", SDL_GetError());

    }


    SDL_Surface* hardelSurface_6 = IMG_Load("bottomleft.png");
    if (!hardelSurface_6) {
        fprintf(stderr, "error loading  image bottomleft: %s\n", IMG_GetError());
    }

    hardelTexture_6 = SDL_CreateTextureFromSurface(renderer, hardelSurface_6);
    SDL_FreeSurface(hardelSurface_6);

    if (!hardelTexture_6) {
        fprintf(stderr, "error creating texture bottomleft: %s\n", SDL_GetError());

    }



    SDL_Surface* hardelSurface_7 = IMG_Load("bottomright.png");
    if (!hardelSurface_7) {
        fprintf(stderr, "error loading image bottomright: %s\n", IMG_GetError());
    }

    hardelTexture_7 = SDL_CreateTextureFromSurface(renderer, hardelSurface_7);
    SDL_FreeSurface(hardelSurface_7);

    if (!hardelTexture_7) {
        fprintf(stderr, "error creating texture bottomright: %s\n", SDL_GetError());

    }



    SDL_Surface* hardelSurface_8 = IMG_Load("topleft.png");
    if (!hardelSurface_8) {
        fprintf(stderr, "error loading  image topleft: %s\n", IMG_GetError());
    }

    hardelTexture_8 = SDL_CreateTextureFromSurface(renderer, hardelSurface_8);
    SDL_FreeSurface(hardelSurface_8);

    if (!hardelTexture_8) {
        fprintf(stderr, "error creating texture topleft: %s\n", SDL_GetError());

    }


    SDL_Surface* hardelSurface_9 = IMG_Load("topright.png");
    if (!hardelSurface_9) {
        fprintf(stderr, "error loading  image topright: %s\n", IMG_GetError());
    }

    hardelTexture_9 = SDL_CreateTextureFromSurface(renderer, hardelSurface_9);
    SDL_FreeSurface(hardelSurface_9);

    if (!hardelTexture_9){
        fprintf(stderr, "Error creating  texture topright: %s\n", SDL_GetError());

    }

    SDL_Surface* hardelSurface_10 = IMG_Load("mouse.png");
    if (!hardelSurface_10) {
        fprintf(stderr, "Error loading  image mouse: %s\n", IMG_GetError());
    }

    hardelTexture_10 = SDL_CreateTextureFromSurface(renderer, hardelSurface_10);
    SDL_FreeSurface(hardelSurface_10);

    if (!hardelTexture_10){
        fprintf(stderr, "error creating  texture mouse: %s\n", SDL_GetError());

    }


    SDL_Surface* hardelSurface_11 = IMG_Load("tailup.png");
    if (!hardelSurface_11) {
        fprintf(stderr, "Error loading  image tailup: %s\n", IMG_GetError());
    }

    hardelTexture_11 = SDL_CreateTextureFromSurface(renderer, hardelSurface_11);
    SDL_FreeSurface(hardelSurface_11);

    if (!hardelTexture_11){
        fprintf(stderr, "error creating texture tailup: %s\n", SDL_GetError());

    }


    SDL_Surface* hardelSurface_12 = IMG_Load("taildown.png");
    if (!hardelSurface_12) {
        fprintf(stderr, "error loading image taildown: %s\n", IMG_GetError());
    }

    hardelTexture_12 = SDL_CreateTextureFromSurface(renderer, hardelSurface_12);
    SDL_FreeSurface(hardelSurface_12);

    if (!hardelTexture_12){
        fprintf(stderr, "error creating texture taildown: %s\n", SDL_GetError());

    }

    SDL_Surface* hardelSurface_13 = IMG_Load("tailright.png");
    if (!hardelSurface_13) {
        fprintf(stderr, "error loading image tailright:   %s\n", IMG_GetError());
    }

    hardelTexture_13 = SDL_CreateTextureFromSurface(renderer, hardelSurface_13);
    SDL_FreeSurface(hardelSurface_13);

    if (!hardelTexture_13){
        fprintf(stderr, "Error creating  texture tailright: %s\n", SDL_GetError());

    }

    SDL_Surface* hardelSurface_14 = IMG_Load("tailleft.png");
    if (!hardelSurface_14) {
        fprintf(stderr, "Error loading  image tailleft: %s\n", IMG_GetError());
    }

    hardelTexture_14 = SDL_CreateTextureFromSurface(renderer, hardelSurface_14);
    SDL_FreeSurface(hardelSurface_14);

    if (!hardelTexture_14){
        fprintf(stderr, "error creating texture tailleft:  %s\n", SDL_GetError());

    }


    SDL_Surface* mousesurface = IMG_Load("finalmouse.png");
    if (!mousesurface) {
        fprintf(stderr, "Error loading finalmouse image: %s\n", IMG_GetError());
    }

    mousef = SDL_CreateTextureFromSurface(renderer, mousesurface);
    SDL_FreeSurface(mousesurface);

    if (!mousef){
        fprintf(stderr, "Error creating finalmouse texture: %s\n", SDL_GetError());

    }

    SDL_Surface* youwinsurface = IMG_Load("youwin.png");
    if (!youwinsurface) {
        fprintf(stderr, "error loading youwin image: %s\n", IMG_GetError());
    }

    youwin = SDL_CreateTextureFromSurface(renderer, youwinsurface);
    SDL_FreeSurface(youwinsurface);

    if (!youwin){
        fprintf(stderr, "Error creating youwin texture: %s\n", SDL_GetError());

    }
    TTF_Font* font2 = TTF_OpenFont("Milk Mango.ttf", 80);
    TTF_Font* font1 = TTF_OpenFont("game_over.ttf", 240);
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                SDL_Quit ();
                exit(0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (pointInRectangleplay(event.button.x, event.button.y, &buttonplay)) {
                    if (level == 0){
                        SDL_RenderClear(renderer);
                        SDL_DestroyTexture(backgroundTexture);
                        SDL_DestroyRenderer(renderer);
                        level = 1;
                        goto DEBUT;
                    }
                }
            case SDL_KEYUP:
            break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    quit = 1 ;
                    SDL_Quit ();
                    exit(0);
                    break;
                case SDLK_UP:
                    if (currentdir != SNAKC_DOWN && snake_head->dir != SNAKC_DOWN )
                     currentdir = SNAKC_UP;
                    break;
                case SDLK_DOWN:
                if (currentdir != SNAKC_UP  && snake_head->dir != SNAKC_UP)
                currentdir = SNAKC_DOWN ;
                    break;
                case SDLK_LEFT:
                if (currentdir != SNAKC_RIGHT &&  snake_head->dir != SNAKC_RIGHT)
                currentdir = SNAKC_LEFT;
                    break;
                case SDLK_RIGHT:
                if (currentdir != SNAKC_LEFT  && snake_head->dir != SNAKC_LEFT)
                currentdir = SNAKC_RIGHT;
                    break;
                case SDLK_SPACE:
                    if (level != 0 ){
                    ps = 1;
                    pause(renderer, font1);
                    }
                    break ;
                }
            break ;
            }
        }
        if (level != 0 ){
        if(!update_game())
            break;
        ate_food();
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        if (currentdir == SNAKC_UP)
        render_head(renderer,hardelTexture);
        if (currentdir == SNAKC_DOWN)
        render_head(renderer,hardelTexture_1);
        if (currentdir == SNAKC_LEFT)
        render_head(renderer,hardelTexture_2);
        if (currentdir == SNAKC_RIGHT)
        render_head(renderer,hardelTexture_3);
        render_snake(renderer,hardelTexture_4,hardelTexture_5,hardelTexture_6,hardelTexture_7,hardelTexture_8,hardelTexture_9,
                     hardelTexture_11,hardelTexture_12,hardelTexture_13,hardelTexture_14);
        if (score == 6) {
            quit = 1;
            varnext = 1;
            break ;
        }
        if (score == 5)
        render_food(renderer, Food.x, Food.y,mousef );
        else
        render_food(renderer, Food.x, Food.y, hardelTexture_10);
        render_score(renderer, font, score);
        } else {
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);

    }
    SDL_DestroyTexture(backgroundTexture);
    SDL_RenderClear(renderer);
    while (1){
            if ((varnext == 0 ) || (varnext == 1 && level == 2)){
                  buttonret.x = 482;
                  buttonret.y = 340;
                  buttonret.h = 105;
                  buttonret.w = 200;
            }
            if (varnext == 0 || (varnext == 1 && level == 2)){
                buttonexit.x = 177 ;
                buttonexit.y = 347 ;
                buttonexit.h = 110  ;
                buttonexit.w = 195 ;
            }
        while (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT:
              SDL_Quit();
              exit(0);
         case SDL_MOUSEBUTTONDOWN:
             if (varnext == 1 && level == 1){
                 buttonret.x = 336;
                 buttonret.y = 360;
                 buttonret.h = 68 ;
                 buttonret.w = 185 ;
                 buttonexit.x = 85 ;
                 buttonexit.y = 372 ;
                 buttonexit.h = 104 ;
                 buttonexit.w = 180 ;

             }
             if (pointInRectangle(event.button.x, event.button.y, &buttonret)) {
                        score = 0 ;
                        SDL_RenderClear(renderer);
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyTexture(backgroundgameover);
                            if (varnext == 1){
                            varnext = 0;
                            quit = 0;
                            }
                        goto DEBUT ;
                    }
             else if (buttonexitrectangle(event.button.x, event.button.y, &buttonexit)){
                        SDL_RenderClear(renderer);
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyTexture(backgroundgameover);
                        SDL_DestroyWindow(window);
                        exit (0);
                        SDL_Quit();
             }

            if (pointInRectanglenext(event.button.x, event.button.y, &buttonnext)){
                if (varnext == 1){
                level = 2 ;
                score = 0 ;
                varnext = 0 ;
                quit = 0 ;
                SDL_RenderClear(renderer);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyTexture(backgroundgameover);
                goto DEBUT ;
                }
            }
                    break;
    }
        }
        SDL_RenderClear(renderer);
        if (varnext == 0){
        SDL_RenderCopy(renderer, backgroundgameover, NULL, NULL);
        render_scorefinal(renderer, font1, score);
        render_sco(renderer, font2, score);
        } else if (varnext == 1 && level == 1) {
        SDL_RenderCopy(renderer, backgroundnext, NULL, NULL);
        } else if (varnext == 1 && level == 2){
          SDL_RenderCopy(renderer, youwin, NULL, NULL);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(backgroundgameover);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    return 0;
}
