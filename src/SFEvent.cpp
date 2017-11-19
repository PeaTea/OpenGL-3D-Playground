#include "SFEvent.h"

sf::Event& SFEvent::get()
{
    return event;
}

sf::Event::EventType SFEvent::type()
{
    return event.type;
}

sf::Event::SizeEvent SFEvent::size()
{
    return event.size;
}