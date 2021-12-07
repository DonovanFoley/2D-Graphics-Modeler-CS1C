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
    QSize sizeHint() const {return QSize(1000, 500);}
    QSize minimumSizeHint() const {return QSize(1000, 500);}

    //to get shapes info
    const vector<Shape*>& getShapes() {return shapeMag;}

    int getSize() {return shapeMag.size(); }
    int getNumShapesRenderArea() {return numShapesRenderArea;}

    //functions to modify shapes
    void addShape(Shape* shapeIn);

    void cutShape(int inRemove);
    void moveShape(int inMove, int coordMove, int x, int y);

private:
    const QImage renderArea;
    sdog::vector<Shape*> shapeMag;
    int numShapesRenderArea;

    void readShapeFile();

   QString getStringColor(QColor color);
   QString getStringPenCap(Qt::PenCapStyle penCapStyle);
   QString getStringPenStyle(Qt::PenStyle penStyle);
   QString getStringPenJointStyle(Qt::PenJoinStyle penJointStyle);
   QString getStringBrush(Qt::BrushStyle brush);
   QString getStringFlag(Qt::AlignmentFlag  flag);
   QString getStringFontStyle(QFont::Style fontStyle);
   QString getStringFontWeight(int fontWeight);

   Shape::ShapeTypes getShapeType(QString shape);
   Qt::GlobalColor   getColor(QString color);
   Qt::PenCapStyle   getPenCapStyle(QString cap);
   Qt::PenStyle      getPenStyle(QString pen);
   Qt::PenJoinStyle  getPenJointStyle(QString penJoint);
   Qt::BrushStyle    getBrushStyle(QString brushStyle);
   Qt::AlignmentFlag getFlag(QString flag);
   QFont::Style      getFontStyle(QString fontStyle);
   QFont::Weight     getFontWeight(QString fontWeight);


};



#endif // RENDERAREA_H
