#ifndef SETTWINDOW_H
#define SETTWINDOW_H

#include <QWidget>
#include <QFont>
#include <QPlainTextEdit>
#include <QJsonDocument>
#include <QFile>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

namespace Ui {
class settWindow;
}

class settWindow : public QWidget
{
    Q_OBJECT

public:
    explicit settWindow();
    ~settWindow();
    bool loadPrefs();

signals:
    void font_changed(const QFont&, bool);
    void family_changed(const QString&);
    void font_size_changed(int);

private slots:
    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_spinBox_valueChanged(int arg1);

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::settWindow *ui;
    QString prefsDoc;
    bool apply_prefs_settings(QFile&);
    void closeEvent (QCloseEvent *event);

};

#endif // SETTWINDOW_H
