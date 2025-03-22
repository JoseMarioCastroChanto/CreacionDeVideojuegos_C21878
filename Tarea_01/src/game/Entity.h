#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 
#include <glm/glm.hpp>
#include <string>

class IENTITY {
protected:
    static int nextId;

};

template<typename TypeEntity>
class Entity : public IENTITY {

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
    void setDirectory(const std::string dir) { directory = dir; }
    std::string getDirectory() const { return directory; }

    void setImgPosX(int pos) { imgPos.x = pos; }
    void setImgPosY(int pos) { imgPos.y = pos; }
    glm::vec2 getImgPos() const { return imgPos; }

    void setTxtPosX(int pos) { txtPos.x = pos; }
    void setTxtPosY(int pos) { txtPos.y = pos; }
    glm::vec2 getTxtPos() const { return txtPos; }

    void setImgVelX(int vel) { imgVel.x = vel; }
    void setImgVelY(int vel) { imgVel.y = vel; }
    glm::vec2 getImgVel() const { return imgVel; }

    void setImgWidth(int width) {imgWidth = width;}
    int getImgWidth() const { return imgWidth; }

    void setImgHeight(int height) {txtHeight = height;}
    int getImgHeight() const { return imgHeight; }

    void setTxtWidth(int width) {txtWidth = width;}
    int getTxtWidth() const { return txtWidth; }

    void setTxtHeight(int height) {txtHeight = height;}
    int getTxtHeight() const { return txtHeight; }

    void setImgTexture(SDL_Texture* texture) { imgTexture = texture; }
    SDL_Texture* getImgTexture() const { return imgTexture; }

    void setTxtTexture(SDL_Texture* texture) { txtTexture = texture; }
    SDL_Texture* getTxtTexture() const { return txtTexture; }

    void setMessage(const std::string& msg) { message = msg; }
    std::string getMessage() const { return message; }

    void setImgAngle(double angle) { imgAngle = angle; }
    double getImgAngle() const { return imgAngle; }

    void setTxtAngle(double angle) { txtAngle = angle; }
    double getTxtAngle() const { return txtAngle; }

    void setSrcRect(int x, int y, int w, int h) {
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;
    }

    const SDL_Rect& getSrcRect() const {
    return srcRect;
    }

    static int getId(){
        static int id = nextId;
        return id;
    }

};

class Calavera{
public:
    Calavera() = default;
};

class Anillo{
public:
    Anillo() = default;
};

class Carta{
public:
    Carta() = default;

};

#endif