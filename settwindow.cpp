#include "settwindow.h"
#include "ui_settwindow.h"

settWindow::settWindow() :
    QWidget(0),
    ui(new Ui::settWindow),
    prefsDoc("prefs.json")
{
    ui->setupUi(this);
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
    QJsonParseError JsonParseError;

    QJsonDocument doc;
    QJsonObject obj;

    if(fileCont.isEmpty()){
        obj.insert("font", "Consolas");
        obj.insert("pSize", 12);
        doc.setObject(obj);
        prefs.write(doc.toJson());
    }
    prefs.close();

    if(!prefs.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }

    doc = QJsonDocument::fromJson(prefs.readAll(), &JsonParseError);
    obj = doc.object();
    QFont f(obj.value("font").toString());
    f.setPointSize(obj.value("pSize").toInt());
    ui->fontComboBox->setCurrentFont(f);
    ui->spinBox->setValue(obj.value("pSize").toInt());
    prefs.close();
    emit font_changed(f);
    return true;
}

void settWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    emit family_changed(f.family());
}

void settWindow::on_spinBox_valueChanged(int arg1)
{
    emit font_size_changed(arg1);
}

void settWindow::on_pushButton_clicked()
{
    /*
    QFile prefs(prefsDoc);
    if(!prefs.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Error", "Cannot open prefs file: " + prefs.errorString());
    }

    QJsonParseError JsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(prefs.readAll(), &JsonParseError);

    QJsonObject prefsObj = doc.object();
    prefsObj.insert("font", "ajio");
    doc.setObject(prefsObj);
    prefs.write(doc.toJson());
    prefs.close();
    */
    //emit funcion para modificar fuente y tamaño
    this->hide();

}


