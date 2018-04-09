#pragma once

#include "Types.h"
#include "GLTexture.h"
#include "Vec2.h"

#include <unordered_map>
#include <glm/glm.hpp>

enum Alphabet
{
    FONT_SPACE = 32,
    FONT_DOT,
    FONT_SLASH_LEFT,
    FONT_ZERO = 48,
    FONT_ONE,
    FONT_TWO,
    FONT_THREE,
    FONT_FOUR,
    FONT_FIVE,
    FONT_SIX,
    FONT_SEVEN,
    FONT_EIGHT,
    FONT_NINE,
    FONT_A = 65,
    FONT_B,
    FONT_C,
    FONT_D,
    FONT_E,
    FONT_F,
    FONT_G,
    FONT_H,
    FONT_I,
    FONT_J,
    FONT_K,
    FONT_L,
    FONT_M,
    FONT_N,
    FONT_O,
    FONT_P,
    FONT_Q,
    FONT_R,
    FONT_S,
    FONT_T,
    FONT_U,
    FONT_V,
    FONT_W,
    FONT_X,
    FONT_Y,
    FONT_Z,
    FONT_SQUARE_BRCKT_OPEN = 91,
    FONT_SLASH_RIGHT,
    FONT_SQUARE_BRCKT_CLOSE
};

class FontRenderer
{
public:
    FontRenderer();
    FontRenderer(conststrref font_path, const bool& erase_data = false, const bool& use_sheet = false);

    void font(conststrref font_path, const Alphabet& start, const Alphabet& end, const bool& erase_data = false, const bool& use_sheet = false);

    void load_numbers(conststrref font_path, const bool& erase_data = false, const bool& use_sheet = false);
    void load_upper_letters(conststrref font_path, const bool& erase_data = false, const bool& use_sheet = false);
    void load_other(conststrref font_path, const bool& erase_data = false, const bool& use_sheet = false);

    void draw(conststrref text, const glm::vec3& pos, const Vec2<float>& size = {1, 1}, const float& yoffset = 0, const glm::vec4& color = {1, 1, 1, 1});

private:
    std::unordered_map<char, GLTexture> m_font;
    char m_start;
};
