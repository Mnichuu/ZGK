//
// Created by stanislaw on 12.01.2026.
//

#include "Application.h"

Application::Application() {
    _viewer = new osgViewer::Viewer();
    _root = new osg::Group();
    _gameController = new GameController();
}

Application::~Application() {}

void Application::init() {
    // Budujemy scenę
    SceneBuilder builder;
    _root = builder.createScene(_gameController);

    // Podpinamy obsługę kliknięć
    _viewer->addEventHandler(new PickHandler(_gameController));

    // Podpinamy update callback (animacje)
    _root->setUpdateCallback(new UpdateCallback(_gameController));

    _viewer->setSceneData(_root);

    // Kamera domyślna
    _viewer->setUpViewInWindow(100, 100, 800, 600);
}

void Application::run() {
    _viewer->realize();
    _viewer->run();
}
