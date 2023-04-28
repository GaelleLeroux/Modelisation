#pragma once

#ifndef MY_WINDOW_HPP
#define MY_WINDOW_HPP


#include <QMainWindow>




//forward declaration
namespace Ui
{
class MainWindow;
}
class myWidgetGL;

/** Declaration of the Window class */
class myWindow: public QMainWindow
{
    Q_OBJECT

public:

    myWindow(QWidget *parent=NULL);
    ~myWindow();



private slots:

    /** Quit the application */
    void action_quit();
    /** Enable the drawing of the meshes */
    void action_draw();
    /** Set the Wireframe mode for the meshes */
    void action_wireframe();

    void action_u_back();
    void action_u_front();
    void action_v_back();
    void action_v_front();

    void action_u_back_negative();
    void action_u_front_negative();
    void action_v_back_negative();
    void action_v_front_negative();

    void action_duplicate_boundaries();

    void action_save_grid();
    void action_load_grid();

    void action_color_patch();
    void action_surface();

    void action_grid();
    void action_grid_position();

private:

    /** Layout for the Window */
    Ui::MainWindow *ui;
    /** The OpenGL Widget */
    myWidgetGL *glWidget;





};

#endif
