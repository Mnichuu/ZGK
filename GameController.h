// language: cpp
#ifndef PROJEKT3D_GAMECONTROLLER_H
#define PROJEKT3D_GAMECONTROLLER_H

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <vector>

class Mole;

class GameController : public osg::Referenced {
public:
    GameController();
    virtual ~GameController() = default;

    void addMole(osg::ref_ptr<Mole> mole);
    void update(float deltaTime);
    void moleHit(Mole* mole);
    int getScore() const;
    Mole* getActiveMole();

private:
    float _timer;
    int _score;
    std::vector<osg::ref_ptr<Mole>> _moles;
};

#endif // PROJEKT3D_GAMECONTROLLER_H
