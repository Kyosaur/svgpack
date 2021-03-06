#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSvgWidget>
#include <QGraphicsSvgItem>
#include <QFileDialog>
#include <QSvgRenderer>
#include <QTimer>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->svgLayout->setScene(new QGraphicsScene(this));
    // i hate it
    connect(ui->svgLayout, &SvgLayout::ready, this, [this](){
        this->ui->svgLayout->setSize(
            this->ui->canvasWidth->value(),
            this->ui->canvasWidth->value()
        );
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_load_clicked()
{
    auto filenames = QFileDialog::getOpenFileNames(
                this,
                "Select one or more SVGs",
                "",
                "SVGs (*.svg)");
    for (auto name : filenames) {
        ui->svgLayout->addItem(name);
    }
    ui->svgLayout->layoutItems();
}

void MainWindow::on_canvasWidth_valueChanged(int width)
{
    ui->svgLayout->setSize(width, ui->canvasHeight->value());
}

void MainWindow::on_canvasHeight_valueChanged(int height)
{
    ui->svgLayout->setSize(ui->canvasWidth->value(), height);
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    ui->svgLayout->setDrawBoundingBoxes(checked);
}

void MainWindow::on_pushButton_clicked()
{
    auto filename = QFileDialog::getSaveFileName(
        this,
        "Export SVG as",
        "",
        "SVG (*.svg)"
    );
    ui->svgLayout->exportSvg(filename);
}
