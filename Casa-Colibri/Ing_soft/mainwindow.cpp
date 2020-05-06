#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#define ancho_res QApplication::desktop()->width()
#define alto_res QApplication::desktop()->height()

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    set_Palette();
    recuperar_alumnos();
    set_Paginas();

    Paginas.setCurrentIndex(0);


    this->setCentralWidget(&Paginas);
    this->showMaximized();


}

MainWindow::~MainWindow()
{
    guardar_alumnos();
    delete ui;
}

void MainWindow::set_Palette()
{
    Paleta_colores.setColor(QPalette::Normal,QPalette::Window,QColor(254, 247, 195));//Fondo (Crema)
    //Paleta_colores.setColor(QPalette::Normal,QPalette::PlaceholderText,QColor(94, 68, 92));
    Paleta_colores.setColor(QPalette::Normal,QPalette::Text,QColor(94, 68, 92));//Texto que escribe el usuario (Morado)
    Paleta_colores.setColor(QPalette::Normal,QPalette::ButtonText,QColor(254, 247, 195));
    Paleta_colores.setColor(QPalette::Normal,QPalette::Base,QColor(254, 247, 195));//Fondo line edit
    Paleta_colores.setColor(QPalette::Normal,QPalette::WindowText,QColor(94, 68, 92));//Texto labels
    Paleta_colores.setColor(QPalette::Normal,QPalette::Button,QColor("94, 68, 92"));

    this->setStyleSheet("QLineEdit { background-color: rgb(254, 247, 195);"
                        "border-style: outset;"
                        "border-width: 1px;"
                        "border-color: rgb(94, 68, 92);"
                        "border-radius: "+QString().number((alto_res/35)/2)+"px;"
                        "padding-left: 3px;"
                        "width: "+QString().number(ancho_res/5)+"px;"
                        "height: "+QString().number(alto_res/35)+"px;"
                        "text-align: center;"
                        "color: rgb(94, 68, 92);"
                        "font-family:  \"Century Gothic\"; }"
                        ""
                        "QPushButton { background-color: rgb(239, 80, 89);"
                        "border-style: flat;"
                        "color: rgb(254, 247, 195);"
                        "width: "+QString().number(ancho_res/10)+"px;"
                        "height: "+QString().number(alto_res/35)+"px;"
                        "border-radius: "+QString().number((alto_res/35)/2)+"px;"
                        "font-family:  \"Century Gothic\";}"
                        ""
                        "QPushButton::pressed { background-color: rgb(191, 60, 68);}"
                        ""
                        "QScrollArea {background-color: rgb(254, 247, 195);"
                        "border-style: flat;}"
                        ""
                        "QScrollBar{border: 3px grey;"
                        "background: rgb(254, 247, 195);"
                        "border-radius: 5px;"
                        "width: 10px;}"
                        ""
                        "QScrollBar::handle{background: rgb(94, 68, 92);"
                        "border-radius: 5px;}");


}

void MainWindow::set_Paginas()
{
    Paginas.setPalette(Paleta_colores);
    Paginas.setAutoFillBackground(true);

    //set_LoginPage();
    //set_MainMenuPage();
    //set_ProfilesPage();
    set_AttendancePage();

}

void MainWindow::set_LoginPage()
{
    QWidget *login=new QWidget;

    QGridLayout *center =new QGridLayout;
    QGridLayout *total =new QGridLayout;

    QLabel *titulo=new QLabel;
    titulo->setText("CASA COLIBRI");
    titulo->setStyleSheet("font: bold "+QString().number(alto_res/10)+"px \"Century Gothic\"; color: rgb(94, 68, 92);");
    center->addWidget(titulo,0,0,Qt::AlignHCenter);

    QLabel *imagen=new QLabel;
    imagen->setStyleSheet("min-width:"+QString().number(alto_res/3)+"px;"
                          "min-height:"+QString().number(alto_res/3)+"px;"
                          "image: url(imgs/logo.png);");
    center->addWidget(imagen,1,0,Qt::AlignHCenter);


    QLineEdit *username=new QLineEdit;
    username->setPlaceholderText("Username");
    username->setAlignment(Qt::AlignCenter);
    center->addWidget(username,2,0,Qt::AlignHCenter);

    QLineEdit *password=new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    password->setPlaceholderText("Contraseña");
    password->setAlignment(Qt::AlignCenter);
    center->addWidget(password,3,0,Qt::AlignHCenter);

    QPushButton *ingresar=new QPushButton;
    ingresar->setText("Ingresar");
    center->addWidget(ingresar,4,0,Qt::AlignHCenter);
    connect(ingresar, &QPushButton::clicked, [=]() { MainWindow::presionar_ingresar(username->text(),password->text()); } );

    total->addLayout(center,0,0,Qt::AlignCenter);
    login->setLayout(total);
    Paginas.addWidget(login);
}

void MainWindow::set_MainMenuPage()
{
    QWidget *MainMenu=new QWidget;
    QGridLayout *total =new QGridLayout;

    MainMenu->setStyleSheet("QPushButton { background-color: rgb(239, 80, 89);"
                        "border-style: flat;"
                        "color: rgb(254, 247, 195);"
                        "width: "+QString().number(alto_res/3)+"px; max-width:"+QString().number(alto_res/3)+"px;"
                        "height: "+QString().number(alto_res/3)+"px; max-height:"+QString().number(alto_res/3)+"px;"
                        "border-radius: "+QString().number((alto_res/3)/2)+"px;"
                        "font: bold "+QString().number(alto_res/18)+"px \"Century Gothic\";}"
                        "QPushButton::pressed { background-color: rgb(191, 60, 68);}");

    QPushButton *perfiles=new QPushButton;
    perfiles->setText("Perfiles");
    total->addWidget(perfiles,0,0);
    connect(perfiles, &QPushButton::clicked, [=]() { Paginas.setCurrentIndex(2); } );

    QPushButton *mood=new QPushButton;
    mood->setText("Estados\nde\nAnimo");
    total->addWidget(mood,0,1);

    QPushButton *asistencia=new QPushButton;
    asistencia->setText("Asistencia");
    total->addWidget(asistencia,0,2);
    connect(asistencia, &QPushButton::clicked, [=]() { Paginas.setCurrentIndex(3); } );

    QPushButton *dreams=new QPushButton;
    dreams->setText("Sueños");
    total->addWidget(dreams,1,0);

    QPushButton *actividades=new QPushButton;
    actividades->setText("Actividades");
    total->addWidget(actividades,1,1);

    QPushButton *extra=new QPushButton;
    extra->setText("Extra");
    total->addWidget(extra,1,2);


    MainMenu->setLayout(total);
    Paginas.addWidget(MainMenu);
}

void MainWindow::set_ProfilesPage()
{
    QWidget *MainMenu=new QWidget;
    QGridLayout *total =new QGridLayout;
    QGridLayout *busca =new QGridLayout;
    QGridLayout *perfiles =new QGridLayout;
    QGridLayout *info =new QGridLayout;

    //HEADER

    QPushButton *burger_icon=new QPushButton;
    QPixmap pixmap("imgs/burger_menu.png");
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(),QColor(254, 247, 195));
    painter.end();

    burger_icon->setFixedSize(alto_res/21,alto_res/21);
    burger_icon->setStyleSheet("border-radius: "+QString().number((alto_res/21)/2)+"px;");
    burger_icon->setIcon(pixmap);
    burger_icon->setIconSize(QSize(alto_res/25,alto_res/25));
    busca->addWidget(burger_icon,0,0);
    connect(burger_icon, &QPushButton::clicked, [=]() {MainWindow::set_BurgerMenu(total);} );

    QLabel *text_busca=new QLabel;
    text_busca->setText("Busca");
    text_busca->setPalette(Paleta_colores);
    text_busca->setFont(QFont("Century Gothic",14,100));
    busca->addWidget(text_busca,0,1);

    QLineEdit *le_busca=new QLineEdit;
    busca->addWidget(le_busca,0,2);

    QPushButton *pb_agregar=new QPushButton;
    pixmap.load("imgs/add_icon.png");
    QPainter painter2(&pixmap);
    painter2.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter2.fillRect(pixmap.rect(),QColor(254, 247, 195));
    painter2.end();
    pb_agregar->setFixedSize(alto_res/21,alto_res/21);
    pb_agregar->setIconSize(QSize(alto_res/32,alto_res/32));
    pb_agregar->setStyleSheet("border-radius: "+QString().number((alto_res/21)/2)+"px;");
    pb_agregar->setIcon(pixmap);
    busca->addWidget(pb_agregar,0,3);

    //ALUMNOS_SCROLL_AREA

    for (int i=0;i<alumnos.size();i++) {
        QPushButton *alumno=new QPushButton;
        pixmap.load("imgs/perfil_icon.png");
        alumno->setStyleSheet("QPushButton { background-color: transparent;"
                              "color: rgb(94, 68, 92);"
                              "height: "+QString().number(alto_res/15)+"px;}"
                              "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                              "color: rgb(254, 247, 195);}");
        alumno->setFont(QFont("Century Gothic",15,100));
        alumno->setIconSize(QSize(alto_res/20,alto_res/20));
        alumno->setIcon(pixmap);
        alumno->setText(alumnos.at(i).nombres+" "+alumnos.at(i).apellidos);
        perfiles->addWidget(alumno,i,0);
        connect(alumno, &QPushButton::clicked, [=]() {} );
    }


    //INFO_SCROLL_AREA

    QPushButton *foto_alumno=new QPushButton;
    pixmap.load("imgs/perfil_icon.png");
    foto_alumno->setStyleSheet("QPushButton { background-color: transparent;"
                               "color: rgb(94, 68, 92);"
                               "border-radius: 45px;}"
                               "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                               "color: rgb(254, 247, 195);}");
    foto_alumno->setIcon(pixmap);
    foto_alumno->setIconSize(QSize(80,80));
    foto_alumno->setFixedSize(90,90);
    info->addWidget(foto_alumno,0,0,Qt::AlignHCenter);
    connect(foto_alumno, &QPushButton::clicked, [=]() {} );

    QLineEdit *nombre_LE=new QLineEdit;
    nombre_LE->setPlaceholderText("Nombres");
    nombre_LE->setAlignment(Qt::AlignCenter);
    info->addWidget(nombre_LE,1,0,Qt::AlignHCenter);

    QLineEdit *apellidos_LE=new QLineEdit;
    apellidos_LE->setPlaceholderText("Apellidos");
    apellidos_LE->setAlignment(Qt::AlignCenter);
    info->addWidget(apellidos_LE,2,0,Qt::AlignHCenter);

    QPushButton *agrega_alumno=new QPushButton;
    agrega_alumno->setText("Agregar");
    info->addWidget(agrega_alumno,3,0,Qt::AlignHCenter);
    connect(agrega_alumno, &QPushButton::clicked, [=]() {
        if(nombre_LE->text().size()>0&&apellidos_LE->text().size()>0){
            alumnos.append(alumno(nombre_LE->text(),apellidos_LE->text(),QDate().currentDate().toString()));
            MainWindow::guardar_alumnos();
            nombre_LE->clear();apellidos_LE->clear();
        }});

    //UNION DE TODOS LOS LAYOUT

    QScrollArea *sa_perfiles =new QScrollArea;
    QWidget *wid_perfiles=new QWidget;
    wid_perfiles->setLayout(perfiles);
    wid_perfiles->setStyleSheet("background-color: rgb(254, 247, 195);");
    sa_perfiles->setWidget(wid_perfiles);
    sa_perfiles->setFixedWidth(ancho_res/3);

    QWidget *wid_info=new QWidget;
    wid_info->setLayout(info);
    QWidget *wid_busca=new QWidget;
    wid_busca->setLayout(busca);

    total->addWidget(wid_busca,0,0,1,0);
    total->addWidget(sa_perfiles,1,0);
    total->addWidget(wid_info,1,1);
    MainMenu->setLayout(total);
    Paginas.addWidget(MainMenu);
}

void MainWindow::set_AttendancePage()
{
    QWidget *Total_widget=new QWidget;
    QWidget *Perfiles_widget=new QWidget;
    QWidget *Contenido_widget=new QWidget;

    QGridLayout *Total_layout =new QGridLayout;
    QGridLayout *Perfiles_layout =new QGridLayout;
    QGridLayout *Contenido_layout =new QGridLayout;
    QScrollArea *Perfiles_ScrollArea =new QScrollArea;

    Total_widget->setStyleSheet("QWidget { background-color: rgb(254, 247, 195);}"
                                "QPushButton { background-color: transparent;"
                                "color: rgb(94, 68, 92);"
                                "height: "+QString().number(alto_res/15)+"px;"
                                "width: "+QString().number(ancho_res/4)+"px;}"
                                "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                                "color: rgb(254, 247, 195);}");

    for (int i=0;i<alumnos.size();i++) {
        QPushButton *alumno=new QPushButton;
        QPixmap pixmap("imgs/perfil_icon.png");
        alumno->setStyleSheet("QPushButton { background-color: transparent;"
                              "color: rgb(254, 247, 195);"
                              "width: "+QString().number(ancho_res/4)+"px;"
                              "height: "+QString().number(alto_res/15)+"px;}"
                              "QPushButton::pressed { background-color: rgb(254, 247, 195);"
                              "color: rgb(94, 68, 92);}");
        alumno->setFont(QFont("Century Gothic",15,100));
        alumno->setIconSize(QSize(alto_res/20,alto_res/20));
        alumno->setIcon(pixmap);
        alumno->setText(alumnos.at(i).nombres+" "+alumnos.at(i).apellidos);
        Perfiles_layout->addWidget(alumno,i,0);
        connect(alumno, &QPushButton::clicked, [=]() {} );
    }

    QPushButton *Empezar=new QPushButton;
    Empezar->setFont(QFont("Century Gothic",35,100));
    Empezar->setText("Empezar");
    Contenido_layout->addWidget(Empezar,0,0);
    connect(Empezar, &QPushButton::clicked, [=]() { MainWindow::take_Attendance(Total_layout,Contenido_widget,alumnos.begin()); } );

    // TO DO.
    QPushButton *Ver_asistencia=new QPushButton;
    Ver_asistencia->setFont(QFont("Century Gothic",35,100));
    Ver_asistencia->setText("Ver Asistencia");
    Contenido_layout->addWidget(Ver_asistencia,1,0);
    connect(Ver_asistencia, &QPushButton::clicked, [=]() { MainWindow::show_Attendance(Total_layout, Contenido_widget,alumnos.begin()); } );

    Perfiles_widget->setLayout(Perfiles_layout);
    Perfiles_ScrollArea->setWidget(Perfiles_widget);
    Perfiles_ScrollArea->setStyleSheet("background-color: rgb(94, 68, 92);");
    Perfiles_ScrollArea->setFixedWidth(ancho_res/3);

    Contenido_widget->setLayout(Contenido_layout);

    Total_layout->addWidget(Perfiles_ScrollArea,0,0);
    Total_layout->addWidget(Contenido_widget,0,1);
    Total_widget->setLayout(Total_layout);
    Paginas.addWidget(Total_widget);
}

void MainWindow::take_Attendance(QGridLayout *total,QWidget *Contenido_wid, QVector<alumno>::iterator iterator)
{
    //Borro todo lo que habia en Contenido_wid y lo saco del layout

    QGridLayout *Contenido_aux= dynamic_cast<QGridLayout*>(Contenido_wid->layout());

    while (Contenido_aux->count()>0) {
        QLayoutItem* item = Contenido_aux->takeAt(0);
        delete item;
    }

    delete Contenido_aux;
    delete Contenido_wid;
    total->removeWidget(Contenido_wid);

    //Creo el reemplazo de Contenido_wid

    QWidget *Cont_wid=new QWidget();
    QGridLayout *Contenido=new QGridLayout();
    Cont_wid->setLayout(Contenido);

    //Si el iterador a llegado al final del vector o a regresado hasta al inicio volvemos a imprimir las opciones de
    //empezar y ver asistencia

    if(iterator==alumnos.end()||iterator<alumnos.begin()){
        QPushButton *Empezar=new QPushButton;
        Empezar->setFont(QFont("Century Gothic",35,100));
        Empezar->setText("Empezar");
        Contenido->addWidget(Empezar,0,0);
        connect(Empezar, &QPushButton::clicked, [=]() { MainWindow::take_Attendance(total,Cont_wid,alumnos.begin()); } );

        QPushButton *Ver_asistencia=new QPushButton;
        Ver_asistencia->setFont(QFont("Century Gothic",35,100));
        Ver_asistencia->setText("Ver Asistencia");
        Contenido->addWidget(Ver_asistencia,1,0);
        connect(Ver_asistencia, &QPushButton::clicked, [=]() {MainWindow::show_Attendance(total, Cont_wid, alumnos.begin());} );
    }

    //Si no imprimimos el alumno que nos señale el iterador con sus opciones de si,no y regresar

    else {
        QLabel *imagen_alumno=new QLabel();
        imagen_alumno->setPixmap(QPixmap("imgs/perfil_icon.png"));
        imagen_alumno->setScaledContents(1);
        imagen_alumno->setFixedSize(alto_res/5,alto_res/5);

        QLabel *nombre_alumno=new QLabel();
        nombre_alumno->setFont(QFont("Century Gothic",35,100));
        nombre_alumno->setStyleSheet("color:rgb(94, 68, 92);");
        nombre_alumno->setText(iterator->nombres+" "+iterator->apellidos);

        QPushButton *si=new QPushButton;
        si->setFont(QFont("Century Gothic",35,100));
        si->setText("SI");
        si->setStyleSheet("QPushButton { background-color: transparent;"
                          "color: rgb(94, 68, 92);"
                          "height: "+QString().number(alto_res/15)+"px;}"
                          "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                          "color: rgb(254, 247, 195);}");
        connect(si, &QPushButton::clicked, [=]() {
            if(QDate().fromString(iterator->inicio_asistencia).daysTo(QDate().currentDate())+1==iterator->asistencia.size())
                iterator->asistencia.replace(iterator->asistencia.size()-1,1,'1');
            else
                iterator->asistencia.push_back('1');
            MainWindow::take_Attendance(total,Cont_wid,iterator+1); } );

        QPushButton *no=new QPushButton;
        no->setFont(QFont("Century Gothic",35,100));
        no->setText("NO");
        no->setStyleSheet("QPushButton { background-color: transparent;"
                          "color: rgb(94, 68, 92);"
                          "height: "+QString().number(alto_res/15)+"px;}"
                          "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                          "color: rgb(254, 247, 195);}");
        connect(no, &QPushButton::clicked, [=]() {
            if(QDate().fromString(iterator->inicio_asistencia).daysTo(QDate().currentDate())+1==iterator->asistencia.size())
                iterator->asistencia.replace(iterator->asistencia.size()-1,1,'0');
            else
                iterator->asistencia.push_back('0');
            MainWindow::take_Attendance(total,Cont_wid,iterator+1); } );

        QPushButton *regresar=new QPushButton;
        regresar->setFont(QFont("Century Gothic",35,100));
        regresar->setText("Regresar");
        regresar->setStyleSheet("QPushButton { background-color: transparent;"
                                "color: rgb(94, 68, 92);"
                                "height: "+QString().number(alto_res/15)+"px;}"
                                "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                                "color: rgb(254, 247, 195);}");
        connect(regresar, &QPushButton::clicked, [=]() { MainWindow::take_Attendance(total,Cont_wid,iterator-1); } );

        Contenido->addWidget(imagen_alumno,0,0,1,0,Qt::AlignCenter);
        Contenido->addWidget(nombre_alumno,1,0,1,0,Qt::AlignCenter);
        Contenido->addWidget(si,2,0);
        Contenido->addWidget(no,2,1);
        Contenido->addWidget(regresar,3,0,1,0,Qt::AlignCenter);

    }

    //Guardamos el repuesto del Contenido_wid en la misma posicion que tenia

    total->addWidget(Cont_wid,0,1);
}

// TO DO
void MainWindow::show_Attendance(QGridLayout *total,QWidget *Contenido_wid, QVector<alumno>::iterator iterator)
{
    QStringList labelAsistencia= {"Asistencia"};
    QStringList labelAlumnos = {};

    //Borramos lo que tenia en contenido
    QGridLayout *Contenido_aux= dynamic_cast<QGridLayout*>(Contenido_wid->layout());

    while (Contenido_aux->count()>0) {
        QLayoutItem* item = Contenido_aux->takeAt(0);
        delete item;
    }

    delete Contenido_aux;
    delete Contenido_wid;
    total->removeWidget(Contenido_wid);

    for(auto alumno : alumnos) {
        labelAlumnos.append(alumno.nombres + " " + alumno.apellidos);
    }

    //Creo el reemplazo de Contenido_wid

    QWidget *Cont_wid=new QWidget();
    QGridLayout *Contenido=new QGridLayout();
    Cont_wid->setLayout(Contenido);

    QPushButton *regresar=new QPushButton;
    regresar->setFont(QFont("Century Gothic",35,100));
    regresar->setText("Regresar");
    regresar->setStyleSheet("QPushButton { background-color: transparent;"
                             "color: rgb(94, 68, 92);"
                             "height: "+QString().number(alto_res/15)+"px;}"
                             "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                             "color: rgb(254, 247, 195);}");
    connect(regresar, &QPushButton::clicked, [=]() { MainWindow::take_Attendance(total,Cont_wid,iterator-1); } );

    // Creamos nuestro calendario.
    QCalendarWidget *calendar = new QCalendarWidget();
    calendar->setGridVisible(true);

    // Nuestra cabecera por default no se ve, colorear con negro los numeros para que se vea.
    calendar->setStyleSheet("color: rgb(0,0,0);");

    // Si el usuario dio click a un dia del calendario.
    connect(calendar, &QCalendarWidget::clicked, this, &MainWindow::on_calendarWidget_clicked);

    // Tabla donde mostrara las asistencias.
    table = new QTableWidget(alumnos.size(), 1);

    table->setHorizontalHeaderLabels(labelAsistencia);
    table->setVerticalHeaderLabels(labelAlumnos);
    table->showGrid();
    table->setStyleSheet("background-color: white");
    //table->setFixedSize(ancho_res/2,alto_res/3*2);

    int column(0);
    // Iterar entre las asistencias de nuestros alumnos y obtener el ultimo numero.
    // Es necesario convertir a QString porque back() nos regresa QChar.
    for(auto alumno : alumnos) {
        QTableWidgetItem *item = new QTableWidgetItem(QString(alumno.asistencia.back()));
        table->setItem(0,column,item);
        item->setBackground(Qt::white);
        column++;
    }

    //Guardamos el repuesto del Contenido_wid en la misma posicion que tenia

    total->addWidget(Cont_wid,0,1);
    Contenido->addWidget(regresar,3,0,1,0,Qt::AlignBottom);
    Contenido->addWidget(calendar,3,0,1,0,Qt::AlignTop);
    Contenido->addWidget(table,3,0,1,0,Qt::AlignCenter);
}

void MainWindow::set_BurgerMenu(QGridLayout *total)
{
        QGridLayout *burger =new QGridLayout;
        QWidget *wid_burger=new QWidget;

        wid_burger->setStyleSheet("QPushButton { background-color: transparent;"
                                  "color: rgb(254, 247, 195);"
                                  "width: "+QString().number(ancho_res/3)+"px;max-width:"+QString().number(ancho_res/3)+"px;"
                                  "height: "+QString().number(alto_res/10)+"px;max-height:"+QString().number(alto_res/10)+"px;"
                                  "font: bold "+QString().number(alto_res/25)+"px \"Century Gothic\";"
                                  "icon-size: "+QString().number(alto_res/15)+"px;}"
                                  "QPushButton::pressed { background-color: rgb(254, 247, 195);"
                                  "color: rgb(94, 68, 92);}"
                                  "QWidget {background-color: rgb(94, 68, 92);}");

        QPushButton *close_menu=new QPushButton;
        QPixmap pixmap("imgs/cruz_icon.svg");
        close_menu->setStyleSheet("QPushButton { border-radius: "+QString().number((alto_res/10)/2)+"px;}"
                                  "QPushButton::pressed { background-color: rgb(254, 247, 195);}");
        close_menu->setFixedSize(alto_res/10,alto_res/10);
        close_menu->setIcon(pixmap);
        burger->addWidget(close_menu,0,0,Qt::AlignHCenter);
        connect(close_menu, &QPushButton::clicked, [=]() {
            delete wid_burger;
            total->removeWidget(wid_burger);} );


        QPushButton *animo=new QPushButton;
        pixmap.load("imgs/estado_animo_icon.svg");
        animo->setIcon(pixmap);
        animo->setText("Estado de Animo");
        burger->addWidget(animo,1,0,Qt::AlignLeft);
        connect(animo, &QPushButton::clicked, [=]() {} );


        QPushButton *asistencia=new QPushButton;
        pixmap.load("imgs/asistencia_icon.png");
        asistencia->setIcon(pixmap);
        asistencia->setText("Asistencia");
        burger->addWidget(asistencia,2,0,Qt::AlignLeft);
        connect(asistencia, &QPushButton::clicked, [=]() { Paginas.setCurrentIndex(3); } );

        QPushButton *suenos=new QPushButton;
        pixmap.load("imgs/suenos_icon.png");
        suenos->setIcon(pixmap);
        suenos->setText("Sueños");
        burger->addWidget(suenos,3,0,Qt::AlignLeft);
        connect(suenos, &QPushButton::clicked, [=]() {} );

        wid_burger->setLayout(burger);
        total->addWidget(wid_burger,0,0,0,1);
}

void MainWindow::presionar_ingresar(QString username,QString password)
{
    QFile file("src/usuarios.json");
    file.open(QIODevice::ReadOnly);
    QJsonDocument Archivo_json( QJsonDocument::fromJson( QByteArray( file.readAll() ) ) );

    QJsonObject jsonObj( Archivo_json.object() );
    QJsonArray arreglo_usuarios( jsonObj["users"].toArray() );

    QMessageBox msgBox;
    msgBox.setText("El usuario no existe.");
    msgBox.setIcon(QMessageBox::Warning);

    for (int i=0;i<arreglo_usuarios.size();i++) {

        QJsonObject usuario( arreglo_usuarios.at(i).toObject() );

        if(username == usuario["username"].toString() && password == usuario["password"].toString() ){
            Paginas.setCurrentIndex(1);
            file.close();
            return;
        }
        if(username == usuario["username"].toString()){
            msgBox.setText("Contraseña Incorrecta.");
            break;
        }
    }

    msgBox.exec();

    file.close();
}

void MainWindow::guardar_alumnos()
{
    QJsonObject objetousuarios,usuario,date;
    QJsonDocument jsonDoc;
    QJsonArray ArregloUsuarios;
    QFile dbFile("src/alumnos.json");

    //Abrimos archivo
    dbFile.open(QIODevice::WriteOnly);

    for(auto it:alumnos){
        usuario["names"]=it.nombres;
        usuario["last_names"]=it.apellidos;
        usuario["first"]=it.inicio_asistencia;
        usuario["attendance"]=it.asistencia;

        ArregloUsuarios.append(usuario);
    }

    objetousuarios["alumnos"]=ArregloUsuarios;

    //Creamos un documento json a partir de un objeto
    jsonDoc = QJsonDocument(objetousuarios);

    //Escribimos el archivo el documento  en formato json
    dbFile.write(jsonDoc.toJson());
    dbFile.close();
}

void MainWindow::recuperar_alumnos()
{
    QFile file("src/alumnos.json");
    file.open(QIODevice::ReadOnly);
    QJsonDocument Archivo_json( QJsonDocument::fromJson( QByteArray( file.readAll() ) ) );

    QJsonObject jsonObj( Archivo_json.object() );
    QJsonArray arreglo_usuarios( jsonObj["alumnos"].toArray() );

    for (int i=0;i<arreglo_usuarios.size();i++) {
        QJsonObject usuario( arreglo_usuarios.at(i).toObject() );
        alumnos.append(alumno(usuario["names"].toString(),usuario["last_names"].toString(),usuario["first"].toString(),usuario["attendance"].toString()));
    }

    file.close();

    for (QVector<alumno>::iterator i=alumnos.begin();i!=alumnos.end();i++){
        while(i->asistencia.size()<QDate().fromString(i->inicio_asistencia).daysTo(QDate().currentDate())){
            i->asistencia.push_back('0');
        }
    }
}


/* Actualizara la tabla de asistencias dependiendo del dia escogido en el calendario. */
void MainWindow::on_calendarWidget_clicked(const QDate& date) {
    // La razon del porque usamos un vector de pares es para obtener el numero
    // del mes del alumno que fue registrado, pues esta guardado como cadena de caracteres,
    // no se puede comparar "mar." == 3.
    QVector< QPair<QString, int> > mesNum = { {"ene.",1}, {"feb.",2}, {"mar.", 3}, {"abr.", 4},
                                             {"may.", 5}, {"jun.",6}, {"jul.", 7}, {"ago.",8},
                                             {"sep.", 9}, {"oct.",10}, {"nov.",11}, {"dic.", 12} };

    // Columna para saber la posicion de los items en la tabla.
    int column(0);
    int diaMesAsi;

    // Obtener el dia y mes actual, esto se hace porque la ultima asistencia tomada seria
    // el dia y mes actual.
    QDate d = QDate::currentDate();
    QString diaActual = d.toString("d");
    QString mesActual = d.toString("M");

    // Iterar en cada alumno para encontrar su inicio de asistencia.
    for(auto alumno : alumnos) {
        QString inicioAsistencia = alumno.inicio_asistencia;

        // Nos interesa el mes y dia del inicio de la asistencia, separaramos el QString.
        // donde parts[1] = mes, parts[2] = dia.
        QStringList parts = inicioAsistencia.split(' ');
        int diaInicioAs = parts[2].toInt();
        QString diaMesAs = parts[1];

        // Iteramos en nuestros meses para encontrar a que numero pertenece el mes.
        for(int i = 0; i < mesNum.size(); i++) {
            if(diaMesAs == mesNum[i].first) {
                diaMesAsi = mesNum[i].second;
                break;
            }
        }

        // Si el mes seleccionado en el calendario coincide con el mes de ingreso del alumno
        // Y ademas el dia de ingreso coincide con el dia seleccionado en el calendario.
        if(date.month() == diaMesAsi and date.day() == diaInicioAs) {
            // Ingresar la asistencia correspondiente a nuestra tabla.
            // En la posicion 0 porque es la primera asistencia que tiene el alumno.
            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(0))));
            table->setItem(0,column,item);
            item->setBackground(Qt::white);
            column++;
        } else {
            // Iterar en nuestra asistencia del alumno.
            for(int i = 0; i < alumno.asistencia.size(); i++) {
                // Como cada bit de nuestro string es un dia y pertenece a un mes y voy a estar iterando
                // y revisando uno por uno, ocupo saber en que momento cambio de mes para reiniciar el dia y el mes.
                // Empezando en el mes que inicio la asistencia del alumno.
                switch(diaMesAsi) {
                    case enero:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 31){
                            diaInicioAs++;
                            diaMesAsi++;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                    case febrero:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 28){
                            diaInicioAs++;
                            diaMesAsi++;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                    case marzo:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 31){
                            diaInicioAs++;
                            diaMesAsi++;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                    case abril:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QString elemento = alumno.asistencia.at(i);
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 30){
                            diaInicioAs = 1;
                            diaMesAsi++;
                            alumno.cambioMes = true;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                    case mayo:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QString elemento = alumno.asistencia.at(i);
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 31){
                            diaInicioAs = 1;
                            diaMesAsi++;
                            alumno.cambioMes = true;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                    case junio:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 31){
                            diaInicioAs++;
                            diaMesAsi++;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                    case julio:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 31){
                            diaInicioAs++;
                            diaMesAsi++;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                    case agosto:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 31){
                            diaInicioAs++;
                            diaMesAsi++;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                    case septiembre:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 31){
                            diaInicioAs++;
                            diaMesAsi++;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                    case octubre:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 30){
                            diaInicioAs++;
                            diaMesAsi++;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                    case noviembre:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 30){
                            diaInicioAs++;
                            diaMesAsi++;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;

                    case diciembre:
                        // Se encontro el dia, imprimir la asistencia de ese dia en la tabla.
                        if(date.day() == diaInicioAs) {
                            QTableWidgetItem *item = new QTableWidgetItem((QString(alumno.asistencia.at(i))));
                            table->setItem(0,column,item);
                            item->setBackground(Qt::white);
                            column++;
                            i = alumno.asistencia.size();
                        }
                        // Habra un cambio de mes.
                        else if(diaInicioAs == 31){
                            diaInicioAs++;
                            diaMesAsi++;
                        }
                        // Aun no hay cambio de mes, solamente incrementar el dia.
                        else {
                            diaInicioAs++;
                        }
                    break;
                } // switch
            }
        }

        if(!(date.month() == diaMesAsi and date.day() >= diaInicioAs)) {
            QTableWidgetItem *item = new QTableWidgetItem((QString("-")));
            table->setItem(0,column,item);
            item->setBackground(Qt::white);
            column++;
        }
    }
}