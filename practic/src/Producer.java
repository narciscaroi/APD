
public class Producer implements Runnable {
	Buffer buffer;
	int id;
	String str;
	static int counter = 0;
	Producer(Buffer buffer, int id) {
		this.buffer = buffer;
		this.id = id;
		str = "Msg ";
	}

	@Override
	public void run() {
		while(counter <= Main.N_CONSUMERS){
			buffer.put(str + counter);
			counter++;
			if(counter == Main.N_CONSUMERS){
				System.out.println("Thread-urile producatoare au scris" +
					"toate cele " + Main.N_CONSUMERS + " mesaje");
			}
		}
	}

}
