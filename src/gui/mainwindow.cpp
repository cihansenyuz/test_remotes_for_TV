#include "../../inc/gui/mainwindow.hpp"
#include "../../res/ui/ui_mainwindow.h"
#include "../../inc/testfactory.hpp"
#include "../../inc/gui/testsettingfactory.hpp"
#include "../../inc/gui/IRSVTsettingsdialog.hpp"
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

    QObject::connect(ui->test_settings_action, &QAction::triggered,
                    this, [this]() {
                        test_settings = TestSettingsFactory::createTestSettings(selected_test);
                        
                        if(test_settings)
                            test_settings->show();
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
    auto test = TestFactory::createTest(selected_test);
    if (test) {
        QObject::connect(test, &RemoteTest::messageFeed,
                        this, &MainWindow::onTestMessageRecieved);

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
            selected_test = "IrSignalValidationTest";
            ui->test_description->setText("1- Her buton basımında IR sinyalinin header (başlık) kısmını ve IR verisini kontrol eder.\n"
            "2- Eğer arka arkaya max hata adeti kez yanlış okuma yapılırsa, testi sonlandırır.\n"
            "3- Belirli adet testte bir, voltaj ölçümü yapar ve sonucu kaydeder.\n"
            "4- Belirli adet ölçümde bir, hafızadaki test sonuçlarını txt dosyasına kaydeder.\n"
            "5- Toplamda toplam test sayısı kadar basım gerçekleştirilir.");
            break;
        case 1:
            selected_test = "BatteryVoltageAndButtonTest";
            ui->test_description->setText("test-2 tanımı");
            break;
        case 2:
            selected_test = "BatteryChargeMonitoringTest";
            ui->test_description->setText("test-3 tanımı");
            break;
        default:
            selected_test.clear();
            break;
    }
}

void MainWindow::onTestMessageRecieved(const QString &message){
    ui->test_message_browser->append(message);
}