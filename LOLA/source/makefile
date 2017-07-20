CXXFLAGS += -I. -std=c++11 -Wall -Wextra -Werror

CPP_FILES = $(wildcard *.cpp)

HouseSensors: makefile $(CPP_FILES)
	@$(CXX) $(CXXFLAGS) -lRTIMULib -lcurl -O $(CPP_FILES) -o $@
