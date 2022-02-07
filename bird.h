#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Bird : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Bird(QPixmap p);
    qreal rotation() const;
    void setRotation(qreal newRotation);

    qreal y() const;
    void setY(qreal newY);
public slots:
    void rotateto(const qreal &end, const int &duration, const QEasingCurve &curve);
    void fall();
    void fly();
    void stopFlying();
public:
    void moveBird();
private:
    enum Position{
        up,
        down,
        Middle
    };
    void updateP();
    Position position;
    bool bdirection;
    qreal m_rotation;

    qreal m_y;
    QPropertyAnimation* yAnimation;
    QPropertyAnimation* rotationAnimation;
    qreal groundposition;

signals:

};

#endif // BIRD_H
