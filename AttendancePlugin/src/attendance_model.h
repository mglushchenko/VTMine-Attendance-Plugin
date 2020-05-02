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

/***************************************************************************//**
 *  Class representing attendance table model.
 ******************************************************************************/
class AttendanceModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    /// Class constructor.
    AttendanceModel(QList<Person*> personList, QObject* parent = nullptr);

    /// Getter for number of rows.
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /// Getter for number of columns.
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /// Getter for table contents.
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /// Getter for table headers.
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                       int role = Qt::EditRole) const override;

    virtual bool setData(const QModelIndex& index, const QVariant& value,
                         int role = Qt::EditRole) override;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    void addDates(QList<QDate*> dates);

protected:
    /// Underlying data.
    QList<Person*> _personList;

    QList<QDate*> _dateList;

    int _columnCount;
};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_ATTENDANCEMODEL_H_
