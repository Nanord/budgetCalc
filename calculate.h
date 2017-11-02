#ifndef CALCULATE_H
#define CALCULATE_H

#include <map>
#include <QString>
#include <cstddef>
#include <QDebug>
#include <QFile>

class calculate
{
public:

    calculate() = default;


    void calc(std::map<QString, QString> &table, bool formState);
    QString get(QString key);

    double trim(double x);

private:

    std::map<QString, QString> table;


    double nds(double sumNds);

    double sumWNds(double sumNds, double nds);

    double profit(double sumWNds);

    double costWork(double sumWNds, double profit);

    double overheads(double sumWNds);

    double directInfestations(double costWork, double overheads);

    double salary(double payday);

    double payday(double directInfestations, double othePayments, double utilities, double increaseFunds, double increaseInventories, double transportServices, double otheServices);


};

#endif
