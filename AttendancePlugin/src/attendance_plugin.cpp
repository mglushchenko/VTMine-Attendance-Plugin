/*******************************************************************************
 *
 *  VTMine Framework.
 *  (c) xidv.ru 2014–2020.
 *
 *  This source is for internal use only — Restricted Distribution.
 *  All rights reserved.
 *
 ******************************************************************************/


#include <QGridLayout>

#include "attendance_plugin.h"
#include "mainwindow.h"


namespace vtmine {

AttendancePlugin::AttendancePlugin()
{

}

bool AttendancePlugin::activate(IFramework* frmw)
{
    _owner = frmw;
    char* argv[] = { NULL };
    int argc = 0;

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}

bool AttendancePlugin::deactivate()
{
    return true;
}

} // namespace vtmine
