#include "mainwindow.h"
#include "ui_mainwindow.h"
#define ancho_res GetSystemMetrics(SM_CXSCREEN)
#define alto_res GetSystemMetrics(SM_CYSCREEN)

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
            alumnos.append(alumno(nombre_LE->text(),apellidos_LE->text()));
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
        connect(asistencia, &QPushButton::clicked, [=]() {} );

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

    for (int i=0;i<arreglo_usuarios.size();i++) {

        QJsonObject usuario( arreglo_usuarios.at(i).toObject() );

        if(username == usuario["username"].toString() && password == usuario["password"].toString() ){
            Paginas.setCurrentIndex(1);
            break;
        }
    }

    file.close();
}

void MainWindow::guardar_alumnos()
{
    QJsonObject objetousuarios,usuario;
    QJsonDocument jsonDoc;
    QJsonArray ArregloUsuarios;
    QFile dbFile("src/alumnos.json");

    //Abrimos archivo
    dbFile.open(QIODevice::WriteOnly);

    for(auto it:alumnos){
        usuario["names"]=it.nombres;
        usuario["last_names"]=it.apellidos;
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
        alumnos.append(alumno(usuario["names"].toString(),usuario["last_names"].toString()));
    }

    file.close();
}
