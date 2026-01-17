// language: cpp
#ifndef PROJEKT3D_SCENEBUILDER_H
#define PROJEKT3D_SCENEBUILDER_H

#include <osg/Group>
#include <osg/ref_ptr>
#include <vector>

class GameController;
class Mole;

// prosty handler klawiszy do trafiania mole (1/2/3)
#include <osgGA/GUIEventHandler>
class MoleKeyHandler : public osgGA::GUIEventHandler {
public:
    MoleKeyHandler(GameController* controller, const std::vector<osg::ref_ptr<Mole>>& moles);
    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override;

private:
    GameController* _controller;
    std::vector<osg::ref_ptr<Mole>> _moles;
};

class SceneBuilder {
public:
    // tworzy scenę i wypełnia outMoles (3 mole)
    static osg::ref_ptr<osg::Group> createScene(GameController* controller,
                                                std::vector<osg::ref_ptr<Mole>>* outMoles = nullptr);
};

#endif // PROJEKT3D_SCENEBUILDER_H
