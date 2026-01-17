//
// Created by stanislaw on 12.01.2026.
//

#ifndef PROJEKT3D_GAMECONTROLLER_H
#define PROJEKT3D_GAMECONTROLLER_H

#pragma once
#include <vector>
#include <osg/Vec3>
#include "Mole.h"
#include "Hammer.h"

class GameController : public osg::Referenced {
public:
    GameController();
    ~GameController() {}

    void addMole(const osg::ref_ptr<Mole> mole);
    void setHammer(osg::ref_ptr<Hammer> hammer);  // nowa metoda

    void update(float deltaTime);
    void moleHit(Mole* mole);

    int getScore() const;
    Mole* getActiveMole();

private:
    std::vector<osg::ref_ptr<Mole>> _moles;
    osg::ref_ptr<Hammer> _hammer;  // młotek
    float _timer;
    int _score;
};

#endif //PROJEKT3D_GAMECONTROLLER_H