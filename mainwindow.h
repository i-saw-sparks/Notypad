#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_File_triggered();

    void on_actionSave_File_triggered();

    void on_actionOpen_File_triggered();

    void on_actionSaveAs_triggered();

private:
    Ui::MainWindow *ui;
    QString activeBuffer;

    bool save_file(QString &currentFile);
};
#endif // MAINWINDOW_H
