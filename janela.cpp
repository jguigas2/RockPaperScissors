#include "janela.h"
#include "classes.h"

#include <ctime>

Janela::Janela(QWidget *parent)
    : QMainWindow{parent}
{

    this->setGeometry(0,0,800,600);
    this->setWindowTitle("PEDRA PAPEL TESOURA");

    QMenuBar *menu = new QMenuBar(this);
    QMenu *secaoMenu = new QMenu("Opcoes", menu);
    menu->addMenu(secaoMenu);
    this->setMenuBar(menu);

    QAction *ler = new QAction("Ler Arquivo", secaoMenu);
    QAction *gravar = new QAction("Gravar Arquivo", secaoMenu);
    secaoMenu->addAction(ler);
    secaoMenu->addAction(gravar);

    connect(gravar, SIGNAL(triggered(bool)), this, SLOT(escreve()));
    connect(ler, SIGNAL(triggered(bool)), this, SLOT(ler()));

    tela = new QGraphicsView(this);
    cena = new QGraphicsScene();

    tela->setGeometry(20,20,760,560);
    tela->setBackgroundBrush(Qt::white);
    tela->setScene(cena);
    cena->setSceneRect(5,5,750,550);
    cena->setBackgroundBrush(Qt::gray);

    ImgPedra = new QPixmap(":/Pedra.png");
    ImgPapel = new QPixmap(":/Papel.png");
    ImgTes = new QPixmap(":/Tesoura.png");

    std::vector<Objeto*>::iterator it;

    objetos.push_back(Pedra::getInstancia(ImgPedra));
    objetos.push_back(Papel::getInstancia(ImgPapel));
    objetos.push_back(Tesoura::getInstancia(ImgTes));

    for(it = objetos.begin(); it != objetos.end(); it++){
        cena->addItem(*it);
    }

    srand(time(NULL));

    Objeto* aux;
    for(it = objetos.begin(); it != objetos.end(); it++){
        aux = *it;
        aux->setPos(rand()%650, rand()%450);
    }

}

void Janela::escreve()
{
    std::vector<Objeto*>::iterator it;
    QFile mFile(nome);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "erro ao abrir";
        return;
    }

    QTextStream out(&mFile);

    Objeto *aux;

    for(it = objetos.begin(); it != objetos.end(); it++){
        aux = *it;
        out << aux->x();
        out << ",";
        out << aux->y();
        out << ",";
        if(aux->isVisibleTo(NULL) == true)
            out << "+";
        else
            out << "-";
        out << ",";
    }

    mFile.flush();
    mFile.close();
    return;
}

void Janela::ler()
{
    std::vector<Objeto*>::iterator it;
    QFile mFile(nome);
    if(!mFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "erro ao abrir";
        return;
    }

    it = objetos.begin();
    QTextStream in(&mFile);
    QString mText;
    mText = in.readAll();

    Objeto *aux;

    QStringList lista = mText.split(QLatin1Char(','), Qt::SkipEmptyParts);

    int j = 3;

    for(int i = 0; i < 3; i++){
    aux = *it;
    aux->setX(lista[j-3].toInt());
    aux->setY(lista[j-2].toInt());
        if(lista[j-1] == '+')
         aux->show();
        it++;
    j = j+3;
    }


}
