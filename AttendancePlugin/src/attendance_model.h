/***************************************************************************//**
 *  \file
 *  \brief     VTMine Framework plugin interface.
 *  \author    Sergey Shershakov, Maria Gluschenko
 *  \version   0.1.0
 *  \date      09.04.2020
 *  \copyright (c) xidv.ru 2014–2020.
 *             This source is for internal use only — Restricted Distribution.
 *             All rights reserved.
 *
 *  Model for displaying attendance table.
 *
 ******************************************************************************/


#ifndef VTMINE_FRAMEWORK_PLUGINS_ATTENDANCEMODEL_H_
#define VTMINE_FRAMEWORK_PLUGINS_ATTENDANCEMODEL_H_


#include <QAbstractTableModel>

#include "person.h"


namespace vtmine {

class AttendanceModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    AttendanceModel(QList<Person*> personList, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    virtual QVariant headerData(int section, Qt::Orientation orientation,
                       int role = Qt::EditRole) const override;

protected:
    QList<Person*> _personList;
};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_ATTENDANCEMODEL_H_
