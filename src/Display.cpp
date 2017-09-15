#include "Display.h"
#include <iostream>
#include "Camera.h"

static Camera camera(glm::vec3(2000.0f, 0.0f, 200.0f));

Display::Display(int width, int height, std::string title, sf::Uint32 style)
	:	should_close	{false}
	,	last_mousex	{width / 2.0f}
	,	last_mousey	{height / 2.0f}
{
	sf::ContextSettings settings;
	settings.minorVersion = 3;
	settings.majorVersion = 3;
	settings.antialiasingLevel = 4;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.attributeFlags = sf::ContextSettings::Core;

	window.create(sf::VideoMode(width, height), title, style, settings);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		throw std::runtime_error("Failed to init GLEW!");
	}

	render_game = new RenderGame(width, height);
}

Display::~Display()
{
	if(render_game) delete render_game;
}

sf::Window& Display::get()
{
	return window;
}

void Display::update()
{
	window.display();
	//std::cout << camera.yaw << std::endl;
}

void Display::render()
{
	render_game->render(camera);
}

void Display::process_keyboard_input(float deltatime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		close();
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{	camera.process_keyboard(CameraMovement::FORWARD, deltatime, *render_game);
	} if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		camera.process_keyboard(CameraMovement::LEFT, deltatime, *render_game);
	} if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		camera.process_keyboard(CameraMovement::BACKWARD, deltatime, *render_game);
	} if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		camera.process_keyboard(CameraMovement::RIGHT, deltatime, *render_game);
	} if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		camera.process_keyboard(CameraMovement::UP, deltatime, *render_game);
	} if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		camera.process_keyboard(CameraMovement::DOWN, deltatime, *render_game);
	}
}

void Display::restrain_camera_y(bool y_mov)
{
	camera.restrain_y_mov(y_mov);
}

void Display::process_mouse_movement(float deltatime)
{
	last_mousex = sf::Mouse::getPosition(window).x;
	last_mousey = sf::Mouse::getPosition(window).y;

	float xoffset = last_mousex - window.getSize().x / 2;
	float yoffset = window.getSize().y / 2 - last_mousey;

	camera.process_mouse_movement(xoffset, yoffset);

	sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
}

void Display::close()
{
	should_close = true;
	window.close();
}

void Display::switch_wireframe(bool wireframe)
{
	if(wireframe)	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
