#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
Widget::Widget(QWidget *parent)
: QWidget(parent)
, ui(new Ui::Widget)
, info(this)
{
ui->setupUi(this);
ui->btnUndo->setEnabled(false);
QPixmap pix("/Users/andrey/Documents/QTproj/porsche.jpg");
int w = ui->label_16->width();
int h = ui->label_16->height();
ui->label_16->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
QPixmap pixx("/Users/andrey/Documents/QTproj/Porsche-Logo.png");
int ww = ui->label_17->width();
int hh = ui->label_17->height();
ui->label_17->setPixmap(pixx.scaled(ww,hh,Qt::KeepAspectRatio));
// регистрация слушателя
connect(&info, SIGNAL(notifyObservers()), this, SLOT(update()));//включаем сигнал для
наблюдателя включающийся при изменении данных
connect(ui->btnCalc, SIGNAL(pressed()), this, SLOT(btnCalcPressed()));//включаем сигналы
включающиеся при нажатии кнопок
connect(ui->btnUndo, SIGNAL(pressed()), this, SLOT(btnUndoPressed()));
connect(ui->btnAddUser, &QPushButton::clicked, this, &Widget::btnUserPressed);
connect(ui->btnIssue, &QPushButton::clicked, this, &Widget::btnIssuePressed);
connect(ui->btnRefund, &QPushButton::clicked, this, &Widget::btnSetRefund);
//connect(ui->moveToUsedButton, &QPushButton::clicked, this, &Widget::moveToUsedTable);
//connect(ui->moveToTableButton, &QPushButton::clicked, this, &Widget::moveToTableView);
//Widget обновляет свое состояние и затем уведомляет о этом изменении, вызывая метод
update(). В ответ на этот вызов метода, наблюдатели реагируют на изменение.
Widget::~Widget()
}
{
delete ui;
}
//public slots
void Widget::update(){
auto value = info.getActualData();//получаем актуальную информацию
if(value != nullptr){//если значение не пустое
fillForm(value);//выводим на форму
}
//update btnUndo state
ui->btnUndo->setEnabled(info.hasCars());
//seting value to null
value=nullptr;
}
//private slots
void Widget::btnCalcPressed(){ //функции добавляют новый автомобиль
auto value=processForm();//создаем объект класса
showCost(value);//вычисляем стоимость и выводим ее
controller.addToTableView(value,ui->tableView);
info.add(value);//добавляем объект в коллекцию предыдущих запросов
carsinfo.add(value);
ui->btnUndo->setEnabled(info.hasCars());
//seting value to null
value=nullptr;
}
void Widget::btnUndoPressed(){
info.undo();//запрос на получение информации о прошлом запросе
ui->cost->setText("0");//стоимость 0
}
void Widget::btnUserPressed(){ auto value=processClientForm();
controller.addToClientTable(value, ui->userTable);
//addToUserTable(value,ui->userTable);
clientinfo.add(value);
value=nullptr;
//функции добавляют нового пользователя
}
void Widget::btnIssuePressed(){
//extraditioninfo.add(addToTableRefund(ui->refundTable));
rentinfo.add(controller.addToTableRefund(ui->refundTable,ui->userTable,ui->tableView,carsinfo,ui-
>issueDate));//добавляет информацию об аренде в таблицу возвратов (refundTable)
}
void Widget::btnSetRefund(){
//setRefundData(ui->refundTable);
controller.setRefundData(ui->refundTable,ui->tableView,rentinfo,ui->refundDate,carsinfo);//вносит
изменения в таблицу возвратов (refundtable), изменяя данные о дате возврата и
//обновляя статус автомобиля в таблице авто (cartable). В
конце функции обновляется модель данных в обеих таблицах.
}
//private
car *Widget::processForm(){//берем данные с формы и создаем новый объект класса
int age = ui->Age->text().toInt();
int ID = ui->Number->text().toInt();
QString Colour = ui->Colour->text();
car::CarType type = static_cast<car::CarType>(ui->CarType->currentIndex());
QString Brand = ui->Brand->text();
return new car(age, ID, Colour, type, Brand);
}
client *Widget::processClientForm(){
int Passport = ui->passport->text().toInt();
int PhoneNumber = ui->phonenumber->text().toInt();
QString FIOclient = ui->FIOclient->text();
QString EMail = ui->EMail->text();
return new client (Passport,PhoneNumber,FIOclient,EMail);
}
void Widget::fillForm(car *value){//заполняем форму актуальной информацией
QString str=value->getBrand();
ui->Brand->setText(str);
str=QString::number(value->getAge());
ui->Age->setText(str);
if (value->getType() == car::CarType::STANDARD) {
ui->CarType->setCurrentIndex(0);
} else if (value->getType() == car::CarType::COMFORT) {
ui->CarType->setCurrentIndex(1);
} else if (value->getType() == car::CarType::LUXURY) {
ui->CarType->setCurrentIndex(2);
} else if (value->getType() == car::CarType::ELECTRIC) {
ui->CarType->setCurrentIndex(3);
}
str=value->getColour();
ui->Colour->setText(str);
str=QString::number(value->getNumber());
ui->Number->setText(str);
}
QString Widget::showCost(car *value){
CalculationFacade cur;//создаем объект фасада вычисления
int rating=cur.getCost(value);//получаем стоимость от фасада
QString str=QString::number(rating);//переводим тип данных стоимости из str в qstring
ui->cost->setText(str);//выводим стоимость на форму
return str;
}
