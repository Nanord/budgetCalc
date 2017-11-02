#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QFile>
#include <QMessageBox>
#include <QToolBar>
#include <QToolButton>
#include <QMenuBar>
#include <QRegExp>
#include <map>
#include <QDate>


#include "calculate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    inline bool getFormState() { return formState; }

private slots:
    void on_action_triggered();     //C НДС

    void on_action_2_triggered();   //Без НДС

    void action_convert();

    void action_aboutProgram();     //Вызываем messagebox для соответвующей кнопки

    void action_reference();        //Вызываем messagebox для соответвующей кнопки

    void on_pushButton_clicked();

    void sClearTable();

private:
    Ui::MainWindow *ui;
    calculate *calc;

    bool formState = 0;             //Состояние формы(с НДС или Без НДС)

    void createAction();            //Создание меню

    void createTableWidget();       //Создание таблицы

    void protectionFromTheFool();   //Запрет ввода ненужных символов

    void clearTable();              //очистить табилцу
};

#endif // MAINWINDOW_H
