#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 
#include <glm/glm.hpp>
#include <string>


class Entity {

    std::string directory;

   //Atributos de la imagen
    SDL_Texture* imgTexture = nullptr;
    glm::vec2 imgPos = glm::vec2();
    glm::vec2 imgVel = glm::vec2();
    int imgWidth = 0;
    int imgHeight=0;
    SDL_Rect srcRect = {0,0,0,0};
    double imgAngle = 0.0;

    //Atributos del texto
    SDL_Texture* txtTexture = nullptr;
    std::string message = "";
    glm::vec2 txtPos = glm::vec2();
    int txtWidth = 0;
    int txtHeight=0;
    double txtAngle = 0.0;

public:
    // Setters y Getters
    void setDirectory(const std::string dir);
    std::string getDirectory() const;

    void setImgPosX(double pos);
    void setImgPosY(double pos);
    glm::vec2 getImgPos() const;

    void setTxtPosX(double pos);
    void setTxtPosY(double pos);
    glm::vec2 getTxtPos() const;

    void setImgVelX(double vel);
    void setImgVelY(double vel);
    glm::vec2 getImgVel() const;

    void setImgWidth(int width);
    int getImgWidth() const;

    void setImgHeight(int height);
    int getImgHeight() const;

    void setTxtWidth(int width);
    int getTxtWidth() const;

    void setTxtHeight(int height);
    int getTxtHeight() const;

    void setImgTexture(SDL_Texture* texture);
    SDL_Texture* getImgTexture() const;

    void setTxtTexture(SDL_Texture* texture);
    SDL_Texture* getTxtTexture() const;

    void setMessage(const std::string& msg);
    std::string getMessage() const;

    void setImgAngle(double angle);
    double getImgAngle() const;

    void setTxtAngle(double angle);
    double getTxtAngle() const;

    void setSrcRect(int x, int y, int w, int h);
    const SDL_Rect& getSrcRect() const;
};


#endif