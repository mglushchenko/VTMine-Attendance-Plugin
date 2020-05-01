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

class Person: public QStandardItem {
public:
    /// Class constructor.
    Person(QString& name, int id);

    /// Name getter.
    QString getName() const { return _name; }

    /// ID getter.
    int getID() const { return _id; }

    /// Attendance map getter.
    QMap<QDate*, bool> getAttendanceMap() const { return _attendanceMap; }

protected:
    /// Person's name.
    QString _name;

    /// Person's ID.
    int _id;

    /// Attendance map (date as key).
    QMap<QDate*, bool> _attendanceMap;
};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_PERSON_H_
