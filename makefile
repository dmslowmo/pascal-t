CPPFLAGS = -O0 -g -Wall -Wextra -pedantic -Werror -std=c++11
RM = rm -rf
SRC = $(shell pwd)
EXEC := $(notdir $(SRC))
SRC_FILES := $(wildcard $(SRC)/*.cpp)
O_FILES := $(SRC_FILES:%.cpp=%.o)

all : $(O_FILES)
	$(CXX) $(CPPFLAGS) -o $(EXEC) $(O_FILES)

clean:
	$(RM) $(O_FILES) $(EXEC)
