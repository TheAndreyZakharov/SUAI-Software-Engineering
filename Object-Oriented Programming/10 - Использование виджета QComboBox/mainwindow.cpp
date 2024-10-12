#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <sstream>
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
ui->setupUi(this);
this->setWindowTitle("Ремонт потолков");
connect(ui->comboBox,SIGNAL(activated(int index)),this,SLOT(on_comboBox_activated(int index)));
connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
connect(ui->lineEdit,SIGNAL(textChanged(const QString
&arg1)),this,SLOT(on_lineEdit_textChanged(const QString &arg1)));
connect(ui->lineEdit_2,SIGNAL(textChanged(const QString
&arg1)),this,SLOT(on_lineEdit_2_textChanged(const QString &arg1)));
}
MainWindow::~MainWindow()
{
delete ui;
}
double price = 0;
void MainWindow::on_comboBox_activated(int index)
{
//Прайслист на 1 метр:
//Шелк - 100
//Крепдешин - 200
//Шерсть - 300
//Ситец - 400
if (index == 1)
{
ui->lineEdit_3->setText("1500");
price = ui->lineEdit->text().toDouble() * ui->lineEdit_2->text().toDouble() * 1500;
ui->result->setText("");
}
{
if (index == 2)
ui->lineEdit_3->setText("600");
price = ui->lineEdit->text().toDouble() * ui->lineEdit_2->text().toDouble() * 600;
ui->result->setText("");
}
{
if (index == 3)
ui->lineEdit_3->setText("700");
price = ui->lineEdit->text().toDouble() * ui->lineEdit_2->text().toDouble() * 700;
ui->result->setText("");
}
{
if (index == 4)
ui->lineEdit_3->setText("3000");
price = ui->lineEdit->text().toDouble() * ui->lineEdit_2->text().toDouble() * 3000;
ui->result->setText("");
}
{
if (index == 0)
ui->lineEdit_3->setText("");
ui->result->setText("");
}
}
void MainWindow::on_pushButton_clicked()
{
ui->result->setText(QString::number(price));
}
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
ui->result->setText("");
}
void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
ui->result->setText("");
}
