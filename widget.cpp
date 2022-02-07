#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPathItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    sc=new Scene(this);
    sc->setSceneRect(-250,-300,500,600);
    QGraphicsPixmapItem* pix=new QGraphicsPixmapItem(QPixmap(":/sky.jpg"));
    sc->addItem(pix);
    pix->setPos(QPointF(0,0)-QPointF(pix->boundingRect().width()/2,
                                     pix->boundingRect().height()/2));
    sc->addLine(-400,0,400,0,QPen(Qt::gray));
    sc->addLine(0,-400,0,400,QPen(Qt::gray));
    sc->addBird();





    ui->graphicsView->setScene(sc);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Start_clicked()
{
   sc->start();

}

