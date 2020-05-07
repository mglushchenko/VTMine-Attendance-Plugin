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

    ~AttendanceModel();

    /// Getter for number of rows.
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /// Getter for number of columns.
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /// Getter for table contents.
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /// Getter for table headers.
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                       int role = Qt::EditRole) const override;

    /** \brief Sets new value of table cell.
     *  \param index -- Cell index.
     *  \param value -- New value.
     *  \param role -- Value role.
     *  \return True in case of success.
     */
    virtual bool setData(const QModelIndex& index, const QVariant& value,
                         int role = Qt::EditRole) override;

    /** \brief Item flags getter.
     *  \param index -- Cell index.
     *  \return Item flags.
     */
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    /** \brief Adds dates to model.
     *  \param dates -- List of dates.
     */
    void addDates(QList<QDate*> dates);

    /// Clears all dates from model.
    void clearDates();

    /** \brief Sets all marks for person to the same value.
     *  \param num -- Number of person in list.
     *  \param checked -- Value to be set.
     */
    void setMarksForPerson(int num, bool checked);

    /** \brief Sets all marks for date to the same value.
     *  \param num -- Number of date in list.
     *  \param checked -- Value to be set.
     */
    void setMarksForDate(int num, bool checked);

    /// Getter for underlying person list.
    QList<Person*> getPersonList() const { return _personList; }

protected:
    /// Underlying data.
    QList<Person*> _personList;

    /// List of marked dates.
    QList<QDate*> _dateList;

    /// Number of columns in model.
    int _columnCount;
};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_ATTENDANCEMODEL_H_
