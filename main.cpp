// language: cpp
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include "SceneBuilder.h"
#include "GameController.h"

int main(int argc, char** argv) {
    osg::ref_ptr<GameController> controller = new GameController();

    std::vector<osg::ref_ptr<Mole>> moles;
    osg::ref_ptr<osg::Group> scene = SceneBuilder::createScene(controller.get(), &moles);

    osgViewer::Viewer viewer;
    viewer.setSceneData(scene.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    viewer.getCamera()->setClearColor(osg::Vec4(0.6f, 0.8f, 1.0f, 1.0f)); // niebo

    // dodaj handler klawiszy mapujący 1/2/3 -> odpowiedni mole
    viewer.addEventHandler(new MoleKeyHandler(controller.get(), moles));

    return viewer.run();
}
