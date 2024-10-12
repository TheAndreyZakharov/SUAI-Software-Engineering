#ifndef MAINWINDOW
H
_
#define MAINWINDOW_H
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
Q_OBJECT
public:
MainWindow(QWidget *parent = nullptr);
~MainWindow();
private:
Ui::MainWindow *ui;
private slots:
void on_PushButton_clicked_Summ();
void on_checkBoxChange();
};
#endif // MAINWINDOW_H4.2
