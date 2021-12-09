#include <QCoreApplication>
#include <QFile>
#include <fstream>
#include <iostream>
#include <string>
#include <QTextStream>
#include "shapes.h"

using namespace std;

Shape* ReadLine(std::ifstream&, int id);
Shape* ReadPolyLine(std::ifstream&, int id);
Shape* ReadPolygon(std::ifstream&, int id);
Shape* ReadRectangle(std::ifstream&, int id);
Shape* ReadSquare(std::ifstream&, int id);
Shape* ReadEllipse(std::ifstream&, int id);
Shape* ReadCircle(std::ifstream&, int id);
Shape* ReadText(std::ifstream&, int id);

Qt::GlobalColor getColor(const std::string&);
Qt::PenStyle getPenStyle(const std::string&);
Qt::PenCapStyle getPenCapStyle(const std::string&);
Qt::PenJoinStyle getPenJoinStyle(const std::string&);
Qt::BrushStyle getBrushStyle(const std::string&);
QFont::Weight getFontWeight(const std::string&);

sdog::vector<Shape*> readFile(string filename)
{
   sdog::vector<Shape*> shapeMag;
   QString namefile = "shapes.txt";
   QFile q_file("shapes.txt");

   if (!q_file.exists())
   {
       qCritical() << "File not opened!";
       exit(1); // error occurred, terminate program
   }

   if(!q_file.open(QIODevice::ReadOnly))
   {
       // Returns a human-readable description of the last device error that occurred.
       qCritical() << q_file.errorString(); //
       exit(1); // error occurred, terminate program
   }

   /* QTextStream stream(&file);
   while (!stream.atEnd())
   {
       QString line = stream.readLine();
       qInfo() << line;
   } */

   int ShapeID;

   ifstream file(filename);

   if(!file.is_open()) {
       qCritical() << "File failed to open!";
   }

   while(file.is_open()) {
       file.ignore(numeric_limits<streamsize>::max(), ':');
       file >> ShapeID;

       if(file.eof()) {
           break;
       }
       switch(ShapeID){
       //Read Line
       case 1:
           shapeMag.push_back(ReadLine(file, ShapeID));
           break;

       //Read PolyLine
       case 2:
           shapeMag.push_back(ReadPolyLine(file, ShapeID));
           break;

       //Read Polygon
       case 3:
           shapeMag.push_back(ReadPolygon(file, ShapeID));
           break;

       //Read Rectangle
       case 4:
           shapeMag.push_back(ReadRectangle(file, ShapeID));
           break;

       //Read Square
       case 5:
           shapeMag.push_back(ReadSquare(file, ShapeID));
           break;

       //Read Ellipse
       case 6:
           shapeMag.push_back(ReadEllipse(file, ShapeID));
           break;

       //Read Circle
       case 7:
           shapeMag.push_back(ReadCircle(file, ShapeID));
           break;

       //Read Text
       case 8:
           shapeMag.push_back(ReadText(file, ShapeID));
           break;
       }
   }
   file.close();
   return shapeMag;
}


/*!
 * \brief ReadLine
 * \param file
 * \param id
 * \return new line object
 */
Shape* ReadLine(std::ifstream& file, int id){
    //======================================
    int x{0};
    int y{0};
    int x2{0};
    int y2{0};
    string color;
    string style;
    string c_style;
    string join;
    int width{0};

    GlobalColor p_color;
    PenStyle p_style;
    PenCapStyle p_c_style;
    PenJoinStyle p_penjoin;
    //======================================

    // ShapeDimensions: get coords for qpoint begin and end
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> x;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> y;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> x2;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> y2;

    //---------------------
    // PenColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    p_color = getColor(color);  // value stored to q_color is never read -- issue?
    // GlobalColor getColor(const string&) - lets the user choose a color, and returns that color

    //---------------------
    // PenWidth
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> width;

    //---------------------
    // PenStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, style);
    p_style = getPenStyle(style);   // never read -- i think it's fine

    //---------------------
    // PenCapStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, c_style);
    p_c_style = getPenCapStyle(c_style);

    //---------------------
    // PenJoinStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, join);
    p_penjoin = getPenJoinStyle(join);

    //---------------------
    // need Qpen object and Qpoints
    QPoint pointBegin(x, y);    // set Qpoints
    QPoint pointEnd(x2, y2);
    QPen pen;
    pen.setColor(p_color);  // set QPen
    pen.setWidth(width);
    pen.setStyle(p_style);
    pen.setCapStyle(p_c_style);
    pen.setJoinStyle(p_penjoin);

    // create new line object and pass in params
    Line* line = new Line(pointBegin, pointEnd, pen, id);

   // return shape;
    return line;
}

Shape* ReadPolyLine(std::ifstream& file, int id){
    //======================================
    string color;
    string style;
    string c_style;
    string join;
    int width{0};

    QColor p_color;
    PenStyle p_style;
    PenCapStyle p_c_style;
    PenJoinStyle p_penjoin;

    std::vector<QPoint> points;
    Polyline* polyline = new Polyline();
    //======================================

    // ShapeDimensions
    file.ignore(numeric_limits<streamsize>::max(), ':');
    do {
        int x{0};
        int y{0};
        file.get();
        file >> x;
        file.get();
        file >> y;
        QPoint pt(x, y);
        polyline->setPoints(pt);
        // points.emplace_back(x, y);  // push_back did not work, but emplace_back did
        // push each point read in into points vector
    } while(file.peek() == ',');  // checks if next character to read is ','

    //---------------------
    // PenColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    p_color = getColor(color);

    //---------------------
    // PenWidth
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> width;

    //---------------------
    // PenStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, style);
    p_style = getPenStyle(style);   // never read -- i think it's fine

    //---------------------
    // PenCapStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, c_style);
    p_c_style = getPenCapStyle(c_style);

    //---------------------
    // PenJoinStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, join);
    p_penjoin = getPenJoinStyle(join);


    polyline->setPen(p_color, width, p_style, p_c_style, p_penjoin);

    return polyline;
}

Shape* ReadPolygon(std::ifstream& file, int id){
    //======================================
    string color;
    string style;
    string c_style;
    string join;
    int width{0};

    QColor p_color;
    PenStyle p_style;
    PenCapStyle p_c_style;
    PenJoinStyle p_penjoin;
    QColor b_color;
    BrushStyle b_style;

    std::vector<QPoint> points;
    //Needs constructor
    Polygon* polygon = new Polygon();
    //======================================

    // ShapeDimensions
    //Does this  work for Polygon?
    file.ignore(numeric_limits<streamsize>::max(), ':');
    do {
        int x{0};
        int y{0};
        file.get();
        file >> x;
        file.get();
        file >> y;
        QPoint pt(x, y);
        polygon->setPoints(pt);
        // points.emplace_back(x, y);  // push_back did not work, but emplace_back did
        // push each point read in into points vector
    } while(file.peek() == ',');  // checks if next character to read is ','

    //---------------------
    // PenColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    p_color = getColor(color);

    //---------------------
    // PenWidth
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> width;

    //---------------------
    // PenStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, style);
    p_style = getPenStyle(style);   // never read -- i think it's fine

    //---------------------
    // PenCapStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, c_style);
    p_c_style = getPenCapStyle(c_style);

    //---------------------
    // PenJoinStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, join);
    p_penjoin = getPenJoinStyle(join);

    //---------------------
    // BrushColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    b_color = getColor(color);

    //---------------------
    // BrushStyle
    file.ignore(numeric_limits<streamsize>::max(),  ':');
    getline(file, style);
    b_style = getBrushStyle(style);


    QPen pen;
    pen.setColor(p_color);  // set QPen
    pen.setWidth(width);
    pen.setStyle(p_style);
    pen.setCapStyle(p_c_style);
    pen.setJoinStyle(p_penjoin);

    QBrush brush;
    brush.setColor(b_color);
    brush.setStyle(b_style);

    return polygon;

    // ==========> need to either set values for obj or
    // make an overloaded constructor to pass values to
}

Shape* ReadRectangle(std::ifstream& file, int id){
    //======================================
    string color;
    string style;
    string c_style;
    string join;
    string bstyle;
    string bcolor;
    int width{0};
    int height{0};
    int x{0};
    int y{0};   // origin = point( x, y )

    QColor p_color;
    PenStyle p_style;
    PenCapStyle p_c_style;
    PenJoinStyle p_penjoin;
    QColor b_color;
    BrushStyle b_style;
    //======================================

    // ShapeDimensions
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> x;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> y;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> width;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> height;

    //---------------------
    // PenColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    p_color = getColor(color);

    //---------------------
    // PenWidth
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> width;

    //---------------------
    // PenStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, style);
    p_style = getPenStyle(style);   // never read -- i think it's fine

    //---------------------
    // PenCapStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, c_style);
    p_c_style = getPenCapStyle(c_style);

    //---------------------
    // PenJoinStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, join);
    p_penjoin = getPenJoinStyle(join);

    //---------------------
    // BrushColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    b_color = getColor(color);

    //---------------------
    // BrushStyle
    file.ignore(numeric_limits<streamsize>::max(),  ':');
    getline(file, style);
    b_style = getBrushStyle(style);


    QPen pen;
    pen.setColor(p_color);  // set QPen
    pen.setWidth(width);
    pen.setStyle(p_style);
    pen.setCapStyle(p_c_style);
    pen.setJoinStyle(p_penjoin);

    QBrush brush;
    brush.setColor(b_color);
    brush.setStyle(b_style);

    //Needs constructor
    // ==========> need to either set values for obj or
    // make an overloaded constructor to pass values to
    Rectangle* rectangle = new Rectangle();
    return rectangle;
}

Shape* ReadSquare(std::ifstream& file, int id){
    //======================================
    string color;
    string style;
    string c_style;
    string join;
    string bstyle;
    string bcolor;
    int width{0};   // square does not have height since width == height
    int x{0};
    int y{0};   // origin = point( x, y )

    QColor p_color;
    PenStyle p_style;
    PenCapStyle p_c_style;
    PenJoinStyle p_penjoin;
    QColor b_color;
    BrushStyle b_style;
    //======================================

    // ShapeDimensions
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> x;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> y;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> width;

    //---------------------
    // PenColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    p_color = getColor(color);

    //---------------------
    // PenWidth
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> width;

    //---------------------
    // PenStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, style);
    p_style = getPenStyle(style);   // never read -- i think it's fine

    //---------------------
    // PenCapStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, c_style);
    p_c_style = getPenCapStyle(c_style);

    //---------------------
    // PenJoinStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, join);
    p_penjoin = getPenJoinStyle(join);

    //---------------------
    // BrushColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    b_color = getColor(color);

    //---------------------
    // BrushStyle
    file.ignore(numeric_limits<streamsize>::max(),  ':');
    getline(file, style);
    b_style = getBrushStyle(style);

    QPen pen;
    pen.setColor(p_color);  // set QPen
    pen.setWidth(width);
    pen.setStyle(p_style);
    pen.setCapStyle(p_c_style);
    pen.setJoinStyle(p_penjoin);

    QBrush brush;
    brush.setColor(b_color);
    brush.setStyle(b_style);

    // ==========> need to either set values for obj or
    // make an overloaded constructor to pass values to
    Square* square = new Square();
    return square;
}

// dipples got tired, to be continued...
//==============================================================

Shape* ReadEllipse(std::ifstream& file, int id){
    string color;
    string style;
    string c_style;
    string join;
    int width{0};

    QColor p_color;
    PenStyle p_style;
    PenCapStyle p_c_style;
    PenJoinStyle p_penjoin;
    QColor b_color;
    BrushStyle b_style;

    std::vector<QPoint> points;

    file.ignore(numeric_limits<streamsize>::max(), ':');
    do {
        int x{0};
        int y{0};
        file.get();
        file >> x;
        file.get();
        file >> y;
        points.emplace_back(x, y);  // push_back did not work, but emplace_back did
        // push each point read in into points vector
    } while(file.peek() == ',');  // checks if next character to read is ','

    // PenColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    p_color = getColor(color);

    // PenWidth
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> width;

    // PenStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, style);
    p_style = getPenStyle(style);   // never read -- i think it's fine

    // PenCapStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, c_style);
    p_c_style = getPenCapStyle(c_style);

    // PenJoinStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, join);
    p_penjoin = getPenJoinStyle(join);

    // BrushColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    b_color = getColor(color);

    // BrushStyle
    file.ignore(numeric_limits<streamsize>::max(),  ':');
    getline(file, style);
    b_style = getBrushStyle(style);

    QPen pen;
    pen.setColor(p_color);  // set QPen
    pen.setWidth(width);
    pen.setStyle(p_style);
    pen.setCapStyle(p_c_style);
    pen.setJoinStyle(p_penjoin);

    QBrush brush;
    brush.setColor(b_color);
    brush.setStyle(b_style);

    //Needs constructor
    Ellipse* ellipse= new Ellipse(points, pen, brush, id);
    return ellipse;
}

Shape* ReadCircle(std::ifstream& file, int id){
    string color;
    string style;
    string c_style;
    string join;
    int width{0};

    QColor p_color;
    PenStyle p_style;
    PenCapStyle p_c_style;
    PenJoinStyle p_penjoin;
    QColor b_color;
    BrushStyle b_style;

    std::vector<QPoint> points;

    file.ignore(numeric_limits<streamsize>::max(), ':');
    do {
        int x{0};
        int y{0};
        file.get();
        file >> x;
        file.get();
        file >> y;
        points.emplace_back(x, y);  // push_back did not work, but emplace_back did
        // push each point read in into points vector
    } while(file.peek() == ',');  // checks if next character to read is ','

    // PenColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    p_color = getColor(color);

    // PenWidth
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> width;

    // PenStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, style);
    p_style = getPenStyle(style);   // never read -- i think it's fine

    // PenCapStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, c_style);
    p_c_style = getPenCapStyle(c_style);

    // PenJoinStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, join);
    p_penjoin = getPenJoinStyle(join);

    // BrushColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    b_color = getColor(color);

    // BrushStyle
    file.ignore(numeric_limits<streamsize>::max(),  ':');
    getline(file, style);
    b_style = getBrushStyle(style);

    QPen pen;
    pen.setColor(p_color);  // set QPen
    pen.setWidth(width);
    pen.setStyle(p_style);
    pen.setCapStyle(p_c_style);
    pen.setJoinStyle(p_penjoin);

    QBrush brush;
    brush.setColor(b_color);
    brush.setStyle(b_style);

    //Needs constructor
    Circle* circle = new Circle(points, pen, brush, id);
    return circle;
}

Shape* ReadText(std::ifstream& file, int id){

    string color;
    string textLine;
    string align;
    string fontSize;
    string fontFam;
    string fontStyle;
    string fontWeight;

    int x1;
    int x2;
    int y1;
    int y2;

    QColor t_color;

    // ShapeDimensions
    file.ignore(numeric_limits<streamsize>::max(), ':');
    file >> x1;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> y1;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> x2;
    file.ignore(numeric_limits<streamsize>::max(), ',');
    file >> y2;

    QPoint topLeft(x1, y1);

    QPoint bottomRight(x2, y2);

    QRect textShape (const QPoint &topLeft, const QPoint &bottomRight);

    // TextString
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, textLine);

    // TextColor
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, color);
    t_color = getColor(color);

    // TextAlignment
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, align);

    // TextPointSize
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, fontSize);

    //TextFontFamily
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, fontFam);

    //TextFontStyle
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, fontStyle);

    //TextFontWeight
    file.ignore(numeric_limits<streamsize>::max(), ':');
    getline(file, fontWeight);

    //Needs constructor
    Text* text = new Text();
    return text;
}



