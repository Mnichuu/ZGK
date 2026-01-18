#ifndef PROJEKT3D_HAMMER_H
#define PROJEKT3D_HAMMER_H

#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/Material>
#include <osg/StateSet>

class Hammer {
public:
    Hammer();

    osg::MatrixTransform* getTransform() { return _transform.get(); }

    void setTarget(const osg::Vec3& target);

    void hit();

    void update(float deltaTime);

private:
    osg::ref_ptr<osg::MatrixTransform> _transform;
    osg::Vec3 _targetPos;
    osg::Vec3 _currentPos;

    bool _isHitting;
    float _hitProgress; // od 0 do 1
};

#endif
