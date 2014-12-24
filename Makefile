CFLAGS=-Wall -ggdb `pkg-config --cflags yaml-0.1`
LDFLAGS=-lresolv `pkg-config --libs yaml-0.1`

SOURCES=$(wildcard src/**/*.c src/*.c) 
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TARGET=xstream

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.0:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

