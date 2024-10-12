#include "mainwindow.h"
#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
ui->setupUi(this);
this->setWindowTitle("Ларёк");
}
MainWindow::~MainWindow()
{
delete ui;
}
/*
* Прайс лист
* 9 Х 12 - 100р
* 10 Х 15 - 200р
* 20 Х 30 - 300р
* Матовая бумага - х1
* Глянцевая бумага - х1.5
* Больше 4 фото - скидка 10%
*/
double a = 0;
double b = 0;
double price = 0;
void MainWindow::on_radioButton_4_toggled(bool checked)
{
a = 3;
ui->result->setText("");
}
void MainWindow::on_radioButton_5_toggled(bool checked)
{
a = 2;
ui->result->setText("");
}
void MainWindow::on_radioButton_toggled(bool checked)
{
b = 10;
ui->result->setText("");
}
void MainWindow::on_radioButton_2_toggled(bool checked)
{
b = 20;
ui->result->setText("");
}
void MainWindow::on_radioButton_3_toggled(bool checked)
{
b = 30;
ui->result->setText("");
}
void MainWindow::on_pushButton_clicked()
{
if (ui->amount->text().toDouble() < 5)
price = a * b * ui->amount->text().toDouble();
else
price = a * b * ui->amount->text().toDouble() * 0.9;
ui->result->setText(QString::number(price));
}
