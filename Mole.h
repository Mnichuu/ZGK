//
// Created by stanislaw on 12.01.2026.
//

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

    // API potrzebne przez GameController
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual bool isVisible() const = 0;
    virtual void update(float delta) = 0;
    osg::ref_ptr<osg::MatrixTransform> getNode() const;

private:
    osg::ref_ptr<osg::MatrixTransform> _transform;
    osg::Vec3 _basePosition;   // pozycja na stole
    float _currentHeight;
    float _speed;              // prędkość wyskoku
    State _state;
};


#endif //PROJEKT3D_MOLE_H