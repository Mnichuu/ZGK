//
// Created by stanislaw on 12.01.2026.
//

#ifndef PROJEKT3D_SCENEBUILDER_H
#define PROJEKT3D_SCENEBUILDER_H

#pragma once
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include "GameController.h"
#include "Mole.h"

class SceneBuilder {
public:
    SceneBuilder();
    ~SceneBuilder();

    osg::ref_ptr<osg::Group> createScene(osg::ref_ptr<GameController> gameController);

private:
    osg::ref_ptr<osg::MatrixTransform> createTable();
    osg::ref_ptr<Mole> createMole(const osg::Vec3& position);
};

#endif //PROJEKT3D_SCENEBUILDER_H