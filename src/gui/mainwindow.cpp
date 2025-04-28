#include "../../inc/gui/mainwindow.hpp"
#include "../../res/ui/ui_mainwindow.h"
#include "../../inc/testfactory.hpp"
#include <QButtonGroup>

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
    
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->IrSignalValidationTestSelection, 0);
    buttonGroup->addButton(ui->BatteryVoltageAndButtonTestSelection, 1);
    buttonGroup->addButton(ui->BatteryChargeMonitoringTestSelection, 2);
    QObject::connect(buttonGroup, &QButtonGroup::idClicked,
                    this, &MainWindow::onTestSelectionChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRunTestButtonClicked()
{
    auto test = TestFactory::createTest(selectedTest);
    if (test) {
        test->runTest();
        delete test; // Clean up after the test
    } else {
        // Handle error: test not found
    }
}

void MainWindow::onTestSelectionChanged(int test_id)
{
    if(test_id >= 0){
        ui->run_test_button->setEnabled(true);
        ui->test_settings_action->setEnabled(true);
    }

    switch (test_id) {
        case 0:
            selectedTest = "IrSignalValidationTest";
            break;
        case 1:
            selectedTest = "BatteryVoltageAndButtonTest";
            break;
        case 2:
            selectedTest = "BatteryChargeMonitoringTest";
            break;
        default:
            selectedTest.clear();
            break;
    }
}