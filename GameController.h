#ifndef PROJEKT3D_GAMECONTROLLER_H
#define PROJEKT3D_GAMECONTROLLER_H

#include <memory>
#include <osg/MatrixTransform>

#include "Hammer.h"
#include "Mole.h"
#include "SceneBuilder.h"
#include "ScoreSystem.h"
class Mole;

class GameController {
public:
    GameController();
    Hammer _hammer;
    // podpinanie elementów sceny
    void setTableTransform(osg::MatrixTransform* table);

    // akcje sterowane klawiaturą
    void toggleTableLock();
    void setSelectedHole(int index);
    void hitSelectedHole();

    // przekazanie dziur z SceneBuilder
    void setHoles(const std::vector<SceneBuilder::Hole>& holes);

    // update młotka, wywoływane w każdej klatce
    void update(float deltaTime);

    void setMoles(const SceneBuilder::SceneData& data, osg::Group* root);

    void setSceneData(const SceneBuilder::SceneData& data);

private:
    osg::ref_ptr<osg::MatrixTransform> _tableTransform;
    bool _tableLocked;

    int _selectedHole;
    std::vector<SceneBuilder::Hole> _holes;

    SceneBuilder::SceneData _sceneData;
    std::vector<std::unique_ptr<Mole>> _moles;
    ScoreSystem _score;
};

#endif