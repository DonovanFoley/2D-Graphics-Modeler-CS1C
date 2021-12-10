#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include "vector.h"
#include "shapes.h"

using sdog::vector;

class RenderArea : public QWidget
{
  public:
    RenderArea(QWidget *parent = nullptr);

    //from drawing example
    void paintEvent(QPaintEvent *event);

    QSize sizeHint() const {return QSize(1000, 500);}           //what does sizehint do - used from renderarea example
    QSize minimumSizeHint() const {return QSize(100, 100);}     //^^

    //to get shapes info
    const vector<Shape*>& getShapes() {return shapeVector;}

    int getSize() {return shapeVector.size(); }
    int getNumShapesRenderArea() {return numShapesRenderArea;}

    //functions to modify shapes
    void addShape(Shape* shapeIn);

    void cutShape(int inRemove);
    void moveShape(int inMove, int coordMove, int x, int y);

    void readShapeFile();

private:
    const QImage renderArea;
    sdog::vector<Shape*> shapeVector;
    int numShapesRenderArea;


};



#endif // RENDERAREA_H
