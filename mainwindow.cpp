#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,settWin(new settWindow)
{
    QObject::connect(settWin, SIGNAL(font_changed(const QFont&, bool)), this, SLOT(modify_font(const QFont&, bool)));
    QObject::connect(settWin, SIGNAL(family_changed(const QString&)), this, SLOT(modify_font(const QString&)));
    QObject::connect(settWin, SIGNAL(font_size_changed(int)), this, SLOT(modify_font(int)));

    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);

    if(!(settWin->loadPrefs())){
        QMessageBox::warning(this, "Error", "Cannot load preferences");
    }else{
        statusBar()->showMessage(tr("Preferences loaded"), 2000);
    }

    settWin->resize(300,300);
}

MainWindow::~MainWindow()
{
    delete settWin;
    delete ui;
}


void MainWindow::modify_font(const QFont &f, bool isMod){
    ui->plainTextEdit->setFont(f);
    if(isMod)
        statusBar()->showMessage(tr("Font modified"), 2000);
}

void MainWindow::modify_font(const QString &f){
    QFont fn(f);
    fn.setPointSize(ui->plainTextEdit->font().pointSize());
    ui->plainTextEdit->setFont(fn);
}

void MainWindow::modify_font(int size){
    QFont f = ui->plainTextEdit->font();
    f.setPointSize(size);
    ui->plainTextEdit->setFont(f);
}

void MainWindow::on_actionNew_File_triggered()
{
    activeBuffer.clear();
    ui->plainTextEdit->setPlainText(QString());
    setWindowTitle("Notypad");
    statusBar()->showMessage(tr("buffer cleared"), 2000);
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
    statusBar()->showMessage(tr("file saved"), 2000);
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
    statusBar()->showMessage(tr("file opened"), 2000);
}



void MainWindow::on_actionSettings_triggered()
{
    settWin->show();
}
