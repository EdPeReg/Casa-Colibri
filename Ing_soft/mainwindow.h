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
#include <QSet>
#include <QDate>
#include <QTableWidget>
#include <QCalendarWidget>
#include <QGroupBox>
#include <QTextEdit>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

enum Mes { enero = 1, febrero, marzo, abril, mayo, junio,
           julio, agosto, septiembre, octubre, noviembre, diciembre };

struct alumno{
    QString nombres;
    QString apellidos;
    QString inicio_asistencia;
    QString asistencia = " ";
    QString estado_animo;
    QString detalles_animo;
    QString foto;
    QString edad;
    QString domicilio;
    QString tutor;
    QString telefono;
    QString grado;
    QString sueno;
    QString detalles_sueno;
    bool cambioMes = false;

    alumno(){

    }
    alumno(QString nombres,QString apellidos,QString inicio_asistencia,QString edad, QString domicilio, QString tutor, QString telefono, QString grado){
        this->nombres=nombres;
        this->apellidos=apellidos;
        this->inicio_asistencia=inicio_asistencia;
        this->edad=edad;
        this->domicilio=domicilio;
        this->tutor=tutor;
        this->telefono=telefono;
        this->grado=grado;
    }
alumno(QString nombres,QString apellidos,QString inicio_asistencia,QString asistencia,QString estado_animo, QString detalles_animo, QString foto,QString edad, QString domicilio, QString tutor, QString telefono, QString grado, QString sueno, QString detalles_sueno){
            this->nombres=nombres;
            this->apellidos=apellidos;
            this->inicio_asistencia=inicio_asistencia;
            this->asistencia=asistencia;
            this->foto=foto;
            this->edad=edad;
            this->domicilio=domicilio;
            this->tutor=tutor;
            this->telefono=telefono;
            this->grado=grado;
            this->estado_animo=estado_animo;
            this->detalles_animo=detalles_animo;
            this->sueno=sueno;
            this->detalles_sueno=detalles_sueno;
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
    QTableWidget *table;

    void set_Palette();
    void set_Paginas();
    void set_LoginPage();
    void set_MainMenuPage();
    void set_ProfilesPage();
    void set_AttendancePage();
    void set_MoodPage();
    void set_DreamPage();
    void take_Attendance(QGridLayout *total, QWidget *Contenido, QVector<alumno>::iterator iterator);
    void show_Attendance(QGridLayout *total, QWidget *Contenido_wid, QVector<alumno>::iterator iterator);
    void set_BurgerMenu(QGridLayout *total);
    void set_BurgerMenu2(QGridLayout *total);
    void set_BurgerMenu3(QGridLayout *total);
    void set_BurgerMenu4(QGridLayout *total);

    void presionar_ingresar(QString username,QString password);
    void guardar_alumnos();
    void recuperar_alumnos();
private slots:
    void on_calendarWidget_clicked(const QDate &date);
};

#endif // MAINWINDOW_H
