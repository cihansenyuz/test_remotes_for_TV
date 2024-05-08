CC = g++
CFLAGS = -std=c++11 -I ./inc
LINKERFLAGS = -lwiringPi -lpthread

solarlessIrButtonClick: solarlessIrButtonClick.o ina238.o irManager.o servoController.o
	$(CC) $^ $(CFLAGS) $(LINKERFLAGS) -o $@

solarCharge: solarCharge.o ina238.o
	$(CC) $^ $(CFLAGS) $(LINKERFLAGS) -o $@

%.o: ./src/%.cpp ./inc/%.hpp
	@$(CC) -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o solarlessIrButtonClick solarCharge