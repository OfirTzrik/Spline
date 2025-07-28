TARGET = spline
SRC = spline.c functions.c
HEADER = functions.h definitions.h
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -ansi -pedantic -s -O2

all: $(TARGET)

$(TARGET): $(SRC) $(HEADER)
	cc $(SRC) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean