package multipleProducersMultipleConsumersNBuffer;

import java.nio.file.Path;
import java.util.Queue;
import java.util.concurrent.Semaphore;

/**
 * @author Gabriel Gutu <gabriel.gutu at upb.ro>
 *
 */
public class Buffer {
    
    Queue queue;
    private Semaphore semProducator;
    private Semaphore semConsumator;
    
    public Buffer(int size) {
        queue = new LimitedQueue(size);
        semProducator = new Semaphore(size);
        semConsumator = new Semaphore(0);
    }

    void put(int value) {
        try{
                semProducator.acquire();
        } catch (InterruptedException e) {
                e.printStackTrace();
        }
        synchronized (queue){
                queue.add(value);
        }
        semConsumator.release();
    }

    int get() {
            try {
                    semConsumator.acquire();
            } catch (InterruptedException e) {
                    e.printStackTrace();
            }
            int aux;
            synchronized (queue){
                    aux = (int)queue.poll();
            }
            semProducator.release();
            return aux;
    }
}
