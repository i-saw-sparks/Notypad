#include "settwindow.h"
#include "ui_settwindow.h"

settWindow::settWindow() :
    QWidget(0),
    ui(new Ui::settWindow)
{
    ui->setupUi(this);
}

settWindow::~settWindow()
{
    delete ui;
}

void settWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    emit font_changed(f);
}
