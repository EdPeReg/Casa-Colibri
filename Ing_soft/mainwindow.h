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
    bool cambioMes = false;

    alumno(){

    }
    alumno(QString nombres,QString apellidos,QString inicio_asistencia){
        this->nombres=nombres;
        this->apellidos=apellidos;
        this->inicio_asistencia=inicio_asistencia;
    }
    alumno(QString nombres,QString apellidos,QString inicio_asistencia,QString asistencia,QString estado_animo, QString detalles_animo){
        this->nombres=nombres;
        this->apellidos=apellidos;
        this->inicio_asistencia=inicio_asistencia;
        this->asistencia=asistencia;
        this->estado_animo=estado_animo;
        this->detalles_animo=detalles_animo;
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
    void take_Attendance(QGridLayout *total, QWidget *Contenido, QVector<alumno>::iterator iterator);
    void show_Attendance(QGridLayout *total, QWidget *Contenido_wid, QVector<alumno>::iterator iterator);
    void add_Mood(QVector<alumno>::iterator iterator, int);
    void conect_Mood(QGridLayout *total, QWidget *Contenido, QString, QVector<alumno>::iterator iterator);
    void set_BurgerMenu(QGridLayout *total);
    void set_BurgerMenu2(QGridLayout *total);
    void set_BurgerMenu3(QGridLayout *total);

    void presionar_ingresar(QString username,QString password);
    void guardar_alumnos();
    void recuperar_alumnos();
private slots:
    void on_calendarWidget_clicked(const QDate &date);
};

#endif // MAINWINDOW_H
