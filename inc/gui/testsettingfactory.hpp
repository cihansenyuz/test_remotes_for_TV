#include <QDialog>
#include <memory>
#include "IRSVTsettingsdialog.hpp"

class TestSettingsFactory{
public:
    static std::unique_ptr<QDialog> createTestSettings(const QString &testName){
        if(testName == "IrSignalValidationTest"){
            return std::make_unique<IRSVTSettingsDialog>();
        } else {
            return nullptr;
        }
    }
};