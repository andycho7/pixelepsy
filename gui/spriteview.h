#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include "sprite/buffer.h"
#include "sprite/sprite.h"
#include "sprite/frame.h"

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QVBoxLayout>

#include <vector>
#include <memory>

class SpriteView : public QGraphicsView
{
    Q_OBJECT
public:
    SpriteView(std::shared_ptr<Buffer> buffer, QWidget* parent = 0);
    SpriteView(QGraphicsScene* scene,  QWidget* parent = 0);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    QPoint pixelLocation(QMouseEvent*);
    bool checkPoint(QPoint);
    void selectFrame(int frame);
    void selectLayer(int layer);
    void updateView();
    void closeEvent(QCloseEvent *);

protected:
    int frameIndex;
    int layerIndex;
    double scala;
    std::shared_ptr<Buffer> buffer;
    std::vector<QPoint> points;
    QVBoxLayout layout;
    QGraphicsScene scene;

public slots:
    void spriteModified();
};

#endif // SPRITEVIEW_H
