#include "../../inc/gui/mainwindow.hpp"
#include "../../res/ui/ui_mainwindow.h"
#include "../../inc/testfactory.hpp"

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
    QObject::connect(ui->run_test_button, &QPushButton::clicked,
                    this, &MainWindow::onRunTestButtonClicked);
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRunTestButtonClicked()
{
    QString selectedTest = "IrSignalValidationTest"; // assign from user selection
    auto test = TestFactory::createTest(selectedTest);
    if (test) {
        test->runTest();
        delete test; // Clean up after the test
    } else {
        // Handle error: test not found
    }
}