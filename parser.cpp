#include "mainwindow.h"
#include "shape.h"
#include "vector.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <stdio.h>
#pragma pack(1)

const int BLOCK_MAX = 500;

struct Data {
    int shapeID;
    QString shapeType;
    int shapeDimensions[10];
    QString penColor;
    int penWidth;
    QString penStyle;
    QString penCapStyle;
    QString penJoinStyle;
    QString brushColor;
    QString brushStyle;
    QString textString;
    QString textColor;
    QString textAlignment;
    int textPointSize;
    QString textFontFamily;
    QString textFontStyle;
    QString textFontWeight;
};

void sdParser(QString filename) {

    Data blockData[BLOCK_MAX];
    QFile file(filename);

    //Checks for file existence
    if (!file.exists()) {
        qCritical() << "File not found!";
        return;
    }

    //Checks if file can be opened and read
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << file.errorString();
        return;
    }

    qInfo() << "Parsing data...";

    QTextStream stream(&file);

    //Parses data
    int blockTrack = 0;
    while (!stream.atEnd()) {
        QString line = stream.readLine();

        //Reads ShapeId to the data struct
        if (line.startsWith("ShapeId:")) {
            line = line.mid(9);
            blockData[blockTrack].shapeID = line.toInt();
            line = file.readLine();
        }

        //Where the magic happens, detects that line starts with ShapeType
        //Enters ShapeType statement, but does not enter any of the specific
        //shape statements.
        if (line.startsWith("ShapeType: Line")) {
            qInfo() << "Reading line data...";
            if (line.startsWith("ShapeDimensions:")) {
                line = line.mid(17);
                blockData[blockTrack].shapeDimensions[1] = line.toInt();
                line = file.readLine();
            }
            else if (line.startsWith("PenColor:")) {
                line = line.mid(10);
                blockData[blockTrack].penColor = line;
                line = file.readLine();
            }
            else if (line.startsWith("PenWidth:")) {
                line = line.mid(10);
                blockData[blockTrack].penWidth = line.toInt();
            }
            else if (line.startsWith("PenStyle:")) {
                line = line.mid(10);
                blockData[blockTrack].penStyle = line;
                line = file.readLine();
            }
            else if (line.startsWith("PenCapStyle:")) {
                line = line.mid(13);
                blockData[blockTrack].penCapStyle = line;
                line = file.readLine();
            }
            //Won't read this for some reason
            else if (line.startsWith("PenJoinStyle:")) {
                line = line.mid(14);
                blockData[blockTrack].penJoinStyle = line;
                line = file.readLine();
            }
            blockTrack++;
        }

        else if (line.startsWith("ShapeType: Polyline")) {
            qInfo() << "Reading polyline data...";
            if (line.startsWith("ShapeDimensions:")) {
                line = line.mid(17);
                blockData[blockTrack].shapeDimensions[1] = line.toInt();
                line = file.readLine();
            }
            else if (line.startsWith("PenColor:")) {
                line = line.mid(10);
                blockData[blockTrack].penColor = line;
                line = file.readLine();
            }
            else if (line.startsWith("PenWidth:")) {
                line = line.mid(10);
                blockData[blockTrack].penWidth = line.toInt();
            }
            else if (line.startsWith("PenStyle:")) {
                line = line.mid(10);
                blockData[blockTrack].penStyle = line;
                line = file.readLine();
            }
            else if (line.startsWith("PenCapStyle:")) {
                line = line.mid(13);
                blockData[blockTrack].penCapStyle = line;
                line = file.readLine();
            }
            //Won't read this for some reason
            else if (line.startsWith("PenJoinStyle:")) {
                line = line.mid(14);
                blockData[blockTrack].penJoinStyle = line;
                line = file.readLine();
            }
            blockTrack++;
        }

        else if (line.startsWith("ShapeType: Polygon")) {
            qInfo() << "Reading polygon data...";
            //Needs to read in up to 10 integers separated by commas into array
            //Use a loop?
            if (line.startsWith("ShapeDimensions:")) {
                line = line.mid(17);
                blockData[blockTrack].shapeDimensions[1] = line.toInt();
                line = file.readLine();
            }

            else if (line.startsWith("PenColor:")) {
                line = line.mid(10);
                blockData[blockTrack].penColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("PenWidth:")) {
                line = line.mid(10);
                blockData[blockTrack].penWidth = line.toInt();
            }

            else if (line.startsWith("PenStyle:")) {
                line = line.mid(10);
                blockData[blockTrack].penStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("PenCapStyle:")) {
                line = line.mid(13);
                blockData[blockTrack].penCapStyle = line;
                line = file.readLine();
            }

            //Won't read this for some reason
            else if (line.startsWith("PenJoinStyle:")) {
                line = line.mid(14);
                blockData[blockTrack].penJoinStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("BrushColor:")) {
                line = line.mid(12);
                blockData[blockTrack].brushColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("BrushStyle:")) {
                line = line.mid(12);
                blockData[blockTrack].brushStyle = line;
                line = file.readLine();
            }
            blockTrack++;
        }

        else if (line.startsWith("ShapeType: Rectangle")) {
            qInfo() << "Reading rectangle data...";
            if (line.startsWith("ShapeDimensions:")) {
                line = line.mid(17);
                blockData[blockTrack].shapeDimensions[1] = line.toInt();
                line = file.readLine();
            }

            else if (line.startsWith("PenColor:")) {
                line = line.mid(10);
                blockData[blockTrack].penColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("PenWidth:")) {
                line = line.mid(10);
                blockData[blockTrack].penWidth = line.toInt();
            }

            else if (line.startsWith("PenStyle:")) {
                line = line.mid(10);
                blockData[blockTrack].penStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("PenCapStyle:")) {
                line = line.mid(13);
                blockData[blockTrack].penCapStyle = line;
                line = file.readLine();
            }

            //Won't read this for some reason
            else if (line.startsWith("PenJoinStyle:")) {
                line = line.mid(14);
                blockData[blockTrack].penJoinStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("BrushColor:")) {
                line = line.mid(12);
                blockData[blockTrack].brushColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("BrushStyle:")) {
                line = line.mid(12);
                blockData[blockTrack].brushStyle = line;
                line = file.readLine();
            }
        }

        else if (line.startsWith("ShapeType: Square")) {
            if (line.startsWith("ShapeDimensions:")) {
                line = line.mid(17);
                blockData[blockTrack].shapeDimensions[1] = line.toInt();
                line = file.readLine();
            }

            else if (line.startsWith("PenColor:")) {
                line = line.mid(10);
                blockData[blockTrack].penColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("PenWidth:")) {
                line = line.mid(10);
                blockData[blockTrack].penWidth = line.toInt();
            }

            else if (line.startsWith("PenStyle:")) {
                line = line.mid(10);
                blockData[blockTrack].penStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("PenCapStyle:")) {
                line = line.mid(13);
                blockData[blockTrack].penCapStyle = line;
                line = file.readLine();
            }

            //Won't read this for some reason
            else if (line.startsWith("PenJoinStyle:")) {
                line = line.mid(14);
                blockData[blockTrack].penJoinStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("BrushColor:")) {
                line = line.mid(12);
                blockData[blockTrack].brushColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("BrushStyle:")) {
                line = line.mid(12);
                blockData[blockTrack].brushStyle = line;
                line = file.readLine();
            }
            blockTrack++;
        }

        else if (line.startsWith("ShapeType: Ellipse")) {
            if (line.startsWith("ShapeDimensions:")) {
                line = line.mid(17);
                blockData[blockTrack].shapeDimensions[1] = line.toInt();
                line = file.readLine();
            }

            else if (line.startsWith("PenColor:")) {
                line = line.mid(10);
                blockData[blockTrack].penColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("PenWidth:")) {
                line = line.mid(10);
                blockData[blockTrack].penWidth = line.toInt();
            }

            else if (line.startsWith("PenStyle:")) {
                line = line.mid(10);
                blockData[blockTrack].penStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("PenCapStyle:")) {
                line = line.mid(13);
                blockData[blockTrack].penCapStyle = line;
                line = file.readLine();
            }

            //Won't read this for some reason
            else if (line.startsWith("PenJoinStyle:")) {
                line = line.mid(14);
                blockData[blockTrack].penJoinStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("BrushColor:")) {
                line = line.mid(12);
                blockData[blockTrack].brushColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("BrushStyle:")) {
                line = line.mid(12);
                blockData[blockTrack].brushStyle = line;
                line = file.readLine();
            }
            blockTrack++;
        }

        else if (line.startsWith("ShapeType: Circle")) {
            if (line.startsWith("ShapeDimensions:")) {
                line = line.mid(17);
                blockData[blockTrack].shapeDimensions[1] = line.toInt();
                line = file.readLine();
            }

            else if (line.startsWith("PenColor:")) {
                line = line.mid(10);
                blockData[blockTrack].penColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("PenWidth:")) {
                line = line.mid(10);
                blockData[blockTrack].penWidth = line.toInt();
            }

            else if (line.startsWith("PenStyle:")) {
                line = line.mid(10);
                blockData[blockTrack].penStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("PenCapStyle:")) {
                line = line.mid(13);
                blockData[blockTrack].penCapStyle = line;
                line = file.readLine();
            }

            //Won't read this for some reason
            else if (line.startsWith("PenJoinStyle:")) {
                line = line.mid(14);
                blockData[blockTrack].penJoinStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("BrushColor:")) {
                line = line.mid(12);
                blockData[blockTrack].brushColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("BrushStyle:")) {
                line = line.mid(12);
                blockData[blockTrack].brushStyle = line;
                line = file.readLine();
            }
            blockTrack++;
        }

        else if (line.startsWith("ShapeType: Text")) {
            if (line.startsWith("ShapeDimensions:")) {
                line = line.mid(17);
                blockData[blockTrack].shapeDimensions[1] = line.toInt();
                line = file.readLine();
            }
            else if (line.startsWith("TextString:")) {
                line = line.mid(12);
                blockData[blockTrack].textString = line;
                line = file.readLine();
            }

            else if (line.startsWith("TextColor:")) {
                line = line.mid(11);
                blockData[blockTrack].textColor = line;
                line = file.readLine();
            }

            else if (line.startsWith("TextPointSize:")) {
                line = line.mid(15);
                blockData[blockTrack].textPointSize = line.toInt();
                line = file.readLine();
            }

            else if (line.startsWith("TextFontFamily:")) {
                line = line.mid(16);
                blockData[blockTrack].textFontFamily = line;
                line = file.readLine();
            }

            else if (line.startsWith("TextFontStyle:")) {
                line = line.mid(15);
                blockData[blockTrack].textFontStyle = line;
                line = file.readLine();
            }

            else if (line.startsWith("TextFontWeight:")) {
                line = line.mid(16);
                blockData[blockTrack].textFontWeight = line;
                line = file.readLine();
            }
            blockTrack++;
        }
    }

    qInfo() << "Data successfully parsed!";

    qInfo() << "Validating that data was parsed correctly...";
    qInfo() << "Outputting data parsed from Block 0 to console...";
    qInfo() << blockData[0].shapeID;
    qInfo() << blockData[0].shapeType;
    qInfo() << blockData[0].penCapStyle;
    qInfo() << blockData[0].penJoinStyle;
    qInfo() << blockData[0].penWidth;
    qInfo() << "Check that this data matches Block 0's in shapes.txt";
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    sdParser("C:/Users/isaac_m2olzwl/OneDrive/Documents/sdPaintParser/shapes.txt");

    return a.exec();
}
