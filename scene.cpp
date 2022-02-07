#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    setPillars();

}

void Scene::addBird()
{
    b=new Bird(QPixmap(":/bird.png"));
    addItem(b);
}

void Scene::start()
{
    b->fly();
    if(!pTimer->isActive()){
        pTimer->start(1300);
    }
}

void Scene::showgameOver()
{
    game_over=new QGraphicsPixmapItem(QPixmap(":/over.png"));
    addItem(game_over);
    game_over->setPos(QPointF(0,0)-QPointF(game_over->boundingRect().width()/2,
                                           game_over->boundingRect().height()/2));
}

void Scene::setPillars()
{
    pTimer=new QTimer(this);
    connect(pTimer,&QTimer::timeout,[=](){
        Pillar* p=new Pillar();
        connect(p,&Pillar::Fail,[=](){
            pTimer->stop();
            endAll();

        });
        addItem(p);
    });
    //pTimer->start(1300);
}

void Scene::endAll()
{
    b->stopFlying();
    QList<QGraphicsItem*> Sitems=items();
    foreach (QGraphicsItem* t, Sitems) {
        Pillar* p=dynamic_cast<Pillar*>(t);
        if(p){
            p->stopPillars();
        }

    }
    showgameOver();
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){
        b->moveBird();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        b->moveBird();
    }
    QGraphicsScene::mousePressEvent(event);
}
