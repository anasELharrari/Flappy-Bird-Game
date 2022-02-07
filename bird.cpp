#include "bird.h"
#include <QTimer>
#include <QGraphicsScene>
Bird::Bird(QPixmap p) :
    position(Position::up),
    bdirection(0)
{
    setPixmap(p);
    QTimer* btimer=new QTimer(this);
    connect(btimer,&QTimer::timeout,[=](){
        updateP();
    });
    btimer->start(80);

    groundposition=scenePos().y()+280;

    yAnimation=new QPropertyAnimation(this,"y",this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundposition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1300);

    yAnimation->start();

    rotationAnimation=new QPropertyAnimation(this,"rotation",this);
    rotateto(80,1300,QEasingCurve::InQuad);

}

void Bird::updateP()
{
  if(position==Position::Middle){
      if(bdirection){
          setPixmap(QPixmap(":/bird.png"));
          position=Position::up;
          bdirection=0;
      }else{
          setPixmap(QPixmap(":/bird.png"));
          position=Position::down;
          bdirection=1;
      }
  }else{
     setPixmap(QPixmap(":/bird.png"));
     position=Position::Middle;
  }
}

qreal Bird::rotation() const
{
    return m_rotation;
}

void Bird::setRotation(qreal newRotation)
{
    m_rotation = newRotation;

    QPointF c=boundingRect().center();
    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(newRotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

qreal Bird::y() const
{
    return m_y;
}

void Bird::setY(qreal newY)
{
    moveBy(0,newY-m_y);
    m_y = newY;
}

void Bird::rotateto(const qreal &end, const int &duration, const QEasingCurve &curve)
{
   rotationAnimation->setStartValue(rotation());
   rotationAnimation->setEndValue(end);
   rotationAnimation->setEasingCurve(curve);
   rotationAnimation->setDuration(duration);

   rotationAnimation->start();
}

void Bird::fall()
{
    if(y()<groundposition){
        yAnimation->stop();
        rotationAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEndValue(groundposition);
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setDuration(1300);
        //yAnimation->start();

        //rotateto(90,1200,QEasingCurve::InCubic);
    }
}

void Bird::fly()
{
    yAnimation->start();
    rotateto(90,1200,QEasingCurve::InCubic);
}

void Bird::stopFlying()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void Bird::moveBird()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal bposy=y();
    yAnimation->setStartValue(bposy);
    yAnimation->setEndValue(bposy-scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(250);

    connect(yAnimation,&QPropertyAnimation::finished,[=](){
        fall();
    });
    yAnimation->start();

    rotateto(-20,200,QEasingCurve::OutCubic);

}
