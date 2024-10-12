#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDoubleValidator>
#include <QValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
Q_OBJECT
public:
MainWindow(QWidget *parent = nullptr);
~MainWindow();
double sum(double a, double b);
private slots:
void on_PushButton_clicked_sum();
void on_PushButton_clicked_dif();
void on_PushButton_clicked_plur();
void on_PushButton_clicked_div();
void on_PushButton_clicked_perc();
void on_textChange(QString);
private:
Ui::MainWindow *ui;
QDoubleValidator m_doubleValidator;
};
#endif // MAINWINDOW_H
