#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QPainter>
#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <Qt>
#include <QRect>
#include "vector.h"
#include <string>

const QString FILE_PATH = "C:/Users/Adit/Desktop/CS1C Project";

using namespace Qt;
using namespace sdog;

//********SHAPE ABC**********
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

    //add copy operations

    Shape(QPaintDevice *device) : qpainter(device)
    {
        id = -1;
        shape = ShapeTypes::blank;
        pen = Qt::SolidLine;
        brush = Qt::NoBrush;
    }

    virtual ~Shape() {}

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
    void setPen(QColor color, int width, Qt::PenStyle style, Qt::PenCapStyle penCap, Qt::PenJoinStyle penJoin)
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
    virtual void draw(QPaintDevice *device) = 0;

    virtual void move(int x, int y, int coord) = 0;

    //get beginning and ends of points for the shape renders
    virtual QPoint getPointBegin() { return QPoint(0,0); }
    virtual QPoint getPointEnd() { return QPoint(0,0); }

    virtual vector<QPoint>& getPoints() {return vect;}

    //virtual double perimeter() const = 0;

    //virtual double area() const = 0;


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

//*******LINE CLASS******
class Line : public Shape
{
private:
    QPoint pointBegin;
    QPoint pointEnd;
public:

    Line() : Shape()
    {
        pointBegin.setX(0);
        pointBegin.setY(0);
        pointEnd.setX(10);
        pointEnd.setY(10);
    }

    Line(QPoint _pointBegin, QPoint _pointEnd) : Shape()
    {
        pointBegin = _pointBegin;
        pointEnd = _pointEnd;
    }

    // contructor to use with parser
    Line(QPoint& x, QPoint& y, QPen& pen, int id)
    {
        setID(id);
        setPen(pen.color(), pen.width(), pen.style(), pen.capStyle(), pen.joinStyle());
        setPoints(x, y);
    }

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

    void move(int x, int y, int coord, int id) override
    {
        QPoint point(x, y);
        if (coord == 1)
        {
            pointBegin = point;
        }
        else if (coord == 2)
        {
            pointEnd = point;
        }


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

    Polyline(QPaintDevice *device, const QPoint& point) : Shape(device)
    {
        points.push_back(point);
    }

    ~Polyline() override {}

    //adds a point to vector that is used to make polyline (QPoint passed in)
    void setPoints(QPoint &point)
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
        getQPainter().setBrush(getBrush());
        getQPainter().drawPolyline(points.begin(), points.size());
        getQPainter().end();
    }

    void move(int x, int y, int coord) override
    {
       QPoint point(x, y);
       points[coord - 1] = point;
    }

    vector<QPoint>& getPoints() override {return points;};

};

/******POLYGON CLASS*****/
class Polygon : public Shape
{
private:
    vector <QPoint> points;

public:
    Polygon() : Shape() {}

    Polygon(QPaintDevice* device, QPoint& _points) : Shape(device)
    {
        points.push_back(_points);
    }


    ~Polygon() override {}

    //adds point to vector used for polygon
    void setPoints(const QPoint& point)
    {
        points.push_back(point);
    }


    void draw(QPaintDevice* device) override
    {
        QString shapeId = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(getPen());
        getQPainter().setBrush(getBrush());
        getQPainter().drawPolygon(points.begin(), points.size());
        getQPainter().end();
    }

    void move(int x, int y, int coord) override
    {
       QPoint point(x, y);
       points[coord - 1] = point;
    }

    vector<QPoint>& getPoints() override {return points;}

};

//*******RECTANGLE CLASS*******
class Rectangle : public Shape
{
private:
    int xpos;
    int ypos;
    int width;
    int height;

public:

    Rectangle() : Shape()
    {
        xpos = 0;
        ypos = 0;
        width = 20;
        height = 10;
    }

    Rectangle(int x, int y, int w, int h) : Shape()
    {
        xpos = x;
        ypos = y;
        width = w;
        height = h;
    }

    void setRectStart(int xCoord, int yCoord)
    {
        xpos = xCoord;
        ypos = yCoord;
    }

    void setWidth(int newWidth)
    {
        width = newWidth;
    }

    void setHeight(int newHeight)
    {
        height = newHeight;
    }

    void draw(QPaintDevice *device) override
    {
        QString shapeId = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(getPen());
        getQPainter().setBrush(getBrush());
        getQPainter().drawRect(xpos, ypos, width, height);
        getQPainter().end();
    }

    void move(int x, int y, int coord) override
    {
        xpos = x;
        ypos = y;
        getQPainter().drawRect(xpos, ypos, width, height);
    }

    int getXCoord()
    {
        return xpos;
    }

    int getYCoord()
    {
        return ypos;
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }
};

//*******SQUARE CLASS*******
class Square : public Shape
{
private:
    int xpos;
    int ypos;
    int width;
    int height;

public:

    Square() : Shape()
    {
        xpos = 0;
        ypos = 0;
        width = 10;
        height = 10;
    }

    Square(QPaintDevice *device, int x, int y, int sL) : Shape(device)
    {
        xpos = x;
        ypos = y;
        width = sL;
        height = width;
    }

    void setSquareStart(int xCoord, int yCoord)
    {
        xpos = xCoord;
        ypos = yCoord;
    }

    void setSideLength(int side)
    {
        width = side;
        height = width;
    }

    void draw(QPaintDevice *device) override
    {
        QString shapeId = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(getPen());
        getQPainter().setBrush(getBrush());
        getQPainter().drawRect(xpos, ypos, width, height);
        getQPainter().end();
    }

    void move(int x, int y, int coord) override
    {
        xpos = x;
        ypos = y;
        getQPainter().drawRect(xpos, ypos, width, height);
    }

    int getXCoord()
    {
        return xpos;
    }

    int getYCoord()
    {
        return ypos;
    }

    int getSideLength()
    {
        return width;
    }
};

//*******CIRCLE CLASS*******
class Circle : public Shape
{
private:
    int xpos;
    int ypos;
    int height;
    int width;

public:

    Circle() : Shape()
    {
        xpos = 0;
        ypos = 0;
        height = 10;
        width = 10;
    }

    Circle(QPaintDevice *device, int x, int y, int rad) : Shape(device)
    {
        xpos = x;
        ypos = y;
        width = rad;
        height = width;
    }

    void setCircleStart(int xCoord, int yCoord)
    {
        xpos = xCoord;
        ypos = yCoord;
    }

    void setRadius(int radius)
    {
        width = radius;
        height = radius;
    }

    void draw(QPaintDevice *device) override
    {
        QString shapeId = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(getPen());
        getQPainter().setBrush(getBrush());
        getQPainter().drawEllipse(xpos, ypos, width, height);
        getQPainter().end();
    }

    int getXCoord()
    {
        return xpos;
    }

    int getYCoord()
    {
        return ypos;
    }

    int getRadius()
    {
        return width;
    }
};

//*******ELLIPSE CLASS*******
class Ellipse : public Shape
{
private:
    int xpos;
    int ypos;
    int height;
    int width;

public:

    Ellipse() : Shape()
    {
        xpos = 0;
        ypos = 0;
        height = 10;
        width = 10;
    }

    Ellipse(QPaintDevice *device, int x, int y, int h, int w) : Shape(device)
    {
        xpos = x;
        ypos = y;
        height = h;
        width = w;
    }

    void setEllipseStart(int xCoord, int yCoord)
    {
        xpos = xCoord;
        ypos = yCoord;
    }

    void setHeight(int newHeight)
    {
        height = newHeight;
    }

    void setWidth(int newWidth)
    {
        width = newWidth;
    }

    void draw(QPaintDevice *device) override
    {
        QString shapeId = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(getPen());
        getQPainter().setBrush(getBrush());
        getQPainter().drawEllipse(xpos, ypos, width, height);
        getQPainter().end();
    }

    int getXCoord()
    {
        return xpos;
    }

    int getYCoord()
    {
        return ypos;
    }

    int getHeight()
    {
        return height;
    }

    int getWidth()
    {
        return width;
    }
};

//******TEXT CLASS********
class Text : public Shape
{
    // Text properties: alignment (right, left, etc)
    //                  color, string to print, font, etc...
    //======================================================
private:
    // coords for top left point of text box
    int tx;
    int ty;
    // coords for bottom right point of text box
    int bx;
    int by;

    QRect textbox;      // creates a null rectangle
    QFont fontobj; // need seperate object to pass values to for QFont functions

    QString TextString;
    QColor TextColor;
    Qt::AlignmentFlag TextAlignment;
    QFont::Style TextFontStyle;
    QString TextFontFamily;
    QFont::Weight TextFontWeight;
    int TextPointSize;

    // PMF's:
    // Setters and draw functions.
    //======================================================
public:

    Text() : Shape() {}

    Text(int id, int tx, int ty, int bx, int by,
         QString TextString, QColor TextColor,
         Qt::AlignmentFlag TextAlignment,
         QFont::Style TextFontStyle, QString TextFontFamily,
         QFont::Weight TextFontWeight, int TextPointSize){
        // this->id = id
        this->tx = tx;
        this->ty = ty;
        this->bx = bx;
        this->by = by;
        //this->textbox = textbox;
        this->TextString = TextString;
        this->TextColor = TextColor;
        this->TextAlignment = TextAlignment;
        this->TextFontStyle = TextFontStyle;
        this->TextFontFamily = TextFontFamily;
        this->TextFontWeight = TextFontWeight;
        this->TextPointSize = TextPointSize;
    }

    Text(QPaintDevice *device) : Shape(device) {}

    ~Text() override {};

    // Setters:
    //===========================
    // Set length and width of text box
    void setTextBox(const int& tx, const int& ty, const int &bx, const int& by)
    {
        textbox.setCoords(tx, ty, bx, by);
    }

    // Set string of text
    void setTextString(const QString& inString)
    {
        TextString = inString;
    }
    //____________________________________________________

    // Set all values of Text shape
    void setTextShape(const QRect& rO, const int tx, const int ty, const int bx, const int by, const QString tString, const QColor tClr,
                      const Qt::AlignmentFlag tAlign, const int tpSize, const QString tFont,
                      const QFont::Style tStyle, const QFont::Weight tWeight)
    {
        textbox = rO;
        this->tx = tx;
        this->ty = ty;
        this->bx = bx;
        this->by = by;

        textbox.setCoords(tx, ty, bx, by);

        TextString = tString;
        TextColor = tClr;
        TextAlignment = tAlign;
        TextPointSize = tpSize;
        TextFontFamily = tFont;
        TextFontStyle = tStyle;
        TextFontWeight = tWeight;

        // specifically for font to print
        fontobj.setPointSize(TextPointSize);
        fontobj.setFamily(TextFontFamily);
        fontobj.setStyle(TextFontStyle);
        fontobj.setWeight(TextFontWeight);

    };
    //____________________________________________________

    // Getters:
    //===========================
    QRect getRect()
    {
        return textbox;
    }
    int getX1Coord()
    {
        return tx;
    }

    int getY1Coord()
    {
        return ty;
    }
    int getX2Coord()
    {
        return bx;
    }

    int getY2Coord()
    {
        return by;
    }
    QString getTextString()
    {
        return TextString;
    }
    //____________________________________________________

    void draw(QPaintDevice* device) override
    {
        QString idStr = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(TextColor);
        getQPainter().setFont(fontobj);
        getQPainter().save();   // push current data onto stack

        // Drawing text:
        getQPainter().drawText(textbox, TextAlignment, TextString);
        getQPainter().setPen(QColor(Qt::GlobalColor::black)); // set color to rgb: 0,0,0

        getQPainter().restore();
        getQPainter().end();    // pop / unwind stack
    }
};




#endif // SHAPE_H
