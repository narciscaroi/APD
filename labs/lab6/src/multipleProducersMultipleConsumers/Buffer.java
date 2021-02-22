package multipleProducersMultipleConsumers;

import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.Semaphore;

public class Buffer {
	ArrayBlockingQueue<Integer> arrBlockingQ = new ArrayBlockingQueue<Integer>(100);


	void put(int value) throws InterruptedException {
		arrBlockingQ.put(value);
	}

	int get() throws InterruptedException {
		return arrBlockingQ.take();
	}
}
