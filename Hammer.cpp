#include "Hammer.h"

Hammer::Hammer()
    : _targetPos(0,0,0),
      _currentPos(0,0,8),
      _isHitting(false),
      _hitProgress(0.0f)
{
    _transform = new osg::MatrixTransform();

    // =========================
    // MATERIAŁY
    // =========================
    osg::ref_ptr<osg::Material> woodMat = new osg::Material();
    woodMat->setDiffuse(osg::Material::FRONT_AND_BACK,
        osg::Vec4(0.75f, 0.55f, 0.30f, 1.0f)); // jasno-brązowy
    woodMat->setAmbient(osg::Material::FRONT_AND_BACK,
        osg::Vec4(0.4f, 0.3f, 0.2f, 1.0f));

    osg::ref_ptr<osg::Material> metalMat = new osg::Material();
    metalMat->setDiffuse(osg::Material::FRONT_AND_BACK,
        osg::Vec4(0.4f, 0.4f, 0.4f, 1.0f));
    metalMat->setSpecular(osg::Material::FRONT_AND_BACK,
        osg::Vec4(0.8f, 0.8f, 0.8f, 1.0f));
    metalMat->setShininess(osg::Material::FRONT_AND_BACK, 64.0f);

    // =========================
    // TRZONEK (pionowy)
    // =========================
    osg::ref_ptr<osg::Cylinder> handle =
        new osg::Cylinder(osg::Vec3(0, 0, 3.0f), 0.4f, 6.0f);

    osg::ref_ptr<osg::ShapeDrawable> handleDrawable =
        new osg::ShapeDrawable(handle);

    osg::ref_ptr<osg::Geode> handleGeode = new osg::Geode();
    handleGeode->addDrawable(handleDrawable);
    handleGeode->getOrCreateStateSet()
        ->setAttributeAndModes(woodMat, osg::StateAttribute::ON);

    _transform->addChild(handleGeode);

    // =========================
    // GŁOWICA (poprzeczna)
    // =========================
    osg::ref_ptr<osg::Cylinder> head =
        new osg::Cylinder(osg::Vec3(0, 0, 6.5f), 0.8f, 3.0f);

    head->setRotation(
        osg::Quat(osg::PI_2, osg::Vec3(1,0,0)) // obrót poziomy
    );

    osg::ref_ptr<osg::ShapeDrawable> headDrawable =
        new osg::ShapeDrawable(head);

    osg::ref_ptr<osg::Geode> headGeode = new osg::Geode();
    headGeode->addDrawable(headDrawable);
    headGeode->getOrCreateStateSet()
        ->setAttributeAndModes(metalMat, osg::StateAttribute::ON);

    _transform->addChild(headGeode);

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
