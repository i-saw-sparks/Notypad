#include "settwindow.h"
#include "ui_settwindow.h"

settWindow::settWindow() :
    QWidget(0),
    ui(new Ui::settWindow),
    prefsDoc("prefs.json")
{
    ui->setupUi(this);

    if(!loadPrefs()){
        QMessageBox::warning(this, "Error", "Cannot load preferences");
    }
}

settWindow::~settWindow()
{
    delete ui;
}

bool settWindow::loadPrefs(){
    QFile prefs(prefsDoc);
    if(!prefs.open(QIODevice::ReadWrite | QIODevice::Text)){
        return false;
    }
    QString fileCont = prefs.readAll();

    if(fileCont.isEmpty()){
        QTextStream out(&prefs);
        fileCont = "{\"Font\":\"console\", \"pSize\":12}";
        out << fileCont;
    }

    prefs.close();
    return true;
}

void settWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    emit font_changed(f);
}

void settWindow::on_pushButton_clicked()
{
    QFile prefs(prefsDoc);
    if(!prefs.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Error", "Cannot open prefs file: " + prefs.errorString());
    }
    prefs.close();
    this->hide();
}

void settWindow::on_spinBox_valueChanged(int arg1)
{
    emit font_size_changed(arg1);
}
