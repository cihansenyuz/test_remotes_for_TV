CC = g++
CFLAGS = -std=c++11 -I ./inc
SOLARLESSIRBUTTONCLICKFLAGS = -lwiringPi -lpthread

solarlessIrButtonClick: solarlessIrButtonClick.o ina238.o irManager.o servoController.o
	$(CC) $^ $(CFLAGS) $(SOLARLESSIRBUTTONCLICKFLAGS) -o $@

%.o: ./src/%.cpp ./inc/%.hpp
	@$(CC) -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o solarlessIrButtonClick