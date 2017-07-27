CXXFLAGS += -I. -std=c++11 -Wall -Wextra -Werror

CPP_FILES = $(wildcard *.cpp)

HouseSensor: makefile $(CPP_FILES)
	$(CXX) $(CXXFLAGS) -lRTIMULib -lcurl -lwiringPi -O $(CPP_FILES) -o $@

stop_sensor: 
	ps -e | grep HouseSensor | awk '{ print $$1; }' | xargs kill -9

Restart_Sensor: stop_sensor HouseSensor 
	./HouseSensor&
