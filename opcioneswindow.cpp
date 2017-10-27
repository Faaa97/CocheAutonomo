#include "opcioneswindow.h"
#include "ui_opcioneswindow.h"

OpcionesWindow::OpcionesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpcionesWindow)
{
    ui->setupUi(this);
}

OpcionesWindow::~OpcionesWindow()
{
    delete ui;
}

void OpcionesWindow::on_buttonBox_accepted()
{

}

void OpcionesWindow::on_buttonBox_rejected()
{

}
