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

    set_LoginPage();
    set_MainMenuPage();
    set_ProfilesPage();
    set_AttendancePage();
    set_MoodPage();

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
    connect(perfiles, &QPushButton::clicked, [=]() {Paginas.setCurrentIndex(2); } );

    QPushButton *mood=new QPushButton;
    mood->setText("Estados\nde\nAnimo");
    total->addWidget(mood,0,1);
    connect(mood, &QPushButton::clicked, [=]() { Paginas.setCurrentIndex(4); } );

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

    QGridLayout *info_alumno = new QGridLayout; // Para mostrar alumnos existentes,Layout que incluye a la caja
    QWidget *wid_info_alumnos=new QWidget;
    wid_info_alumnos->setLayout(info_alumno);

    QGroupBox *Contenido_Widget = new QGroupBox(tr("Agregar nuevo perfil")); // Widget de la Caja suple a info
    QVBoxLayout *vbox = new QVBoxLayout; //Layout de lo que hay dentro de la Caja suple a info

    MainMenu->setStyleSheet("QWidget { background-color: rgb(254, 247, 195);}"
                                "QPushButton { background-color: transparent;"
                                "color: rgb(94, 68, 92);"
                                "height: "+QString().number(alto_res/15)+"px;"
                                "width: "+QString().number(ancho_res/4)+"px;}"
                                "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                                "color: rgb(254, 247, 195);}");

    // /////////////////////////////////////////HEADER///////////////////////

    //HEADER
    QPushButton *burger_icon=new QPushButton;
    QPixmap pixmap("imgs/burger_menu.png");
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(),QColor(94, 68, 92));
    painter.end();

    burger_icon->setFixedSize(alto_res/21,alto_res/21);
    burger_icon->setStyleSheet("border-radius: "+QString().number((alto_res/21)/2)+"px;");
    burger_icon->setIcon(pixmap);
    burger_icon->setIconSize(QSize(alto_res/25,alto_res/25));
    busca->addWidget(burger_icon,0,0);
    connect(burger_icon, &QPushButton::clicked, [=]() {MainWindow::set_BurgerMenu(total);} );

    QLabel *titulo=new QLabel;
    titulo->setText("Perfiles");
    titulo->setPalette(Paleta_colores);
    titulo->setFont(QFont("Century Gothic",20,100));
    busca->addWidget(titulo,0,2,Qt::AlignLeft);

    //QLabel *text_busca=new QLabel;
    //text_busca->setText("Busca");
    //text_busca->setPalette(Paleta_colores);
    //text_busca->setFont(QFont("Century Gothic",14,100));
    //busca->addWidget(text_busca,0,1);

    //QLineEdit *le_busca=new QLineEdit;
    //busca->addWidget(le_busca,0,2);
    /*
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
    */
    // ///////////////////////////////////////////////////////////////////////////////

    //ALUMNOS_SCROLL_AREA
    QLabel *auxiliar_name = new QLabel;
    QVector<alumno>::iterator iterator = alumnos.begin();

    QLabel *Visor=new QLabel;
    QPushButton *foto_alumno=new QPushButton;
    QLabel *nombre_alumno=new QLabel;
    QLabel *apellidos_alumno=new QLabel;
    QLabel *edad_alumno=new QLabel;
    QLabel *domicilio_alumno=new QLabel;
    QLabel *tutor_alumno=new QLabel;
    QLabel *telefono_alumno=new QLabel;
    QLabel *grado_alumno=new QLabel;

    // ////////////////CARGANDO ALUMNOS EN EL PERFILES SCROLL AREA/////////////////////////
    for (int i=0;i<alumnos.size();i++) {
        iterator = alumnos.begin()+i;
        QPushButton *alumno=new QPushButton;
        pixmap.load("imgs/perfil_icon.png");
        alumno->setStyleSheet("QPushButton { background-color: transparent;"
                              "color: rgb(254, 247, 195);"
                              "height: "+QString().number(alto_res/15)+"px;}"
                              "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                              "color: rgb(94, 68, 92);}");
        alumno->setFont(QFont("Century Gothic",15,100));
        alumno->setIconSize(QSize(alto_res/20,alto_res/20));
        alumno->setIcon(pixmap);
        alumno->setText(alumnos.at(i).nombres+" "+alumnos.at(i).apellidos);
        perfiles->addWidget(alumno,i,0);
        connect(alumno, &QPushButton::clicked, [=]() {
            auxiliar_name->setText(iterator->nombres+iterator->apellidos);//Widget que cacha lo que diga el boton clickeado
            //Eliminando contenido del widget que muestra alumnos
            info_alumno->removeWidget(Visor);
            info_alumno->removeWidget(foto_alumno);
            info_alumno->removeWidget(nombre_alumno);
            info_alumno->removeWidget(apellidos_alumno);
            info_alumno->removeWidget(edad_alumno);
            info_alumno->removeWidget(domicilio_alumno);
            info_alumno->removeWidget(tutor_alumno);
            info_alumno->removeWidget(telefono_alumno);
            info_alumno->removeWidget(grado_alumno);

            //Si el alumno tiene información cargada desplegamos la info en el widget para mostrar
            if (iterator->nombres!= ""){
                Visor->setText("Visor de perfiles");
                Visor->setAlignment(Qt::AlignCenter);
                Visor->setFont(QFont("Century Gothic",18,100));
                info_alumno->addWidget(Visor,0,0,Qt::AlignHCenter);

                QPixmap pixmap;
                if (iterator->foto == ""){
                    pixmap.load("imgs/perfil_icon.png");
                }
                else{
                    pixmap.load(iterator->foto);
                }
                foto_alumno->setStyleSheet("QPushButton { background-color: transparent;"
                                           "color: rgb(254, 247, 195);"
                                           "border-radius: 45px;}"
                                           "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                                           "color: rgb(94, 68, 92);}");
                foto_alumno->setIcon(pixmap);
                foto_alumno->setIconSize(QSize(80,80));
                foto_alumno->setFixedSize(90,90);
                info_alumno->addWidget(foto_alumno,1,0,Qt::AlignHCenter);

                nombre_alumno->setText(iterator->nombres);
                nombre_alumno->setFont(QFont("Century Gothic",12,70));
                nombre_alumno->setAlignment(Qt::AlignCenter);
                info_alumno->addWidget(nombre_alumno,2,0,Qt::AlignHCenter);

                apellidos_alumno->setText(iterator->apellidos);
                apellidos_alumno->setFont(QFont("Century Gothic",12,70));
                apellidos_alumno->setAlignment(Qt::AlignCenter);
                info_alumno->addWidget(apellidos_alumno,3,0,Qt::AlignHCenter);

                edad_alumno->setText(iterator->edad);
                edad_alumno->setFont(QFont("Century Gothic",12,70));
                edad_alumno->setAlignment(Qt::AlignCenter);
                info_alumno->addWidget(edad_alumno,4,0,Qt::AlignHCenter);

                domicilio_alumno->setText(iterator->domicilio);
                domicilio_alumno->setFont(QFont("Century Gothic",12,70));
                domicilio_alumno->setAlignment(Qt::AlignCenter);
                info_alumno->addWidget(domicilio_alumno,5,0,Qt::AlignHCenter);

                tutor_alumno->setText(iterator->tutor);
                tutor_alumno->setFont(QFont("Century Gothic",12,70));
                tutor_alumno->setAlignment(Qt::AlignCenter);
                info_alumno->addWidget(tutor_alumno,6,0,Qt::AlignHCenter);

                telefono_alumno->setText(iterator->telefono);
                telefono_alumno->setFont(QFont("Century Gothic",12,70));
                telefono_alumno->setAlignment(Qt::AlignCenter);
                info_alumno->addWidget(telefono_alumno,7,0,Qt::AlignHCenter);

                grado_alumno->setText(iterator->grado);
                grado_alumno->setFont(QFont("Century Gothic",12,70));
                grado_alumno->setAlignment(Qt::AlignCenter);
                info_alumno->addWidget(grado_alumno,8,0,Qt::AlignHCenter);

            }
            total->addWidget(wid_info_alumnos,1,2);// PARA QUE EL VISOR APAREZA HASTA QUE SE SELECCIONE UN ALUMNO
        } );
    }

    // //////////////////////INFO DE LLENADO///////////////////////////////////////////////////

    QLineEdit *nombre_llenado=new QLineEdit;
    nombre_llenado->setPlaceholderText("Nombres");
    nombre_llenado->setAlignment(Qt::AlignCenter);
    vbox->addWidget(nombre_llenado,1,Qt::AlignHCenter);

    QLineEdit *apellidos_llenado=new QLineEdit;
    apellidos_llenado->setPlaceholderText("Apellidos");
    apellidos_llenado->setAlignment(Qt::AlignCenter);
    vbox->addWidget(apellidos_llenado,2,Qt::AlignHCenter);

    QLineEdit *edad_llenado=new QLineEdit;
    edad_llenado->setPlaceholderText("Edad");
    edad_llenado->setAlignment(Qt::AlignCenter);
    vbox->addWidget(edad_llenado,2,Qt::AlignHCenter);

    QLineEdit *domicilio_llenado=new QLineEdit;
    domicilio_llenado->setPlaceholderText("Domicilio");
    domicilio_llenado->setAlignment(Qt::AlignCenter);
    vbox->addWidget(domicilio_llenado,2,Qt::AlignHCenter);

    QLineEdit *tutor_llenado=new QLineEdit;
    tutor_llenado->setPlaceholderText("Nombre del tutor");
    tutor_llenado->setAlignment(Qt::AlignCenter);
    vbox->addWidget(tutor_llenado,2,Qt::AlignHCenter);

    QLineEdit *telefono_llenado=new QLineEdit;
    telefono_llenado->setPlaceholderText("Telefono");
    telefono_llenado->setAlignment(Qt::AlignCenter);
    vbox->addWidget(telefono_llenado,2,Qt::AlignHCenter);

    QLineEdit *grado_llenado=new QLineEdit;
    grado_llenado->setPlaceholderText("Grado escolar");
    grado_llenado->setAlignment(Qt::AlignCenter);
    vbox->addWidget(grado_llenado,2,Qt::AlignHCenter);

    QScrollArea *sa_perfiles =new QScrollArea;
    sa_perfiles->setWidgetResizable(true); //FRANCISCO: Para que el scroll Area modifique su tamaño al agrear alumnos
    QWidget *wid_perfiles=new QWidget;

    // ////////////////////////////////////////////////////////////////////////

    //Agregando boton de editar foto
    QPushButton *edit_foto=new QPushButton;
    pixmap.load("imgs/edit_icon.png");
    edit_foto->setFixedSize(alto_res/21,alto_res/21);
    edit_foto->setIconSize(QSize(alto_res/32,alto_res/32));
    edit_foto->setStyleSheet("border-radius: "+QString().number((alto_res/21)/2)+"px;");
    edit_foto->setIcon(pixmap);
    info_alumno->addWidget(edit_foto,1,1);
    connect(edit_foto, &QPushButton::clicked, [=]() {
        if (auxiliar_name->text().size()>0){
            QVector<alumno>::iterator iterator2 = alumnos.begin();
            QFileDialog foto;
            QString dir;
            QStringList fileNames;
            if (foto.exec()){
                if (foto.selectedFiles().size()>0){//Si no selecciona ninguna foto no hace nada
                    fileNames = foto.selectedFiles();
                    dir = fileNames[0];
                    for (int i=0;i<alumnos.size();i++) {
                        iterator2 = alumnos.begin()+i;
                        if (iterator2->nombres + iterator2->apellidos == auxiliar_name->text()){
                            iterator2->foto.replace(0,iterator2->foto.size(),dir);
                        }
                    }
                }
            }
        }
    });

    //Funcion de agregar alumno
    QPushButton *agrega_alumno=new QPushButton;
    agrega_alumno->setText("Agregar");
    vbox->addWidget(agrega_alumno,3,Qt::AlignHCenter);
    connect(agrega_alumno, &QPushButton::clicked, [=]( ) {
        if(nombre_llenado->text().size()>0&&apellidos_llenado->text().size()>0){
            alumnos.append(alumno(nombre_llenado->text(),apellidos_llenado->text(),QDate().currentDate().toString(),edad_llenado->text(),domicilio_llenado->text(),tutor_llenado->text(),telefono_llenado->text(),grado_llenado->text()));
            MainWindow::guardar_alumnos();
            nombre_llenado->clear();apellidos_llenado->clear();
            edad_llenado->clear();domicilio_llenado->clear();
            tutor_llenado->clear();telefono_llenado->clear();
            grado_llenado->clear();
        }});

    // /////////////////BOTON PARA ACTUALIZAR PERFILES//////////////////////////
    QPushButton *actualizar_perfiles=new QPushButton;
    actualizar_perfiles->setText("Actualizar perfiles");
    actualizar_perfiles->setFont(QFont("Century Gothic",20,100));
    actualizar_perfiles->setIconSize(QSize(alto_res/40,alto_res/40));
    busca->addWidget(actualizar_perfiles,0,1,Qt::AlignLeft);
    connect(actualizar_perfiles, &QPushButton::clicked, [=]( ) {
            QVector<alumno>::iterator iterator = alumnos.begin();
            QPixmap pixmap("imgs/burger_menu.png");
            QPainter painter(&pixmap);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(pixmap.rect(),QColor(94, 68, 92/*254, 247, 195*/));
            painter.end();
            for (int i=0;i<alumnos.size();i++) {
                iterator = alumnos.begin()+i;
                QPushButton *alumno=new QPushButton;
                pixmap.load("imgs/perfil_icon.png");
                alumno->setStyleSheet("QPushButton { background-color: transparent;"
                                      "color: rgb(254, 247, 195);"
                                      "height: "+QString().number(alto_res/15)+"px;}"
                                      "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                                      "color: rgb(94, 68, 92);}");
                alumno->setFont(QFont("Century Gothic",15,100));
                alumno->setIconSize(QSize(alto_res/20,alto_res/20));
                alumno->setIcon(pixmap);
                alumno->setText(alumnos.at(i).nombres+" "+alumnos.at(i).apellidos);
                perfiles->addWidget(alumno,i,0);
                connect(alumno, &QPushButton::clicked, [=]() {
                    auxiliar_name->setText(iterator->nombres+iterator->apellidos);//Widget que cacha lo que diga el boton clickeado
                    //Eliminando contenido del widget que muestra alumnos

                    info_alumno->removeWidget(Visor);
                    info_alumno->removeWidget(foto_alumno);
                    info_alumno->removeWidget(nombre_alumno);
                    info_alumno->removeWidget(apellidos_alumno);
                    info_alumno->removeWidget(edad_alumno);
                    info_alumno->removeWidget(domicilio_alumno);
                    info_alumno->removeWidget(tutor_alumno);
                    info_alumno->removeWidget(telefono_alumno);
                    info_alumno->removeWidget(grado_alumno);

                    //Si el alumno tiene información cargada desplegamos la info en el widget para mostrar
                    if (iterator->nombres!= ""){
                        Visor->setText("Visor de perfiles");
                        Visor->setAlignment(Qt::AlignCenter);
                        Visor->setFont(QFont("Century Gothic",18,100));
                        info_alumno->addWidget(Visor,0,0,Qt::AlignHCenter);

                        QPixmap pixmap;
                        if (iterator->foto == ""){
                            pixmap.load("imgs/perfil_icon.png");
                        }
                        else{
                            pixmap.load(iterator->foto);
                        }
                        foto_alumno->setStyleSheet("QPushButton { background-color: transparent;"
                                                   "color: rgb(254, 247, 195);"
                                                   "border-radius: 45px;}"
                                                   "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                                                   "color: rgb(94, 68, 92);}");
                        foto_alumno->setIcon(pixmap);
                        foto_alumno->setIconSize(QSize(80,80));
                        foto_alumno->setFixedSize(90,90);
                        info_alumno->addWidget(foto_alumno,1,0,Qt::AlignHCenter);

                        nombre_alumno->setText(iterator->nombres);
                        nombre_alumno->setFont(QFont("Century Gothic",12,70));
                        nombre_alumno->setAlignment(Qt::AlignCenter);
                        info_alumno->addWidget(nombre_alumno,2,0,Qt::AlignHCenter);

                        apellidos_alumno->setText(iterator->apellidos);
                        apellidos_alumno->setFont(QFont("Century Gothic",12,70));
                        apellidos_alumno->setAlignment(Qt::AlignCenter);
                        info_alumno->addWidget(apellidos_alumno,3,0,Qt::AlignHCenter);

                        edad_alumno->setText(iterator->edad);
                        edad_alumno->setFont(QFont("Century Gothic",12,70));
                        edad_alumno->setAlignment(Qt::AlignCenter);
                        info_alumno->addWidget(edad_alumno,4,0,Qt::AlignHCenter);

                        domicilio_alumno->setText(iterator->domicilio);
                        domicilio_alumno->setFont(QFont("Century Gothic",12,70));
                        domicilio_alumno->setAlignment(Qt::AlignCenter);
                        info_alumno->addWidget(domicilio_alumno,5,0,Qt::AlignHCenter);

                        tutor_alumno->setText(iterator->tutor);
                        tutor_alumno->setFont(QFont("Century Gothic",12,70));
                        tutor_alumno->setAlignment(Qt::AlignCenter);
                        info_alumno->addWidget(tutor_alumno,6,0,Qt::AlignHCenter);

                        telefono_alumno->setText(iterator->telefono);
                        telefono_alumno->setFont(QFont("Century Gothic",12,70));
                        telefono_alumno->setAlignment(Qt::AlignCenter);
                        info_alumno->addWidget(telefono_alumno,7,0,Qt::AlignHCenter);

                        grado_alumno->setText(iterator->grado);
                        grado_alumno->setFont(QFont("Century Gothic",12,70));
                        grado_alumno->setAlignment(Qt::AlignCenter);
                        info_alumno->addWidget(grado_alumno,8,0,Qt::AlignHCenter);
                    }
                    total->addWidget(wid_info_alumnos,1,2);// PARA QUE EL VISOR APAREZA HASTA QUE SE SELECCIONE UN ALUMNO
                } );
            }
        });
    // ////////////////////////////////////////////////


    //UNION DE TODOS LOS LAYOUT
    wid_perfiles->setLayout(perfiles);
    wid_perfiles->setStyleSheet("background-color: rgb(94, 68, 92);");
    sa_perfiles->setWidget(wid_perfiles);
    sa_perfiles->setFixedWidth(ancho_res/3);

    Contenido_Widget->setLayout(vbox);
    QWidget *wid_busca=new QWidget;
    wid_busca->setLayout(busca);

    total->addWidget(wid_busca,0,0,1,0);
    total->addWidget(sa_perfiles,1,0);
    total->addWidget(Contenido_Widget,1,1);

    MainMenu->setLayout(total);

    Paginas.addWidget(MainMenu);
}

// HERE
void MainWindow::set_AttendancePage()
{
    QWidget *Total_widget=new QWidget;
    QWidget *Perfiles_widget=new QWidget;
    QWidget *Contenido_widget=new QWidget;

    QWidget *header_widget = new QWidget;
    QGridLayout *header =new QGridLayout; //Layout del header, incluye el botón burger y el titulo

    QGridLayout *Total_layout =new QGridLayout;
    QGridLayout *Perfiles_layout =new QGridLayout;
    QGridLayout *Contenido_layout =new QGridLayout;
    QScrollArea *Perfiles_ScrollArea =new QScrollArea;
    Perfiles_ScrollArea->setWidgetResizable(true);

    Total_widget->setStyleSheet("QWidget { background-color: rgb(254, 247, 195);}"
                                "QPushButton { background-color: transparent;"
                                "color: rgb(94, 68, 92);"
                                "height: "+QString().number(alto_res/15)+"px;"
                                "width: "+QString().number(ancho_res/4)+"px;}"
                                "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                                "color: rgb(254, 247, 195);}");

    //HEADER
    QPushButton *burger_icon=new QPushButton;
    QPixmap pixmap("imgs/burger_menu.png");
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(),QColor(94, 68, 92/*254, 247, 195*/));
    painter.end();

    QLabel *titulo=new QLabel;
    titulo->setText("Registro de Asistencias");
    titulo->setPalette(Paleta_colores);
    titulo->setFont(QFont("Century Gothic",20,100));
    header->addWidget(titulo,0,2,Qt::AlignLeft);

    burger_icon->setFixedSize(alto_res/21,alto_res/21);
    burger_icon->setStyleSheet("border-radius: "+QString().number((alto_res/21)/2)+"px;");
    burger_icon->setIcon(pixmap);
    burger_icon->setIconSize(QSize(alto_res/25,alto_res/25));
    header->addWidget(burger_icon,0,0);
    connect(burger_icon, &QPushButton::clicked, [=]() {MainWindow::set_BurgerMenu3(Total_layout);} );

    //Conectando header al Layout del Header
    header_widget->setLayout(header);

    for (int i=0;i<alumnos.size();i++) {
        QPushButton *alumno=new QPushButton;
        QPixmap pixmap("imgs/perfil_icon.png");
        alumno->setStyleSheet("QPushButton { background-color: transparent;"
                              "color: rgb(254, 247, 195);"
                              "width: "+QString().number(ancho_res/4)+"px;"
                              "height: "+QString().number(alto_res/15)+"px;}"
                              "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                              "color: rgb(94, 68, 92);}");
        alumno->setFont(QFont("Century Gothic",15,100));
        alumno->setIconSize(QSize(alto_res/20,alto_res/20));
        alumno->setIcon(pixmap);
        alumno->setText(alumnos.at(i).nombres+" "+alumnos.at(i).apellidos);
        Perfiles_layout->addWidget(alumno,i,0);
        connect(alumno, &QPushButton::clicked, [=]() {} );
    }

    //BOTON PARA ACTUALIZAR PERFILES
    QPushButton *actualizar_perfiles=new QPushButton;
    actualizar_perfiles->setText("Actualizar perfiles");
    actualizar_perfiles->setFont(QFont("Century Gothic",20,100));
    actualizar_perfiles->setIconSize(QSize(alto_res/40,alto_res/40));
    header->addWidget(actualizar_perfiles,0,1,Qt::AlignLeft);
    connect(actualizar_perfiles, &QPushButton::clicked, [=]( ) {
            QVector<alumno>::iterator iterator = alumnos.begin();
            QPixmap pixmap("imgs/burger_menu.png");
            QPainter painter(&pixmap);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(pixmap.rect(),QColor(94, 68, 92/*254, 247, 195*/));
            painter.end();
            for (int i=0;i<alumnos.size();i++) {
                iterator = alumnos.begin()+i;
                QPushButton *alumno = new QPushButton;
                pixmap.load("imgs/perfil_icon.png");
                alumno->setStyleSheet("QPushButton { background-color: transparent;"
                                      "color: rgb(254, 247, 195);"
                                      "height: "+QString().number(alto_res/15)+"px;}"
                                      "QPushButton::pressed { background-color: rgb(254, 247, 195);"
                                      "color: rgb(94, 68, 92);}");
                alumno->setFont(QFont("Century Gothic",15,100));
                alumno->setIconSize(QSize(alto_res/20,alto_res/20));
                alumno->setIcon(pixmap);
                alumno->setText(alumnos.at(i).nombres+" "+alumnos.at(i).apellidos);
                Perfiles_layout->addWidget(alumno,i,0);
            }
        });

    QPushButton *Empezar=new QPushButton;
    Empezar->setFont(QFont("Century Gothic",35,100));
    Empezar->setText("Empezar");
    Contenido_layout->addWidget(Empezar,0,0);
    connect(Empezar, &QPushButton::clicked, [=]() { MainWindow::take_Attendance(Total_layout,Contenido_widget,alumnos.begin()); } );

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

    Total_layout->addWidget(header_widget,0,0,1,0);
    Total_layout->addWidget(Perfiles_ScrollArea,1,0);
    Total_layout->addWidget(Contenido_widget,1,1);
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

    total->addWidget(Cont_wid,1,1);
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
    table->setFixedSize(ancho_res/4,alto_res/4);

    int column(0);
    // Iterar entre las asistencias de nuestros alumnos y obtener el ultimo numero.
    // Es necesario convertir a QString porque back() nos regresa QChar.
    for(auto alumno : alumnos) {
        QTableWidgetItem *item = new QTableWidgetItem(QString(alumno.asistencia.back()));
        table->setItem(0,column,item);
        item->setBackground(Qt::white);
        column++;
    }

    Contenido->addWidget(regresar,2,0);
    Contenido->addWidget(calendar,0,0);
    Contenido->addWidget(table,1,0,Qt::AlignHCenter);

    //Guardamos el repuesto del Contenido_wid en la misma posicion que tenia

    total->addWidget(Cont_wid,1,1);

}

void MainWindow::set_MoodPage()
{
    QWidget *Total_widget=new QWidget; //Widget general
    QGridLayout *Total_layout =new QGridLayout; //Layout de toda la página

    QWidget *header_widget = new QWidget;
    QGridLayout *header =new QGridLayout; //Layout del header, incluye el botón burger y el titulo

    QWidget *Perfiles_Widget = new QWidget; //Widget de los alumnos
    QGridLayout *Perfiles_layout = new QGridLayout;//Layout de los alumnos, dentro del cuadro
    QScrollArea *Perfiles_ScrollArea =new QScrollArea;
    Perfiles_ScrollArea->setWidgetResizable(true);

    QGridLayout *Contenido_layout =new QGridLayout;//Layout que incluye a la caja
    QGroupBox *Contenido_Widget = new QGroupBox(tr("Estado de ánimo del alumno")); // Widget de la Caja
    QVBoxLayout *vbox = new QVBoxLayout; //Layout de lo que hay dentro de la Caja

    Total_widget->setStyleSheet("QWidget { background-color: rgb(254, 247, 195);}"
                                "QPushButton { background-color: transparent;"
                                "color: rgb(94, 68, 92);"
                                "height: "+QString().number(alto_res/15)+"px;"
                                "width: "+QString().number(ancho_res/4)+"px;}"
                                "QPushButton::pressed { background-color: rgb(94, 68, 92);"
                                "color: rgb(254, 247, 195);}");


    //HEADER
    QPushButton *burger_icon=new QPushButton;
    QPixmap pixmap("imgs/burger_menu.png");
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(),QColor(94, 68, 92/*254, 247, 195*/));
    painter.end();

    burger_icon->setFixedSize(alto_res/21,alto_res/21);
    burger_icon->setStyleSheet("border-radius: "+QString().number((alto_res/21)/2)+"px;");
    burger_icon->setIcon(pixmap);
    burger_icon->setIconSize(QSize(alto_res/25,alto_res/25));
    header->addWidget(burger_icon,0,0);
    connect(burger_icon, &QPushButton::clicked, [=]() {MainWindow::set_BurgerMenu2(Total_layout);} );

    QLabel *titulo=new QLabel;
    titulo->setText("Registro de estado de Animo");
    titulo->setPalette(Paleta_colores);
    titulo->setFont(QFont("Century Gothic",20,100));
    header->addWidget(titulo,0,2,Qt::AlignLeft);

    //Conectando header al Layout del Header
    header_widget->setLayout(header);

    //CAJA

    //Agregando Line Edit para el titulo del estado de ánimo
    QLineEdit *estado=new QLineEdit;
    estado->setPlaceholderText("¿Cómo se encuentra hoy?");
    estado->setAlignment(Qt::AlignCenter);
    vbox->addWidget(estado,1,Qt::AlignCenter);

    //Agregando Text Box para los detalles del estado de ánimo
    QTextEdit *detalles=new QTextEdit;
    detalles->setPlaceholderText("Ingresa los detalles de su estado de ánimo");
    detalles->setAlignment(Qt::AlignLeft);
    vbox->addWidget(detalles,2,Qt::AlignCenter);

    //Agregando botón guardar
    QPushButton *guardar = new QPushButton;
    guardar->setText("Guardar");
    guardar->setFont(QFont("Century Gothic",20,100));
    vbox->addWidget(guardar,3,Qt::AlignCenter);

    //Conectando caja al Widget de contenido y a su vez conectando el contenido al layout de contenido
    Contenido_Widget->setLayout(vbox);
    Contenido_layout->addWidget(Contenido_Widget);

    //Creando iterador para moverse entre los alumnos del json
    QVector<alumno>::iterator iterator = alumnos.begin();

    //Etiquetas que mostrarán el animo del alumno seleccionado dentro de la caja
    QLabel *mood_alumno = new QLabel;
    QLabel *details_alumno = new QLabel;
    QLabel *auxiliar_Name = new QLabel;

    for (int i=0;i<alumnos.size();i++) {
        iterator = alumnos.begin()+i;
        QPushButton *alumno = new QPushButton;
        pixmap.load("imgs/perfil_icon.png");
        alumno->setStyleSheet("QPushButton { background-color: transparent;"
                              "color: rgb(254, 247, 195);"
                              "height: "+QString().number(alto_res/15)+"px;}"
                              "QPushButton::pressed { background-color: rgb(254, 247, 195);"
                              "color: rgb(94, 68, 92);}");
        alumno->setFont(QFont("Century Gothic",15,100));
        alumno->setIconSize(QSize(alto_res/20,alto_res/20));
        alumno->setIcon(pixmap);
        alumno->setText(alumnos.at(i).nombres+" "+alumnos.at(i).apellidos);
        Perfiles_layout->addWidget(alumno,i,0);
        connect(alumno, &QPushButton::clicked, [=]() {
            //Borramos los widgets para que se sobrescriban
            vbox->removeWidget(mood_alumno);
            vbox->removeWidget(details_alumno);

            auxiliar_Name->setText(iterator->nombres+iterator->apellidos);

            //Agregando widgets de Estado y detalles cargados desde el json
            mood_alumno->setText("Estado actual: " + iterator->estado_animo);
            mood_alumno->setFont(QFont("Century Gothic",12,70));
            vbox->addWidget(mood_alumno,4,Qt::AlignLeft);

            details_alumno->setText("Detalles: " + iterator->detalles_animo);
            details_alumno->setFont(QFont("Century Gothic",12,70));
            vbox->addWidget(details_alumno,5,Qt::AlignLeft);
            mood_alumno->clear();
            details_alumno->clear();
        });
    }

    connect(guardar, &QPushButton::clicked, [=]() {
        QVector<alumno>::iterator iterator2 = alumnos.begin();
        for (int i=0;i<alumnos.size();i++) {
            iterator2 = alumnos.begin()+i;
            if (iterator2->nombres + iterator2->apellidos == auxiliar_Name->text()){
                //Convirtiendo estado y detalles a QStrings
                const QString a = estado->text();
                QString b = detalles->toPlainText();
                //Editando atributos en el alumno en json
                iterator2->estado_animo.replace(0,iterator2->estado_animo.size(),a);
                iterator2->detalles_animo.replace(0,iterator2->detalles_animo.size(),b);
                //Borramos los widgets para que se sobrescriban
                vbox->removeWidget(mood_alumno);
                vbox->removeWidget(details_alumno);
                //Agregando widgets de Estado y detalles cargados desde el json
                mood_alumno->setText("Estado actual: " + a);
                mood_alumno->setFont(QFont("Century Gothic",12,100));
                vbox->addWidget(mood_alumno,4,Qt::AlignLeft);

                details_alumno->setText("Detalles: " + b);
                details_alumno->setFont(QFont("Century Gothic",12,100));
                vbox->addWidget(details_alumno,5,Qt::AlignLeft);
            }
        }
    });

    //BOTON PARA ACTUALIZAR PERFILES
    QPushButton *actualizar_perfiles=new QPushButton;
    actualizar_perfiles->setText("Actualizar perfiles");
    actualizar_perfiles->setFont(QFont("Century Gothic",20,100));
    actualizar_perfiles->setIconSize(QSize(alto_res/40,alto_res/40));
    header->addWidget(actualizar_perfiles,0,1,Qt::AlignLeft);
    connect(actualizar_perfiles, &QPushButton::clicked, [=]( ) {
            QVector<alumno>::iterator iterator = alumnos.begin();
            QPixmap pixmap("imgs/burger_menu.png");
            QPainter painter(&pixmap);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(pixmap.rect(),QColor(94, 68, 92/*254, 247, 195*/));
            painter.end();
            for (int i=0;i<alumnos.size();i++) {
                iterator = alumnos.begin()+i;
                QPushButton *alumno = new QPushButton;
                pixmap.load("imgs/perfil_icon.png");
                alumno->setStyleSheet("QPushButton { background-color: transparent;"
                                      "color: rgb(254, 247, 195);"
                                      "height: "+QString().number(alto_res/15)+"px;}"
                                      "QPushButton::pressed { background-color: rgb(254, 247, 195);"
                                      "color: rgb(94, 68, 92);}");
                alumno->setFont(QFont("Century Gothic",15,100));
                alumno->setIconSize(QSize(alto_res/20,alto_res/20));
                alumno->setIcon(pixmap);
                alumno->setText(alumnos.at(i).nombres+" "+alumnos.at(i).apellidos);
                Perfiles_layout->addWidget(alumno,i,0);
                connect(alumno, &QPushButton::clicked, [=]() {
                    //Borramos los widgets para que se sobrescriban
                    vbox->removeWidget(mood_alumno);
                    vbox->removeWidget(details_alumno);

                    auxiliar_Name->setText(iterator->nombres+iterator->apellidos);

                    //Agregando widgets de Estado y detalles cargados desde el json
                    mood_alumno->setText("Estado actual: " + iterator->estado_animo);
                    mood_alumno->setFont(QFont("Century Gothic",12,70));
                    vbox->addWidget(mood_alumno,4,Qt::AlignLeft);

                    details_alumno->setText("Detalles: " + iterator->detalles_animo);
                    details_alumno->setFont(QFont("Century Gothic",12,70));
                    vbox->addWidget(details_alumno,5,Qt::AlignLeft);
                    mood_alumno->clear();
                    details_alumno->clear();
                });
            }
        });

    //Conectando layout de alumnos al widget de alumnos
    //A su vez el widget de alumnos al layout general de alumnos y a la Scroll Area de alumnos
    Perfiles_Widget->setLayout(Perfiles_layout);
    Perfiles_ScrollArea->setWidget(Perfiles_Widget);
    Perfiles_ScrollArea->setFixedWidth(ancho_res/3);
    Perfiles_ScrollArea->setStyleSheet("background-color: rgb(94, 68, 92);");

    //Conectando
    Total_layout->addWidget(header_widget,0,0,1,0);
    Total_layout->addWidget(Perfiles_ScrollArea,1,0);
    Total_layout->addWidget(Contenido_Widget,1,1);
    Total_widget->setLayout(Total_layout);
    Paginas.addWidget(Total_widget);
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
        connect(animo, &QPushButton::clicked, [=]() { Paginas.setCurrentIndex(4);} );


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

void MainWindow::set_BurgerMenu2(QGridLayout *total)
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


        QPushButton *perfiles=new QPushButton;
        pixmap.load("imgs/perfil_icon.png");
        perfiles->setIcon(pixmap);
        perfiles->setText("Perfiles");
        burger->addWidget(perfiles,1,0,Qt::AlignLeft);
        connect(perfiles, &QPushButton::clicked, [=]() { Paginas.setCurrentIndex(2); } );


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

void MainWindow::set_BurgerMenu3(QGridLayout *total)
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


        QPushButton *perfiles=new QPushButton;
        pixmap.load("imgs/perfil_icon.png");
        perfiles->setIcon(pixmap);
        perfiles->setText("Perfiles");
        burger->addWidget(perfiles,1,0,Qt::AlignLeft);
        connect(perfiles, &QPushButton::clicked, [=]() { Paginas.setCurrentIndex(2); } );


        QPushButton *animo=new QPushButton;
        pixmap.load("imgs/estado_animo_icon.svg");
        animo->setIcon(pixmap);
        animo->setText("Estado de Animo");
        burger->addWidget(animo,2,0,Qt::AlignLeft);
        connect(animo, &QPushButton::clicked, [=]() { Paginas.setCurrentIndex(4); } );

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
        usuario["mood"]=it.estado_animo;
        usuario["details"]=it.detalles_animo;
        usuario["foto"]=it.foto;
        usuario["edad"]=it.edad;
        usuario["domicilio"]=it.domicilio;
        usuario["tutor"]=it.tutor;
        usuario["telefono"]=it.telefono;
        usuario["grado"]=it.grado;

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
        alumnos.append(alumno(usuario["names"].toString(),usuario["last_names"].toString(),usuario["first"].toString(),usuario["attendance"].toString(),usuario["mood"].toString(),usuario["details"].toString(),usuario["foto"].toString(),usuario["edad"].toString(),usuario["domicilio"].toString(),usuario["tutor"].toString(),usuario["telefono"].toString(),usuario["grado"].toString()));
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
    int primerMes;

    // Obtener el dia y mes actual, esto se hace porque la ultima asistencia tomada seria
    // el dia y mes actual.
    QDate d = QDate::currentDate();
    QString diaActual = d.toString("d");
    QString mesActual = d.toString("M");

    // Obtenemos nuestro primer mes del alumno, pues se asume que ese mes es el mes minimo
    // de donde empezaron haber alumnos registrados.
    QString inicioAsistencia = alumnos[0].inicio_asistencia;
    QStringList parts = inicioAsistencia.split(' ');
    QString diaMesAs = parts[1];
    int primerDia = parts[2].toInt();

    // Iteramos en nuestros meses para encontrar a que numero pertenece el mes.
    for(int i = 0; i < mesNum.size(); i++) {
        if(diaMesAs == mesNum[i].first) {
            primerMes = mesNum[i].second;
            break;
        }
    }

    // Se utiliza el mes y dia del primer alumno ingresado como el limite minimo donde debe haber asistencias, con eso, si se
    // escoge un mes menor al mes que ingreso el alumno, significa que no debe haber alumnos registrados
    // antes que el, lo mismo pasa en el mes que se registro, en ese mismo mes pero dias antes de el no hay alumnos registrados.
    if((date.month() < primerMes) or (date.month() == primerMes and date.day() < primerDia)) {
        for(auto alumno : alumnos) {
            QTableWidgetItem *item = new QTableWidgetItem(QString("-"));
            table->setItem(0,column,item);
            item->setBackground(Qt::white);
            column++;
        }
        column = 0;
    }
    // La misma logica aplica si se escoje un mes despues de la fecha actual o un dia despues, pues sera el ultimo dia o mes donde hubo asistencias.
    else if((date.month() > mesActual.toInt()) or (date.month() == mesActual.toInt() and date.day() > diaActual.toInt())) {
        for(auto alumno : alumnos) {
            QTableWidgetItem *item = new QTableWidgetItem(QString("-"));
            table->setItem(0,column,item);
            item->setBackground(Qt::white);
            column++;
        }
        column = 0;
    } else {
        // Iterar en cada alumno para encontrar su inicio de asistencia.
        for(auto alumno : alumnos) {
            inicioAsistencia = alumno.inicio_asistencia;

            // Nos interesa el mes y dia del inicio de la asistencia, separaramos el QString.
            // donde parts[1] = mes, parts[2] = dia.
            parts = inicioAsistencia.split(' ');
            int diaInicioAs = parts[2].toInt();
            diaMesAs = parts[1];

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
                                diaInicioAs = 1;
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
                                diaInicioAs = 1;
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
                                diaInicioAs = 1;
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
                                diaInicioAs = 1;
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
                                diaInicioAs=1;
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
                                diaInicioAs=1;
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
                                diaInicioAs=1;
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
                                diaInicioAs=1;
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
                                diaInicioAs=1;
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

            // Escribira en la tabla "-" si no hay registro del alumno en el dia que se escogio en el calendario.
            if(!(date.month() == diaMesAsi and date.day() >= diaInicioAs)) {
                QTableWidgetItem *item = new QTableWidgetItem((QString("-")));
                table->setItem(0,column,item);
                item->setBackground(Qt::white);
                column++;
            }
        } // for
    }
}



