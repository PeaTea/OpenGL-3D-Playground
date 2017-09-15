#include "Display.h"
#include "SFEvent.h"
#include <iostream>
#include "Game.h"

#define DEBUG
#define FULLSCREEN 1
static bool wire_frame = false;
static bool y_mov_switch = false;
static bool out_of_focus = false;

// Everything I need to know for a PC platform
namespace PC
{
#if FULLSCREEN
	constexpr int WIDTH = 1920;
	constexpr int HEIGHT = 1080;
#else
	constexpr int WIDTH = 800;
	constexpr int HEIGHT = 600;
#endif
	const std::string TITLE = "PeaTea's OpenGL Scratchpad";
}


int main()
{
	// Creates a display
#if FULLSCREEN
	Display display(PC::WIDTH, PC::HEIGHT, PC::TITLE, sf::Style::Fullscreen);
#else
	Display display(PC::WIDTH, PC::HEIGHT, PC::TITLE, sf::Style::Default);
#endif

	sf::Clock clock;
	float delta_time = 0.0f;
	float current_time = 0.0f;
	float last_time = 0.0f;

	SFEvent sfevent;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//glFrontFace(GL_CW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	while(!display.should_close)
	{
		current_time = (float)clock.getElapsedTime().asMilliseconds();
		delta_time = current_time - last_time;
		last_time = current_time;

		while(display.get().pollEvent(sfevent.get()))
		{
			switch(sfevent.type())
			{
			case sf::Event::Closed:
				display.close();
				break;
			case sf::Event::Resized:
				glViewport(0, 0, sfevent.size().width, sfevent.size().height);
				break;
#ifdef DEBUG
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
				{
					display.switch_wireframe(!wire_frame);
					wire_frame = !wire_frame;
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
				{
					display.restrain_camera_y(!y_mov_switch);
					y_mov_switch = !y_mov_switch;
				}
				break;
#endif
			case sf::Event::LostFocus:
				out_of_focus = true;
				break;
			case sf::Event::GainedFocus:
				out_of_focus = false;
				break;
			}
		}

		if(!out_of_focus)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if FULLSCREEN
			display.process_mouse_movement(delta_time);
#endif
			display.process_keyboard_input(delta_time);

			display.render();
			display.update(); // Also swaps buffers

			//std::cout << glGetError() << std::endl;
		}
	}
}
