CC = g++
CFLAGS = -g -O3 -w
  
INCLUDES =
OBJS = main.o

TARGET = Polymorphism

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm $(OBJS) $(TARGET)
	

