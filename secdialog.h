#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QMainWindow>

namespace Ui {
class secDialog;
}

class secDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit secDialog(QWidget *parent = nullptr);
    ~secDialog();

private:
    Ui::secDialog *ui;
};

#endif // SECDIALOG_H
