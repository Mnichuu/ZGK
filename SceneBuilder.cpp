//
// Created by stanislaw on 12.01.2026.
//

#include "SceneBuilder.h"

SceneBuilder::SceneBuilder() {}
SceneBuilder::~SceneBuilder() {}

osg::ref_ptr<osg::Group> SceneBuilder::createScene(osg::ref_ptr<GameController> gameController) {
    osg::ref_ptr<osg::Group> root = new osg::Group();

    // Stół
    root->addChild(createTable());

    // Trzy figurki mole
    osg::Vec3 positions[3] = {
        osg::Vec3(-2.0f, 0.0f, 0.0f),
        osg::Vec3(0.0f, 0.0f, 0.0f),
        osg::Vec3(2.0f, 0.0f, 0.0f)
    };

    for (int i = 0; i < 3; ++i) {
        osg::ref_ptr<Mole> mole = createMole(positions[i]);
        gameController->addMole(mole); // Mole przechowywane w GameController
        root->addChild(mole->getNode());
    }

    return root;
}

osg::ref_ptr<osg::MatrixTransform> SceneBuilder::createTable() {
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3(0, 0, -0.5f), 10.0f, 5.0f, 1.0f);
    geode->addDrawable(new osg::ShapeDrawable(box));

    osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform();
    transform->addChild(geode);
    return transform;
}

osg::ref_ptr<Mole> SceneBuilder::createMole(const osg::Vec3& position) {
    osg::ref_ptr<Mole> mole = new Mole(position);
    return mole;
}
