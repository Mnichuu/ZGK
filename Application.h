//
// Created by stanislaw on 12.01.2026.
//

#ifndef PROJEKT3D_APPLICATION_H
#define PROJEKT3D_APPLICATION_H

#pragma once
#include <osgViewer/Viewer>
#include <osg/Group>
#include "SceneBuilder.h"
#include "PickHandler.h"
#include "UpdateCallback.h"
#include "GameController.h"

class Application {
public:
    Application();
    ~Application();

    void init();
    void run();

private:
    osg::ref_ptr<osgViewer::Viewer> _viewer;
    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<GameController> _gameController;
};



#endif //PROJEKT3D_APPLICATION_H