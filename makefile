TARGET = spline
LIBS   = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: $(TARGET)

$(TARGET): spline.c
	cc spline.c $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean

