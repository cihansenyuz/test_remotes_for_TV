# Gereksinimler

## wiringPi kütüphanesi
yüklemek için:

```
$ cd ~
$ git clone https://github.com/WiringPi/WiringPi.git
$ cd WiringPi
$ ./build
```

Kurulumu teyit etmek için:
```$ gpio -v```

## cmake
yüklemek için:

```
$ sudo apt update
$ sudo apt install cmake
```

## Qt Framework
yüklemek için:
https://www.qt.io/download-open-source adresinden installer'ı indir
Installer vasıtasıyla Qt 6.7.3 versiyonu veya gözüken en düşük versiyonu yükle. Üst versiyonlar GLIBC versiyon uyumsuzluğu gösterebilir Rasbian OS ile.

# Kullanım

batteryChargeMonitoringTest testini build etmek için, cmake'in TEST_FILE değişkenine ilgili testin dosyasını geçmelisiniz.

```
$ mkdir solar_charge_build
$ cmake -DTEST_FILE=batteryChargeMonitoringTest -B solar_charge_build/
$ cmake --build solar_charge_build/
```

Testi başlatmak için

```
$ ./solar_charge_build/remote_tester
```
