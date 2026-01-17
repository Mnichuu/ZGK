//
// Created by stanislaw on 17.01.2026.
//

#ifndef PROJEKT3D_GAMECONTROLLER_H
#define PROJEKT3D_GAMECONTROLLER_H

#include <osg/MatrixTransform>

#include "Hammer.h"
#include "SceneBuilder.h"

class GameController {
public:
    GameController();
    Hammer _hammer;
    // podpinanie elementów sceny
    void setTableTransform(osg::MatrixTransform* table);

    // akcje sterowane klawiaturą
    void toggleTableLock();
    void moveTable(float dx);

    void setSelectedHole(int index);
    void hitSelectedHole();

    // NOWE: przekazujemy dziury z SceneBuilder
    void setHoles(const std::vector<SceneBuilder::Hole>& holes);

    // update młotka, wywoływane w każdej klatce
    void update(float deltaTime);

    void setSceneData(const SceneBuilder::SceneData& data);

private:
    osg::ref_ptr<osg::MatrixTransform> _tableTransform;
    bool _tableLocked;

    int _selectedHole;
    std::vector<SceneBuilder::Hole> _holes; // trzymamy dziury

    SceneBuilder::SceneData _sceneData;
};

#endif //PROJEKT3D_GAMECONTROLLER_H