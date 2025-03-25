#include "Entity.h"

void Entity::setDirectory(const std::string dir) { directory = dir; }
std::string  Entity::getDirectory() const { return directory; }

void  Entity::setImgPosX(double pos) { imgPos.x = pos; }
void  Entity::setImgPosY(double pos) { imgPos.y = pos; }
glm::vec2  Entity::getImgPos() const { return imgPos; }

void  Entity::  setTxtPosX(double pos) { txtPos.x = pos; }
void  Entity:: setTxtPosY(double pos) { txtPos.y = pos; }
glm::vec2  Entity::  getTxtPos() const { return txtPos; }

void  Entity::setImgVelX(double vel) { imgVel.x = vel; }
void  Entity::setImgVelY(double vel) { imgVel.y = vel; }
glm::vec2  Entity::getImgVel() const { return imgVel; }

void  Entity::setImgWidth(int width) {imgWidth = width;}
int  Entity::getImgWidth() const { return imgWidth; }

void  Entity::setImgHeight(int height) {imgHeight = height;}
int  Entity::getImgHeight() const { return imgHeight; }

void  Entity::setTxtWidth(int width) {txtWidth = width;}
int  Entity::getTxtWidth() const { return txtWidth; }

void  Entity::setTxtHeight(int height) {txtHeight = height;}
int  Entity::getTxtHeight() const { return txtHeight; }

void  Entity::setImgTexture(SDL_Texture* texture) { imgTexture = texture; }
SDL_Texture*  Entity::getImgTexture() const { return imgTexture; }

void  Entity::setTxtTexture(SDL_Texture* texture) { txtTexture = texture; }
SDL_Texture*  Entity::getTxtTexture() const { return txtTexture; }

void  Entity::setMessage(const std::string& msg) { message = msg; }
std::string  Entity::getMessage() const { return message; }

void  Entity::setImgAngle(double angle) { imgAngle = angle; }
double  Entity::getImgAngle() const { return imgAngle; }

void  Entity::setTxtAngle(double angle) { txtAngle = angle; }
double  Entity::getTxtAngle() const { return txtAngle; }

void  Entity::setSrcRect(int x, int y, int w, int h) {
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;
    }

const SDL_Rect&  Entity::getSrcRect() const {
    return srcRect;
    }