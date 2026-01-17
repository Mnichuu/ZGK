#include "SceneBuilder.h"

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/StateSet>

SceneBuilder::SceneData SceneBuilder::createScene() {
    SceneData data;
    data.root = new osg::Group();

    // =========================
    // PARAMETRY STOŁU
    // =========================
    const float tableWidth     = 40.0f;
    const float tableDepth     = 20.0f;
    const float tableThickness = 0.12f;
    const float tableZ         = tableThickness * 0.5f;

    // =========================
    // TRANSFORM STOŁU
    // =========================
    data.tableTransform = new osg::MatrixTransform();
    data.root->addChild(data.tableTransform);

    // =========================
    // BLAT STOŁU
    // =========================
    osg::ref_ptr<osg::Box> tableBox =
        new osg::Box(osg::Vec3(0,0,tableZ), tableWidth, tableDepth, tableThickness);
    osg::ref_ptr<osg::ShapeDrawable> tableDrawable = new osg::ShapeDrawable(tableBox);
    tableDrawable->setColor(osg::Vec4(0.55f,0.33f,0.12f,1.0f));

    osg::ref_ptr<osg::Geode> tableGeode = new osg::Geode();
    tableGeode->addDrawable(tableDrawable);

    data.tableTransform->addChild(tableGeode);

    // =========================
    // DZIURY
    // =========================
    const float holeRadius = 5.0f;
    const float holeHeight = 0.02f;
    const float holeZ = tableZ + tableThickness*0.5f + 0.001f;
    const float xOffsets[3] = {-10.0f,0.0f,10.0f};

    for (int i=0; i<3; ++i) {
        osg::ref_ptr<osg::MatrixTransform> holeTransform = new osg::MatrixTransform();
        holeTransform->setMatrix(osg::Matrix::translate(xOffsets[i],0.0f,holeZ));

        osg::ref_ptr<osg::Cylinder> hole = new osg::Cylinder(osg::Vec3(0,0,0), holeRadius, holeHeight);
        osg::ref_ptr<osg::ShapeDrawable> holeDrawable = new osg::ShapeDrawable(hole);
        holeDrawable->setColor(osg::Vec4(0.02f,0.02f,0.02f,1.0f));

        osg::ref_ptr<osg::Geode> holeGeode = new osg::Geode();
        holeGeode->addDrawable(holeDrawable);

        osg::StateSet* ss = holeGeode->getOrCreateStateSet();
        ss->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
        ss->setRenderBinDetails(50,"RenderBin");

        holeTransform->addChild(holeGeode);
        data.tableTransform->addChild(holeTransform);

        // zapisujemy transform i drawable dla późniejszej zmiany koloru
        Hole h;
        h.transform = holeTransform;
        h.drawable  = holeDrawable;
        data.holes.push_back(h);
    }

    // =========================
    // PODŁOGA
    // =========================
    osg::ref_ptr<osg::Box> floorBox = new osg::Box(osg::Vec3(0,0,-0.5f), 40.0f, 20.0f, 1.0f);
    osg::ref_ptr<osg::ShapeDrawable> floorDrawable = new osg::ShapeDrawable(floorBox);
    floorDrawable->setColor(osg::Vec4(0.2f,0.6f,0.2f,1.0f));
    osg::ref_ptr<osg::Geode> floorGeode = new osg::Geode();
    floorGeode->addDrawable(floorDrawable);
    data.root->addChild(floorGeode);

    return data;
}
