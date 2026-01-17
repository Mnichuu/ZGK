//
// Created by stanislaw on 17.01.2026.
//

#include "InputHandler.h"
#include "GameController.h"
#include <osgGA/GUIEventAdapter>

InputHandler::InputHandler(GameController* controller)
    : _controller(controller)
{}

bool InputHandler::handle(const osgGA::GUIEventAdapter& ea,
                          osgGA::GUIActionAdapter&) {

    if (ea.getEventType() != osgGA::GUIEventAdapter::KEYDOWN)
        return false;

    switch (ea.getKey()) {

        case 'l':
        case 'L':
            _controller->toggleTableLock();
            return true;

        case 'a':
        case 'A':
            _controller->moveTable(-0.2f);
            return true;

        case 'd':
        case 'D':
            _controller->moveTable(0.2f);
            return true;

        case '1':
            _controller->setSelectedHole(0);
            return true;

        case '2':
            _controller->setSelectedHole(1);
            return true;

        case '3':
            _controller->setSelectedHole(2);
            return true;

        case osgGA::GUIEventAdapter::KEY_Space:
            _controller->hitSelectedHole();
            return true;
    }

    return false;
}
