#ifndef OPCIONESWINDOW_H
#define OPCIONESWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class OpcionesWindow;
}

class OpcionesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OpcionesWindow(QWidget *parent = 0);
    ~OpcionesWindow();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::OpcionesWindow *ui;
};

#endif // OPCIONESWINDOW_H
