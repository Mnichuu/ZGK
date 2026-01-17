// language: cpp
// File: `SceneBuilder.h`
#ifndef PROJEKT3D_SCENEBUILDER_H
#define PROJEKT3D_SCENEBUILDER_H

#include <osg/Group>
#include <osg/ref_ptr>

class SceneBuilder {
public:
    // Tworzy scenę z blatem i trzema dziurami
    static osg::ref_ptr<osg::Group> createScene();
};

#endif // PROJEKT3D_SCENEBUILDER_H
