## Gereksinimler

# wiringPi kütüphanesi
yüklemek için:

'''
$ cd ~
$ git clone https://github.com/WiringPi/WiringPi.git
$ cd WiringPi
$ ./build
'''

Kurulumu teyit etmek için: $ gpio -v

# cmake
yüklemek için:

'''
$ sudo apt update
$ sudo apt install cmake
'''

## Kullanım

batteryChargeMonitoringTest testini build etmek için, cmake'in TEST_FILE değişkenine ilgili testin dosyasını geçmelisiniz.

'''
$ mkdir solar_charge_build
$ cmake -DTEST_FILE=batteryChargeMonitoringTest -B solar_charge_build/
$ cmake --build solar_charge_build/
'''

Testi başlatmak için

'''
$ ./solar_charge_build/remote_tester
'''
