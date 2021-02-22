package oneProducerOneConsumer;
/**
 * @author cristian.chilipirea
 *
 */
public class Buffer {
	int a=-1;

	synchronized void put(int value) {
		if(a != -1) {
			try {
				wait();
			} catch (InterruptedException e){
				e.printStackTrace();
			}
		}
		a = value;
		notify();
	}

	synchronized int get() {
		if(a == -1){
			try {
				wait();
			} catch (InterruptedException e){
				e.printStackTrace();
			}
		}
		int aux = a;
		notify();
		a = -1;
		return aux;
	}
}
