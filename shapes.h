#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QColor>
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
        id = 0;
        shape = ShapeTypes::blank;          //default shapeType
        pen = Qt::SolidLine;                //default pen stroke - solid line
        brush = Qt::NoBrush;                // default brush type - no brush pattern (use Qt::SolidPattern for uniform color)

        id = numShapes;
        numShapes++;
    }

    //add copy operations

    Shape(QPaintDevice *device) : qpainter(device)
    {
        id = 0;
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
    void setBrush(QColor color, Qt::BrushStyle style)
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

    virtual void move(int x, int y, int coord, int id) = 0;

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
    static int numShapes;

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
const int DEFAULT_NUM_PTS = 8;
//******POLYLINE CLASS********
class Polyline : public Shape
{
private:
    QPoint pointArr[DEFAULT_NUM_PTS];
    int numPts;

public:
    Polyline() : Shape() {}

    Polyline(QPoint *point, int NP) : Shape()
    {
        numPts = NP;
        for (int i = 0; i < numPts; i++)
        {
            pointArr[i] = point[i];
        }
    }

    ~Polyline() override {}

    //adds a point to vector that is used to make polyline (QPoint passed in)
    void setPoints(const QPoint &point)
    {
        pointArr[numPts] = point;
        numPts++;
    }

    //draws polyline
    void draw(QPaintDevice *device) override
    {
        QString shapeId = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(getPen());
        getQPainter().setBrush(getBrush());
        getQPainter().drawPolyline(pointArr, numPts);
        getQPainter().drawText(pointArr[0], shapeId);
        getQPainter().end();
    }

    void move(int x, int y, int coord, int id) override
    {
       QPoint point(x, y);
       pointArr[coord - 1] = point;
    }

    //vector<QPoint>& getPoints() override {return points;};

};

/******POLYGON CLASS*****/
class Polygon : public Shape
{
private:
    QPoint pointArr[DEFAULT_NUM_PTS];
    int numPts;

public:
    Polygon() : Shape() {}

    Polygon(QPoint *point, int NP) : Shape()
    {
        numPts = NP;
        for (int i = 0; i < numPts; i++)
        {
            pointArr[i] = point[i];
        }
    }


    ~Polygon() override {}

    //adds point to vector used for polygon
    void setPoints(const QPoint& point)
    {
        pointArr[numPts] = point;
        numPts++;
    }


    void draw(QPaintDevice* device) override
    {
        QString shapeId = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(getPen());
        getQPainter().setBrush(getBrush());
        getQPainter().drawPolyline(pointArr, numPts);
        getQPainter().drawText(pointArr[0], shapeId);
        getQPainter().end();
    }

    void move(int x, int y, int coord, int id) override
    {
       QPoint point(x, y);
       pointArr[coord - 1] = point;
    }

    //vector<QPoint>& getPoints() override {return points;}

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
        width = 0;
        height = 0;
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
        getQPainter().drawText(xpos, ypos, shapeId);
        getQPainter().end();
    }

    void move(int x, int y, int coord, int id) override
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

    void move(int x, int y, int coord, int id) override
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
        width = 10;
        height = 10;
    }

    Circle(int x, int y, int w, int h) : Shape()
    {
        xpos = x;
        ypos = y;
        width = w;
        height = h;
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

    void move(int x, int y, int coord, int id) override
    {
        xpos = x;
        ypos = y;
        getQPainter().drawEllipse(xpos, ypos, width, height);

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
    int width;
    int height;


public:

    Ellipse() : Shape()
    {
        xpos = 0;
        ypos = 0;
        width = 10;
        height = 10;
    }

    Ellipse(int x, int y, int w, int h) : Shape()
    {
        xpos = x;
        ypos = y;
        width = w;
        height = h;
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
        getQPainter().drawText(xpos, ypos, shapeId);
        getQPainter().end();
    }

    void move(int x, int y, int coord, int id) override
    {
        xpos = x;
        ypos = y;
        getQPainter().drawEllipse(xpos, ypos, width, height);

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

    QFont fontobj; // need seperate object to pass values to for QFont functions

    QString TextString;
    QColor TextColor;
    Qt::AlignmentFlag TextAlignment;
    int TextPointSize;

    // PMF's:
    // Setters and draw functions.
    //======================================================
public:

    Text() : Shape() {}

    Text(int tx, int ty, int bx, int by,
         QString TextString, int TC,
         int TA,
         int TFS, int TFF,
         int TFW, int TPS){
        // this->id = id
        this->tx = tx;
        this->ty = ty;
        this->bx = bx;
        this->by = by;
        //this->textbox = textbox;
        this->TextString = TextString;
        //this->TextColor = TextColor;
        //this->TextAlignment = TextAlignment;
        //this->TextFontStyle = TextFontStyle;
        //this->TextFontFamily = TextFontFamily;
        //this->TextFontWeight = TextFontWeight;

        switch(TC)
        {
            case 0: TextColor = Qt::blue;
                break;
            case 1: TextColor = Qt::red;
                break;
            case 2: TextColor = Qt::green;
                break;
            case 3: TextColor = Qt::yellow;
                break;
            case 4: TextColor = Qt::black;
                break;
            case 5: TextColor = Qt::white;
                break;
            case 6: TextColor = Qt::cyan;
                break;
            case 7: TextColor = Qt::magenta;
                break;
            case 8: TextColor = Qt::gray;
                break;
        }

        switch(TA)
        {
            case 0: TextAlignment = Qt::AlignLeft;
                break;
            case 1: TextAlignment = Qt::AlignCenter;
                    break;
            case 2: TextAlignment = Qt::AlignRight;
                    break;
            case 3: TextAlignment = Qt::AlignTop;
                    break;
            case 4: TextAlignment = Qt::AlignBottom;
                break;
        }

        switch(TFS)
        {
            case 0:
                break;
            case 1: fontobj.setItalic(1);
                break;
            case 2: fontobj.setBold(1);
                break;
        }

        switch(TFF)
        {
            case 0: fontobj.setFamily("Comic Sans MS");
                break;
            case 1: fontobj.setFamily("Courier");
                break;
            case 2: fontobj.setFamily("Helvetica");
                break;
            case 3: fontobj.setFamily("Times");
                break;
        }

        switch(TFW)
        {
            case 0: fontobj.setWeight(QFont::Thin);
                break;
            case 1: fontobj.setWeight(QFont::Light);
                    break;
            case 2: fontobj.setWeight(QFont::Normal);
                    break;
            case 3: fontobj.setWeight(QFont::Bold);
                    break;
        }

        fontobj.setPointSize(TPS);
    }

    Text(QPaintDevice *device) : Shape(device) {}

    ~Text() override {};

    // Setters:
    //===========================
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
        this->tx = tx;
        this->ty = ty;
        this->bx = bx;
        this->by = by;

        TextString = tString;
        TextColor = tClr;
        TextAlignment = tAlign;
        TextPointSize = tpSize;

        // specifically for font to print
        fontobj.setPointSize(TextPointSize);

    };
    //____________________________________________________

    // Getters:
    //===========================
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
        QString shapeId = "ID: " + QString::number(getID());
        getQPainter().begin(device);
        getQPainter().setPen(TextColor);
        getQPainter().setFont(fontobj);

        // Drawing text:
        getQPainter().drawText(this->tx, this->ty, this->bx, this->by, TextAlignment, TextString);
        getQPainter().drawText(this->tx, this->ty, shapeId);


        getQPainter().end();    // pop / unwind stack
    }

    void move(int x, int y, int coord, int id) override
    {
        this->tx = x;
        this->ty = y;
    }
};




#endif // SHAPE_H
