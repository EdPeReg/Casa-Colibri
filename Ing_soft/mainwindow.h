#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QStackedWidget>
#include <QScrollArea>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QVector>
#include <QPainter>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

struct alumno{
    QString nombres;
    QString apellidos;

    alumno(){

    }
    alumno(QString nombres,QString apellidos){
        this->nombres=nombres;
        this->apellidos=apellidos;
    }
    bool operator <(alumno a){
        return this->nombres<a.nombres;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPalette Paleta_colores;
    QStackedWidget Paginas;
    QLineEdit LE_style;
    QVector<alumno> alumnos;

    void set_Palette();
    void set_Paginas();
    void set_LoginPage();
    void set_MainMenuPage();
    void set_ProfilesPage();
    void set_AttendancePage();
    void take_Attendance(QGridLayout *total, QWidget *Contenido, int iterator);
    void set_BurgerMenu(QGridLayout *total);

    void presionar_ingresar(QString username,QString password);
    void guardar_alumnos();
    void recuperar_alumnos();
};

#endif // MAINWINDOW_H
