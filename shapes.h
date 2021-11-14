#ifndef SHAPE_H
#define SHAPE_H


#include <QObject>
#include <QPainter>
#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <Qt>
#include "vector.h"
#include <string>

const QString FILE_PATH = "C:/Users/Adit/Desktop/CS1C Project";

using namespace Qt;
using namespace sdog;

//********SHAPE ABC***********
class Shape : public QPainter
{   
public:
    enum ShapeTypes {blank, line, polyline, polygon, rectangle, square, ellipse, circle, text};

    Shape()
    {
        id = -1;
        shape = ShapeTypes::blank;          //default shapeType
        pen = Qt::SolidLine;                //default pen stroke - solid line
        brush = Qt::NoBrush;                // default brush type - no brush pattern (use Qt::SolidPattern for uniform color)
    }

    Shape(QPaintDevice *device) : qpainter(device)
    {
        id = -1;
        shape = ShapeTypes::blank;
        pen = Qt::SolidLine;
        brush = Qt::NoBrush;
    }

    virtual ~Shape();

    /*****GETTERS*****/
    //returns Shape ID
    int getID() const { return id; };

    //returns shape type of object
    ShapeTypes getShape() const { return shape;};

    //QRect idBox;

    //returns QPen pen
    QPen & getPen() { return pen;};

    //returns QBrush brush
    QBrush & getBrush() { return brush; };

    /*******SETTERS*******/

    //set shapes ID taking integer value from file read variable
    void setID(const int identification)
    {
        id = identification;
        return;
    }

    //sets shape to the shape type it is using enum shapeTypes
    void setShape(ShapeTypes shapetype)
    {
        shape = shapetype;
        return;
    }

    //sets QPen - uses Qt::GlobalColor (constructs color based on val, Qt::GlobalColor uses predefined QColor objects), width, Qt::PenStyle, Qt::PenCapStyle, and Qt::PenJoinStyle based on arguments passed in from file
    // uses values passed in for QPen setters to set pen types
    void setPen(Qt::GlobalColor color, int width, Qt::PenStyle style, Qt::PenCapStyle penCap, Qt::PenJoinStyle penJoin)
    {
        pen.setColor(color);
        pen.setWidth(width);
        pen.setStyle(style);
        pen.setCapStyle(penCap);
        pen.setJoinStyle(penJoin);
        return;

    }

    //sets QBrush - uses Qt::GlobalColor (constructs color based on val, Qt::GlobalColor uses predefined QColor objects), and Qt::BrushStyle
    void setBrush(Qt::GlobalColor color, Qt::BrushStyle style)
    {
        brush.setColor(color);
        brush.setStyle(style);
        return;
    }

    //sets pen and brush to a default
    void defaultStyle()
    {
        pen = Qt::SolidLine;
        brush = Qt::NoBrush;

        qpainter.setPen(pen);
        qpainter.setBrush(brush);
        return;
    }

    //pure virtual function - draws shape for every subclass
    virtual void draw(QPaintDevice *device, const int x = 0, const int y = 0) = 0;

    //get beginning and ends of points for the shape renders
    virtual QPoint getPointBegin() { return QPoint(0,0); }
    virtual QPoint getPointEnd() { return QPoint(0,0); }

    virtual vector<QPoint>& getPoints() {return vect;}

protected:
    QPainter & getQPainter()
    {
        return qpainter;
    }

private:
    QPainter qpainter;

    int id;
    ShapeTypes shape;
    QPen pen;
    QBrush brush;
    vector<QPoint> vect;

};

//*******LINE CLASS*******
class Line : public Shape
{
private:
    QPoint pointBegin;
    QPoint pointEnd;
public:

    Line() : Shape() {}

    Line(QPaintDevice *device) : Shape(device) {}

    //setPoints - sets points through QPoint objects
    void setPoints(const QPoint &begin, const QPoint &end)
    {
        pointBegin = begin;
        pointEnd = end;
    }

    //draws line
    void draw(QPaintDevice *device) override
    {
        QString shapeId = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(getPen());
        getQPainter().setBrush(getBrush());
        getQPainter().drawLine(pointBegin, pointEnd);
        getQPainter().drawText(pointBegin, shapeId);
        getQPainter().end();
    }

    QPoint getPointBegin() override
    {
        return pointBegin;
    }

    QPoint getPointEnd() override
    {
        return pointEnd;
    }


};

//******POLYLINE CLASS********
class Polyline : public Shape
{
private:
    vector <QPoint> points;
public:
    Polyline() : Shape() {}

    Polyline(QPaintDevice *device) : Shape(device) {}

    ~Polyline() override {}

    //adds a point to vector that is used to make polyline (QPoint passed in)
    void setPoints(const QPoint &point)
    {
        points.push_back(point);
        return;
    }

    //draws polyline
    void draw(QPaintDevice *device) override
    {
        QString shapeId = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(getPen());
        getQPainter().drawPolyline(points.begin(), points.size());
        getQPainter().end();
    }

    vector<QPoint>& getPoints() override {return points;};

};



#endif // SHAPE_H
