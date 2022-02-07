#ifndef PILLAR_H
#define PILLAR_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QObject>
#include <QPropertyAnimation>
class Pillar :public QObject , public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setx)
public:
    explicit Pillar();
    ~Pillar();
    qreal x() const;
    void setx(qreal newX);
    void stopPillars();

private:
    QGraphicsPixmapItem* TPillar;
    QGraphicsPixmapItem* BPillar;
    qreal m_x;
    QPropertyAnimation* xAnimation;
    int ypos;
    int xRand;
    bool isCollide();

signals:
    void Fail();

};

#endif // PILLAR_H
