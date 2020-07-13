#include "mainwindow.h"
#include <windows.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),centralget(0),mineView(0),mineNumLcd(0),m_timer(0),minScene(0),timeLcd(0),smilebutton(0)
{
    this->setWindowTitle("Fantasy Mine");
    this->setWindowIcon(QIcon(":/images/MineSweeping.png"));
    QPixmap pix(":/images/1.gif");
    QSplashScreen splash(pix);
    QLabel splashlabel(&splash);
    QMovie splashgif(":/images/1.gif");
    splashlabel.setMovie(&splashgif);
    splashgif.start();
    splash.show();
    splash.setCursor(Qt::BlankCursor);//不显示鼠标外观
    for(int i=0;i<15000;i+=splashgif.speed())
    {
        QCoreApplication::processEvents();
        Sleep(splashgif.speed()/5);
    }
    creatAction();
    creatMenu();
    sound = new QSound(":/sound/File0021.wav");
    BlackGround_sound = new QSound(":/sound/music.wav");
    sound->play();
    settings = new QSettings("ViewSet","Myset",this);
    slot_newGame();
}


MainWindow::~MainWindow()
{
}

void MainWindow::creatMenu()
{
    QMenuBar *menbar = this->menuBar();
    QMenu *menu = menbar->addMenu("Game");
    menu->addAction(newaction);
    menu->addSeparator();
    menu->addAction(lowleveaction);
    menu->addAction(middleleveaction);
    menu->addAction(heightleveaction);
    menu->addAction(customaction);
    menu->addSeparator();
    menu->addAction(coloraction);
    menu->addAction(soundaction);
    menu->addAction(heroaction);
    menu->addSeparator();
    menu->addAction(exitaction);
    QMenu *about_menu = menbar->addMenu("Help");
    about_menu->addAction(aboutaction);
}


void MainWindow::creatAction()
{
    newaction = new QAction("StartGame",this);
    this->connect(newaction,SIGNAL(triggered(bool)),this,SLOT(slot_newGame()));
    newaction->setChecked(true);
    newaction->setCheckable(true);

    lowleveaction= new QAction("LowLeve",this);
    lowleveaction->setCheckable(true);
    middleleveaction = new QAction("MiddleLeve",this);
    middleleveaction->setCheckable(true);

    heightleveaction = new QAction("HeightLeve",this);
    heightleveaction->setCheckable(true);
    customaction = new QAction("CustomGame",this);
    customaction->setCheckable(true);

    QActionGroup *actiongroup = new QActionGroup(this);
    actiongroup->addAction(lowleveaction);
    actiongroup->addAction(middleleveaction);
    actiongroup->addAction(heightleveaction);
    actiongroup->addAction(customaction);
    this->connect(actiongroup,SIGNAL(triggered(QAction*)),this,SLOT(slot_newGameLeve(QAction*)));

    coloraction = new QAction("SetBackGroundMusic",this);
    this->connect(coloraction,SIGNAL(triggered(bool)),this,SLOT(slot_colorChange()));
    coloraction->setCheckable(true);
    soundaction = new QAction("SetSound",this);
    this->connect(soundaction,SIGNAL(triggered(bool)),this,SLOT(slot_soundChange()));
    soundaction->setCheckable(true);
    heroaction = new QAction("WorldHero",this);
    this->connect(heroaction,SIGNAL(triggered(bool)),this,SLOT(slot_showHero()));
    heroaction->setCheckable(true);
    exitaction = new QAction("Exit",this);
    this->connect(exitaction,SIGNAL(triggered(bool)),this,SLOT(close()));
    exitaction->setCheckable(true);
    aboutaction = new QAction("AboutFantasyMine",this);
    this->connect(aboutaction,SIGNAL(triggered(bool)),this,SLOT(slot_about()));
    aboutaction->setCheckable(true);
}


void MainWindow::readSettings()
{
    settings->beginGroup("row_col");
    int row = settings->value("row",Common::LOWROWANDCOL).toInt();
    int col = settings->value("col",Common::LOWROWANDCOL).toInt();
    settings->endGroup();

    settings->beginGroup("mine_leve");
    int mines = settings->value("mine",Common::LOWMINENUM).toInt();
    int currentleve = settings->value("leve",Common::LOWLEVE).toInt();
    settings->endGroup();

    this->minScene->m_scenerow = row;
    this->minScene->m_scenecol = col;
    this->minScene->m_minesum = mines;
    this->minScene->m_currentLeve = currentleve;
}


void MainWindow::writeSettings()
{
    settings->beginGroup("row_col");
    settings->setValue("row",this->minScene->m_scenerow);
    settings->setValue("col",this->minScene->m_scenecol);
    settings->endGroup();

    settings->beginGroup("mine_leve");
    settings->setValue("mine",this->minScene->m_minesum);
    settings->setValue("leve",this->minScene->m_currentLeve);
    settings->endGroup();
}


void MainWindow::slot_newGame()
{
    centralget->deleteLater();
    mineView->deleteLater();
    minScene->deleteLater();
    mineNumLcd->deleteLater();
    timeLcd->deleteLater();
    smilebutton->deleteLater();
    m_timer->deleteLater();
    centralget = new QWidget(this);
    this->setCentralWidget(centralget);

    timeLcd = new QLCDNumber(centralget);
    mineNumLcd = new QLCDNumber(centralget);
    QPalette pale_time = this->timeLcd->palette();
    pale_time.setColor(QPalette::WindowText,Qt::red);
    this->setPalette(pale_time);

    smilebutton = new QPushButton(this);
    smilebutton->setIcon(QIcon(":/images/Asuna.jpg"));
    smilebutton->setIconSize(QSize(50,50));
    smilebutton->setFixedSize(70,70);
    this->connect(smilebutton,SIGNAL(clicked(bool)),this,SLOT(slot_newGame()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(mineNumLcd);
    hlayout->addStretch();
    hlayout->addWidget(smilebutton);
    hlayout->addStretch();
    hlayout->addWidget(timeLcd);

    minScene = new MineScene(this);
    mineView = new QGraphicsView(centralget);
    readSettings();
    this->connect(minScene,SIGNAL(signal_scenenewGame()),this,SLOT(slot_newGame()));
    this->connect(minScene,SIGNAL(signal_scenedisplayMineNum(int)),this,SLOT(slot_displayMineNum(int)));
    this->connect(minScene,SIGNAL(signal_successPassGame()),this,SLOT(slot_updateHero()));
    this->connect(minScene,SIGNAL(signal_scenebutton()),this,SLOT(slot_buttonChange()));
    this->connect(minScene,SIGNAL(signal_scenetimerflag()),this,SLOT(slot_timerflag()));

    QVBoxLayout *vlayout = new QVBoxLayout(centralget);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(mineView);
    minScene->setSceneRect(0,0,(minScene->m_scenecol)*25,(minScene->m_scenerow)*25);
    mineView->setFixedSize(minScene->width() + 15 , minScene->height() + 20);
    mineView->setScene(minScene);
    this->setFixedSize(mineView->width() + 20 ,mineView->height() + 120);

    if(minScene->m_currentLeve == Common::LOWLEVE)
        lowleveaction->setChecked(true);
    else if(minScene->m_currentLeve == Common::MIDDLEVE)
        middleleveaction->setChecked(true);
    else if(minScene->m_currentLeve == Common::HEIGHTLEVE)
        heightleveaction->setChecked(true);
    else if(minScene->m_currentLeve == Common::CUSTOMLEVE)
        customaction->setChecked(true);

    m_time = 0;
    mineNumLcd->display(minScene->m_minesum);
    timeLcd->display(m_time);
    m_timer = new QTimer(this);

    this->connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_displayTime()));
    this->minScene->initScene();
    QPixmap pixmap(":/images/blackgroud.jpg");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);
}


void MainWindow::slot_newGameLeve(QAction *action)
{
    if(action == lowleveaction)
    {
        this->minScene->m_scenerow = Common::LOWROWANDCOL;
        this->minScene->m_scenecol = Common::LOWROWANDCOL;
        this->minScene->m_minesum = Common::LOWMINENUM;
        this->minScene->m_currentLeve = Common::LOWLEVE;
    }
    else if(action == middleleveaction)
    {
        this->minScene->m_scenerow = Common::MIDDLEROWANDCOL;
        this->minScene->m_scenecol = Common::MIDDLEROWANDCOL;
        this->minScene->m_minesum = Common::MIDDLEMINENUM;
        this->minScene->m_currentLeve = Common::MIDDLEVE;
    }
    else if(action == heightleveaction)
    {
        this->minScene->m_scenerow = Common::HEIGHTROW;
        this->minScene->m_scenecol = Common::HEIGHTCOL;
        this->minScene->m_minesum = Common::HEIGHTMINENUM;
        this->minScene->m_currentLeve = Common::HEIGHTLEVE;
    }
    else if(action == customaction)
    {
        Customgamedialog *customdialog = new Customgamedialog(this);
        this->connect(customdialog,SIGNAL(signal_sendCustomset(int,int,int)),this,SLOT(slot_accpetCustomval(int,int,int)));
        customdialog->exec();
    }
    writeSettings();
    slot_newGame();
}


void MainWindow::slot_accpetCustomval(int rows,int cols ,int mines)
{
    this->minScene->m_currentLeve = Common::CUSTOMLEVE;
    settings->beginGroup("row_col");
    settings->setValue("row",rows);
    settings->setValue("col",cols);
    settings->endGroup();

    settings->beginGroup("mine_leve");
    settings->setValue("mine",mines);
    settings->setValue("leve",this->minScene->m_currentLeve);
    settings->endGroup();
    slot_newGame();
}


void MainWindow::slot_colorChange()
{
    if(coloraction->isCheckable())
    {
        this->coloraction->setCheckable(false);
        this->coloraction->setChecked(false);
        BlackGround_sound->stop();
    }
    else
    {
        this->coloraction->setCheckable(true);
        this->coloraction->setChecked(true);
        BlackGround_sound->setLoops(50);
        BlackGround_sound->play();
    }
}


void MainWindow::slot_soundChange()
{
    if(soundaction->isCheckable())
    {
        this->soundaction->setCheckable(false);
        this->soundaction->setChecked(false);
        minScene->m_soundOpen = false;
    }
    else
    {
        this->soundaction->setCheckable(true);
        this->soundaction->setChecked(true);
        minScene->m_soundOpen = true;
    }
}


void MainWindow::slot_showHero()
{
    Herodialog *herodia = new Herodialog(this);
    herodia->exec();
}


void MainWindow::slot_about()
{
    QMessageBox::about(this,"About Mines","Sorry!No Money!");
}


void MainWindow::slot_updateHero()
{
    Herodialog *hero = new Herodialog(this);
    QString time1 = QString::number(timeLcd->value());
    hero->settings->beginGroup("time_name");
    QString lowtime = hero->settings->value("low_time").toString();
    QString middletime = hero->settings->value("middle_time").toString();
    QString heighttime = hero->settings->value("height_time").toString();
    hero->settings->endGroup();
    bool ok;
    QString name = QInputDialog::getText(this,"Success","Input you name :",QLineEdit::Normal,"Alice",&ok);
    if(minScene->m_currentLeve == Common::LOWLEVE)
    {
        if(lowtime.toInt() >  time1.toInt())
        {   
           if(ok)
           {
               hero->settings->beginGroup("time_name");
               hero->settings->setValue("low_time",time1);
               hero->settings->setValue("low_name",name);
               hero->settings->endGroup();
           }
        }
    }
    else if(minScene->m_currentLeve == Common::MIDDLEVE)
    {
        if(middletime.toInt() >  time1.toInt())
        {
           if(ok)
           {
               hero->settings->beginGroup("time_name");
               hero->settings->setValue("middle_time",time1);
               hero->settings->setValue("middle_name",name);
               hero->settings->endGroup();
           }
        }
    }
    else if(minScene->m_currentLeve == Common::HEIGHTLEVE)
    {
        if(heighttime.toInt() >  time1.toInt())
        {
           if(ok)
           {
               hero->settings->beginGroup("time_name");
               hero->settings->setValue("height_time",time1);
               hero->settings->setValue("height_name",name);
               hero->settings->endGroup();
           }
        }
    }
    else if(minScene->m_currentLeve == Common::CUSTOMLEVE){}
    goodGame();
}


void MainWindow::slot_displayMineNum(int mines)
{   
    int mine = minScene->m_minesum - mines;
    mineNumLcd->display(mine);
}


void MainWindow::slot_displayTime()
{
    if(!minScene->m_isGameOver)
    {
        timeLcd->display(m_time++);
    }

    else if(minScene->m_isGameOver)
        m_timer->stop();
}


void MainWindow::slot_buttonChange()
{
    smilebutton->setIcon(QIcon(":/images/Asuna1.jpg"));
}


void MainWindow::slot_timerflag()
{  
    minScene->timer_flag = true;
    if(minScene->timer_flag)
        m_timer->start(1000);
}


void MainWindow::goodGame()
{
    QMessageBox *custom_box = new QMessageBox(this);
    custom_box->setWindowTitle(tr("Success"));
    custom_box->setText(tr("Good Game!Restart Game?"));
    QPixmap px = QPixmap(":/images/a.jpg");

    QSize picSize(150,100);
    QPixmap scaledPixmap = px.scaled(picSize, Qt::KeepAspectRatio);
    custom_box->setIconPixmap(scaledPixmap);
    QPushButton *yes_button = custom_box->addButton("RESTART",QMessageBox::ActionRole);
    QPushButton *no_button = custom_box->addButton("EXITGAME",QMessageBox::ActionRole);

    custom_box->exec();
    QAbstractButton *clickButton = custom_box->clickedButton();  //获取按钮的状态
    if(clickButton == yes_button)
        slot_newGame();
    else if(clickButton == no_button)
        this->close();
}
