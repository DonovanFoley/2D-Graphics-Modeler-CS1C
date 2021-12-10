#include "secdialog.h"
#include "ui_secdialog.h"
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QFont>


secDialog::secDialog(QWidget *parent) : QMainWindow(parent), ui(new Ui::secDialog)
{
    ui->setupUi(this);
}

secDialog::~secDialog()
{
    delete ui;
}



void secDialog::on_pushButton_clicked()         //line
{
    QColor color;
    Qt::PenStyle style = Qt::NoPen;
    Qt::PenCapStyle penCap =  Qt::FlatCap;
    Qt::PenJoinStyle penJoin = Qt::RoundJoin;


    int xpos1 = ui->spinBox_line_firstX->text().toInt();
    int ypos1 = ui->spinBox_line_firstY->text().toInt();
    int xpos2 = ui->spinBox_line_secondX->text().toInt();
    int ypos2 = ui->spinBox_line_secondY->text().toInt();

    int inPenColor = ui->comboBox_setPenColor_2->currentIndex();
    int inPenWidth = ui->spinBox_setPenWidth_2->text().toInt();
    int inPenStyle = ui->comboBox_setPenStyle_2->currentIndex();
    int inPenCapStyle = ui->comboBox_setPenCapStyle_3->currentIndex();
    int inPenJoinStyle = ui->comboBox_setPenJoinStyle_2->currentIndex();


    QPoint point1;
    QPoint point2;
    point1.setX(xpos1);
    point1.setY(ypos1);
    point2.setX(xpos2);
    point2.setY(ypos2);


    Shape *line = new Line(point1, point2);

    switch(inPenColor)
    {
        case 0 :
            color = Qt::blue;
            break;
        case 1 :
            color = Qt::red;
            break;
        case 2 :
            color = Qt::green;
            break;
        case 3 :
            color = Qt::yellow;
            break;
        case 4 :
            color = Qt::black;
            break;
        case 5 :
            color = Qt::white;
            break;
        case 6 :
            color = Qt::cyan;
            break;
        case 7 :
            color = Qt::magenta;
            break;
        case 8 :
            color = Qt::gray;
            break;
    }

    switch(inPenStyle)
    {
        case 0 :
            style = Qt::SolidLine;
            break;
        case 1 :
            style = Qt::DashLine;
            break;
        case 2 :
            style = Qt::DotLine;
            break;
        case 3 :
            style = Qt::DashDotLine;
            break;
        case 4 :
             style = Qt::DashDotDotLine;
            break;
        case 5 :
             style = Qt::NoPen;
    }

    switch(inPenCapStyle)
    {
        case 0 :
            penCap = Qt::SquareCap;
            break;
        case 1 :
            penCap = Qt::FlatCap;
            break;
        case 2 :
            penCap = Qt::RoundCap;
            break;
    }

    switch(inPenJoinStyle)
    {
        case 0 :
            penJoin = Qt::BevelJoin;
            break;
        case 1 :
            penJoin = Qt::MiterJoin;
            break;
        case 2 :
            penJoin = Qt::RoundJoin;
            break;
    }

    line->setPen(color, inPenWidth, style, penCap, penJoin);

    ui->widget->addShape(line);

    ui->widget->update();


}


void secDialog::on_pushButton_3_clicked()       //rect
{
    QColor penColor;
    QColor brushColor;
    Qt::PenStyle style = Qt::NoPen;
    Qt::PenCapStyle penCap =  Qt::FlatCap;
    Qt::PenJoinStyle penJoin = Qt::RoundJoin;
    Qt::BrushStyle brushStyle = Qt::SolidPattern;

    int x = ui->spinBox->text().toInt();
    int y = ui->spinBox_2->text().toInt();
    int l = ui->spinBox_3->text().toInt();
    int w = ui->spinBox_4->text().toInt();

    int inPenColor = ui->comboBox_setPenColor_3->currentIndex();
    int inBrushColor = ui->comboBox_setBrushColor_3->currentIndex();
    int inPenWidth = ui->spinBox_setPenWidth_3->text().toInt();
    int inBrushStyle = ui->comboBox_setBrushStyle_3->currentIndex();
    int inPenStyle = ui->comboBox_setPenStyle_3->currentIndex();
    int inPenCapStyle = ui->comboBox_setPenCapStyle_4->currentIndex();
    int inPenJoinStyle = ui->comboBox_setPenJoinStyle_3->currentIndex();

    switch(inPenColor)
    {
        case 0 :
            penColor = Qt::blue;
            break;
        case 1 :
            penColor = Qt::red;
            break;
        case 2 :
            penColor = Qt::green;
            break;
        case 3 :
            penColor = Qt::yellow;
            break;
        case 4 :
            penColor = Qt::black;
            break;
        case 5 :
            penColor = Qt::white;
            break;
        case 6 :
            penColor = Qt::cyan;
            break;
        case 7 :
            penColor = Qt::magenta;
            break;
        case 8 :
            penColor = Qt::gray;
            break;
    }

    switch(inBrushColor)
    {
    case 0 :
        brushColor = Qt::blue;
        break;
    case 1 :
        brushColor = Qt::red;
        break;
    case 2 :
        brushColor = Qt::green;
        break;
    case 3 :
        brushColor = Qt::yellow;
        break;
    case 4 :
        brushColor = Qt::black;
        break;
    case 5 :
        brushColor = Qt::white;
        break;
    case 6 :
        brushColor = Qt::cyan;
        break;
    case 7 :
        brushColor = Qt::magenta;
        break;
    case 8 :
        brushColor = Qt::gray;
        break;
    }

    switch(inPenStyle)
    {
        case 0 :
            style = Qt::SolidLine;
            break;
        case 1 :
            style = Qt::DashLine;
            break;
        case 2 :
            style = Qt::DotLine;
            break;
        case 3 :
            style = Qt::DashDotLine;
            break;
        case 4 :
             style = Qt::DashDotDotLine;
            break;
        case 5 :
             style = Qt::NoPen;
    }

    switch(inPenCapStyle)
    {
        case 0 :
            penCap = Qt::SquareCap;
            break;
        case 1 :
            penCap = Qt::FlatCap;
            break;
        case 2 :
            penCap = Qt::RoundCap;
            break;
    }

    switch(inPenJoinStyle)
    {
        case 0 :
            penJoin = Qt::BevelJoin;
            break;
        case 1 :
            penJoin = Qt::MiterJoin;
            break;
        case 2 :
            penJoin = Qt::RoundJoin;
            break;
    }

    switch(inBrushStyle)
    {
        case 0:
            brushStyle = Qt::NoBrush;
        case 1:
            brushStyle = Qt::SolidPattern;
        case 2:
            brushStyle = Qt::HorPattern;
        case 3:
            brushStyle = Qt::VerPattern;

    }

    Rectangle *rectangle = new Rectangle();

    rectangle->setRectStart(x, y);
    rectangle->setHeight(l);
    rectangle->setWidth(w);
    rectangle->setPen(penColor, inPenWidth, style, penCap, penJoin);
    rectangle->setBrush(brushColor, brushStyle);

    ui->widget->addShape(rectangle);

    ui->widget->update();
}


void secDialog::on_pushButton_4_clicked()      //ellipse
{
    QColor penColor;
    QColor brushColor;
    Qt::PenStyle style = Qt::NoPen;
    Qt::PenCapStyle penCap =  Qt::FlatCap;
    Qt::PenJoinStyle penJoin = Qt::RoundJoin;
    Qt::BrushStyle brushStyle = Qt::SolidPattern;

    int x = ui->spinBox_ellipse_firstX->text().toInt();
    int y = ui->spinBox_ellipse_firstY->text().toInt();
    int w = ui->spinBox_ellipse_axisX_2->text().toInt();
    int l = ui->spinBox_ellipse_axisY_2->text().toInt();

    int inPenColor = ui->comboBox_setPenColor_4->currentIndex();
    int inBrushColor = ui->comboBox_setBrushColor_4->currentIndex();
    int inPenWidth = ui->spinBox_setPenWidth_4->text().toInt();
    int inBrushStyle = ui->comboBox_setBrushStyle_4->currentIndex();
    int inPenStyle = ui->comboBox_setPenStyle_4->currentIndex();
    int inPenCapStyle = ui->comboBox_setPenCapStyle_4->currentIndex();
    int inPenJoinStyle = ui->comboBox_setPenJoinStyle_4->currentIndex();

    switch(inPenColor)
    {
        case 0 :
            penColor = Qt::blue;
            break;
        case 1 :
            penColor = Qt::red;
            break;
        case 2 :
            penColor = Qt::green;
            break;
        case 3 :
            penColor = Qt::yellow;
            break;
        case 4 :
            penColor = Qt::black;
            break;
        case 5 :
            penColor = Qt::white;
            break;
        case 6 :
            penColor = Qt::cyan;
            break;
        case 7 :
            penColor = Qt::magenta;
            break;
        case 8 :
            penColor = Qt::gray;
            break;
    }

    switch(inBrushColor)
    {
    case 0 :
        brushColor = Qt::blue;
        break;
    case 1 :
        brushColor = Qt::red;
        break;
    case 2 :
        brushColor = Qt::green;
        break;
    case 3 :
        brushColor = Qt::yellow;
        break;
    case 4 :
        brushColor = Qt::black;
        break;
    case 5 :
        brushColor = Qt::white;
        break;
    case 6 :
        brushColor = Qt::cyan;
        break;
    case 7 :
        brushColor = Qt::magenta;
        break;
    case 8 :
        brushColor = Qt::gray;
        break;
    }

    switch(inPenStyle)
    {
        case 0 :
            style = Qt::SolidLine;
            break;
        case 1 :
            style = Qt::DashLine;
            break;
        case 2 :
            style = Qt::DotLine;
            break;
        case 3 :
            style = Qt::DashDotLine;
            break;
        case 4 :
             style = Qt::DashDotDotLine;
            break;
        case 5 :
             style = Qt::NoPen;
    }

    switch(inPenCapStyle)
    {
        case 0 :
            penCap = Qt::SquareCap;
            break;
        case 1 :
            penCap = Qt::FlatCap;
            break;
        case 2 :
            penCap = Qt::RoundCap;
            break;
    }

    switch(inPenJoinStyle)
    {
        case 0 :
            penJoin = Qt::BevelJoin;
            break;
        case 1 :
            penJoin = Qt::MiterJoin;
            break;
        case 2 :
            penJoin = Qt::RoundJoin;
            break;
    }

    switch(inBrushStyle)
    {
        case 0:
            brushStyle = Qt::NoBrush;
        case 1:
            brushStyle = Qt::SolidPattern;
        case 2:
            brushStyle = Qt::HorPattern;
        case 3:
            brushStyle = Qt::VerPattern;

    }


    Ellipse *ellipse = new Ellipse(x, y, w ,l);

    ellipse->setPen(penColor, inPenWidth, style, penCap, penJoin);
    ellipse->setBrush(brushColor, brushStyle);

    ui->widget->addShape(ellipse);
    ui->widget->update();

}


void secDialog::on_pushButton_5_clicked()           //text
{
       int xpos1 = ui->spinBox_text_X->text().toInt();
       int ypos1 = ui->spinBox_text_Y->text().toInt();
       int xpos2 = ui->spinBox_text_box_width->text().toInt();
       int ypos2 = ui->spinBox_text_box_hight->text().toInt();

       QString TextString = ui->textEdit->toPlainText();
       int TextColor = ui->comboBox_textColor->currentIndex();
       int TextAlignment = ui->comboBox_text_alignment->currentIndex();
       int TextFontStyle = ui->comboBox_textFontStyles->currentIndex();
       int TextFontFamily = ui->comboBox_textFontFamily->currentIndex();
       int TextFontWeight = ui->comboBox_fontWeight->currentIndex();
       int TextPointSize = ui->spinBox_text_point_size->text().toInt();

       Text *text = new Text(xpos1, ypos1, xpos2, ypos2, TextString, TextColor, TextAlignment, TextFontStyle, TextFontFamily, TextFontWeight, TextPointSize);

       ui->widget->addShape(text);
       ui->widget->update();
}


void secDialog::on_pushButton_deleteShape_clicked()
{
    int shapeId = ui->spinBox_delete_id->text().toInt();

    ui->widget->cutShape(shapeId);
    ui->widget->update();
}

void secDialog::on_pushButton_move_clicked()            //move
{
    int x = ui->spinBox_moveX->text().toInt();
    int y = ui->spinBox_moveY->text().toInt();
    int coord = ui->spinBox_moveCoordinate->text().toInt();
    int id = ui->spinBox_move_id->text().toInt();

    ui->widget->moveShape(id, coord, x, y);
    ui->widget->update();


}

void secDialog::on_pushButton_2_clicked()       //polyline
{
    QColor color;
    Qt::PenStyle style = Qt::NoPen;
    Qt::PenCapStyle penCap =  Qt::FlatCap;
    Qt::PenJoinStyle penJoin = Qt::RoundJoin;

    QPoint point;
    int x;
    int y;

    int numPts = ui->spinBox_polyline_pointsAdded->text().toInt();
    QPoint *qPointPtr = new QPoint[numPts];

    int inPenColor = ui->comboBox_setPenColor_5->currentIndex();
    int inPenWidth = ui->spinBox_setPenWidth_5->text().toInt();
    int inPenStyle = ui->comboBox_setPenStyle_5->currentIndex();
    int inPenCapStyle = ui->comboBox_setPenCapStyle_6->currentIndex();
    int inPenJoinStyle = ui->comboBox_setPenJoinStyle_5->currentIndex();

    for(int i = 0; i < numPts; i++)
    {
        if (i == 0)
        {
            x = ui->spinBox_polyline_firstX->text().toInt();
            y = ui->spinBox_polyline_firstY->text().toInt();
            point.setX(x);
            point.setY(y);
            qPointPtr[i] = point;
        }
        if (i == 1)
        {
            x = ui->spinBox_polyline_secondX->text().toInt();
            y = ui->spinBox_polyline_secondY->text().toInt();
            point.setX(x);
            point.setY(y);
            qPointPtr[i] = point;
        }
        if (i == 2)
        {
            x = ui->spinBox_polyline_thirdX->text().toInt();
            y = ui->spinBox_polyline_thirdY->text().toInt();
            point.setX(x);
            point.setY(y);
            qPointPtr[i] = point;
        }
        if (i == 3)
        {
            x = ui->spinBox_polyline_fourthX->text().toInt();
            y = ui->spinBox_polyline_fourthY->text().toInt();
            point.setX(x);
            point.setY(y);
            qPointPtr[i] = point;
        }
        if (i == 4)
        {
            x = ui->spinBox_polyline_fifthX->text().toInt();
            y = ui->spinBox_polyline_fifthY->text().toInt();
            point.setX(x);
            point.setY(y);
            qPointPtr[i] = point;
        }
        if (i == 5)
        {
            x = ui->spinBox_polyline_sixthX->text().toInt();
            y = ui->spinBox_polyline_sixthY->text().toInt();
            point.setX(x);
            point.setY(y);
            qPointPtr[i] = point;
        }
        if (i == 6)
        {
            x = ui->spinBox_5->text().toInt();
            y = ui->spinBox_6->text().toInt();
            point.setX(x);
            point.setY(y);
            qPointPtr[i] = point;
        }
        if (i == 7)
        {
            x = ui->spinBox_7->text().toInt();
            y = ui->spinBox_8->text().toInt();
            point.setX(x);
            point.setY(y);
            qPointPtr[i] = point;
        }
    }


    Shape *polyline = new Polyline(qPointPtr, numPts);

    switch(inPenColor)
    {
        case 0 :
            color = Qt::blue;
            break;
        case 1 :
            color = Qt::red;
            break;
        case 2 :
            color = Qt::green;
            break;
        case 3 :
            color = Qt::yellow;
            break;
        case 4 :
            color = Qt::black;
            break;
        case 5 :
            color = Qt::white;
            break;
        case 6 :
            color = Qt::cyan;
            break;
        case 7 :
            color = Qt::magenta;
            break;
        case 8 :
            color = Qt::gray;
            break;
    }

    switch(inPenStyle)
    {
        case 0 :
            style = Qt::SolidLine;
            break;
        case 1 :
            style = Qt::DashLine;
            break;
        case 2 :
            style = Qt::DotLine;
            break;
        case 3 :
            style = Qt::DashDotLine;
            break;
        case 4 :
             style = Qt::DashDotDotLine;
            break;
        case 5 :
             style = Qt::NoPen;
    }

    switch(inPenCapStyle)
    {
        case 0 :
            penCap = Qt::SquareCap;
            break;
        case 1 :
            penCap = Qt::FlatCap;
            break;
        case 2 :
            penCap = Qt::RoundCap;
            break;
    }

    switch(inPenJoinStyle)
    {
        case 0 :
            penJoin = Qt::BevelJoin;
            break;
        case 1 :
            penJoin = Qt::MiterJoin;
            break;
        case 2 :
            penJoin = Qt::RoundJoin;
            break;
    }

    polyline->setPen(color, inPenWidth, style, penCap, penJoin);

    ui->widget->addShape(polyline);
    ui->widget->update();
}


void secDialog::on_pushButton_6_clicked()   //polygon
{
        QPoint point;
        int x;
        int y;

        QColor brushColor;
        QColor color;
        Qt::PenStyle style = Qt::NoPen;
        Qt::PenCapStyle penCap =  Qt::FlatCap;
        Qt::PenJoinStyle penJoin = Qt::RoundJoin;
        Qt::BrushStyle brushStyle = Qt::SolidPattern;

        int numPts = ui->spinBox_polygon_pointsAdded->text().toInt();
        QPoint *qPointPtr = new QPoint[numPts];

        int inPenColor = ui->comboBox_setPenColor_6->currentIndex();
        int inPenWidth = ui->spinBox_setPenWidth_6->text().toInt();
        int inPenStyle = ui->comboBox_setPenStyle_6->currentIndex();
        int inPenCapStyle = ui->comboBox_setPenCapStyle_7->currentIndex();
        int inPenJoinStyle = ui->comboBox_setPenJoinStyle_7->currentIndex();
        int inBrushColor = ui->comboBox_setBrushColor_5->currentIndex();
        int inBrushStyle = ui->comboBox_setBrushStyle_5->currentIndex();

        for(int i = 0; i < numPts; i++)
        {
            if (i == 0)
            {
                x = ui->spinBox_polygon_firstX->text().toInt();
                y = ui->spinBox_polygon_firstY->text().toInt();
                point.setX(x);
                point.setY(y);
                qPointPtr[i] = point;
            }
            if (i == 1)
            {
                x = ui->spinBox_polygon_secondX->text().toInt();
                y = ui->spinBox_polygon_secondY->text().toInt();
                point.setX(x);
                point.setY(y);
                qPointPtr[i] = point;
            }
            if (i == 2)
            {
                x = ui->spinBox_polygon_thirdX->text().toInt();
                y = ui->spinBox_polygon_thirdY->text().toInt();
                point.setX(x);
                point.setY(y);
                qPointPtr[i] = point;
            }
            if (i == 3)
            {
                if (i == (numPts - 1))
                {
                    x = ui->spinBox_polygon_firstX->text().toInt();
                    y = ui->spinBox_polygon_firstY->text().toInt();
                }
                else
                {
                    x = ui->spinBox_polygon_fourthX->text().toInt();
                    y = ui->spinBox_polygon_fourthY->text().toInt();
                }
                point.setX(x);
                point.setY(y);
                qPointPtr[i] = point;
            }
            if (i == 4)
            {
                if (i == (numPts - 1))
                {
                    x = ui->spinBox_polygon_firstX->text().toInt();
                    y = ui->spinBox_polygon_firstY->text().toInt();
                }
                else
                {
                    x = ui->spinBox_polygon_fifthX->text().toInt();
                    y = ui->spinBox_polygon_fifthY->text().toInt();
                }
                point.setX(x);
                point.setY(y);
                qPointPtr[i] = point;
            }
            if (i == 5)
            {
                if (i == (numPts - 1))
                {
                    x = ui->spinBox_polygon_firstX->text().toInt();
                    y = ui->spinBox_polygon_firstY->text().toInt();
                }
                else
                {
                    x = ui->spinBox_polygon_sixthX->text().toInt();
                    y = ui->spinBox_polygon_sixthY->text().toInt();
                }
                point.setX(x);
                point.setY(y);
                qPointPtr[i] = point;
            }
            if (i == 6)
            {
                if (i == (numPts - 1))
                {
                    x = ui->spinBox_polygon_firstX->text().toInt();
                    y = ui->spinBox_polygon_firstY->text().toInt();
                }
                else
                {
                    x = ui->spinBox_polygon_seventhX->text().toInt();
                    y = ui->spinBox_polygon_seventhY->text().toInt();
                }
                point.setX(x);
                point.setY(y);
                qPointPtr[i] = point;
            }
            if (i == 7)
            {
                if (i == (numPts - 1))
                {
                    x = ui->spinBox_polygon_firstX->text().toInt();
                    y = ui->spinBox_polygon_firstY->text().toInt();
                }
                else
                {
                    x = ui->spinBox_polygon_eighthX->text().toInt();
                    y = ui->spinBox_polygon_eighthY->text().toInt();
                }
                point.setX(x);
                point.setY(y);
                qPointPtr[i] = point;
            }
        }

        Shape *polygon = new Polygon(qPointPtr, numPts);

        switch(inPenColor)
        {
            case 0 :
                color = Qt::blue;
                break;
            case 1 :
                color = Qt::red;
                break;
            case 2 :
                color = Qt::green;
                break;
            case 3 :
                color = Qt::yellow;
                break;
            case 4 :
                color = Qt::black;
                break;
            case 5 :
                color = Qt::white;
                break;
            case 6 :
                color = Qt::cyan;
                break;
            case 7 :
                color = Qt::magenta;
                break;
            case 8 :
                color = Qt::gray;
                break;
        }

        switch(inPenStyle)
        {
            case 0 :
                style = Qt::SolidLine;
                break;
            case 1 :
                style = Qt::DashLine;
                break;
            case 2 :
                style = Qt::DotLine;
                break;
            case 3 :
                style = Qt::DashDotLine;
                break;
            case 4 :
                 style = Qt::DashDotDotLine;
                break;
            case 5 :
                 style = Qt::NoPen;
        }

        switch(inPenCapStyle)
        {
            case 0 :
                penCap = Qt::SquareCap;
                break;
            case 1 :
                penCap = Qt::FlatCap;
                break;
            case 2 :
                penCap = Qt::RoundCap;
                break;
        }

        switch(inPenJoinStyle)
        {
            case 0 :
                penJoin = Qt::BevelJoin;
                break;
            case 1 :
                penJoin = Qt::MiterJoin;
                break;
            case 2 :
                penJoin = Qt::RoundJoin;
                break;
        }

        switch(inBrushStyle)
        {
            case 0:
                brushStyle = Qt::NoBrush;
            case 1:
                brushStyle = Qt::SolidPattern;
            case 2:
                brushStyle = Qt::HorPattern;
            case 3:
                brushStyle = Qt::VerPattern;

        }

        switch(inBrushColor)
        {
        case 0 :
            brushColor = Qt::blue;
            break;
        case 1 :
            brushColor = Qt::red;
            break;
        case 2 :
            brushColor = Qt::green;
            break;
        case 3 :
            brushColor = Qt::yellow;
            break;
        case 4 :
            brushColor = Qt::black;
            break;
        case 5 :
            brushColor = Qt::white;
            break;
        case 6 :
            brushColor = Qt::cyan;
            break;
        case 7 :
            brushColor = Qt::magenta;
            break;
        case 8 :
            brushColor = Qt::gray;
            break;
        }

        polygon->setPen(color, inPenWidth, style, penCap, penJoin);
        polygon->setBrush(brushColor, brushStyle);

        ui->widget->addShape(polygon);
        ui->widget->update();
}

