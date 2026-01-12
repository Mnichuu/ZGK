//
// Created by stanislaw on 12.01.2026.
//

#include "UpdateCallback.h"
#include <osg/Timer>

void UpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv) {
    if (!_gameController) return;

    // Obliczamy deltaTime w sekundach
    osg::Timer_t currentTime = osg::Timer::instance()->tick();
    double deltaTime = osg::Timer::instance()->delta_s(_lastTime, currentTime);
    _lastTime = currentTime;

    // Update logiki gry
    _gameController->update(static_cast<float>(deltaTime));

    // Wywołanie update dla dzieci w scenie
    traverse(node, nv);
}
