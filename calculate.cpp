#include "calculate.h"

enum {NDS, WITHOUTNDS};
void calculate::calc(std::map<QString, QString> &data, bool formState)
{
    table = data;
    if(formState == NDS)
    {
        //ндс
        table.insert({"nds",QString::number(nds(table["sumNds"].toDouble()))});
        //Сумма без ндс
        table.insert({"sumWNds", QString::number(sumWNds(table["sumNds"].toDouble(), table.at("nds").toDouble()))});
    }
    //прибыль
    table.insert({"profit", QString::number(profit(table["sumWNds"].toDouble()))});
    //себестоимость работ
    table.insert({"costWork", QString::number(costWork(table["sumWNds"].toDouble(), table.at("profit").toDouble()))});
    //Накладные расходы
    table.insert({"overheads", QString::number(overheads(table["sumWNds"].toDouble()))});
    //Прямые затраты
    table.insert({"directInfestations", QString::number(directInfestations(table.at("costWork").toDouble(), table.at("overheads").toDouble()))});

    //ЗП
    table.insert({"payday", QString::number(payday(table.at("directInfestations").toDouble(), table["othePayments"].toDouble(),  table["utilities"].toDouble(),  table["increaseFunds"].toDouble(),  table["increaseInventories"].toDouble(),  table["transportServices"].toDouble(),  table["otheServices"].toDouble()))});
    //Начисления на выплаты по оплате труда
    table.insert({"salary", QString::number(salary(table.at("payday").toDouble()))});
}

QString calculate::get(QString key)
{
    return (table.find(key) != table.end()) ?
                table[key] :
                QString();
}



// НДС
double calculate::nds(double sumNds)
{

    return sumNds - (sumNds / 1.18);
}

//Сумма без НДС
double calculate::sumWNds(double sumNds, double nds)
{
    return (sumNds - nds);
}

//прибыль
double calculate::profit(double sumWNds)
{
    if(sumWNds > 5000000)
    {
        return sumWNds * 0.04;
    }
    else
    {
        return sumWNds * 0.06;
    }
}

//себестоимость работ
double calculate::costWork(double sumWNds, double profit)
{
    return (sumWNds - profit);
}

//Накладные расходы
double calculate::overheads(double sumWNds)
{

    if(sumWNds > 5000000)
    {
      return (sumWNds * 0.13);
    }
    else
    {
      return (sumWNds * 0.14);
    }
}

 //Прямые затраты
double calculate::directInfestations(double costWork, double overheads)
{
    return costWork - overheads;
}

//Начисления на выплаты по оплате труда
double calculate::salary(double payday)
{
    return (payday * 0.302);
}

double calculate::payday(double directInfestations, double othePayments, double utilities, double increaseFunds, double increaseInventories, double transportServices, double otheServices)
{
    if( othePayments != 0 && utilities != 0 && increaseFunds != 0 && increaseInventories != 0 && transportServices != 0 && otheServices != 0)
    {
       return  directInfestations - ((othePayments - utilities - increaseFunds - increaseInventories - transportServices - otheServices) / 1.302);
    }
    else
    {
        return directInfestations / 1.302;
    }
}

double calculate::trim(double x)
{
    x = x * 100;
    return ceil(x) / 100;
}


