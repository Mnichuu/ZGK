//
// Created by stanislaw on 12.01.2026.
//

#include "PickHandler.h"
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/IntersectionVisitor>
#include <osg/Node>

bool PickHandler::handle(const osgGA::GUIEventAdapter& ea,
                         osgGA::GUIActionAdapter& aa)
{
    if (!_gameController) return false;

    if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH &&
        ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
    {
        osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
        if (!viewer) return false;

        float x = ea.getX();
        float y = ea.getY();

        // Tworzymy promień od kamery przez punkt kliknięcia
        osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
            new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, x, y);
        osgUtil::IntersectionVisitor iv(intersector.get());
        viewer->getCamera()->accept(iv);

        if (intersector->containsIntersections()) {
            for (auto& hit : intersector->getIntersections()) {
                osg::NodePath nodePath = hit.nodePath;
                for (auto it = nodePath.rbegin(); it != nodePath.rend(); ++it) {
                    osg::Node* node = *it;
                    // Sprawdzenie, czy kliknięty node jest mole
                    Mole* mole = dynamic_cast<Mole*>(node->getUserData());
                    if (mole && mole->isVisible()) {
                        _gameController->moleHit(mole);
                        return true; // trafienie
                    }
                }
            }
        }
    }
    return false;
}
