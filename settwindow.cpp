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
    QJsonDocument doc;
    QJsonObject obj;

    if(fileCont.isEmpty()){
        obj.insert("font", "Consolas");
        obj.insert("pSize", 12);
        doc.setObject(obj);
        prefs.write(doc.toJson());
    }
    prefs.close();

    return apply_prefs_settings(prefs);
}

bool settWindow::apply_prefs_settings(QFile &prefs){
    if(!prefs.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }

    QJsonParseError JsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(prefs.readAll(), &JsonParseError);
    QJsonObject obj = doc.object();
    QFont f(obj.value("font").toString());
    f.setPointSize(obj.value("pSize").toInt());
    ui->fontComboBox->setCurrentFont(f);
    ui->spinBox->setValue(obj.value("pSize").toInt());
    prefs.close();
    emit font_changed(f, false);
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

void settWindow::on_saveButton_clicked()
{
    QFile prefs(prefsDoc);
    if(!prefs.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
        QMessageBox::warning(this, "Error", "Cannot open prefs file: " + prefs.errorString());
    }

    QJsonDocument doc;
    QJsonObject prefsObj;
    prefsObj.insert("font", ui->fontComboBox->currentFont().family());
    prefsObj.insert("pSize",ui->spinBox->value());
    doc.setObject(prefsObj);
    prefs.write(doc.toJson());
    prefs.close();

    QFont f(ui->fontComboBox->currentFont().family(), ui->spinBox->value());
    emit font_changed(f, true);

    this->hide();
}

void settWindow::on_cancelButton_clicked()
{
    QFile f(prefsDoc);
    apply_prefs_settings(f);
    this->hide();
}

void settWindow::closeEvent (QCloseEvent *event){
    QFile f(prefsDoc);
    apply_prefs_settings(f);
    this->hide();
}
