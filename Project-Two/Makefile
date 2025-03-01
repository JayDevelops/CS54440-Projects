CXX = g++
CXXFLAGS = -Wall -std=c++11

# ExectableNames scheme
SENDER = sender 
RECEIVER = receiver 

# Source files
SENDER_SRC = sender.cpp
RECEIVER_SRC = receiver.cpp

# Objectfiles
SENDER_OBJ = $(SENDER_SRC:.cpp=.o)
RECEIVER_OBJ = $(RECEIVER_SRC:.cpp=.o)

all: $(SENDER) $(RECEIVER)

$(SENDER): $(SENDER_OBJ)
	$(CXX) $(CXXFLAGS) -o $(SENDER) $(SENDER_OBJ)

$(RECEIVER): $(RECEIVER_OBJ)
	$(CXX) $(CXXFLAGS) -o $(RECEIVER) $(RECEIVER_OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SENDER) $(RECEIVER) $(SENDER_OBJ) $(RECEIVER_OBJ)

.PHONY: all clean
