#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
ui->setupUi(this);
this->setWindowTitle("Покупка костюма");
QPixmap pix("/Users/andrey/Documents/QTproj/remont.jpg");
int w = ui->image->width();
int h = ui->image->height();
ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
connect(ui->pushButton, &QPushButton::clicked, this,
&MainWindow::on_PushButton_clicked_Summ);
connect(ui->checkBox, &QCheckBox::stateChanged, this, &MainWindow::on_checkBoxChange);
connect(ui->checkBox_2, &QCheckBox::stateChanged, this, &MainWindow::on_checkBoxChange);
connect(ui->checkBox_3, &QCheckBox::stateChanged, this, &MainWindow::on_checkBoxChange);
connect(ui->checkBox_4, &QCheckBox::stateChanged, this, &MainWindow::on_checkBoxChange);
connect(ui->checkBox_5, &QCheckBox::stateChanged, this, &MainWindow::on_checkBoxChange);
connect(ui->checkBox_6, &QCheckBox::stateChanged, this, &MainWindow::on_checkBoxChange);
}
MainWindow::~MainWindow()
{
delete ui;
}
void MainWindow::on_PushButton_clicked_Summ()
{
double sum = 15000;
QString str;
if(ui->checkBox->isChecked())
{
sum+=10000;
}
{
if(ui->checkBox_2->isChecked())
sum+=3000;
}
{
if(ui->checkBox_3->isChecked())
sum+=1500;
}
{
if(ui->checkBox_4->isChecked())
sum+=8000;
}
{
if(ui->checkBox_5->isChecked())
sum+=1500;
}
{
if(ui->checkBox_6->isChecked())
sum+=1500;
if(ui->checkBox->isChecked() && ui->checkBox_2->isChecked() && ui->checkBox_3->isChecked() &&
ui->checkBox_4->isChecked() && ui->checkBox_5->isChecked() && ui->checkBox_6->isChecked())
}
{
ui->label_3->setText("Сумма без скидки = " + str.setNum(sum) + "р.\nС учетом скидки 10% = " +
str.setNum(sum - (sum-15000)*0.1) + "р.\nСумма скидки = " + str.setNum((sum-15000)*0.1) +
"р.\nCумма без доп.услуг = " + str.setNum(15000) + "р.\nСумма доп.услуг = " + str.setNum(sum-
15000) + "р.");
}
else
{
ui->label_3->setText(str.setNum(sum) + "р.\nCумма без доп.услуг = " + str.setNum(15000) +
"р.\nСумма доп.услуг = " + str.setNum(sum-15000) + "р.");
}
void MainWindow::on_checkBoxChange()
}
{
ui->label_3->clear();
}
