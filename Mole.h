// File: `Mole.h`
#ifndef PROJEKT3D_MOLE_H
#define PROJEKT3D_MOLE_H

#pragma once
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Vec3>
#include <osg/Referenced>

class Mole : public osg::Referenced {
public:
    enum State {
        HIDDEN,
        RISING,
        VISIBLE,
        FALLING
    };

    explicit Mole(const osg::Vec3& position);
    Mole() = default;
    ~Mole() override = default;

    // API potrzebne przez GameController - nie są już czysto wirtualne
    virtual void show();
    virtual void hide();
    virtual bool isVisible() const;
    virtual void update(float delta);
    osg::ref_ptr<osg::MatrixTransform> getNode() const;

private:
    osg::ref_ptr<osg::MatrixTransform> _transform;
    osg::Vec3 _basePosition;
    float _currentHeight;
    float _speed;
    State _state;
};

#endif //PROJEKT3D_MOLE_H
