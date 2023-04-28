#include "myWindow.hpp"

#include "myWidgetGL.hpp"
#include "../../lib/common/error_handling.hpp"
#include "ui_mainwindow.h"

#include <iostream>

myWindow::myWindow(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow)
{
    try
    {
        //Setup window layout
        ui->setupUi(this);

        //Create openGL context
        QGLFormat qglFormat;
        qglFormat.setVersion(1,2);

        //Create OpenGL Widget renderer
        glWidget=new myWidgetGL(qglFormat);

        //Add the OpenGL Widget into the layout
        ui->layout_scene->addWidget(glWidget);
    }
    catch(cpe::exception_cpe const& e)
    {
        std::cout<<std::endl<<e.report_exception()<<std::endl;
    }

    //Connect slot and signals
    connect(ui->quit,SIGNAL(clicked()),this,SLOT(action_quit()));
    connect(ui->draw,SIGNAL(clicked()),this,SLOT(action_draw()));
    connect(ui->wireframe,SIGNAL(clicked()),this,SLOT(action_wireframe()));

    connect(ui->u_back,SIGNAL(clicked()),this,SLOT(action_u_back()));
    connect(ui->u_front,SIGNAL(clicked()),this,SLOT(action_u_front()));
    connect(ui->v_back,SIGNAL(clicked()),this,SLOT(action_v_back()));
    connect(ui->v_front,SIGNAL(clicked()),this,SLOT(action_v_front()));

    connect(ui->u_back_negative,SIGNAL(clicked()),this,SLOT(action_u_back_negative()));
    connect(ui->u_front_negative,SIGNAL(clicked()),this,SLOT(action_u_front_negative()));
    connect(ui->v_back_negative,SIGNAL(clicked()),this,SLOT(action_v_back_negative()));
    connect(ui->v_front_negative,SIGNAL(clicked()),this,SLOT(action_v_front_negative()));

    connect(ui->duplicate_boundaries,SIGNAL(clicked()),this,SLOT(action_duplicate_boundaries()));

    connect(ui->save_grid,SIGNAL(clicked()),this,SLOT(action_save_grid()));
    connect(ui->load_grid,SIGNAL(clicked()),this,SLOT(action_load_grid()));

    connect(ui->color_patch,SIGNAL(clicked()),this,SLOT(action_color_patch()));
    connect(ui->surface,SIGNAL(clicked()),this,SLOT(action_surface()));

    connect(ui->grid,SIGNAL(clicked()),this,SLOT(action_grid()));
    connect(ui->grid_position,SIGNAL(clicked()),this,SLOT(action_grid_position()));

}

myWindow::~myWindow()
{}

void myWindow::action_quit()
{
    close();
}

void myWindow::action_draw()
{
    glWidget->change_draw_state();
}

void myWindow::action_wireframe()
{
    bool const state_wireframe=ui->wireframe->isChecked();
    glWidget->wireframe(state_wireframe);
}

void myWindow::action_u_back() {glWidget->scene_3d.add_u_back();}
void myWindow::action_u_front() {glWidget->scene_3d.add_u_front();}
void myWindow::action_v_back() {glWidget->scene_3d.add_v_back();}
void myWindow::action_v_front() {glWidget->scene_3d.add_v_front();}

void myWindow::action_u_back_negative() {glWidget->scene_3d.delete_u_back();}
void myWindow::action_u_front_negative() {glWidget->scene_3d.delete_u_front();}
void myWindow::action_v_back_negative() {glWidget->scene_3d.delete_v_back();}
void myWindow::action_v_front_negative() {glWidget->scene_3d.delete_v_front();}

void myWindow::action_duplicate_boundaries() {glWidget->scene_3d.duplicate_boundaries();}

void myWindow::action_save_grid() {glWidget->scene_3d.save_control_polygon();}
void myWindow::action_load_grid() {glWidget->scene_3d.load_control_polygon();}

void myWindow::action_color_patch() {glWidget->scene_3d.set_uniform_color(!ui->color_patch->isChecked());}
void myWindow::action_surface() {glWidget->scene_3d.set_draw_spline(ui->surface->isChecked());}

void myWindow::action_grid() {glWidget->scene_3d.set_draw_polygon_line(ui->grid->isChecked());}
void myWindow::action_grid_position() {glWidget->scene_3d.set_draw_polygon_vertices(ui->grid_position->isChecked());}
