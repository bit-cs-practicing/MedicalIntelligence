#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "domain/id.h"
#include "core.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << Id("a").getId();
    Core core;
    QMessageBox::information(this, "title", QString::number(core.add(1, 2)));
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

