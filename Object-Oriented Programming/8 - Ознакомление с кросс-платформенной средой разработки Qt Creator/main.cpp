#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
ui->setupUi(this);
connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_PushButton);
}
MainWindow::~MainWindow()
{
delete ui;
void MainWindow::on_PushButton()
}
{
ui->label_2->setText(ui->lineEdit->text());
ui->lineEdit->clear();
}
