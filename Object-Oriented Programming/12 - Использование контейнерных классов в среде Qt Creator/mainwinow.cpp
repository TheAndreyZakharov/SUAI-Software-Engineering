#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
ui->setupUi(this);
this->setWindowTitle("Захаров 4133К");
}
MainWindow::~MainWindow()
{
delete ui;
}
//элкмент по индексу
void MainWindow::on_pushButton_clicked()
{
if (list.count() > ui->index_input->text().toInt())
{
ui->value_input->setText(list.at(ui->index_input->text().toInt()));
ui->index_input->clear();
}
else
{
ui->value_input->setText("Индекс вне списка");
ui->index_input->clear();
}
ui->summ->clear();
}
//удалить по индексу
void MainWindow::on_pushButton_2_clicked()
{
if (list.count() > ui->index_input->text().toInt())
{
ui->value_input->setText(list.at(ui->index_input->text().toInt()));
list.removeAt(ui->index_input->text().toInt());
ui->listWidget_2->clear();
ui->listWidget_2->addItems(list);
ui->value_input->clear();
ui->index_input->clear();
}
else
{
ui->value_input->setText("Индекс вне списка");
ui->index_input->clear();
}
ui->summ->clear();
}
//удалить по значению
void MainWindow::on_pushButton_3_clicked()
{
if (list.contains(ui->value_input->text()))
{
ui->index_input->setText(QString::number(list.indexOf(ui->value_input->text())));
list.removeAt(ui->index_input->text().toInt());
ui->listWidget_2->clear();
ui->listWidget_2->addItems(list);
ui->value_input->clear();
ui->index_input->clear();
}
else
{
ui->index_input->setText("--");
ui->value_input->clear();
}
ui->summ->clear();
}
//добавить элемент
void MainWindow::on_pushButton_4_clicked()
{
if (ui->value_input->text() != "")
list += ui->value_input->text();
ui->listWidget_2->clear();
ui->listWidget_2->addItems(list);
ui->value_input->clear();
ui->index_input->clear();
ui->summ->clear();
}
//сумма
void MainWindow::on_pushButton_5_clicked()
{
int sum_ = 0;
foreach(const QString &str, list)
sum_ += str.toInt();
ui->summ->setText(QString::number(sum_));
ui->value_input->clear();
ui->index_input->clear();
}
//сумма чётных
void MainWindow::on_pushButton_6_clicked()
{
int sum_ = 0;
foreach(const QString& str, list)
if (!(str.toInt() % 2))
sum_ += str.toInt();
ui->summ->setText(QString::number(sum_));
ui->value_input->clear();
ui->index_input->clear();
}
//очистить коллекцию
void MainWindow::on_pushButton_9_clicked()
{
list.clear();
ui->listWidget_2->clear();
ui->value_input->clear();
ui->index_input->clear();
ui->summ->clear();
}
//взять из файла
void MainWindow::on_pushButton_7_clicked()
{
switch(ui->comboBox->currentIndex())
{
case 0:
{
ui->listWidget->clear();
ui->listWidget_2->clear();
QFile fin("/Users/andrey/Documents/QTproj/test.txt");
fin.open(QFile::ReadOnly | QFile::Text);
QString buffer = fin.readLine();
list = buffer.split(" ");
ui->listWidget->addItems(list);
fin.close();
break;
}
{
case 1:
ui->listWidget->clear();
ui->listWidget_2->clear();
QFile fin("/Users/andrey/Documents/QTproj/input.txt");
fin.open(QFile::ReadOnly | QFile::Text);
QString buffer = fin.readLine();
list = buffer.split(" ");
ui->listWidget->addItems(list);
fin.close();
break;
}
{
case 2:
ui->listWidget->clear();
ui->listWidget_2->clear();
QFile fin("/Users/andrey/Documents/QTproj/output.txt");
fin.open(QFile::ReadOnly | QFile::Text);
QString buffer = fin.readLine();
list = buffer.split(" ");
ui->listWidget->addItems(list);
fin.close();
break;
}
}
}
//сохранить в файл
void MainWindow::on_pushButton_8_clicked()
{
switch(ui->comboBox->currentIndex())
{
case 0:
{
QFile fin("/Users/andrey/Documents/QTproj/test.txt");
fin.open(QFile::WriteOnly | QFile::Text);
QTextStream stream(&fin);
QList<QString>::iterator it = list.begin();
for (; it != list.end() - 1; ++it)
stream << *it << " ";
stream << *it;
fin.flush();
fin.close();
break;
}
{
case 1:
QFile fin("/Users/andrey/Documents/QTproj/input.txt");
fin.open(QFile::WriteOnly | QFile::Text);
QTextStream stream(&fin);
QList<QString>::iterator it = list.begin();
for (; it != list.end() - 1; ++it)
stream << *it << " ";
stream << *it;
fin.flush();
fin.close();
break;
}
{
case 2:
QFile fin("/Users/andrey/Documents/QTproj/output.txt");
fin.open(QFile::WriteOnly | QFile::Text);
QTextStream stream(&fin);
QList<QString>::iterator it = list.begin();
for (; it != list.end() - 1; ++it)
stream << *it << " ";
stream << *it;
fin.flush();
fin.close();
break;
}
}
}
//задание 1 - неотрицательные в том же порядке
void MainWindow::on_pushButton_10_clicked()
{
QString str;
int i = 0;
int j = 0;
foreach(str, list)
{
if (str.toInt() >= 0)
{
list.swapItemsAt(i++, j);
j++;
}
else
list.takeAt(j);
}
ui->listWidget_2->clear();
ui->listWidget_2->addItems(list);
ui->value_input->clear();
ui->index_input->clear();
ui->summ->clear();
}
// сумма между 1 и 2 орицательным
void MainWindow::on_pushButton_11_clicked()
{
int sum_ = 0;
bool flag_1 = false, flag_2 = false;
foreach(QString str, list)
{
if (str.toInt() < 0)
{
if (flag_1)
flag_2 = true;
else
flag_1 = true;
}
else
if ((flag_1) && !(flag_2))
sum_ += str.toInt();
}
ui->summ->clear();
if ((flag_1) && (flag_2))
ui->summ->setText(QString::number(sum_));
ui->value_input->clear();
ui->index_input->clear();
}
