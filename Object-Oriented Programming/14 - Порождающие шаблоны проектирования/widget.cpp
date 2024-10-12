#include "widget.h"
#include "./ui_widget.h"
#include "estate.h"
#include "states.h"
#include "calculationfacade.h"
Widget::Widget(QWidget *parent) :
QWidget(parent),
ui(new Ui::Widget),
info(this)
{
ui->setupUi(this);
ui->btnUndo->setEnabled(false);
// регистрация слушателя
connect(&info, SIGNAL(notifyObservers()), this, SLOT(update()));
connect(ui->btnCalc, SIGNAL(pressed()), this, SLOT(btnCalcPressed()));
connect(ui->btnUndo, SIGNAL(pressed()), this, SLOT(btnUndoPressed()));
Widget::~Widget()
}
{
delete ui;
}
// public slots
void Widget::update()
{
auto value = info.getActualData();
if(value != nullptr){
fillForm(value);
}
// update btnUndo state
ui->btnUndo->setEnabled(info.hasStates());
// setting value to NULL
value = nullptr;
}
// private slots
void Widget::btnCalcPressed()
{
auto value = processForm();
showCost(value);
info.add(value);
ui->btnUndo->setEnabled(true);
// setting value to NULL
value = nullptr;
void Widget::btnUndoPressed()
}
{
info.undo();
auto value = info.getActualData();
showCost(value);
fillForm(value);
if (info.hasStates())
ui->btnUndo->setEnabled(true);
else
ui->btnUndo->setEnabled(false);
}
// private
Estate *Widget::processForm()
{
Estate *estate = new Estate(ui->age->text().toInt(),
ui->hp->text().toInt(),
ui->residents->text().toInt(),
(ui->period->currentIndex() + 1) * 6,
(Estate::EstateType)ui->estateType->currentIndex(),
ui->owner->text());
//info.add(estate);
return estate;
void Widget::fillForm(Estate *value)
}
{
ui->age->setText(QString::number(value->getAge()));
ui->hp->setText(QString::number(value->getHp()));
ui->residents->setText(QString::number(value->getResidents()));
ui->owner->setText(value->getOwner());
ui->period->setCurrentIndex((value->getMonths() / 6) - 1);
switch (value->getType())
{
case Estate::ECONOM:
{
ui->estateType->setCurrentIndex(0);
break;
case Estate::LUXURIOUS:
}
{
ui->estateType->setCurrentIndex(1);
break;
case Estate::SPEC:
}
{
ui->estateType->setCurrentIndex(2);
break;
case Estate::PLANE:
}
{
ui->estateType->setCurrentIndex(3);
break;
}
}
void Widget::showCost(Estate *value)
}
{
ui->cost->setText(QString::number(CalculationFacade::getCost(value)));
}
