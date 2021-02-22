import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.Semaphore;

public class Buffer {
    
    Queue queue;
    private Semaphore semProducator;
    private Semaphore semConsumator;
    
    public Buffer(int size) {
        queue = new LimitedQueue(Main.limQuSize);
        semProducator = new Semaphore(Main.limQuSize);
        semConsumator = new Semaphore(0);
    }

    void put(String str) {
        try{
                semProducator.acquire();
        } catch (InterruptedException e) {
                e.printStackTrace();
        }
        synchronized (queue){
                queue.add(str);
        }
        semConsumator.release();
    }

    String get() {
            try {
                    semConsumator.acquire();
            } catch (InterruptedException e) {
                    e.printStackTrace();
            }
            String aux;
            synchronized (queue){
                    aux = (String)queue.poll();
            }
            semProducator.release();
            return aux;
    }
}
