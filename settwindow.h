#ifndef SETTWINDOW_H
#define SETTWINDOW_H

#include <QWidget>

namespace Ui {
class settWindow;
}

class settWindow : public QWidget
{
    Q_OBJECT

public:
    explicit settWindow(QWidget *parent = nullptr);
    ~settWindow();

private:
    Ui::settWindow *ui;
};

#endif // SETTWINDOW_H
