#include "reportFile.hpp"

void ReportFile::measureAndSave(double voltage_value) {
    voltages.push_back(voltage_value);
    save(voltage_value);
}

void ReportFile::save(double voltage_value) {
    std::ofstream file("voltage_measurements.txt", std::ios::app);
    file << voltage_value << std::endl;
    file.close();
}