#ifndef CONTACT_H
#define CONTACT_H

#include <QDialog>

namespace Ui
{
class Contact;
}

class Contact : public QDialog
{
    Q_OBJECT

public:
    explicit Contact(QWidget *parent = nullptr);
    ~Contact();

private:
    Ui::Contact *ui;
};

#endif // CONTACT_H
