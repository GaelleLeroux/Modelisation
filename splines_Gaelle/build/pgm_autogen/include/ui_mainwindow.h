/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QCheckBox *wireframe;
    QPushButton *draw;
    QPushButton *quit;
    QWidget *tab_4;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout;
    QCheckBox *grid;
    QCheckBox *color_patch;
    QCheckBox *grid_position;
    QCheckBox *surface;
    QWidget *tab;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_2;
    QPushButton *u_back;
    QPushButton *v_back;
    QPushButton *u_front;
    QPushButton *v_front;
    QPushButton *u_back_negative;
    QPushButton *v_back_negative;
    QPushButton *u_front_negative;
    QPushButton *v_front_negative;
    QPushButton *duplicate_boundaries;
    QPushButton *save_grid;
    QPushButton *load_grid;
    QVBoxLayout *layout_scene;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(902, 509);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(300, 400));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayoutWidget = new QWidget(tab_3);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 281, 351));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        wireframe = new QCheckBox(gridLayoutWidget);
        wireframe->setObjectName(QStringLiteral("wireframe"));
        sizePolicy1.setHeightForWidth(wireframe->sizePolicy().hasHeightForWidth());
        wireframe->setSizePolicy(sizePolicy1);
        wireframe->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(wireframe, 0, 0, 1, 1);

        draw = new QPushButton(gridLayoutWidget);
        draw->setObjectName(QStringLiteral("draw"));
        sizePolicy1.setHeightForWidth(draw->sizePolicy().hasHeightForWidth());
        draw->setSizePolicy(sizePolicy1);
        draw->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(draw, 1, 0, 1, 1);

        quit = new QPushButton(gridLayoutWidget);
        quit->setObjectName(QStringLiteral("quit"));
        sizePolicy1.setHeightForWidth(quit->sizePolicy().hasHeightForWidth());
        quit->setSizePolicy(sizePolicy1);
        quit->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(quit, 2, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayoutWidget_2 = new QWidget(tab_4);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 10, 271, 341));
        gridLayout = new QGridLayout(gridLayoutWidget_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        grid = new QCheckBox(gridLayoutWidget_2);
        grid->setObjectName(QStringLiteral("grid"));
        grid->setChecked(true);

        gridLayout->addWidget(grid, 0, 0, 1, 1);

        color_patch = new QCheckBox(gridLayoutWidget_2);
        color_patch->setObjectName(QStringLiteral("color_patch"));

        gridLayout->addWidget(color_patch, 0, 1, 1, 1);

        grid_position = new QCheckBox(gridLayoutWidget_2);
        grid_position->setObjectName(QStringLiteral("grid_position"));
        grid_position->setChecked(true);

        gridLayout->addWidget(grid_position, 1, 0, 1, 1);

        surface = new QCheckBox(gridLayoutWidget_2);
        surface->setObjectName(QStringLiteral("surface"));
        surface->setChecked(true);

        gridLayout->addWidget(surface, 1, 1, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayoutWidget_3 = new QWidget(tab);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 20, 271, 331));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        u_back = new QPushButton(gridLayoutWidget_3);
        u_back->setObjectName(QStringLiteral("u_back"));

        gridLayout_2->addWidget(u_back, 0, 0, 1, 1);

        v_back = new QPushButton(gridLayoutWidget_3);
        v_back->setObjectName(QStringLiteral("v_back"));

        gridLayout_2->addWidget(v_back, 0, 1, 1, 1);

        u_front = new QPushButton(gridLayoutWidget_3);
        u_front->setObjectName(QStringLiteral("u_front"));

        gridLayout_2->addWidget(u_front, 1, 0, 1, 1);

        v_front = new QPushButton(gridLayoutWidget_3);
        v_front->setObjectName(QStringLiteral("v_front"));

        gridLayout_2->addWidget(v_front, 1, 1, 1, 1);

        u_back_negative = new QPushButton(gridLayoutWidget_3);
        u_back_negative->setObjectName(QStringLiteral("u_back_negative"));

        gridLayout_2->addWidget(u_back_negative, 2, 0, 1, 1);

        v_back_negative = new QPushButton(gridLayoutWidget_3);
        v_back_negative->setObjectName(QStringLiteral("v_back_negative"));

        gridLayout_2->addWidget(v_back_negative, 2, 1, 1, 1);

        u_front_negative = new QPushButton(gridLayoutWidget_3);
        u_front_negative->setObjectName(QStringLiteral("u_front_negative"));

        gridLayout_2->addWidget(u_front_negative, 3, 0, 1, 1);

        v_front_negative = new QPushButton(gridLayoutWidget_3);
        v_front_negative->setObjectName(QStringLiteral("v_front_negative"));

        gridLayout_2->addWidget(v_front_negative, 3, 1, 1, 1);

        duplicate_boundaries = new QPushButton(gridLayoutWidget_3);
        duplicate_boundaries->setObjectName(QStringLiteral("duplicate_boundaries"));

        gridLayout_2->addWidget(duplicate_boundaries, 4, 0, 1, 2);

        save_grid = new QPushButton(gridLayoutWidget_3);
        save_grid->setObjectName(QStringLiteral("save_grid"));

        gridLayout_2->addWidget(save_grid, 5, 0, 1, 1);

        load_grid = new QPushButton(gridLayoutWidget_3);
        load_grid->setObjectName(QStringLiteral("load_grid"));

        gridLayout_2->addWidget(load_grid, 5, 1, 1, 1);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        horizontalLayout->addLayout(verticalLayout);

        layout_scene = new QVBoxLayout();
        layout_scene->setObjectName(QStringLiteral("layout_scene"));
        layout_scene->setSizeConstraint(QLayout::SetDefaultConstraint);

        horizontalLayout->addLayout(layout_scene);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 902, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        wireframe->setText(QApplication::translate("MainWindow", "Wireframe", Q_NULLPTR));
        draw->setText(QApplication::translate("MainWindow", "Draw", Q_NULLPTR));
        quit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Viewer", Q_NULLPTR));
        grid->setText(QApplication::translate("MainWindow", "Grid", Q_NULLPTR));
        color_patch->setText(QApplication::translate("MainWindow", "Color patch", Q_NULLPTR));
        grid_position->setText(QApplication::translate("MainWindow", "Grid position", Q_NULLPTR));
        surface->setText(QApplication::translate("MainWindow", "Surface", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Spline", Q_NULLPTR));
        u_back->setText(QApplication::translate("MainWindow", "+u back", Q_NULLPTR));
        v_back->setText(QApplication::translate("MainWindow", "+v back", Q_NULLPTR));
        u_front->setText(QApplication::translate("MainWindow", "+u front", Q_NULLPTR));
        v_front->setText(QApplication::translate("MainWindow", "+v front", Q_NULLPTR));
        u_back_negative->setText(QApplication::translate("MainWindow", "-u back", Q_NULLPTR));
        v_back_negative->setText(QApplication::translate("MainWindow", "-v back", Q_NULLPTR));
        u_front_negative->setText(QApplication::translate("MainWindow", "-u front", Q_NULLPTR));
        v_front_negative->setText(QApplication::translate("MainWindow", "-v front", Q_NULLPTR));
        duplicate_boundaries->setText(QApplication::translate("MainWindow", "Duplicate boundaries", Q_NULLPTR));
        save_grid->setText(QApplication::translate("MainWindow", "Save Grid", Q_NULLPTR));
        load_grid->setText(QApplication::translate("MainWindow", "Load Grid", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Control Polygon", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
