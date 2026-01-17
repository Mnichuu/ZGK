// language: cpp
// File: `main.cpp`
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include "SceneBuilder.h"

int main(int argc, char** argv) {
    osg::ref_ptr<osg::Group> scene = SceneBuilder::createScene();

    osgViewer::Viewer viewer;
    viewer.setSceneData(scene.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    viewer.getCamera()->setClearColor(osg::Vec4(0.6f, 0.8f, 1.0f, 1.0f)); // kolor tła

    return viewer.run();
}
