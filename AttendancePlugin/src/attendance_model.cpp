/*******************************************************************************
 *
 *  VTMine Framework.
 *  (c) xidv.ru 2014–2020.
 *
 *  This source is for internal use only — Restricted Distribution.
 *  All rights reserved.
 *
 ******************************************************************************/


#include <QLocale>

#include "attendance_model.h"


namespace vtmine {

AttendanceModel::AttendanceModel(QList<Person*> personList, QObject* parent)
                : _personList(personList)
{
    _columnCount = 2 + _personList.at(0)->_attendanceRecord.size();
}

AttendanceModel::~AttendanceModel()
{
    for (Person* p: _personList)
        delete p;
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
        {
            QLocale locale = QLocale(QLocale::English, QLocale::UnitedStates);
            QDate* date = _personList.at(0)->_attendanceRecord[section - 2].first;
            return locale.toString(*date);
        }
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
        if ((Qt::CheckState)value.toInt() == Qt::Checked)
        {
            p->_attendanceRecord[index.column() - 2].second = true;
        }
        else
        {
             p->_attendanceRecord[index.column() - 2].second = false;
        }

        emit dataChanged(index, index);
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

void AttendanceModel::clearDates()
{
    beginRemoveColumns(QModelIndex(), 2, columnCount() - 1);
    for (Person* p: _personList)
    {
        p->_attendanceRecord.clear();
    }
    endRemoveColumns();
    _columnCount = 2;
}

void AttendanceModel::setMarksForPerson(int num, bool checked)
{
    if (num >= _personList.size())
        return;
    Person* p = _personList.at(num);
    for (auto& pair: p->_attendanceRecord)
        pair.second = checked;

    QModelIndex start = index(num, 2);
    QModelIndex end = index(num, columnCount());

    emit dataChanged(start, end);
}

void AttendanceModel::setMarksForDate(int num, bool checked)
{
    if (num >= columnCount())
        return;

    for (Person* p: _personList)
        p->_attendanceRecord[num - 2].second = checked;

    QModelIndex start = index(0, num);
    QModelIndex end = index(rowCount(), num);

    emit dataChanged(start, end);
}

} // namespace vtmine
