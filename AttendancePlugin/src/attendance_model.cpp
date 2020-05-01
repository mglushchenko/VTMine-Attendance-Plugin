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

}

int AttendanceModel::rowCount(const QModelIndex& parent) const
{
    return _personList.size();
}

int AttendanceModel::columnCount(const QModelIndex& parent) const
{
    return _personList.at(0)->getAttendanceMap().size() + 2;
}

QVariant AttendanceModel::data(const QModelIndex& index, int role) const
{
    if (index.column() > columnCount())
        return QVariant();
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
            return QString::number(curr->getAttendanceMap().values().at(index.column()));
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
            return _personList.at(0)->getAttendanceMap().keys()
                    .at(section)->toString();
        }
    }

    return QVariant();
}

} // namespace vtmine
