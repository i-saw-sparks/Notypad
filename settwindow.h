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

private slots:
    void on_fontComboBox_currentFontChanged(const QFont &f);

private:
    Ui::settWindow *ui;
};

#endif // SETTWINDOW_H
