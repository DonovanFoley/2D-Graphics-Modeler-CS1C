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

void sdParser(QString filename) {

    struct Data {
        int shapeID;
        QString shapeType;
        int shapeDimensions[10];
        QString penColor;
        int penWidth;
        QString penStyle;
        QString penCapStyle;
        QString penJoinStyle;
    };

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
    int lineTrack = 0;
    int blockTrack = 0;
    while (!stream.atEnd()) {
        QString line = stream.readLine();

        if (line.startsWith("ShapeID:")) {
            line = line.mid(9);
            blockData[blockTrack].shapeID = line.toInt();
            line = file.readLine();
        }

        else if (line.startsWith("ShapeType:")) {
            line = line.mid(11);
            blockData[blockTrack].shapeType = line;
            line = file.readLine();
        }

        //Needs to read in up to 10 integers separated by commas into array
        //Use a loop?
        else if (line.startsWith("ShapeDimensions:")) {
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

        else if (line.startsWith("PenJoinStyle:")) {
            line = line.mid(14);
            blockData[blockTrack].penJoinStyle = line;
            line = file.readLine();
        }
        qInfo() << "Data for line " << lineTrack << "parsed...";

        lineTrack++;
        if (lineTrack == 8) {
            blockTrack++;
            lineTrack = 0;
        }
    }

    qInfo() << "Data successfully parsed!";

    qInfo() << "Validating that data was parsed correctly...";
    qInfo() << "Outputting data parsed from Block 1 to console...";
    qInfo() << blockData[1].shapeID;
    qInfo() << blockData[1].shapeType;
    qInfo() << blockData[1].penCapStyle;
    qInfo() << blockData[1].penJoinStyle;
    qInfo() << blockData[1].penWidth;
    qInfo() << "Check that this data matches Block 1's in shapes.txt";
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    sdParser("C:/Users/isaac_m2olzwl/OneDrive/Documents/sdPaintParser/shapes.txt");

    return a.exec();
}
