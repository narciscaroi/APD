package task1;

public class Main {
        public static void main(String[] args) {
                int numThreads = Runtime.getRuntime().availableProcessors();

                Thread[] threads = new Thread[numThreads];
                for(int i = 0; i < numThreads; i++){
                        threads[i] = new Thread(new Task1(i));
                        threads[i].start();
                }

                for(int i = 0; i < numThreads; i++){
                        try {
                                threads[i].join();
                        }
                        catch (InterruptedException exception){
                                exception.printStackTrace();
                        }
                }
        }
}
