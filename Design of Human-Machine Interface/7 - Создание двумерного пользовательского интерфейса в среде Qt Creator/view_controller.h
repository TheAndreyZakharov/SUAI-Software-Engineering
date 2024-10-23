#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H
#include <QObject>
#include <rent.h>
#include <car.h>
#include <cars.h>
#include <client.h>
#include <QTableView>
#include <QStandardItemModel>
#include <calculationfacade.h>
#include <QLineEdit>
class View_Controller : public QObject
{
    Q_OBJECT
public:
    explicit View_Controller(QObject *parent = nullptr);
    void addToTableView(car* lastObject, QTableView* tableView);
    void addToClientTable(client* Object, QTableView* tableClient);
    rent* addToTableRefund(QTableView* tableRefund,QTableView* tableClient,QTableView* tableView,cars& carsinfo,QLineEdit* issueDate);
    void setRefundData(QTableView* refundtable,QTableView* cartable,rented& rentinfo,QLineEdit* refundDate,cars& carsinfo);//лайн эдит с датой, список выданных, тблица авто
signals:
};
#endif // VIEW_CONTROLLER_H
