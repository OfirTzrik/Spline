TARGET = spline
LIBS   = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -ansi -pedantic -s -O2

all: $(TARGET)

$(TARGET): spline.c
	cc spline.c $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean

