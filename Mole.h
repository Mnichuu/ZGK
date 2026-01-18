#ifndef PROJEKT3D_MOLE_H
#define PROJEKT3D_MOLE_H

#include <osg/MatrixTransform>
#include <osg/ref_ptr>

#include "GameController.h"

class Mole {
public:
    explicit Mole(const osg::Vec3& holePos, int holeIndex);

    osg::MatrixTransform* getNode() { return _root.get(); }

    void update(double dt);

    bool isVisible();

    int getHoleIndex();

    void hide();

private:
    osg::ref_ptr<osg::MatrixTransform> _root;
    int _holeIndex;
    osg::Vec3 _basePos;

    enum State {
        HIDDEN,
        RISING,
        VISIBLE,
        FALLING
    };

    State _state;
    float _timer;
};

#endif //PROJEKT3D_MOLE_H