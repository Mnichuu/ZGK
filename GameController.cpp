//
// Created by stanislaw on 12.01.2026.
//

#include "GameController.h"
#include <cstdlib>
#include <ctime>

GameController::GameController() : _timer(0.0f), _score(0) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void GameController::addMole(osg::ref_ptr<Mole> mole) {
    _moles.push_back(mole);
}

void GameController::update(float deltaTime) {
    _timer -= deltaTime;
    if (_timer <= 0.0f) {
        // losujemy mole do wyskoku
        int idx = std::rand() % _moles.size();
        if (!_moles[idx]->isVisible()) {
            _moles[idx]->show();
        }
        _timer = 1.0f + static_cast<float>(std::rand() % 100) / 50.0f; // 1.0-3.0s
    }

    // update wszystkich mole
    for (auto& mole : _moles) {
        mole->update(deltaTime);
    }
}

void GameController::moleHit(Mole* mole) {
    if (mole && mole->isVisible()) {
        mole->hide();
        _score++;
    }
}

int GameController::getScore() const {
    return _score;
}

Mole* GameController::getActiveMole() {
    for (auto& mole : _moles) {
        if (mole->isVisible()) {
            return mole.get();
        }
    }
    return nullptr;
}


