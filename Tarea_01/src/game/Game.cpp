#include "Game.h"
#include <iostream>
#include <fstream>

Game:: Game(){
    this->calavera = new Entity<Calavera>();
    this->anillo = new Entity<Anillo>();
    this->carta = new Entity<Carta>();
 }

Game:: ~Game(){

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

    this->getConfig();

      //Creacion de la ventana
    this->window = SDL_CreateWindow(
        "Tarea 01", //Titulo de la ventana
        SDL_WINDOWPOS_CENTERED, //Pos x en la pantalla
        SDL_WINDOWPOS_CENTERED, //Pos y en la pantalla
        this->windowData.windowWidth, //Ancho
        this->windowData.windowHeight, //Alto
        SDL_WINDOW_SHOWN //Flags

    );

    // Crear renderer
    renderer = SDL_CreateRenderer(
      this->window,
      -1, //Driver de la pantalla
      0 // Flags  
    );

    //Cargar texto
    this->font = TTF_OpenFont(fontData.directory.c_str(), this->fontData.size);

    this->isRunning = true;
    this->initEntity(this->calavera);
    this->initEntity(this->anillo);
    this->initEntity(this->carta);

 }

template<typename T>
void Game::initEntity(Entity<T>* entity){
     
     // Inicilaizar datos de la imagen
    SDL_Surface* imgSurface = IMG_Load(entity->getDirectory().c_str());
    entity->setImgTexture (SDL_CreateTextureFromSurface(this->renderer, imgSurface));
    SDL_FreeSurface(imgSurface);
    entity->setSrcRect(0,0,
    entity->getImgWidth(),entity->getImgHeight());
     // Inicilaizar datos del texto
     SDL_Surface* txtSurface = TTF_RenderText_Solid(
        this->font, //fuente
        entity->getMessage().c_str(), //texto
        this->fontData.fontColor//color
        );
    entity->setTxtTexture (SDL_CreateTextureFromSurface(this->renderer, txtSurface));
    SDL_FreeSurface(txtSurface);

}

void Game::getConfig(){
    std::string fileName = "config.txt";
    std::ifstream inputFile(fileName);
    std::string label;

    // Obtener datos del archivo de configuacion
    while(inputFile >> label){
        if(label.compare("window") == 0){
            inputFile >> this->windowData.windowWidth;
            inputFile >> this->windowData.windowHeight;
            inputFile >> this->windowData.r;
            inputFile >> this->windowData.g;
            inputFile >> this->windowData.b;
        }
        else if(label.compare("font") == 0){
            int color = 0;
            inputFile >> this->fontData.directory;
            inputFile >> color;
            this->fontData.fontColor.r = color;
            inputFile >> color;
            this->fontData.fontColor.g = color;
            inputFile >> color;
            this->fontData.fontColor.b = color;
            inputFile >> this->fontData.size;

        }
        else if(label.compare("entity") == 0){
            std::string name = "";
            inputFile >> name;
            if(name.compare("calavera") == 0){
                this->loadEntity(this->calavera,inputFile,name);   
            }
            else if(name.compare("anillo") == 0){
                this->loadEntity(this->anillo,inputFile,name);      
            }
            else if(name.compare("carta") == 0){
                this->loadEntity(this->carta,inputFile,name);   
            }
        }
    }

}
template<typename T>
void Game::loadEntity(Entity<T>* entity, std::ifstream& inputFile, std::string name) {
    std::string directory;
    int width, height, posX, posY, velX, velY;
    double angle;

    inputFile >> directory >> width >> height >> posX >> posY >> velX >> velY >> angle;

    //Cargar los valres de la imagen
    entity->setDirectory(directory);
    entity->setImgWidth(width);
    entity->setImgHeight(height);
    entity->setImgPosX(posX);
    entity->setImgPosY(posY);
    entity->setImgVelX(velX);
    entity->setImgVelY(velY);
    entity->setImgAngle(angle);

    // Calcular el centro de la imagen
    int centerX = posX + width / 2;
    int centerY = posY + height / 2;

    // Calcular la posición del texto para que su centro coincida con el centro de la imagen
    // Se supone el ancho y la altura igual al de la imagen
    int txtPosX = centerX - (width / 2); 
    int txtPosY = centerY - (height / 2); 

    // Establecer los valores en la entidad
    entity->setMessage(name); 
    entity->setTxtWidth(width+20); // se ajusta para que sea legible
    entity->setTxtHeight(height-10); // se ajusta para que sea legible
    entity->setTxtPosX(txtPosX);
    entity->setTxtPosY(txtPosY);
    entity->setTxtAngle(angle);

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
                } else if (sdlEvent.key.keysym.sym == SDLK_p) {  
                    this->isPaused = !this->isPaused;
                     if (this->isPaused) {
                        this->wasPaused = true;
                    }  
                }
                break;
            
            default:
                break;
            }

        }
}

void Game::update() {
    if (this->isPaused) {
        // No actualizar nada mientras está pausado
        return;
    }

    // Evitar un salto en deltaTime
    if (this->wasPaused) {
        this->mPrvsFrame = SDL_GetTicks();  
        this->wasPaused = false;  
    }

    // Calcular la espera
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - this->mPrvsFrame);
    if (0 < timeToWait && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    // Calcular deltaTime en segundos
    double deltaTime = (SDL_GetTicks() - this->mPrvsFrame) / 1000.0;
    this->mPrvsFrame = SDL_GetTicks();

    this->updateEntity(this->calavera, deltaTime);
    this->updateEntity(this->anillo, deltaTime);
    this->updateEntity(this->carta, deltaTime);
}

template<typename T>
void Game::updateEntity(Entity<T>* entity, double deltaTime) {
    // Nuevas posiciones
    double newPosX = entity->getImgPos().x;
    double newPosY = entity->getImgPos().y;
    newPosX += entity->getImgVel().x * deltaTime;
    newPosY += entity->getImgVel().y * deltaTime;

    // Dimensiones de la imagen
    int width = entity->getImgWidth();
    int height = entity->getImgHeight();

      // Verificar choque y rebotar
    if (newPosX <= 0 || newPosX + width >= this->windowData.windowWidth) {
        entity->setImgVelX(-entity->getImgVel().x);
    } 
    
    if (newPosY <= 0 || newPosY + height >= this->windowData.windowHeight) {
        entity->setImgVelY(-entity->getImgVel().y);
    }

  
    entity->setImgPosX(newPosX);
    entity->setImgPosY(newPosY);

    // Calcular el centro de la imagen
    int centerX = static_cast<int>(newPosX + width / 2);
    int centerY = static_cast<int>(newPosY + height / 2);

    // Calcular la posición del texto
    int txtPosX = centerX - (entity->getTxtWidth() / 2);
    int txtPosY = centerY - (entity->getTxtHeight() / 2);

    // Actualizar la posición del texto
    entity->setTxtPosX(txtPosX);
    entity->setTxtPosY(txtPosY);
  
    
}


void Game::render(){
    //Establece el color con el que se va a dibujar la ventana
    SDL_SetRenderDrawColor(this->renderer, this->windowData.r, 
    this->windowData.g, this->windowData.b, 255);
    //Limpiar ventana
    SDL_RenderClear(this->renderer);

    this->renderEntity(this->calavera);
    this->renderEntity(this->anillo);
    this->renderEntity(this->carta);

    //Actualizar ventana
    SDL_RenderPresent(this->renderer);

}

template<typename T>
void Game::renderEntity(Entity<T>* entity){


    SDL_Rect imgDstRect = {
        static_cast<int>(entity->getImgPos().x),
        static_cast<int>(entity->getImgPos().y),
        static_cast<int>(entity->getImgWidth()),
        static_cast<int>(entity->getImgHeight())
    };

    SDL_Rect txtDstRect = {
        static_cast<int>(entity->getTxtPos().x),
        static_cast<int>(entity->getTxtPos().y),
        static_cast<int>(entity->getTxtWidth()),
        static_cast<int>(entity->getTxtHeight())
    };

    //Dibujar imagen
    SDL_RenderCopyEx(
        this->renderer,
        entity->getImgTexture(),
        &entity->getSrcRect(),
        &imgDstRect,
        entity->getImgAngle(),
        NULL,
        SDL_FLIP_NONE
    );

    //Dibujar texto
    SDL_RenderCopyEx(
        this->renderer,
        entity->getTxtTexture(),
        NULL, // si es null dibuja toda la textura
        &txtDstRect,
        entity->getTxtAngle(),
        NULL,
        SDL_FLIP_NONE
    );


}

void Game::run(){
    while(this->isRunning){
        processInput();
        update();
        render();
            }
 }

void Game::destroy(){
    // Liberar recursos
    this->destroyEntity(this->calavera);
    this->destroyEntity(this->anillo);
    this->destroyEntity(this->carta);
    delete calavera;
    delete anillo;
    delete carta;
   

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    TTF_CloseFont(this->font);

    TTF_Quit();
    SDL_Quit();
 }

template<typename T>
void Game::destroyEntity(Entity<T>* entity){
    SDL_DestroyTexture(entity->getImgTexture());
    SDL_DestroyTexture(entity->getTxtTexture());
}
