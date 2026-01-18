#include "Mole.h"

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <cstdlib>

Mole::Mole(const osg::Vec3& holePos, int holeIndex)
    : _holeIndex(holeIndex),
      _basePos(holePos),
      _state(HIDDEN),
      _timer(0.0f)
{
    _root = new osg::MatrixTransform();

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    // Prosty kret = cylinder
    osg::ref_ptr<osg::Cylinder> body =
        new osg::Cylinder(osg::Vec3(0, 0, 0.0f), 3.0f, 6.0f);

    osg::ref_ptr<osg::ShapeDrawable> drawable =
        new osg::ShapeDrawable(body);

    drawable->setColor(osg::Vec4(0.4f, 0.25f, 0.1f, 1.0f));

    geode->addDrawable(drawable);
    _root->addChild(geode);

    // Start schowany
    _root->setMatrix(
        osg::Matrix::translate(_basePos + osg::Vec3(0, 0, -5.0f))
    );
}

void Mole::update(double dt) {
    _timer += dt;

    switch (_state) {
        case HIDDEN:
            if (_timer > 2.0f + (std::rand() % 2000) / 1000.0f) {
                _state = RISING;
                _timer = 0.0f;
            }
            break;

        case RISING: {
            float t = std::min(_timer / 0.3f, 1.0f);
            _root->setMatrix(
                osg::Matrix::translate(_basePos + osg::Vec3(0, 0, -5.0f + 5.0f * t))
            );
            if (t >= 1.0f) {
                _state = VISIBLE;
                _timer = 0.0f;
            }
            break;
        }

        case VISIBLE:
            if (_timer > 1.0f) {
                _state = FALLING;
                _timer = 0.0f;
            }
            break;

        case FALLING: {
            float t = std::min(_timer / 0.3f, 1.0f);
            _root->setMatrix(
                osg::Matrix::translate(_basePos + osg::Vec3(0, 0, 0.0f - 5.0f * t))
            );
            if (t >= 1.0f) {
                _state = HIDDEN;
                _timer = 0.0f;
            }
            break;
        }
    }
}

bool Mole::isVisible() {
    return _state == VISIBLE;
}

int Mole::getHoleIndex() {
    return _holeIndex;
}

void Mole::hide() {
    _state = FALLING;
}