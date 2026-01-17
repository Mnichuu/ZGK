// language: cpp
// File: `SceneBuilder.cpp`
#include "SceneBuilder.h"

#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/Box>
#include <osg/Cylinder>
#include <osg/Material>
#include <osg/StateSet>

osg::ref_ptr<osg::Group> SceneBuilder::createScene() {
    osg::ref_ptr<osg::Group> root = new osg::Group();

    // parametry stołu
    const float tableWidth = 3.0f;
    const float tableDepth = 1.5f;
    const float tableThickness = 0.12f;
    const float tableZ = tableThickness * 0.5f;

    // blat stołu jako box
    osg::ref_ptr<osg::Box> tableBox = new osg::Box(osg::Vec3(0.0f, 0.0f, tableZ),
                                                   tableWidth, tableDepth, tableThickness);
    osg::ref_ptr<osg::ShapeDrawable> tableDrawable = new osg::ShapeDrawable(tableBox);
    tableDrawable->setColor(osg::Vec4(0.55f, 0.33f, 0.12f, 1.0f));

    osg::ref_ptr<osg::Geode> tableGeode = new osg::Geode();
    tableGeode->addDrawable(tableDrawable);

    osg::ref_ptr<osg::Material> mat = new osg::Material();
    mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.55f, 0.33f, 0.12f, 1.0f));
    tableGeode->getOrCreateStateSet()->setAttributeAndModes(mat, osg::StateAttribute::ON);

    root->addChild(tableGeode);

    // trzy dziury jako ciemne cylindry lekko pod powierzchnią blatu
    const float holeRadius = 0.28f;
    const float holeHeight = 0.10f;
    const float holeZ = tableZ - tableThickness * 0.5f + holeHeight * 0.5f - 0.01f;
    const float xOffsets[3] = { -0.9f, 0.0f, 0.9f };

    for (int i = 0; i < 3; ++i) {
        osg::ref_ptr<osg::Cylinder> hole = new osg::Cylinder(osg::Vec3(xOffsets[i], 0.0f, holeZ),
                                                             holeRadius, holeHeight);
        hole->setAxis(osg::Vec3(0.0f, 0.0f, 1.0f));
        osg::ref_ptr<osg::ShapeDrawable> holeDrawable = new osg::ShapeDrawable(hole);
        holeDrawable->setColor(osg::Vec4(0.02f, 0.02f, 0.02f, 1.0f));

        osg::ref_ptr<osg::Geode> holeGeode = new osg::Geode();
        holeGeode->addDrawable(holeDrawable);
        holeGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);

        root->addChild(holeGeode);
    }

    // prosty "podest"/podłoga
    osg::ref_ptr<osg::Box> floorBox = new osg::Box(osg::Vec3(0.0f, 0.0f, -0.5f), 10.0f, 10.0f, 1.0f);
    osg::ref_ptr<osg::ShapeDrawable> floorDrawable = new osg::ShapeDrawable(floorBox);
    floorDrawable->setColor(osg::Vec4(0.2f, 0.6f, 0.2f, 1.0f));
    osg::ref_ptr<osg::Geode> floorGeode = new osg::Geode();
    floorGeode->addDrawable(floorDrawable);
    root->addChild(floorGeode);

    return root;
}
