#include "classes.h"
#include <QtGui>

Pedra* Pedra::instanciaPedra = nullptr;
Papel* Papel::instanciaPapel = nullptr;
Tesoura* Tesoura::instanciaTes = nullptr;

Objeto::Objeto()
{
    this->setAcceptHoverEvents(true);
}

QRectF Objeto::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void Objeto::setImg(QPixmap *img){
    Imagem = img;
}

void Objeto::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    painter->drawPixmap(0,0,100,100,this->getImg());
}

void Pedra::colisao()
{
    QPointF posicao;
    QGraphicsItem *aux;
    QList<QGraphicsItem *> itensColidindo = collidingItems();
    for(int i = 0, n = itensColidindo.size(); i < n; ++i){
        if(typeid(*(itensColidindo[i])) == typeid(Papel)){
            posicao = this->pos();
            this->hide();
            aux = itensColidindo[i];
            aux->setPos(posicao);
            return;
        }
        else if(typeid(*(itensColidindo[i])) == typeid(Tesoura)){
            aux = itensColidindo[i];
            posicao = aux->pos();
            aux->hide();
            this->setPos(posicao);
            return;
        }

    }
    return;

}

void Papel::colisao()
{
    QPointF posicao;
    QGraphicsItem *aux;
    QList<QGraphicsItem *> itensColidindo = collidingItems();
    for(int i = 0, n = itensColidindo.size(); i < n; ++i){
        if(typeid(*(itensColidindo[i])) == typeid(Tesoura)){
            posicao = this->pos();
            this->hide();
            aux = itensColidindo[i];
            aux->setPos(posicao);
            return;
        }
        else if(typeid(*(itensColidindo[i])) == typeid(Pedra)){
            aux = itensColidindo[i];
            posicao = aux->pos();
            aux->hide();
            this->setPos(posicao);
            return;
        }

    }
    return;

}

void Tesoura::colisao()
{
    QPointF posicao;
    QGraphicsItem *aux;
    QList<QGraphicsItem *> itensColidindo = collidingItems();
    for(int i = 0, n = itensColidindo.size(); i < n; ++i){
        if(typeid(*(itensColidindo[i])) == typeid(Pedra)){
            posicao = this->pos();
            this->hide();
            aux = itensColidindo[i];
            aux->setPos(posicao);

            return;
        }
        else if(typeid(*(itensColidindo[i])) == typeid(Papel)){
            aux = itensColidindo[i];
            posicao = aux->pos();
            aux->hide();
            this->setPos(posicao);

            return;
        }
    }
}

void Objeto::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qApp->setOverrideCursor(Qt::OpenHandCursor);
}

void Objeto::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qApp->setOverrideCursor(Qt::ArrowCursor);
    this->colisao();
}

void Objeto::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF cursorAnterior = event->lastScenePos();
    QPointF cursorAtual = event->scenePos();
    QPointF pontoAnterior = this->pos();

    float pontoX = (cursorAtual.rx() - cursorAnterior.rx() + pontoAnterior.rx());
    float pontoY = (cursorAtual.ry() - cursorAnterior.ry() + pontoAnterior.ry());
try{
    if(pontoX < 0 || pontoY < 0 || pontoX > 650 || pontoY > 450)
        throw -1;
    else this->setPos(pontoX,pontoY);
}
    catch(int x){}
}
