#ifndef SETTWINDOW_H
#define SETTWINDOW_H

#include <QWidget>
#include <QFont>
#include <QPlainTextEdit>

namespace Ui {
class settWindow;
}

class settWindow : public QWidget
{
    Q_OBJECT

public:
    explicit settWindow();
    ~settWindow();

signals:
    void font_changed(const QFont&);
    void font_size_changed(int);

private slots:
    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::settWindow *ui;
};

#endif // SETTWINDOW_H
