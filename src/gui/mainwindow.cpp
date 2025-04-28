#include "../../inc/gui/mainwindow.hpp"
#include "../../res/ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->hardware_settings_action, &QAction::triggered,
                    this, [this]() {
                        if (!hardware_settings) {
                            hardware_settings = std::make_unique<HardwareSettings>(this);
                        }
                        hardware_settings->show();
                    });
}

MainWindow::~MainWindow()
{
    delete ui;
}