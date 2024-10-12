#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <states.h>
#include <estate.h>
#include <calculationfacade.h>
#include <myexception.h>
namespace Ui {
class Widget;
}
class Widget : public QWidget
{
Q_OBJECT
public:
explicit Widget(QWidget *parent = 0);
~Widget();
public slots:
void update();
private slots:
void btnCalcPressed();
void btnUndoPressed();
private:
//для 4 задания
Estate *processForm();
void fillForm(Estate *value);
void showCost(Estate *value);
private:
Ui::Widget *ui;
States info;
};
#endif // WIDGET_H
