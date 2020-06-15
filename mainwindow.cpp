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
    setWindowTitle("Notypad");
}

void MainWindow::on_actionSave_File_triggered()
{
    if(activeBuffer.isEmpty()){
        activeBuffer = QFileDialog::getSaveFileName(this, "Save", tr("New File"),tr("*.txt"));
    }

    save_file(activeBuffer);
}

void MainWindow::on_actionSaveAs_triggered()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, "Save as", tr("New File"), tr("*.txt"));

    if(save_file(fileName)){
        activeBuffer = fileName;
    }
}

bool MainWindow::save_file(QString &currentFile){
    QFile file(currentFile);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return false;
    }

    setWindowTitle(currentFile);
    QTextStream out(&file);
    out<<ui ->plainTextEdit->toPlainText();
    file.close();
    return true;
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


