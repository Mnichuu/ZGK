//
// Created by stanislaw on 12.01.2026.
//

#include "Mole.h"

Mole::Mole(const osg::Vec3& position)
    : _basePosition(position), _currentHeight(0.0f), _speed(2.0f), _state(HIDDEN)
{
    // Geometria figurki (prosty cylinder)
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    osg::ref_ptr<osg::Cylinder> cylinder = new osg::Cylinder(osg::Vec3(0,0,0), 0.5f, 1.0f);
    geode->addDrawable(new osg::ShapeDrawable(cylinder));

    _transform = new osg::MatrixTransform();
    _transform->setMatrix(osg::Matrix::translate(_basePosition.x(), _basePosition.y(), -1.0f)); // start hidden
    _transform->addChild(geode);
}

void Mole::show() {
    if (_state == HIDDEN) {
        _state = RISING;
    }
}

void Mole::hide() {
    if (_state == VISIBLE) {
        _state = FALLING;
    }
}

void Mole::update(float deltaTime) {
    switch(_state) {
        case RISING:
            _currentHeight += _speed * deltaTime;
            if (_currentHeight >= 1.0f) {
                _currentHeight = 1.0f;
                _state = VISIBLE;
            }
            break;
        case FALLING:
            _currentHeight -= _speed * deltaTime;
            if (_currentHeight <= 0.0f) {
                _currentHeight = 0.0f;
                _state = HIDDEN;
            }
            break;
        default:
            break;
    }

    // aktualizacja transformacji
    _transform->setMatrix(osg::Matrix::translate(
        _basePosition.x(),
        _basePosition.y(),
        -1.0f + _currentHeight
    ));
}

bool Mole::isVisible() const {
    return _state == VISIBLE;
}

osg::ref_ptr<osg::MatrixTransform> Mole::getNode() const {
    return _transform;
}


