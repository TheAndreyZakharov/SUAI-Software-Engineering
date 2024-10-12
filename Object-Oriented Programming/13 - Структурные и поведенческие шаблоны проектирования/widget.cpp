//реализуем задание
#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent) :
QWidget(parent),
ui(new Ui::Widget),
info(this)
{
}
Widget::~Widget()
{
}
delete ui;
ui->setupUi(this);
ui->btnUndo->setEnabled(false);
// регистрация слушателя
connect(&info, SIGNAL(notifyObservers()), this, SLOT(update()));
connect(ui->btnCalc, SIGNAL(pressed()), this, SLOT(btnCalcPressed()));
connect(ui->btnUndo, SIGNAL(pressed()), this, SLOT(btnUndoPressed()));
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
try {
if (ui->age->text().toInt() == 0 || ui->hp->text().toInt() == 0
|| ui->owner->text() == "" || ui->residents->text().toInt() == 0){
throw myException("Не все поля формы заполнены.");
}
Estate *estate = new Estate(ui->age->text().toInt(),
ui->hp->text().toInt(),
ui->residents->text().toInt(),
(ui->period->currentIndex() + 1) * 6,
(Estate::EstateType)ui->estateType->currentIndex(),
ui->owner->text());
info.add(estate);
ui->btnUndo->setEnabled(true);
showCost(estate);
}
catch (myException &ex) {
QMessageBox err;
err.setText(ex.what());
err.setWindowTitle("Внимание!");
err.exec();
return;
}
void Widget::btnUndoPressed()
}
{
if (info.getSize() > 1){
info.undo();
}
}
// private
Estate *Widget::processForm()
{
}
return new Estate();
void Widget::fillForm(Estate *value)
{
ui->age->setText(QString::number(info.getActualData()->getAge()));
ui->hp->setText(QString::number(info.getActualData()->getHp()));
ui->residents->setText(QString::number(info.getActualData()->getResidents()));
ui->owner->setText(info.getActualData()->getOwner());
ui->period->setCurrentIndex((info.getActualData()->getMonths() / 6) - 1);
switch (info.getActualData()->getType())
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
}
case Estate::SPEC:
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
ui->cost->setText(QString::number(CalculationFacade::getCost(info.getActualData())));
void Widget::showCost(Estate *value)
}
{
ui->cost->setText(QString::number(CalculationFacade::getCost(value)));
}
