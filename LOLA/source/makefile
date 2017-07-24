CXXFLAGS += -I. -std=c++11 -Wall -Wextra -Werror

CPP_FILES = $(wildcard *.cpp)

Humidity_Sensor: makefile $(CPP_FILES)
	$(CXX) $(CXXFLAGS) -lRTIMULib -lcurl -O $(CPP_FILES) -o $@

stop_sensor: 
	ps -e | grep Humidity_Sensor | awk '{ print $$1; }' | xargs kill -9

Restart_Sensor: stop_sensor Humidity_Sensor 
	./Humidity_Sensor&
