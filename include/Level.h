#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <SFML/Graphics/Image.hpp>
#include "GLTexture.h"

class Level
{
public:
	Level(int width, int height);
	Level(const std::string& path);
	~Level();

	int get_width() const;
	int get_height() const;
	const unsigned char* get_data();
	sf::Color get_pixel(unsigned int x, unsigned int y) const;
	void draw(std::vector<GLTexture>& textures);
	//void draw_transparent(std::vector<GLTexture>& textures);

private:
	int width;
	int height;
	sf::Image image;
};

#endif