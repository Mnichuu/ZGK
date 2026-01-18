//
// Created by stanislaw on 17.01.2026.
//

#include "GameController.h"
#include <iostream>
#include <memory>
#include <osg/Matrix>

#include "Mole.h"

GameController::GameController()
    : _tableLocked(true),
      _selectedHole(0)
{}

void GameController::setTableTransform(osg::MatrixTransform* table) {
    _tableTransform = table;
}

void GameController::toggleTableLock() {
    _tableLocked = !_tableLocked;
    std::cout << (_tableLocked ? "Table locked\n" : "Table unlocked\n");
}

void GameController::moveTable(float dx) {
    if (_tableLocked || !_tableTransform) return;

    osg::Matrix m = _tableTransform->getMatrix();
    m *= osg::Matrix::translate(dx, 0.0f, 0.0f);
    _tableTransform->setMatrix(m);
}

void GameController::setSelectedHole(int index) {
    if (index < 0 || index >= static_cast<int>(_holes.size())) return;

    _selectedHole = index;
    std::cout << "Selected hole: " << index << "\n";

    // Zmieniamy kolory wszystkich dziur
    for (int i = 0; i < static_cast<int>(_holes.size()); ++i) {
        osg::Vec4 color = (i == _selectedHole) ? osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)
                                               : osg::Vec4(0.02f, 0.02f, 0.02f, 1.0f);
        _holes[i].drawable->setColor(color);
        _hammer.setTarget(_sceneData.holes[_selectedHole].transform->getMatrix().getTrans());
    }
}


void GameController::hitSelectedHole() {
    std::cout << "Hit hole " << _selectedHole << " 🔨\n";
    _hammer.hit();
}

void GameController::setHoles(const std::vector<SceneBuilder::Hole>& holes) {
    _holes = holes;
}

void GameController::update(float deltaTime) {
    _hammer.update(deltaTime);
    for (auto& m : _moles) {
        m->update(deltaTime);
    }
}

void GameController::setSceneData(const SceneBuilder::SceneData& data) {
    _sceneData = data;
    _tableTransform = data.tableTransform;

    // ustaw młotek nad pierwszą dziurą domyślnie
    if (!_sceneData.holes.empty()) {
        _hammer.setTarget(_sceneData.holes[_selectedHole].transform->getMatrix().getTrans());
    }
}

void GameController::setMoles(const SceneBuilder::SceneData& data, osg::Group* root) {
    _moles.clear();

    for (int i = 0; i < 3; ++i) {
        osg::Vec3 holePos =
            data.holes[i].transform->getMatrix().getTrans();

        auto mole = std::make_unique<Mole>(holePos);
        root->addChild(mole->getNode());

        _moles.push_back(std::move(mole));
    }
}


