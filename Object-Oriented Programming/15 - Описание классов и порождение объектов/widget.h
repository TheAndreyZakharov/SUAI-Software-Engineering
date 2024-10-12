#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <cars.h>
#include <car.h>
#include <client.h>
#include <calculationfacade.h>
#include <QStandardItemModel>
#include <qtableview.h>
#include <rent.h>
#include <view_controller.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class Widget : public QWidget
{
Q_OBJECT
public:
Widget(QWidget *parent = nullptr);
~Widget();
clients clientinfo;
cars carsinfo;
rented rentinfo;
public slots:
void update();//функция вызываемая при передаче сигнала наблюдателю
//вызывается при поступлении сигнала, после выполняется
//взаимодействие с States и заполнение данных на форме.
private slots:
void btnCalcPressed();//слот выполняющийся при нажатии кнопки "расчитать стоимость"
void btnUndoPressed();//слот выполняющийся при нажатии кнопки "последний запрос"
void btnUserPressed();
void btnIssuePressed();
void btnSetRefund();
private:
Ui::Widget *ui;
car *processForm();//функция обрабатывающая данные формы, создает объект класс
client *processClientForm();
void fillForm(car *value);//функция отвечающая за отображение данных объекта класса на форме
QString showCost(car *value);//функция отображающая стоимость получая ее от класса
calculationfacade
cars info;//коллекция предыдущих запросов
void addToTableView(car* lastObject, QTableView* tableView);
void addToUserTable(client* Object, QTableView* tableUser);
rent* addToTableRefund(QTableView* tableRefund);
void setRefundData(QTableView* refundtable);
View_Controller controller;
//void moveToUsedTable();
//void moveToTableView();
};
#endif // WIDGET_H
