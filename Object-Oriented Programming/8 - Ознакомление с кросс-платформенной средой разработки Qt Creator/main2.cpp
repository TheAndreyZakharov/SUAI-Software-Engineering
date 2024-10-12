#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow){
ui->setupUi(this);
ui->lineEdit_3->setReadOnly(true);
ui->lineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^([0-9]*\\.[0-
9]+)$"), this));
ui->lineEdit_2->setValidator(new QRegularExpressionValidator(QRegularExpression("^([0-9]*\\.[0-
9]+)$"), this));
this->setWindowTitle("Calcul");
connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_PushButton_clicked_sum);
connect(ui->pushButton_2, &QPushButton::clicked, this,
&MainWindow::on_PushButton_clicked_dif);
connect(ui->pushButton_3, &QPushButton::clicked, this,
&MainWindow::on_PushButton_clicked_plur);
connect(ui->pushButton_4, &QPushButton::clicked, this,
&MainWindow::on_PushButton_clicked_div);
connect(ui->pushButton_5, &QPushButton::clicked, this,
&MainWindow::on_PushButton_clicked_perc);
connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::on_textChange);
connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &MainWindow::on_textChange);
}
double MainWindow::sum(double a, double b)
{
return a + b;
}
void MainWindow::on_PushButton_clicked_sum()
{
double te = ui->lineEdit->text().toDouble();
double te2 = ui->lineEdit_2->text().toDouble();
double sm = sum(te, te2);
QString str;
str.setNum(sm);
ui->lineEdit_3->setText(str);
}
void MainWindow::on_PushButton_clicked_dif()
{
double te = ui->lineEdit->text().toDouble();
double te2 = ui->lineEdit_2->text().toDouble();
double dif = te-te2;
QString str;
str.setNum(dif);
ui->lineEdit_3->setText(str);
}
void MainWindow::on_PushButton_clicked_plur()
{
double te = ui->lineEdit->text().toDouble();
double te2 = ui->lineEdit_2->text().toDouble();
double plur = te*te2;
QString str;
str.setNum(plur);
ui->lineEdit_3->setText(str);
}
void MainWindow::on_PushButton_clicked_div()
{
QString str;
double te = ui->lineEdit->text().toDouble();
double te2 = ui->lineEdit_2->text().toDouble();
if(te2 != 0)
{
double div = te/te2;
str.setNum(div);
ui->lineEdit_3->setText(str);
}else
{
ui->lineEdit_3->setText("Imposible, try again");
}
}
void MainWindow::on_PushButton_clicked_perc()
{
double te = ui->lineEdit->text().toDouble();
double te2 = ui->lineEdit_2->text().toDouble();
double dif = 0.01*te2*te;
QString str;
str.setNum(dif);
ui->lineEdit_3->setText(str);
}
void MainWindow::on_textChange(QString str)
{
ui->lineEdit_3->clear();
}
MainWindow::~MainWindow()
{
delete ui;
}
