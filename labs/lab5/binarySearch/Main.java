package binarySearch;

public class Main {
        public static void main(String[] args) throws InterruptedException {
                int numThreads = Runtime.getRuntime().availableProcessors();
                int[] pozitii_in_threads = new int[numThreads];
                int[] v = new int[100];
                for(int i = 0; i < 10; i++) {
                        v[i] = i;
                }

                int element_cautat = 5;
                int start = 0;
                int end = 100;
                boolean finished = false;
                MyThread[] threads = new MyThread[numThreads];

                while (start <= end && !finished) {
                        for(int i = 0; i < numThreads; i++) {
                                pozitii_in_threads[i] = start +
                                        (int) ((double) (end-start) /
                                                (numThreads+1) * (i+1));

                                threads[i] = new MyThread(element_cautat, pozitii_in_threads[i], v);
                                threads[i].start();
                        }

                        for(int i = 0; i < numThreads; i++) {
                                try {
                                        threads[i].join();
                                }
                                catch (InterruptedException exception){
                                        exception.printStackTrace();
                                }
                        }

                        for(int i = 0; i < numThreads; i++){
                                if(threads[i].found == 0) {
                                        finished = true;
                                        System.out.println(threads[i].position);
                                        break;
                                }
                                else if(i == 0 && threads[i].found == -1)
                                        end = pozitii_in_threads[i]-1;
                                else if(i == numThreads-1 && threads[i].found == 1)
                                        start = pozitii_in_threads[i] + 1;
                                else if(threads[i].found == 1 &&
                                        threads[i+1].found == -1 &&
                                        i < numThreads-1) {

                                        start = pozitii_in_threads[i] + 1;
                                        end = pozitii_in_threads[i] - 1;
                                }

                        }
                }
        }
}
