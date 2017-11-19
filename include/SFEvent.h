#ifndef SFEVENT_H
#define SFEVENT_H

#include <SFML/Window/Event.hpp>

class SFEvent
{
public:
    sf::Event& get();
    sf::Event::EventType type();
    sf::Event::SizeEvent size();

private:
    sf::Event event;
};

#endif 