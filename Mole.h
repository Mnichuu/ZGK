//
// Created by stanislaw on 18.01.2026.
//

#ifndef PROJEKT3D_MOLE_H
#define PROJEKT3D_MOLE_H

#include <osg/MatrixTransform>
#include <osg/ref_ptr>

class Mole {
public:
    explicit Mole(const osg::Vec3& holePos);

    osg::MatrixTransform* getNode() { return _root.get(); }

    void update(double dt);

private:
    osg::ref_ptr<osg::MatrixTransform> _root;

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