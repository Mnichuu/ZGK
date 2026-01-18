#ifndef PROJEKT3D_INPUTHANDLER_H
#define PROJEKT3D_INPUTHANDLER_H

#include <osgGA/GUIEventHandler>

class GameController;

class InputHandler : public osgGA::GUIEventHandler {
public:
    InputHandler(GameController* controller);

    bool handle(const osgGA::GUIEventAdapter& ea,
                osgGA::GUIActionAdapter& aa) override;

private:
    GameController* _controller;

    bool _dragging = false;
    float _lastX = 0.0f;
};

#endif
