#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , info(this)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->pushButtonHome2, SIGNAL(clicked()), this, SLOT(on_pushButtonHome2_clicked()));
    connect(ui->pushButtonHome3, SIGNAL(clicked()), this, SLOT(on_pushButtonHome3_clicked()));
    connect(ui->pushButtonHome4, SIGNAL(clicked()), this, SLOT(on_pushButtonHome4_clicked()));
    ui->btnUndo->setEnabled(false);
    QPixmap pix("/Users/andrey/Documents/SUAI/3.1/ООП/porsche.jpg");
    int w = ui->label_16->width();
    int h = ui->label_16->height();
    ui->label_16->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    QPixmap pixx("/Users/andrey/Documents/SUAI/3.1/ООП/Porsche-Logo.png");
    int ww = ui->label_17->width();
    int hh = ui->label_17->height();
    ui->label_17->setPixmap(pixx.scaled(ww,hh,Qt::KeepAspectRatio));
    // регистрация слушателя
    connect(&info, SIGNAL(notifyObservers()), this, SLOT(update()));//включаем сигнал для наблюдателя включающийся при изменении данных
    connect(ui->btnCalc, SIGNAL(pressed()), this, SLOT(btnCalcPressed()));//включаем сигналы включающиеся при нажатии кнопок
    connect(ui->btnUndo, SIGNAL(pressed()), this, SLOT(btnUndoPressed()));
    connect(ui->btnAddUser, &QPushButton::clicked, this, &Widget::btnUserPressed);
    connect(ui->btnIssue, &QPushButton::clicked, this, &Widget::btnIssuePressed);
    connect(ui->btnRefund, &QPushButton::clicked, this, &Widget::btnSetRefund);









    //connect(ui->moveToUsedButton, &QPushButton::clicked, this, &Widget::moveToUsedTable);
    //connect(ui->moveToTableButton, &QPushButton::clicked, this, &Widget::moveToTableView);
    //Widget обновляет свое состояние и затем уведомляет о этом изменении, вызывая метод update(). В ответ на этот вызов метода, наблюдатели реагируют на изменение.
}
Widget::~Widget()
{
    delete ui;
}









void Widget::on_pushButtonHome2_clicked() {
    ui->stackedWidget->setCurrentIndex(0); // Возвращение на главную страницу
}

void Widget::on_pushButtonHome3_clicked() {
    ui->stackedWidget->setCurrentIndex(0); // Возвращение на главную страницу
}

void Widget::on_pushButtonHome4_clicked() {
    ui->stackedWidget->setCurrentIndex(0); // Возвращение на главную страницу
}

void Widget::on_pushButtonAddCar_clicked() {
    ui->stackedWidget->setCurrentIndex(3); // Перенаправление на page_4
}

void Widget::on_pushButtonAddClient_clicked() {
    ui->stackedWidget->setCurrentIndex(2); // Перенаправление на page_3
}

void Widget::on_pushButtonOperations_clicked() {
    ui->stackedWidget->setCurrentIndex(1); // Перенаправление на page_2
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




void Widget::btnCalcPressed(){                             //функции добавляют новый автомобиль
    auto value=processForm();//создаем объект класса
    showCost(value);//вычисляем стоимость и выводим ее
    controller.addToTableView(value,ui->tableView, ui->tableView2);
    info.add(value);//добавляем объект в коллекцию предыдущих запросов
    carsinfo.add(value);
    ui->btnUndo->setEnabled(info.hasCars());
    //seting value to null
    value=nullptr;




    saveTableViewDataToFullRefundFile();
}




void Widget::btnUndoPressed(){
    info.undo();//запрос на получение информации о прошлом запросе
    ui->cost->setText("0");//стоимость 0
}




void Widget::btnUserPressed(){                        //функции добавляют нового пользователя
    auto value=processClientForm();
    controller.addToClientTable(value, ui->userTable);
    controller.addToClientTable(value, ui->userTable2); //*****
    //addToUserTable(value,ui->userTable);
    clientinfo.add(value);
    value=nullptr;




    saveUserTableDataToFullRefundFile();
}



void Widget::btnIssuePressed(){
    // Проверяем, выбраны ли клиент и автомобиль
    QModelIndex userIndex = ui->userTable->currentIndex();
    QModelIndex carIndex = ui->tableView->currentIndex();

    if (!userIndex.isValid() || !carIndex.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите клиента и автомобиль перед выдачей.");
        return;
    }

    // Получаем состояние выбранного автомобиля из массива carsinfo, используя выбранный индекс строки
    int carRowIndex = carIndex.row();
    if (carRowIndex < 0 || carRowIndex >= carsinfo.array.size()) {
        QMessageBox::warning(this, "Ошибка", "Произошла ошибка при выборе автомобиля. Пожалуйста, попробуйте снова.");
        return;
    }
    bool carCondition = carsinfo.array[carRowIndex]->condition;

    if (!carCondition) {
        QMessageBox::warning(this, "Ошибка", "Выбранный автомобиль уже выдан другому клиенту.");
        return;
    }

    // Добавляем информацию о выдаче автомобиля
    rent* result = controller.addToTableRefund(ui->refundTable, ui->userTable, ui->tableView, carsinfo, ui->issueDate);


    // Проверяем, успешно ли добавлена запись
    if (!result) {
        QMessageBox::warning(this, "Ошибка", "Не удалось выдать автомобиль. Пожалуйста, проверьте введенные данные и попробуйте снова.");
        return;
    }
    // Проверяем, есть ли хотя бы одна строка в refundTable
    if (ui->refundTable->model()->rowCount() > 0) {
        // Проверяем, выбраны ли клиент и автомобиль
        if (!ui->userTable->currentIndex().isValid() || !ui->tableView->currentIndex().isValid()) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите клиента и автомобиль перед выдачей.");
            return;
        }
    }


    // Если все проверки пройдены и автомобиль успешно выдан, добавляем информацию в список аренд
    rentinfo.add(result);//добавляет информацию об аренде в таблицу возвратов (refundTable)

    saveToFullRefundData();
    saveToCurrentRefundData();

}


void Widget::btnSetRefund(){
    // Проверяем, выбраны ли клиент и автомобиль
    if (!ui->userTable->currentIndex().isValid() || !ui->tableView->currentIndex().isValid()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите клиента и автомобиль перед возвратом.");
        return;
    }
    //setRefundData(ui->refundTable);
    controller.setRefundData(ui->refundTable,ui->tableView,rentinfo,ui->refundDate,carsinfo);//вносит изменения в таблицу возвратов (refundtable), изменяя данные о дате возврата и
                                                               //обновляя статус автомобиля в таблице авто (cartable). В конце функции обновляется модель данных в обеих таблицах.
    saveToFullRefundData();
    saveToCurrentRefundData();


}
















// Path to the files
const QString fullRefundDataPath = "/Users/andrey/Documents/3.1/ООП/LIXXX/full_refund_data.txt";
const QString currentRefundDataPath = "/Users/andrey/Documents/3.1/ООП/LIXXX/current_refund_data.txt";

void Widget::saveToFullRefundData() {
    QFile file(fullRefundDataPath);
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);

    // Iterate through all rows in refundTable and save data to the file
    for (int row = 0; row < ui->refundTable->model()->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < ui->refundTable->model()->columnCount(); ++col) {
            QString cellData = ui->refundTable->model()->data(ui->refundTable->model()->index(row, col)).toString();
            rowData << cellData;
        }
        out << rowData.join("\t") << "\n";  // Tab-separated values
    }

    file.close();
}

void Widget::saveToCurrentRefundData() {
    QFile file(currentRefundDataPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    // Iterate through all rows in refundTable and save data to the file
    for (int row = 0; row < ui->refundTable->model()->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < ui->refundTable->model()->columnCount(); ++col) {
            QString cellData = ui->refundTable->model()->data(ui->refundTable->model()->index(row, col)).toString();
            rowData << cellData;
        }
        out << rowData.join("\t") << "\n";  // Tab-separated values
    }

    file.close();
}

void Widget::saveTableViewDataToFullRefundFile() {
    QFile file("/Users/andrey/Documents/3.1/ООП/LIXXX/full_refund_data.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);

    // Save a header to identify the section of the data
    out << "=== tableView Data ===\n";

    // Iterate through all rows in tableView and save data to the file
    for (int row = 0; row < ui->tableView->model()->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < ui->tableView->model()->columnCount(); ++col) {
            QString cellData = ui->tableView->model()->data(ui->tableView->model()->index(row, col)).toString();
            rowData << cellData;
        }
        out << rowData.join("\t") << "\n";  // Tab-separated values
    }

    file.close();
}



void Widget::saveUserTableDataToFullRefundFile() {
    QFile file("/Users/andrey/Documents/3.1/ООП/LIXXX/full_refund_data.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);

    // Save a header to identify the section of the data
    out << "=== userTable Data ===\n";

    // Iterate through all rows in userTable and save data to the file
    for (int row = 0; row < ui->userTable->model()->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < ui->userTable->model()->columnCount(); ++col) {
            QString cellData = ui->userTable->model()->data(ui->userTable->model()->index(row, col)).toString();
            rowData << cellData;
        }
        out << rowData.join("\t") << "\n";  // Tab-separated values
    }

    file.close();
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



