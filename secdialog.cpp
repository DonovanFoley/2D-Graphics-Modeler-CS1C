#include "secdialog.h"
#include "ui_secdialog.h"

secDialog::secDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);
}

secDialog::~secDialog()
{
    delete ui;
}

void secDialog::on_pushButton_clicked()         //line
{
    int xpos1 = ui->spinBox_line_firstX->text().toInt();
    int ypos1 = ui->spinBox_line_firstY->text().toInt();
    int xpos2 = ui->spinBox_line_secondX->text().toInt();
    int ypos2 = ui->spinBox_line_secondY->text().toInt();

    QPoint point1;
    QPoint point2;
    point1.setX(xpos1);
    point1.setY(ypos1);
    point2.setX(xpos2);
    point2.setY(ypos2);


    Shape *line = new Line(point1, point2);

    ui->widget->addShape(line);

    ui->widget->update();
}
