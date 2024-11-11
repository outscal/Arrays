#include "../../header/Event/EventPollingManager.h"
#include "../../header/GameWindow/GameWindowManager.h"
#include <iostream>

namespace Event
{
    using namespace GameWindow;

    EventPollingManager::EventPollingManager(sf::RenderWindow* window) { game_window = window; }

    EventPollingManager::~EventPollingManager() = default;


    void EventPollingManager::update()
    {
        updateButtonsState(left_mouse_button_state);
        updateButtonsState(right_mouse_button_state);
    }

    void EventPollingManager::processEvents()
    {
        if (isGameWindowOpen())
        {
            // Iterate over all events in the queue.
            while (game_window->pollEvent(game_event))
            {
                if (gameWindowWasClosed() || hasQuitGame())
                    game_window->close();
            }
        }
    }

    void EventPollingManager::updateButtonsState(ButtonState& button_state)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            switch (button_state)
            {
            case ButtonState::RELEASED:
                button_state = ButtonState::PRESSED;
                break;
            case ButtonState::PRESSED:
                button_state = ButtonState::HELD;
                break;
            }
        }
        else
        {
            button_state = ButtonState::RELEASED;
        }
    }

    bool EventPollingManager::isGameWindowOpen() { return game_window != nullptr; }

    bool EventPollingManager::gameWindowWasClosed() { return game_event.type == sf::Event::Closed; }

    bool EventPollingManager::hasQuitGame() { return (isKeyboardEvent() && pressedEscapeKey()); }

    bool EventPollingManager::isKeyboardEvent() { return game_event.type == sf::Event::KeyPressed; } 

    bool EventPollingManager::pressedEscapeKey() { return game_event.key.code == sf::Keyboard::Escape; }

    bool EventPollingManager::pressedLeftMouseButton() { return left_mouse_button_state == ButtonState::PRESSED; }

    bool EventPollingManager::pressedRightMouseButton() { return right_mouse_button_state == ButtonState::PRESSED; }
}