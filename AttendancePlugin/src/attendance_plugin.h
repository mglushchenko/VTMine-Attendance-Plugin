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
 *  Plugin for attendance control.
 *
 ******************************************************************************/

#ifndef VTMINE_FRAMEWORK_PLUGINS_TESTPLUGIN_H_
#define VTMINE_FRAMEWORK_PLUGINS_TESTPLUGIN_H_


#include <QtPlugin>
#include <QApplication>
#include <QPushButton>
#include <QWidget>

#include "AttendancePlugin_global.h"
#include "../../../../src/core/iplugin.h"
#include "../../../../src/core/framework.h"


namespace vtmine {

/***************************************************************************//**
 *  Attendance plugin class.
 ******************************************************************************/
class ATTENDANCE_PLUGIN_EXPORT AttendancePlugin: public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "testplugin.0.1" FILE "attendance_plugin.json")
    Q_INTERFACES(vtmine::IPlugin)

public:
    /// Default constructor.
    AttendancePlugin();

    /// Class destructor.
    ~AttendancePlugin() override
    {
        deactivate();
    }

    /** \brief Activates plugin main window.
     *  \param frmw -- Framework that launched the plugin.
     *  \return True in case of success.
     */
    bool activate(vtmine::IFramework* frmw) override;

    /** \brief Deactivates plugin.
     *  \return True in case of success.
     */
    bool deactivate() override;

protected:
    /// Framework that launched the plugin.
    IFramework* _owner;
};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_TESTPLUGIN_H_
