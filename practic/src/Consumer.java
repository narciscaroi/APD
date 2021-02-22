
public class Consumer implements Runnable {
	Buffer buffer;
	int id;
	int counter = 0;
	Consumer(Buffer buffer, int id) {
		this.buffer = buffer;
		this.id = id;
	}

	@Override
	public void run() {
                if (counter == 0) {
                        System.out.println("thread " + id + " read " + buffer.get());
                        counter++;
                }
	}
}