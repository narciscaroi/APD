package task1;

public class Task1 implements Runnable {
        private int threadId;
        public Task1(final int id){
                this.threadId = id;
        };

        @Override
        public void run() {
                System.out.println("Hello from thread " + threadId);
        }
}
