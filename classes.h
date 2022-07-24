#ifndef CLASSES_H
#define CLASSES_H
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

class ClasseAbstrata
{
public:
    virtual void colisao() = 0;
};

class Objeto : public QGraphicsItem, ClasseAbstrata
{
    QPixmap *Imagem;
public:
    Objeto();
    void setImg(QPixmap *img);
    QPixmap getImg(){return *Imagem;}
protected:
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

class Pedra : public Objeto
{
    static Pedra* instanciaPedra;
    Pedra(QPixmap* foto) : Objeto(){
        Objeto::setImg(foto);
    }
public:
    Pedra (const Pedra &obj) = delete;
    Pedra operator=(Pedra obj) = delete;
    static Pedra *getInstancia(QPixmap* foto){
        if(instanciaPedra == nullptr)
                instanciaPedra = new Pedra(foto);
        return instanciaPedra;
    }
    void colisao();

};

class Tesoura : public Objeto
{
    static Tesoura* instanciaTes;
    Tesoura(QPixmap* foto) : Objeto(){
        Objeto::setImg(foto);
    }
public:
    Tesoura (const Tesoura &obj) = delete;
    Tesoura operator=(Tesoura obj) = delete;
    static Tesoura *getInstancia(QPixmap* foto){
        if(instanciaTes == nullptr)
                instanciaTes = new Tesoura(foto);
        return instanciaTes;
    }
    void colisao();    

};

class Papel : public Objeto
{
    static Papel* instanciaPapel;
    Papel(QPixmap* foto) : Objeto(){
        Objeto::setImg(foto);
    }
public:
    Papel (const Papel &obj) = delete;
    Papel operator=(Papel obj) = delete;
    static Papel *getInstancia(QPixmap* foto){
        if(instanciaPapel == nullptr)
                instanciaPapel = new Papel(foto);
        return instanciaPapel;
    }
    void colisao();

};
#endif // CLASSES_H
