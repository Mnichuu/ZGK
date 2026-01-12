//
// Created by stanislaw on 12.01.2026.
//

#ifndef PROJEKT3D_PICKHANDLER_H
#define PROJEKT3D_PICKHANDLER_H

#pragma once
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include "GameController.h"

class PickHandler : public osgGA::GUIEventHandler {
public:
    PickHandler(osg::ref_ptr<GameController> controller)
        : _gameController(controller) {}

    virtual bool handle(const osgGA::GUIEventAdapter& ea,
                        osgGA::GUIActionAdapter& aa) override;

private:
    osg::ref_ptr<GameController> _gameController;
};



#endif //PROJEKT3D_PICKHANDLER_H