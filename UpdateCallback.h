//
// Created by stanislaw on 12.01.2026.
//

#ifndef PROJEKT3D_UPDATECALLBACK_H
#define PROJEKT3D_UPDATECALLBACK_H

#pragma once
#include <osg/NodeCallback>
#include <osg/NodeVisitor>
#include <osg/Timer>
#include "GameController.h"

class UpdateCallback : public osg::NodeCallback {
public:
    UpdateCallback(osg::ref_ptr<GameController> controller)
        : _gameController(controller),
          _lastTime(osg::Timer::instance()->tick()) {}

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) override;

private:
    osg::ref_ptr<GameController> _gameController;
    osg::Timer_t _lastTime;
};



#endif //PROJEKT3D_UPDATECALLBACK_H