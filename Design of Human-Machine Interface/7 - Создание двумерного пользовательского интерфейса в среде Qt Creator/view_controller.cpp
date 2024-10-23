#include <QMessageBox>
#include "view_controller.h"
View_Controller::View_Controller(QObject *parent)
    : QObject{parent}
{
}
void View_Controller::addToTableView(car* lastObject, QTableView* tableView)//cool
{
    CalculationFacade cur;
    // Получаем указатель на модель данных
    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(tableView->model());
    if (!model)
    {
    // Если модель данных не является типом QStandardItemModel, создаем новую модель
    model = new QStandardItemModel(tableView);
    tableView->setModel(model);
    model->setHorizontalHeaderLabels({"Название","Комплектация","Номер","Цвет","Год выпуска","Взнос","Наличие"});
    }
    // Получаем количество строк в таблице
    int rowCount = model->rowCount();
    // Создаем новую строку в модели данных
    QList<QStandardItem*> newRow;
    // Создаем элементы для каждого столбца таблицы
    QString condition = "В наличии";
    QStandardItem* typeItem = new QStandardItem(lastObject->getTypeString());
    QStandardItem* ageItem = new QStandardItem(QString::number(lastObject->getAge()));
    //QStandardItem* residentsItem = new QStandardItem(QString::number(lastObject->getResidents()));
    //QStandardItem* monthsItem = new QStandardItem(QString::number(lastObject->getMonthsForMVC()));
    //QStandardItem* priceItem = new QStandardItem(QString::number(lastObject->getPrice()));
    QStandardItem* BrandItem = new QStandardItem(lastObject->getBrand());
    QStandardItem* ColourItem = new QStandardItem(lastObject->getColour());
    QStandardItem* NumberItem = new QStandardItem(QString::number(lastObject->getNumber()));
    //QStandardItem* TitleItem = new QStandardItem(lastObject->getTitle());
    QStandardItem* CostItem = new QStandardItem(QString::number(cur.getCost(lastObject)));
    QStandardItem* conditionItem = new QStandardItem(condition);
    // Добавляем созданные элементы в новую строку
    newRow.append(BrandItem);
    newRow.append(typeItem);
    //newRow.append(priceItem);
    newRow.append(NumberItem);
    newRow.append(ColourItem);
    newRow.append(ageItem);
    newRow.append(CostItem);
    newRow.append(conditionItem);
   // Добавляем новую строку в модель данных
    model->insertRow(rowCount, newRow);
    // Обновляем таблицу
    tableView->viewport()->update();
}
void View_Controller::addToClientTable(client* Object,QTableView* tableClient){//cool
    // Получаем указатель на модель данных
    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(tableClient->model());
    if (!model)
    {
    // Если модель данных не является типом QStandardItemModel, создаем новую модель
    model = new QStandardItemModel(tableClient);
    tableClient->setModel(model);
    model->setHorizontalHeaderLabels({"Паспорт","ФИО","EMail","Номер"});
    }
    int rowCount = model->rowCount();
    // Создаем новую строку в модели данных
    QList<QStandardItem*> newRow;
    // Создаем элементы для каждого столбца таблицы
    QStandardItem* PassportItem = new QStandardItem(QString::number(Object->getPassport()));
    QStandardItem* FIOItem = new QStandardItem(Object->getFIO());
    QStandardItem* EMailItem = new QStandardItem(Object->getEMail());
    QStandardItem* PhoneNumberItem = new QStandardItem(QString::number(Object->getPhoneNumber()));
    // Добавляем созданные элементы в новую строку
    newRow.append(PassportItem);
    newRow.append(FIOItem);
    //newRow.append(priceItem);
    newRow.append(EMailItem);
    newRow.append(PhoneNumberItem);
   // Добавляем новую строку в модель данных
    model->insertRow(rowCount, newRow);
    // Обновляем таблицу
    tableClient->viewport()->update();
}
rent* View_Controller::addToTableRefund(QTableView* tableRefund,QTableView* tableClient,QTableView* tableView,cars& carsinfo,QLineEdit* issueDate){//остальные две таблицы тоже нужны, и список книг и лайн эдит с датой
    int curid;
    QString curids;
// Получаем выделенные элементы из двух предыдущих таблиц
    QModelIndexList selectedPersonIndexes = tableClient->selectionModel()->selectedIndexes();
    QModelIndexList selectedCarIndexes = tableView->selectionModel()->selectedIndexes();
    QModelIndex index = tableView->currentIndex();
    //получаем указатель на модель данных для замены поля наличия
    QStandardItemModel* model1 = dynamic_cast<QStandardItemModel*>(tableView->model());
    // Изменяем значение в четвертом столбце выбранной строки
    QStandardItem* item = model1->itemFromIndex(index.sibling(index.row(), 6)); // 3 - индекс четвертого столбца
// Получаем номер читательского билета и идентификатор книги из выделенных элементов
    QString personNumber = selectedPersonIndexes.at(0).data().toString();
    QString carNumber = selectedCarIndexes.at(2).data().toString();
    for(int i =0;i<carsinfo.array.size();i++){
        curid=carsinfo.array[i]->Number;
        curids=QString::number(curid);
        if(curids==carNumber){
            if (carsinfo.array[i]->condition==false){
                QMessageBox::warning(nullptr, "Ошибка", "Выбранный автомобиль уже выдан другому клиенту.");
                //проверяете состояние автомобиля, используя condition
                                                             //Если автомобиль уже взят в аренду (т.е. condition == true),
                                                             //не разрешаем его повторное взятие, и функция возвращает управление, и новая запись о выдаче в таблицу не добавляется.
                return nullptr;
            }
            else{
                carsinfo.array[i]->condition=false;
                item->setData("Выдана", Qt::DisplayRole);
                //selectedCarIndexes.at(6).data()="Выдана";
                //ui->clientTable->selectionModel()->selectedIndexes().at(6).data()=cond;
                break;
            }
        }
    }
    // Получаем данные для поля "Дата выдачи" из LineEdit
    QString issueDate1 = issueDate->text();
    //extradition* value (personNumber.toInt(),carNumber.toInt(),issueDate);
    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(tableRefund->model());
    if (!model)
    {
    // Если модель данных не является типом QStandardItemModel, создаем новую модель
    model = new QStandardItemModel(tableRefund);
    tableRefund->setModel(model);
    model->setHorizontalHeaderLabels({"Паспорт", "Серийный номер", "Дата выдачи", "Дата возврата"});
    }
    int rowCount = model->rowCount();
    // Создаем новую строку в модели данных
    QList<QStandardItem*> newRow;
    // Создаем объекты для хранения данных
    QString returnDate = ""; // Поле "Дата возврата" не заполняется
    QStandardItem* personNumberItem = new QStandardItem(personNumber);
    QStandardItem* carNumberItem = new QStandardItem(carNumber);
    QStandardItem* issueDateItem = new QStandardItem(issueDate1);
    QStandardItem* returnDateItem = new QStandardItem(returnDate);
    // Добавляем созданные элементы в новую строку
    newRow.append(personNumberItem);
    newRow.append(carNumberItem);
    newRow.append(issueDateItem);
    newRow.append(returnDateItem);
    // Добавляем новую строку в модель данных
    model->insertRow(rowCount, newRow);
    tableRefund->viewport()->update();
    tableView->viewport()->update();

    return new rent(personNumber.toInt(),carNumber.toInt(),issueDate1);
}
void View_Controller::setRefundData(QTableView* refundtable,QTableView* booktable,rented& rentinfo,QLineEdit* refundDate,cars& carsinfo){//лайн эдит с датой, список выдач, тблица книг
    // Получаем индекс выбранной строки в таблице
    QModelIndex index = refundtable->currentIndex();
    // Получаем значение из LineEdit
    QString value = refundDate->text();////////////////////////////////////////////////////////////
    // Получаем модель данных, которая отображается в таблице
    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(refundtable->model());
    QModelIndexList selectedCarIndexes = refundtable->selectionModel()->selectedIndexes();
    QString carNumber1 = selectedCarIndexes.at(1).data().toString();
    int curid;
    for(int i =0;i<rentinfo.array.size();i++){
        curid=rentinfo.array[i]->CarNumber;
        //curids=QString::number(curid);
        if(curid==carNumber1.toInt()){
            if (rentinfo.array[i]->getRefund()==" "){
                rentinfo.array[i]->setRefund(value);
                //item->setData("Выдана", Qt::DisplayRole);
                //selectedBookIndexes.at(6).data()="Выдана";
                //ui->userTable->selectionModel()->selectedIndexes().at(6).data()=cond;
                break;
            }
        }
    }
    curid=0;
    //QModelIndexList selectedBookIndexes = booktable->selectionModel()->selectedIndexes();
    //QString bookId = selectedBookIndexes.at(2).data().toString();
    for(int i =0;i<carsinfo.array.size();i++){
        curid=carsinfo.array[i]->Number;
        //curids=QString::number(curid);
        if(curid==carNumber1.toInt()){
            if (carsinfo.array[i]->condition==true){                //после возврата автомобиля обновляется состояние автомобиля
                                                                    //Теперь, этот автомобиль можно вновь выдать в аренду.
                return;
            }
            else{
                carsinfo.array[i]->condition=true;
                //item->setData("Выдана", Qt::DisplayRole);
                //selectedBookIndexes.at(6).data()="Выдана";
                //ui->userTable->selectionModel()->selectedIndexes().at(6).data()=cond;
                break;
            }
        }
    }
    // Изменяем значение в четвертом столбце выбранной строки
    QStandardItem* item = model->itemFromIndex(index.sibling(index.row(), 3)); // 3 - индекс четвертого столбца
    item->setData(value, Qt::DisplayRole);
    // Получаем идентификатор машины из выбранной строки в таблице выдач
    QModelIndex indexIssued = refundtable->currentIndex();
    QString carNumber2 = indexIssued.sibling(indexIssued.row(), 1).data().toString(); // 1 - индекс второго столбца
    // Находим элемент в таблице машин с таким же идентификатором
    QStandardItemModel* modelCars = dynamic_cast<QStandardItemModel*>(booktable->model());
    int rowCount = modelCars->rowCount();
    int bookRow = -1;
    for (int i = 0; i < rowCount; i++) {
        QModelIndex indexBook = modelCars->index(i, 2); // 0 - индекс первого столбцаъ
        if (indexBook.data().toString() == carNumber2) {
            bookRow = i;
            break;
        }
    }
    // Если элемент найден, то изменяем значение в шестом столбце
    if (bookRow != -1) {
        QStandardItem* item = modelCars->itemFromIndex(modelCars->index(bookRow, 6)); // 5 - индекс шестого столбца (наличие)
        item->setData("В наличии", Qt::DisplayRole);

        // Обновляем модель данных в таблице машин
        booktable->setModel(modelCars);
    }
    // Обновляем модель данных в таблице
    refundtable->setModel(model);
}
