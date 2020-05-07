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
 *  Attendance plugin help window.
 *
 ******************************************************************************/

#ifndef VTMINE_FRAMEWORK_PLUGINS_HELPWINDOW_H_
#define VTMINE_FRAMEWORK_PLUGINS_HELPWINDOW_H_


#include <QWidget>
#include <QDialog>


namespace Ui {
class HelpWindow;
}

namespace vtmine {

/***************************************************************************//**
 *  Help window class.
 ******************************************************************************/
class HelpWindow : public QDialog
{
    Q_OBJECT

public:
    /// Class constructor.
    explicit HelpWindow(QWidget *parent = nullptr);

    /// Class destructor.
    ~HelpWindow();

    /** \brief Opens file with help information.
     *  \param path -- Path to help file.
     */
    void openFile(QString& path);

protected:
    /// Widget UI.
    Ui::HelpWindow* ui;
};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_HELPWINDOW_H_
