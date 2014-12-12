CFLAGS=-Wall -ggdb
LDFLAGS=-lresolv

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

