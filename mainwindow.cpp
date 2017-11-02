#include "mainwindow.h"
#include "ui_mainwindow.h"



//Cостояния формы
enum {NDS, WITHOUTNDS};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    calc(new calculate)
{
    ui->setupUi(this);
    //  начальное состояние формы
    formState = NDS;
    //  Подключение стилей
    QFile styleF;

    styleF.setFileName(":/style.qss");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();

    qApp->setStyleSheet(qssStr);
    //...................................


    //  Создание Action в MenuBar
    MainWindow::createAction();


    //  Создаем таблицу
    MainWindow::createTableWidget();

    //  Защита от дурака
    MainWindow::protectionFromTheFool();
}


void MainWindow::createAction()
{
    //  Создание Action в MenuBar
    QAction *convert = new QAction("&Конвертировать", this);
    QAction *aboutProgram = new QAction("О прогр&амме", this);
    QAction *reference = new QAction("Спра&вка", this);
    QAction *buttonClearTable = new QAction("Очистит&ь таблицу", this);

    ui->menuBar->addAction(convert);
    ui->menuBar->addAction(aboutProgram);
    ui->menuBar->addAction(reference);
    ui->menuBar->addAction(buttonClearTable);

    //  Нажатие на Action
    connect(convert, SIGNAL(triggered()), this, SLOT(action_convert()));
    connect(aboutProgram, SIGNAL(triggered()), this, SLOT(action_aboutProgram()));
    connect(reference, SIGNAL(triggered()), this, SLOT(action_reference()));
    connect(buttonClearTable, SIGNAL(triggered(bool)), this, SLOT(sClearTable()));
}

void MainWindow::createTableWidget()
{
    //  Создаем таблицу
    ui->tableWidget->setRowCount(15);
    ui->tableWidget->setColumnCount(2);

    //  Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    //  Устанавливаем заголовки колонок
    QDate dateToday = QDate::currentDate();
    QString str1 = dateToday.toString("dd.MM.yyyy");
    QString str2 = "г.руб";
    QString str = str1 + str2;
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()
                                                  << "Код КБК РФ"
                                                  << str);
    //  Устанавливаем заголовки строк
    ui->tableWidget->setVerticalHeaderLabels(QStringList()
                                                << "Заработная плата"
                                                << "Начисления выплаты по оплате труда"
                                                << "Прочие выплаты (суточные)"
                                                << "Комунальные услуги"
                                                << "Увеличение стоимости основных средств"
                                                << "Увеличение стоимости материальных запасов"
                                                << "Транспортные услуги"
                                                << "Прочие услуги (прожив., команд.)"
                                                << "Прямые затраты"
                                                <<"Накладные расходы"
                                                << "Себестоисость работы"
                                                << "Прибыль"
                                                << "Сумма без НДС"
                                                << "НДС"
                                                << "Договорная цена с НДС");
    //  Графический костыль
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    QRegExp exp("[0-9.]{60}");
    QLineEdit *edit;
    QString value[] = {"211", "213", "212", "223", "310", "340", "222", "226"};
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
          for(int j = 0; j < ui->tableWidget->columnCount(); j++)
          {
            ui->tableWidget->setRowHeight(i, 21);
            edit = new QLineEdit();
            edit->setAlignment(Qt::AlignCenter);
            edit->setValidator(new QRegExpValidator(exp, this));
            edit->setStyleSheet("QLineEdit {background-color: #FFFFFF; margin: -5px;}");
            if(j == 0 && i >= 0)
            {
                edit->setDisabled(true);
                if(i <= 6)
                {
                    edit->setStyleSheet("QLineEdit {font-weight: bold; color: #333; background-color: #FFFFFF; margin: -5px}");
                    edit->setText(value[i]);
                }

            }
            if(j == 1 && i >= 0)
            {
                if((i >= 2 && i <= 7) || (i == 14))
                {
                    edit->setPlaceholderText("Введите число");
                }
                else
                {
                    edit->setDisabled(true);
                    edit->setPlaceholderText("-");
                }
            }
            ui->tableWidget->setCellWidget(i, j, edit); // вставляем ячейку
          }

}




void MainWindow::on_action_triggered()
{
    if(this->formState != NDS)
    {
        this->formState = NDS;

        clearTable();

        //  графический костыль
        ui->tableWidget->setMinimumHeight(340);
        ui->tableWidget->setMaximumHeight(340);

        ui->tableWidget->setRowHidden(13, false);
        ui->tableWidget->setRowHidden(14, false);


        // изменить состояние строки "Сумма без НДС"
        ((QLineEdit*)ui->tableWidget->cellWidget(12, 1))->setDisabled(true);
        ((QLineEdit*)ui->tableWidget->cellWidget(12, 1))->setPlaceholderText("-");

    }
    else
    {
        this->formState = NDS;
    }
}

void MainWindow::on_action_2_triggered()
{
    if(this->formState != WITHOUTNDS)
    {
        this->formState = WITHOUTNDS;

        clearTable();

        //  грфический костыль
        ui->tableWidget->setMinimumHeight(300);
        ui->tableWidget->setMaximumHeight(300);

        ui->tableWidget->setRowHidden(13, true);
        ui->tableWidget->setRowHidden(14, true);

        ((QLineEdit*)ui->tableWidget->cellWidget(12, 1))->setDisabled(false);
        ((QLineEdit*)ui->tableWidget->cellWidget(12, 1))->setPlaceholderText("Введите число");
    }
    else
    {
        this->formState = WITHOUTNDS;
    }
}


void MainWindow::action_convert()
{
    QMessageBox msg;
    msg.setText("Проверьте правильность введеных\n"
             "вами данных");
    msg.setWindowTitle("Error");

    msg.exec();
}

void MainWindow::action_aboutProgram()
{
    QMessageBox msg;
    msg.setText("​Сметный калькулятор \n"
                "Версия 1.0.0 \n"
                "\n"
                "Разработано студентами 15-СБК \n"
                "Потом и кровью");
    msg.setWindowTitle("О программе");

    msg.exec();
}

void MainWindow::action_reference()
{
    QMessageBox msg;
    msg.setText("​Сметный калькулятор работает в двух"
             "режимах: с НДС (по умолчанию) и без"
             "НДС. Сменить режим можно в шапке "
             "программы."
             "Работает с входными данными, "
             "которые вводит пользователь в "
             "основные поля для ввода \"Договорная"
             "цена (с НДС)\" или же \"Сумма без НДС\""
             "а также с учетом других расходов."
             "Кроме того для корректного создания сметы необходимо "
             "ввести контактные данные, такие как: должность "
             "руководителя, наименование, ФИО руководителя "
             "орагинизации; номер договора, руководителя, "
             "подразделение, тему и срок.");
    msg.setWindowTitle("Справка");

    msg.exec();
}


void MainWindow::protectionFromTheFool()
{
    //регулярные выражения
    QRegExp exp("[a-zA-zа-яА-я0-9. ]{60}");     //цыфры и буквы
    QRegExp exp2("[0-9.]{60}");             //только цыфры
    QRegExp exp3("[a-zA-Zа-яА-Я ]{60}");    //только буквы
    QRegExp dataExp("[0-9]{2}[.]{1}[0-9]{2}[.]{1}[0-9]{4}");

    //Для должности руководителя
    ui->position->setValidator(new QRegExpValidator(exp,this));

    //Для наименновании организации
    ui->nameCompany->setValidator(new QRegExpValidator(exp,this));

    //ФИО
    ui->fullName->setValidator(new QRegExpValidator(exp3,this));

    //Номер договора
    ui->contractNumber->setValidator(new QRegExpValidator(exp2,this));

    //Руководитель
    ui->chief->setValidator(new QRegExpValidator(exp3,this));

    //Подразделение
    ui->subdivision->setValidator(new QRegExpValidator(exp,this));

    //Тема
    ui->subject->setValidator(new QRegExpValidator(exp,this));

    //Срок
    ui->time_1->setValidator(new QRegExpValidator(dataExp,this));
    ui->time_2->setValidator(new QRegExpValidator(dataExp,this));

    //Главный бухгалтер
    ui->accountant->setValidator(new QRegExpValidator(exp3,this));

    //Руководитель
    ui->manager->setValidator(new QRegExpValidator(exp3,this));
}

void MainWindow::clearTable()
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        ((QLineEdit *)ui->tableWidget->cellWidget(i,1))->setText("");
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if( (!ui->tableWidget->cellWidget(14,1)->isHidden() &&  ((QLineEdit *)ui->tableWidget->cellWidget(14,1))->text() != 0) || (ui->tableWidget->cellWidget(14,1)->isHidden() && ((QLineEdit *)ui->tableWidget->cellWidget(12,1))->text() != 0) )
    {
        //создаем контейнер map
        std::map<QString, QString> table;

        //записываем значения

        if(this->formState == NDS)
        {
            //Договорная цена с НДС
            table["sumNds"] = ((QLineEdit *)ui->tableWidget->cellWidget(14,1))->text();
        }
        else
        {
            //Сумма без НДС
            table["sumWNds"] = ((QLineEdit *)ui->tableWidget->cellWidget(12,1))->text();
        }
        //Прочие услуги
        table["otheServices"] = ((QLineEdit *)ui->tableWidget->cellWidget(7,1))->text();
        //Трансротные услуги
        table["transportServices"] = ((QLineEdit *)ui->tableWidget->cellWidget(6,1))->text();
        //Увел. стоимости мат запасов
        table["increaseInventories"] = ((QLineEdit *)ui->tableWidget->cellWidget(5,1))->text();
        //увел. стоимости основ средств
        table["increaseFunds"] = ((QLineEdit *)ui->tableWidget->cellWidget(4,1))->text();
        //комунальные услуги
        table["utilities"] = ((QLineEdit *)ui->tableWidget->cellWidget(3,1))->text();
        //Прочие выплаты
        table["othePayments"] = ((QLineEdit *)ui->tableWidget->cellWidget(2,1))->text();

        //пихаем туда наш map
        calc->calc(table, formState);

        //выводим измененный map
        // QString("Расстояние от излучающего гидрофона до антенны (м): %1").arg(QString::number(n, 'f', 3))
        //ндс
        ((QLineEdit *)ui->tableWidget->cellWidget(13,1))->setText(QString::number(calc->trim(calc->get("nds").toDouble())));
        //Сумма без НДС
        ((QLineEdit *)ui->tableWidget->cellWidget(12,1))->setText(QString::number(calc->trim(calc->get("sumWNds").toDouble())));
        //прибыль
        ((QLineEdit *)ui->tableWidget->cellWidget(11,1))->setText(QString::number(calc->trim(calc->get("profit").toDouble())));
        //Себестоимость работы
        ((QLineEdit *)ui->tableWidget->cellWidget(10,1))->setText(QString::number(calc->trim(calc->get("costWork").toDouble())));
        //Накладные расходы
        ((QLineEdit *)ui->tableWidget->cellWidget(9,1))->setText(QString::number(calc->trim(calc->get("overheads").toDouble())));
        //Прямые затраты
        ((QLineEdit *)ui->tableWidget->cellWidget(8,1))->setText(QString::number(calc->trim(calc->get("directInfestations").toDouble())));
        //Начисления на выплаты по оплате труда
        ((QLineEdit *)ui->tableWidget->cellWidget(1,1))->setText(QString::number(calc->trim(calc->get("salary").toDouble())));
        //ЗП
        ((QLineEdit *)ui->tableWidget->cellWidget(0,1))->setText(QString::number(calc->trim(calc->get("payday").toDouble())));
    }
    else
    {
        QMessageBox msg;
        msg.setText("​Поле \"Договорная цена с НДС\" или же \"Сумма\n"
                    "без НДС\" не заполнено или равно 0");
        msg.setWindowTitle("Error");

        msg.exec();
    }
}

void MainWindow::sClearTable()
{
    clearTable();
}
