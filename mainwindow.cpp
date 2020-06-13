#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

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
    QString fileName;
    if(activeBuffer.isEmpty()){
        fileName = QFileDialog::getSaveFileName(this, "Save", tr("New File"),tr("*.txt"));

        activeBuffer = fileName;
    }else{
        fileName = activeBuffer;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui ->plainTextEdit->toPlainText();
    out<<text;
    file.close();
}
