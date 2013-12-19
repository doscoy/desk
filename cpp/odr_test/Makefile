TARGET_NAME = ttt

TARGET = $(TARGET_NAME).exe

SRCS = main.cpp aaa.cpp bbb.cpp

.SUFFIXES:
.SUFFIXES: .o .cpp

LD = g++
CXX = g++

OBJS = $(SRCS:%.cpp=%.o)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

