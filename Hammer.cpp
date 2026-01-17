#include "Hammer.h"

Hammer::Hammer()
    : _targetPos(0,0,0), _currentPos(0,0,5), _isHitting(false), _hitProgress(0.0f)
{
    _transform = new osg::MatrixTransform();

    // prosty młotek: cylinder jako trzonek + kula jako końcówka
    osg::ref_ptr<osg::Cylinder> handle = new osg::Cylinder(osg::Vec3(0,0,0.5f), 0.5f, 5.0f);
    osg::ref_ptr<osg::ShapeDrawable> handleDrawable = new osg::ShapeDrawable(handle);
    osg::ref_ptr<osg::Geode> handleGeode = new osg::Geode();
    handleGeode->addDrawable(handleDrawable);
    _transform->addChild(handleGeode);

    osg::ref_ptr<osg::Sphere> head = new osg::Sphere(osg::Vec3(0,0,5.0f), 1.0f);
    osg::ref_ptr<osg::ShapeDrawable> headDrawable = new osg::ShapeDrawable(head);
    osg::ref_ptr<osg::Geode> headGeode = new osg::Geode();
    headGeode->addDrawable(headDrawable);
    _transform->addChild(headGeode);

    _currentPos = osg::Vec3(0,0,5.0f);
}

void Hammer::setTarget(const osg::Vec3& target) {
    _targetPos = target + osg::Vec3(0, 0, 5.0f); // nad dziurą 5 jednostek w górę
}

void Hammer::hit() {
    if (!_isHitting) {
        _isHitting = true;
        _hitProgress = 0.0f;
    }
}

void Hammer::update(float deltaTime) {
    // interpolacja pozycji do celu
    float speed = 5.0f;
    _currentPos += (_targetPos - _currentPos) * speed * deltaTime;

    // animacja uderzenia
    if (_isHitting) {
        _hitProgress += deltaTime * 5.0f; // szybkość uderzenia
        if (_hitProgress >= 1.0f) {
            _hitProgress = 0.0f;
            _isHitting = false;
        }
        float offset = -5.0f * (_hitProgress < 0.5f ? _hitProgress*2 : (1.0f-_hitProgress)*2);
        _transform->setMatrix(osg::Matrix::translate(_currentPos + osg::Vec3(0,0,offset)));
    } else {
        _transform->setMatrix(osg::Matrix::translate(_currentPos));
    }
}
