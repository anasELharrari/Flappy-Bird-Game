#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "scene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_Start_clicked();

private:
    Ui::Widget *ui;
    Scene* sc;
};
#endif // WIDGET_H
