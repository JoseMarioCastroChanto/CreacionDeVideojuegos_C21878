#include "Game.h"
#include <iostream>

Game:: Game(){
 std::cout << "Se ejecuta constructor Game"<< std::endl; 
 }

Game:: ~Game(){
 std::cout << "Se ejecuta destructor Game"<< std::endl; 
 }

 void Game::init(){
    // Inicializar SDL2
     if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Error al inicializar SDL" << std::endl;
        return;
    }

    if(TTF_Init() < 0){
         std::cout << "Error al inicializar SDL TTF" << std::endl;
        return;

    }

    this->windowWidth= 800;
    this->windowHeight = 600;

      //Creacion de la ventana
    this->window = SDL_CreateWindow(
        "MiniMotor", //Titulo de la ventana
        SDL_WINDOWPOS_CENTERED, //Pos x en la pantalla
        SDL_WINDOWPOS_CENTERED, //Pos y en la pantalla
        this->windowWidth, //Ancho
        this->windowHeight, //Alto
        SDL_WINDOW_SHOWN //Flags

    );

    // Crear renderer
    renderer = SDL_CreateRenderer(
      this->window,
      -1, //Driver de la pantalla
      0 // Flags  
    );

    //Cargar texto
    this->fontSize = 20;
    this->font = TTF_OpenFont("./assets/fonts/press_start_2p.ttf", this->fontSize);

    this->isRunning = true;

    // Inicilaizar datos de la imagen
    this->imageWidth = 32;
    this->imageHeight = 32;
    this->pos.x = (this->windowWidth /2) - (this->imageWidth / 2);
    this->pos.y = (this->windowHeight /2) - (this->imageHeight/ 2);
    SDL_Surface* imgSurface = IMG_Load("./assets/images/skull_00.png");
    this->imgTexture = SDL_CreateTextureFromSurface(this->renderer, imgSurface);
    SDL_FreeSurface(imgSurface);
    this->srcRect.x = 0;
    this->srcRect.y = 0;
    this->srcRect.w = this->imageWidth;
    this->srcRect.h = this->imageHeight;

     // Inicilaizar datos del texto
     this->message = "miniMotor";
     this->fontColor.r = 255;
     SDL_Surface* txtSurface = TTF_RenderText_Solid(
        this->font, //fuente
        this->message.c_str(), //texto
        this->fontColor //color
        );
    this->txtTexture = SDL_CreateTextureFromSurface(this->renderer, txtSurface);
    this->txtWidth= txtSurface->w;
    this->txtHeight= txtSurface->h;
    this->txtPos.x = (this->windowWidth / 2) - (this->txtWidth / 2);
    this->txtPos.y = 20;
    SDL_FreeSurface(txtSurface);


 }

void Game::processInput(){
     //Registro que almacena los datos de evento
        SDL_Event sdlEvent;

        // SDL_PollEvent saca de la cola de eventos de SDL un evento pendiente y lo
        // almacena en un registro de tipo SDL_Event
        while(SDL_PollEvent(&sdlEvent)){
            switch(sdlEvent.type){
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if(sdlEvent.key.keysym.sym == SDLK_ESCAPE){
                    isRunning = false;
                }
                break;
            default:
                break;
            }

        }
}

void::Game::render(){
    //Establece el color con el que se va a dibujar la ventana
    SDL_SetRenderDrawColor(this->renderer, 30, 30, 30, 255);
    //Limpiar ventana
    SDL_RenderClear(this->renderer);

    SDL_Rect imgDstRect = {
        static_cast<int>(this->pos.x),
        static_cast<int>(this->pos.y),
        static_cast<int>(this->imageWidth),
        static_cast<int>(this->imageHeight)
    };

    SDL_Rect txtDstRect = {
        static_cast<int>(this->txtPos.x),
        static_cast<int>(this->txtPos.y),
        static_cast<int>(this->txtWidth),
        static_cast<int>(this->txtHeight)
    };

    //Dibujar imagen
    SDL_RenderCopyEx(
        this->renderer,
        this->imgTexture,
        &this->srcRect,
        &imgDstRect,
        this->angle,
        NULL,
        SDL_FLIP_NONE
    );

    //Dibujar texto
    SDL_RenderCopyEx(
        this->renderer,
        this->txtTexture,
        NULL, // si es null dibuja toda la textura
        &txtDstRect,
        this->txtAngle,
        NULL,
        SDL_FLIP_NONE
    );

    //Actualizar ventana
    SDL_RenderPresent(this->renderer);

}

void Game::run(){
    while(this->isRunning){
        processInput();
        //update();
        render();
        }
 }

void Game::destroy(){
    // Liberar recursos
    SDL_DestroyTexture(this->imgTexture);
    SDL_DestroyTexture(this->txtTexture);

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    TTF_Quit();
    SDL_Quit();
 }

