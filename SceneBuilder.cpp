// language: cpp
#include "SceneBuilder.h"
#include "Mole.h"
#include "GameController.h"

#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/PositionAttitudeTransform>
#include <osg/Box>
#include <osg/NodeCallback>
#include <osg/Group>
#include <osg/Camera>
#include <osg/FrameStamp>

// Update callback wywołujący GameController::update na każdą klatkę
class ControllerUpdateCallback : public osg::NodeCallback {
public:
    ControllerUpdateCallback(GameController* controller) : _controller(controller), _lastTime(-1.0) {}
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) override {
        if (!_controller) { traverse(node, nv); return; }
        if (nv && nv->getFrameStamp()) {
            double t = nv->getFrameStamp()->getSimulationTime();
            if (_lastTime < 0.0) _lastTime = t;
            float dt = static_cast<float>(t - _lastTime);
            _lastTime = t;
            _controller->update(dt);
        }
        traverse(node, nv);
    }
private:
    GameController* _controller;
    double _lastTime;
};

// --- MoleKeyHandler implementation ---
MoleKeyHandler::MoleKeyHandler(GameController* controller, const std::vector<osg::ref_ptr<Mole>>& moles)
    : _controller(controller), _moles(moles) {}

bool MoleKeyHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
    if (ea.getEventType() != osgGA::GUIEventAdapter::KEYDOWN) return false;
    int idx = -1;
    int key = ea.getKey();
    if (key == osgGA::GUIEventAdapter::KEY_1) idx = 0;
    else if (key == osgGA::GUIEventAdapter::KEY_2) idx = 1;
    else if (key == osgGA::GUIEventAdapter::KEY_3) idx = 2;
    if (idx >= 0 && idx < static_cast<int>(_moles.size())) {
        if (_controller) {
            _controller->moleHit(_moles[idx].get());
            return true;
        }
    }
    return false;
}

// --- SceneBuilder implementation ---
osg::ref_ptr<osg::Group> SceneBuilder::createScene(GameController* controller,
                                                   std::vector<osg::ref_ptr<Mole>>* outMoles) {
    osg::ref_ptr<osg::Group> root = new osg::Group();

    // stolik - prosty box (blat)
    const float tableWidth = 3.0f;
    const float tableDepth = 1.5f;
    const float tableThickness = 0.12f;
    const float tableZ = tableThickness * 0.5f; // wysokość środka blatu

    osg::ref_ptr<osg::Box> tableBox = new osg::Box(osg::Vec3(0.0f, 0.0f, tableZ),
                                                   tableWidth, tableDepth, tableThickness);
    osg::ref_ptr<osg::ShapeDrawable> tableDrawable = new osg::ShapeDrawable(tableBox);
    tableDrawable->setColor(osg::Vec4(0.55f, 0.33f, 0.12f, 1.0f)); // brąz

    osg::ref_ptr<osg::Geode> tableGeode = new osg::Geode();
    tableGeode->addDrawable(tableDrawable);

    osg::ref_ptr<osg::Material> mat = new osg::Material();
    mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.55f, 0.33f, 0.12f, 1.0f));
    tableGeode->getOrCreateStateSet()->setAttributeAndModes(mat, osg::StateAttribute::ON);

    root->addChild(tableGeode);

    // trzy "dziury" — ciemne cylindry lekko pod powierzchnią blatu
    const float holeRadius = 0.28f;
    const float holeHeight = 0.10f;
    const float holeZ = tableZ - tableThickness * 0.5f + holeHeight * 0.5f - 0.01f;

    const float xOffsets[3] = { -0.9f, 0.0f, 0.9f };

    for (int i = 0; i < 3; ++i) {
        osg::ref_ptr<osg::Cylinder> holeCylinder = new osg::Cylinder(osg::Vec3(xOffsets[i], 0.0f, holeZ),
                                                                    holeRadius, holeHeight);
        holeCylinder->setAxis(osg::Vec3(0.0f, 0.0f, 1.0f));
        osg::ref_ptr<osg::ShapeDrawable> holeDrawable = new osg::ShapeDrawable(holeCylinder);
        holeDrawable->setColor(osg::Vec4(0.02f, 0.02f, 0.02f, 1.0f));

        osg::ref_ptr<osg::Geode> holeGeode = new osg::Geode();
        holeGeode->addDrawable(holeDrawable);
        holeGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);

        root->addChild(holeGeode);
    }

    // podłoga
    osg::ref_ptr<osg::Box> floorBox = new osg::Box(osg::Vec3(0.0f, 0.0f, -0.5f), 10.0f, 10.0f, 1.0f);
    osg::ref_ptr<osg::ShapeDrawable> floorDrawable = new osg::ShapeDrawable(floorBox);
    floorDrawable->setColor(osg::Vec4(0.2f, 0.6f, 0.2f, 1.0f));
    osg::ref_ptr<osg::Geode> floorGeode = new osg::Geode();
    floorGeode->addDrawable(floorDrawable);
    root->addChild(floorGeode);

    // tworzymy 3 mole i ustawiamy je nad dziurami
    std::vector<osg::ref_ptr<Mole>> localMoles;
    for (int i = 0; i < 3; ++i) {
        osg::ref_ptr<Mole> mole = new Mole();
        mole->setPosition(osg::Vec3(xOffsets[i], 0.0f, mole->isVisible() ? 0.0f : -0.18f));
        // Mole jest transformem — dodajemy go jako child sceny, ustawiając translację
        root->addChild(mole.get());

        if (controller) controller->addMole(mole);
        localMoles.push_back(mole);
    }

    if (outMoles) {
        *outMoles = localMoles;
    }

    // update callback wywołujący update kontrolera
    if (controller) {
        root->setUpdateCallback(new ControllerUpdateCallback(controller));
    }

    return root;
}
