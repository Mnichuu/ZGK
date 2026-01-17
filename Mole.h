// language: cpp
#ifndef PROJEKT3D_MOLE_H
#define PROJEKT3D_MOLE_H

#include <osg/PositionAttitudeTransform>
#include <osg/ref_ptr>
#include <osg/Geode>

class Mole : public osg::PositionAttitudeTransform {
public:
    Mole(float radius = 0.22f, float hiddenZ = -0.18f, float visibleZ = 0.16f);
    virtual ~Mole() = default;

    void show();
    void hide();
    void update(float dt);
    bool isVisible() const;

    osg::Geode* getGeode() { return _geode.get(); }

protected:
    enum State { HIDDEN, RISING, VISIBLE, HIDING };
    State _state;
    float _currentZ;
    float _hiddenZ;
    float _visibleZ;
    float _speed; // units per second
    osg::ref_ptr<osg::Geode> _geode;
};

#endif // PROJEKT3D_MOLE_H
