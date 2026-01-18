#ifndef PROJEKT3D_SCENEBUILDER_H
#define PROJEKT3D_SCENEBUILDER_H

#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <vector>

class SceneBuilder {
public:
    struct Hole {
        osg::ref_ptr<osg::MatrixTransform> transform;
        osg::ref_ptr<osg::ShapeDrawable> drawable;
    };

    struct SceneData {
        osg::ref_ptr<osg::Group> root;
        osg::ref_ptr<osg::MatrixTransform> tableTransform;
        std::vector<Hole> holes;
    };

    static SceneData createScene();
};

#endif
