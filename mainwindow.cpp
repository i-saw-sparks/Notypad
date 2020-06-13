#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);

}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_File_triggered()
{
    activeBuffer.clear();
    ui->plainTextEdit->setPlainText(QString());
}

void MainWindow::on_actionSave_File_triggered()
{
    if(activeBuffer.isEmpty()){
        activeBuffer = QFileDialog::getSaveFileName(this, "Save", tr("New File"),tr("*.txt"));
    }

    QFile file(activeBuffer);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(activeBuffer);
    QTextStream out(&file);
    out<<ui ->plainTextEdit->toPlainText();
    file.close();
}

void MainWindow::on_actionOpen_File_triggered()
{
    activeBuffer.clear();
    activeBuffer = QFileDialog::getOpenFileName(this, "Open");
    QFile file(activeBuffer);

    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(activeBuffer);
    QTextStream in(&file);
    QString str = in.readAll();
    ui->plainTextEdit->setPlainText(str);
    file.close();
}
