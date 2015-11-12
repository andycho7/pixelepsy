#include "gui/canvas.h"
#include "sprite/buffer.h"
#include "sprite/sprite.h"
#include "sprite/frame.h"

#include <vector>
#include <memory>

#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>


Canvas::Canvas(std::shared_ptr<Buffer> buffer, QWidget *parent)
    : QGraphicsView(parent)
    , frameIndex(0)
    , layerIndex(0)
    , scala(20)
    , buffer(buffer)
    , scene(new QGraphicsScene)
{
    this->setLayout(&layout);
    this->setContentsMargins(0, 0, 0, 0);
    this->setScene(&scene);
    updateView();
    this->show();
}

void Canvas::selectFrame(int frame) {

}

void Canvas::selectLayer(int layer) {

}

void Canvas::updateView() {
    scene.clear();
    Frame frame = buffer->current()->getFrame(frameIndex);
    for (auto layer = frame.getLayersBegin(); layer != frame.getLayersEnd(); layer++)
        scene.addPixmap(QPixmap::fromImage(**layer))->show();
    this->scale(qreal(scala), qreal(scala));
}

void Canvas::mousePressEvent(QMouseEvent* event) {
    this->points.clear();
}

void Canvas::mouseReleaseEvent(QMouseEvent* event) {

}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    QPoint point = this->pixelLocation(event);
    if (checkPoint(point))
        this->points.push_back(point);
}

QPoint Canvas::pixelLocation(QMouseEvent* event) {
    return (this->mapToScene(event->pos())).toPoint();
}

bool Canvas::checkPoint(QPoint point) {
    int x = point.x();
    int y = point.y();
    int width = this->buffer.get()->current().get()->getWidth();
    int height = this->buffer.get()->current().get()->getHeight();
    return ((x >= 0) && (y >= 0)) && ((x < width) && (y < height));
}


