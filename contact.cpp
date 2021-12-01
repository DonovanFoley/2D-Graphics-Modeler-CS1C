#include "contact.h"
#include "ui_contact.h"
#include <QPixmap>

Contact::Contact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contact)
{
    ui->setupUi(this);
    QPixmap pix(":/img/img/scrumdogs.jpg");
    int w = 201;
    int h = 191;
    ui->ScrumDogsPic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

Contact::~Contact()
{
    delete ui;
}
