#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

#include "SceneBuilder.h"
#include "GameController.h"
#include "InputHandler.h"

int main(int argc, char** argv)
{
    // =========================
    // 1. Budowa sceny
    // =========================
    SceneBuilder::SceneData scene = SceneBuilder::createScene();

    // =========================
    // 2. Kontroler gry (logika)
    // =========================
    GameController gameController;
    gameController.setSceneData(scene);

    gameController.setTableTransform(scene.tableTransform.get());
    gameController.setHoles(scene.holes);

    // dodaj młotek do sceny
    scene.root->addChild(gameController._hammer.getTransform());

    // =========================
    // 3. Viewer
    // =========================
    osgViewer::Viewer viewer;
    viewer.setSceneData(scene.root.get());
    viewer.setUpViewInWindow(100, 100, 1280, 800);

    viewer.setSceneData(scene.root.get());
    // =========================
    // 4. Kamera (statyczna)
    // =========================
    viewer.setCameraManipulator(nullptr);

    // ustawienia kamery
    const float tableZ = 0.06f;
    osg::Vec3 eye(0.0f, -40.0f, 20.0f);
    osg::Vec3 center(0.0f, 0.0f, tableZ);
    osg::Vec3 up(0.0f, 0.0f, 1.0f);

    viewer.getCamera()->setViewMatrixAsLookAt(eye, center, up);
    viewer.getCamera()->setProjectionMatrixAsPerspective(
        30.0, 16.0 / 9.0, 0.1, 100.0
    );

    // =========================
    // 5. Obsługa wejścia
    // =========================
    viewer.addEventHandler(new InputHandler(&gameController));

    // =========================
    // 6. Start pętli renderującej
    // =========================
    // pętla renderująca z update
    while (!viewer.done()) {
        double t0 = viewer.getFrameStamp()->getReferenceTime();
        viewer.frame();
        double t1 = viewer.getFrameStamp()->getReferenceTime();
        gameController.update(t1 - t0);
    }
    return 0;
}
