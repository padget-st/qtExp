#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), m_tasks{}
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask);
    updateStatus();
}

void MainWindow::addTask()
{
    bool ok{};
    QString name = QInputDialog::getText(this,
                                         tr("Add task"),
                                         tr("Task name"),
                                         QLineEdit::Normal,
                                         tr("Untitled task"),
                                         &ok);
    if(ok && !name.isEmpty())
    {
        qDebug() << "User added a new task by clicking the button";
        Task* task = new Task(name);

        connect(task, &Task::removed, this, &MainWindow::removeTask);
        connect(task, &Task::statusChanged, this, &MainWindow::taskStatusChanged);
        m_tasks.push_back(task);
        ui->tasksLayout->addWidget(task);
        updateStatus();
    }
}

void MainWindow::removeTask(Task* task)
{
    m_tasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task* task)
{
    updateStatus();
}

void MainWindow::updateStatus()
{
    int completedCount{};
    for(auto task : qAsConst(m_tasks))
    {
        if(task->isCompleted())
        {
            completedCount++;
        }
    }

    int todoCount{ m_tasks.size() - completedCount };
    ui->statusLabel->setText(QString("Status: %1 todo / %2 completed")
                             .arg(todoCount)
                             .arg(completedCount));
}

MainWindow::~MainWindow()
{
    delete ui;
}
