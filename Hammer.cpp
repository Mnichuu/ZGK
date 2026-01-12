//
// Created by stanislaw on 12.01.2026.
//

#include "Hammer.h"

Hammer::Hammer(const osg::Vec3& startPos)
    : _startPos(startPos),
      _isHitting(false),
      _progress(0.0f),
      _speed(3.0f) // prędkość animacji
{
    // Prosta geometria młotka (sześcian)
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3(0,0,0), 0.5f);
    geode->addDrawable(new osg::ShapeDrawable(box));

    _transform = new osg::MatrixTransform();
    _transform->setMatrix(osg::Matrix::translate(_startPos));
    _transform->addChild(geode);
}

void Hammer::hit(const osg::Vec3& targetPos) {
    _targetPos = targetPos;
    _progress = 0.0f;
    _isHitting = true;
}

void Hammer::update(float deltaTime) {
    if (!_isHitting) return;

    _progress += _speed * deltaTime;
    if (_progress >= 1.0f) {
        _progress = 1.0f;
        _isHitting = false;
    }

    // interpolacja liniowa start -> target -> start
    float t = (_progress < 0.5f) ? (_progress * 2.0f) : ((1.0f - _progress) * 2.0f);
    osg::Vec3 pos = _startPos + (_targetPos - _startPos) * t;

    _transform->setMatrix(osg::Matrix::translate(pos));
}

osg::ref_ptr<osg::MatrixTransform> Hammer::getNode() const {
    return _transform;
}
