CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET   = WordStrike
SRCS     = main.cpp \
           Game.cpp \
           EasyMode.cpp \
           MediumMode.cpp \
           HardMode.cpp \
           WordRepository.cpp \
           Player.cpp \
           HintEngine.cpp \
           SessionManager.cpp \
           FeedbackRenderer.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
