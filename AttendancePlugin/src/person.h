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
 *  Class representing an attendee.
 *
 ******************************************************************************/


#ifndef VTMINE_FRAMEWORK_PLUGINS_PERSON_H_
#define VTMINE_FRAMEWORK_PLUGINS_PERSON_H_


#include <QString>
#include <QMap>
#include <QDate>
#include <QStandardItem>


namespace vtmine {

/***************************************************************************//**
 *  Class representing an attendee model.
 ******************************************************************************/
class Person: public QStandardItem {
public:
    /// Class constructor.
    Person(QString& name, int id);

    /** \brief Constructor for CSV deserialization.
     *  \param csv -- CSV string.
     *  \param dates -- List of dates.
     */
    Person(QString& csv, QList<QDate*>& dates);

    /// Name getter.
    QString getName() const { return _name; }

    /// ID getter.
    int getID() const { return _id; }    

    /** \brief Represents class data as CSV-format string.
     *  \return CSV-format string.
     */
    QString toCsv() const;

    /// Attendance record (pairs of date and true/false for attendance).
    std::vector<std::pair<QDate*, bool>> _attendanceRecord;

protected:
    /// Person's ID.
    int _id;

    /// Person's name.
    QString _name;

};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_PERSON_H_
