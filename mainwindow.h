#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QSharedData>
#include <settwindow.h>
#include <QLabel>




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

    void on_actionSettings_triggered();

public slots:
    void modify_font(const QFont&, bool);
    void modify_font(const QString&);
    void modify_font(int);


private:
    Ui::MainWindow *ui;
    QString activeBuffer;
    settWindow *settWin;


    bool save_file(QString &currentFile);
};
#endif // MAINWINDOW_H
