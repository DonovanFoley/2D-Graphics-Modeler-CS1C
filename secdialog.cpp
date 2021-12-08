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

void secDialog::on_pushButton_clicked()
{
    int xpos1 = ui->spinBox_line_firstX->text().toInt();
    int ypos1 = ui->spinBox_line_firstY->text().toInt();
    int xpos2 = ui->spinBox_line_secondX->text().toInt();
    int ypos2 = ui->spinBox_line_secondY->text().toInt();

    Shape *rectangle = new Rectangle(xpos1, ypos1, xpos2, ypos2);

    ui->widget->addShape(rectangle);

    ui->widget->update();
}
