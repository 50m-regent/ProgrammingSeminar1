CC = gcc
OBJS = gcmsub1.o gcmmain1.o

gcm1: $(OBJS)
	$(CC) $^ -o $@

$(OBJS) : gcm.h

clean:
	$(RM) *.o