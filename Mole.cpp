// language: cpp
#include "Mole.h"
#include <osg/ShapeDrawable>
#include <osg/Material>

Mole::Mole(float radius, float hiddenZ, float visibleZ)
    : _state(HIDDEN), _currentZ(hiddenZ),
      _hiddenZ(hiddenZ), _visibleZ(visibleZ), _speed(1.2f) {

    // sphere representing the mole
    osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius);
    osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(sphere);
    sd->setColor(osg::Vec4(0.6f, 0.3f, 0.2f, 1.0f));

    _geode = new osg::Geode();
    _geode->addDrawable(sd);

    // material to look better under lighting
    osg::ref_ptr<osg::Material> mat = new osg::Material();
    mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.6f, 0.3f, 0.2f, 1.0f));
    _geode->getOrCreateStateSet()->setAttributeAndModes(mat, osg::StateAttribute::ON);

    // initially hidden below surface
    setPosition(osg::Vec3(0.0f, 0.0f, _currentZ));
    addChild(_geode.get());
}

void Mole::show() {
    if (_state == HIDDEN || _state == HIDING) {
        _state = RISING;
    }
}

void Mole::hide() {
    if (_state == VISIBLE || _state == RISING) {
        _state = HIDING;
    }
}

bool Mole::isVisible() const {
    return _state == VISIBLE || _state == RISING;
}

void Mole::update(float dt) {
    if (_state == RISING) {
        _currentZ += _speed * dt;
        if (_currentZ >= _visibleZ) {
            _currentZ = _visibleZ;
            _state = VISIBLE;
        }
        setPosition(osg::Vec3(0.0f, 0.0f, _currentZ));
    } else if (_state == HIDING) {
        _currentZ -= _speed * dt;
        if (_currentZ <= _hiddenZ) {
            _currentZ = _hiddenZ;
            _state = HIDDEN;
        }
        setPosition(osg::Vec3(0.0f, 0.0f, _currentZ));
    } else {
        // If VISIBLE or HIDDEN, ensure position set
        setPosition(osg::Vec3(0.0f, 0.0f, _currentZ));
    }
}
