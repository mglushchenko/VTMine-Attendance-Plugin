/*******************************************************************************
 *
 *  VTMine Framework.
 *  (c) xidv.ru 2014–2020.
 *
 *  This source is for internal use only — Restricted Distribution.
 *  All rights reserved.
 *
 ******************************************************************************/


#include "attendance_model.h"


namespace vtmine {

AttendanceModel::AttendanceModel(QList<Person*> personList, QObject* parent)
                : _personList(personList)
{
    _columnCount = 2;
}

int AttendanceModel::rowCount(const QModelIndex& parent) const
{
    return _personList.size();
}

int AttendanceModel::columnCount(const QModelIndex& parent) const
{
    return _columnCount;
}

QVariant AttendanceModel::data(const QModelIndex& index, int role) const
{
    if (index.column() > columnCount())
        return QVariant();

    if (role == Qt::CheckStateRole && index.column() > 1)
    {
        Person* curr = _personList.at(index.row());
        bool checked = curr->_attendanceRecord[index.column() - 2].second;
        if (checked)
            return Qt::Checked;
        return Qt::Unchecked;
    }

    if (role == Qt::DisplayRole)
    {
        Person* curr = _personList.at(index.row());
        switch (index.column())
        {
        case 0:
            return QString::number(curr->getID());
        case 1:
            return QString(curr->getName());
        default:
            return QString::number(curr->_attendanceRecord[index.column() - 2]
                    .second);
        }
    }
    return QVariant();
}

QVariant AttendanceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || section > columnCount())
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0:
            return tr("ID");
        case 1:
            return tr("Name");
        default:
            return _personList.at(0)->_attendanceRecord[section - 2].first->toString();
        }
    }

    return QVariant();
}

bool AttendanceModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
            return false;

    if (role == Qt::CheckStateRole)
    {
        Person* p = _personList.at(index.row());
        //QDate* toChange = p->_attendanceMap.keys().at(index.column() - 2);
        if ((Qt::CheckState)value.toInt() == Qt::Checked)
        {
            p->_attendanceRecord[index.column() - 2].second = true;
            //p->_attendanceMap[toChange] = true;
        }
        else
        {
             p->_attendanceRecord[index.column() - 2].second = false;
             //p->_attendanceMap[toChange] = false;
        }
        return true;
    }
    return false;
}

Qt::ItemFlags AttendanceModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if (index.column() > 1)
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable
                | Qt::ItemIsUserCheckable;

    return QAbstractTableModel::flags(index);
}

void AttendanceModel::addDates(QList<QDate*> dates)
{
    for (QDate* date: dates)
    {
        beginInsertColumns(QModelIndex(), columnCount(), columnCount());
        for (Person* p: _personList)
            p->_attendanceRecord.push_back(std::make_pair(date, false));

        endInsertColumns();
        ++_columnCount;
    }
}

} // namespace vtmine
