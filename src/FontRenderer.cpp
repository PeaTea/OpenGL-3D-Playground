#include "FontRenderer.h"
#include "OutUtils.h"
#include "BasicRenderer.h"
#include "Utils.h"

#include <stb_image.h>

FontRenderer::FontRenderer()
    : m_start{FONT_ZERO}
{

}

FontRenderer::FontRenderer(conststrref font_path, const bool& erase_data, const bool& use_sheet)
    :   m_start {FONT_ZERO}
{
    font(font_path, FONT_SPACE, FONT_Z, true, use_sheet);
}


void FontRenderer::font(conststrref font_path, const Alphabet& start, const Alphabet& end, const bool& erase_data, const bool& use_sheet)
{
    if(erase_data)  
    {
        m_font.clear();
    }

    m_start = start - 1;

    if(!use_sheet)
    {
        for(; ++m_start <= end;)
        {
            std::string filename = m_start > FONT_SLASH_LEFT && m_start < FONT_SQUARE_BRCKT_OPEN 
                ? font_path + "/" + m_start + ".png" 
                : font_path + "/" + std::to_string((int)m_start) + ".png";
            
            if(file::exists(filename))
                m_font[m_start] = {filename, false, CLAMP_TO_EDGE, CLAMP_TO_EDGE, NEAREST, NEAREST, false};
        }
    }
    else
    {
        logging::log("[FontRenderer] -> SpriteSheets not yet supported", lstream::fatal_error);
    }
}


void FontRenderer::load_numbers(conststrref font_path, const bool& erase_data, const bool& use_sheet)
{
    font(font_path, FONT_ZERO, FONT_NINE, erase_data, use_sheet);
}


void FontRenderer::load_upper_letters(conststrref font_path, const bool& erase_data, const bool& use_sheet)
{
    font(font_path, FONT_A, FONT_Z, erase_data, use_sheet);
}


void FontRenderer::load_other(conststrref font_path, const bool& erase_data, const bool& use_sheet)
{
    font(font_path, FONT_SPACE, FONT_SLASH_LEFT, erase_data, use_sheet);
    font(font_path, FONT_SQUARE_BRCKT_OPEN, FONT_SQUARE_BRCKT_CLOSE, false, use_sheet);
}


void FontRenderer::draw(conststrref text, const glm::vec3& pos, const Vec2<float>& size, const float& yoffset, const glm::vec4& color)
{
    std::vector<std::string> split_by_newlines;
    utils::split(text, '\n', split_by_newlines);

    int j = 1;
    for(const auto& s : split_by_newlines)
    {
        for(int i{0}; i < s.size(); i++)
        {
            BasicRenderer::draw_sprite(m_font[text[i]].id(), {pos.x + i * size.x, pos.y + j * (size.y + yoffset), 1}, size, color);
        }
        ++j;
    }
}