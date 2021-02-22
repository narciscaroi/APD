build:
	gcc mutex.c -o mutex -lpthread -Wall
	gcc barrier.c -o barrier -lpthread -Wall
	gcc multiply_seq.c -o multiply_seq -lpthread -Wall -lm
	gcc multiply.c -o multiply -lpthread -Wall -lm
	gcc strassen.c -o strassen -lpthread -Wall
clean:
	rm -rf mutex barrier multiply_seq multiply strassen
