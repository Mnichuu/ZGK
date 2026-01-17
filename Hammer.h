//
// Created by stanislaw on 12.01.2026.
//

#ifndef PROJEKT3D_HAMMER_H
#define PROJEKT3D_HAMMER_H

#pragma once
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Vec3>

class Hammer : public osg::Referenced {
public:
    Hammer(const osg::Vec3& startPos);
    ~Hammer() {}

    void hit(const osg::Vec3& targetPos); // wywołuje animację uderzenia
    void update(float deltaTime);         // update pozycji w każdej klatce
    osg::ref_ptr<osg::MatrixTransform> getNode() const;

private:
    osg::ref_ptr<osg::MatrixTransform> _transform;
    osg::Vec3 _startPos;
    osg::Vec3 _targetPos;
    bool _isHitting;
    float _progress;      // 0.0 -> start, 1.0 -> koniec animacji
    float _speed;
};



#endif //PROJEKT3D_HAMMER_H