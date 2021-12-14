#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QMainWindow>
#include "contact.h"

namespace Ui {
class secDialog;
}

class secDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit secDialog(QWidget *parent = nullptr);
    ~secDialog();

private slots:
    void on_pushButton_clicked();
    void on_actionContact_Info_triggered();

private:
    Ui::secDialog *ui;
    Contact *uiContact;
};

#endif // SECDIALOG_H
