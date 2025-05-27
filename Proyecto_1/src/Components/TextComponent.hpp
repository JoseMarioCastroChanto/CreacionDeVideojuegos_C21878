#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <SDL2/SDL.h>
#include <string>

/**
 * @brief Component to handle text rendering attributes.
 * 
 * Contains the text string, font identifier, text color, and
 * dimensions (width and height) of the rendered text.
 */
struct TextComponent{
    std::string text;      ///< The text content to render
    std::string fontId;    ///< Identifier for the font used
    SDL_Color color;       ///< Color of the text (RGBA)
    int width;             ///< Width of the rendered text
    int height;            ///< Height of the rendered text

    /**
     * @brief Constructor for TextComponent.
     * 
     * @param text Initial text string (default empty)
     * @param fontId Font identifier string (default empty)
     * @param r Red component of text color (default 0)
     * @param g Green component of text color (default 0)
     * @param b Blue component of text color (default 0)
     * @param a Alpha component of text color (default 0)
     */
    TextComponent(const std::string& text = "", const std::string& fontId = "",
                  u_char r = 0, u_char g = 0, u_char b = 0, u_char a = 0) {
        this->text = text;
        this->fontId = fontId;
        this->color.r = r;
        this->color.g = g;
        this->color.b = b;
        this->color.a = a;
        this->width = 0;
        this->height = 0;
    }
};

#endif
