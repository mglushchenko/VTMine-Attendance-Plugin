/*******************************************************************************
 *
 *  VTMine Framework.
 *  (c) xidv.ru 2014–2020.
 *
 *  This source is for internal use only — Restricted Distribution.
 *  All rights reserved.
 *
 ******************************************************************************/



#include "person.h"


namespace vtmine {

Person::Person(QString& name, int id)
        : _name(name)
        , _id(id)
{

}

Person::Person(QString& csv, QList<QDate*>& dates)
{
    char delim = ';';
    QStringList data = csv.split(delim);
    _id = data[0].toInt();
    _name = data[1];
    for (int i = 2; i < data.size(); ++i)
    {
        QDate* date = dates.at(i - 2);
        bool attended = data[i] == "+";
        _attendanceRecord.push_back(std::make_pair(date, attended));
    }
}

QString Person::toCsv() const
{
    char delim = ';';
    QString res = QString::number(_id) + delim;
    res += _name + delim;
    for (auto& pair: _attendanceRecord)
    {
        QString attended;
        if (pair.second)
            attended = "+";
        else
            attended = "-";
        res += attended + delim;
    }
    res.remove(res.size() - 1, 1);
    res += "\n";
    return res;
}

} // namespace vtmine
