#include "pillar.h"
#include "bird.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
Pillar::Pillar(): TPillar(new QGraphicsPixmapItem(QPixmap(":/pillar.png"))),
    BPillar(new QGraphicsPixmapItem(QPixmap(":/pillar.png")))
{
    TPillar->setPos(QPointF(0,0)-QPointF(TPillar->boundingRect().width()/2,
                                         TPillar->boundingRect().height()+60));
    BPillar->setPos(QPointF(0,0)+QPointF(-BPillar->boundingRect().width()/2,
                                         60));

    addToGroup(TPillar);
    addToGroup(BPillar);

    ypos=QRandomGenerator::global()->bounded(160);
    xRand=QRandomGenerator::global()->bounded(200);

    setPos(QPointF(0,0)+QPointF(260+xRand,ypos));

    xAnimation=new QPropertyAnimation(this,"x",this);
    xAnimation->setStartValue(260+xRand);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1700);

    connect(xAnimation,&QPropertyAnimation::finished,[=](){
       scene()->removeItem(this);
       delete this;
    });

    xAnimation->start();



}

Pillar::~Pillar()
{

}

qreal Pillar::x() const
{
    return m_x;
}

void Pillar::setx(qreal newX)
{
    if(isCollide()){
        emit Fail();
    }
    m_x = newX;
    setPos(QPointF(0,0)+QPointF(newX,ypos));
}

void Pillar::stopPillars()
{
    xAnimation->stop();
}

bool Pillar::isCollide()
{
    QList<QGraphicsItem*> CItems=TPillar->collidingItems();
    CItems.append(BPillar->collidingItems());
    foreach(QGraphicsItem* t , CItems){
        Bird* b=dynamic_cast<Bird*>(t);
       if(b){
           return true;
       }
    }
    return false;
}
