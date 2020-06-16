#include "settwindow.h"
#include "ui_settwindow.h"

settWindow::settWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settWindow)
{
    ui->setupUi(this);
}

settWindow::~settWindow()
{
    delete ui;
}
