#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include "Sysinfo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
      ui{new Ui::MainWindow},
      mCpuWidget{this}
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(new QHBoxLayout());
    ui->centralwidget->layout()->addWidget(&mCpuWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

