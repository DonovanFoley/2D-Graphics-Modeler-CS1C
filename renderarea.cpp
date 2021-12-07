#include "renderarea.h"
#include "shapes.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent), shapeMag(10)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(RenderArea::sizeHint());
    numShapesRenderArea = 0;
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPaintDevice *device = this;
    for(int i = 0; i < shapeMag.size(); i++)
    {
        shapeMag[i]->draw(device);
    }

    QPainter painter(this);

    //demo shapes - idk where we would make the shapes
    //QPoint pointA;
    //QPoint pointB;
    //pointA.setX(0);
    //pointA.setY(10);
    //pointB.setX(0);
    //pointB.setY(10);
    //Line line;
    //line.setPoints(pointA, pointB);
    //line.draw(device);
    Rectangle rectangle;
    rectangle.setRectStart(10, 10);
    rectangle.setWidth(200);
    rectangle.setHeight(100);
    rectangle.draw(device);

}

void RenderArea::addShape(Shape *shapeIn)
{
    shapeMag.push_back(shapeIn);
    numShapesRenderArea++;
}

void RenderArea::cutShape(int inRemove)
{
    sdog::vector<Shape*>::iterator i;

    for (i = shapeMag.begin(); i < shapeMag.end(); ++i)
    {
        if((*i)->getID() == inRemove)
        {
            shapeMag.erase(i);
            numShapesRenderArea--;
            break;
        }
    }

}

void RenderArea::moveShape(int inMove, int coordMove, int x, int y)
{
    for(int i = 0; i < shapeMag.size(); i++)
    {
        if (shapeMag[i]->getID() == inMove)
        {
            //shapeMag[i]->move(x, y, coordMove); //implement move in abc and classes
            break;
        }
    }
}
