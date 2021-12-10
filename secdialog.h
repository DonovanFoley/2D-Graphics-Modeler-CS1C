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

private slots:


    void on_pushButton_clicked();     //line

//  void on_pushButton_3_clicked(); //polyline

    void on_pushButton_move_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_deleteShape_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::secDialog *ui;
};

#endif // SECDIALOG_H
