public class Main {

        public static final int N_PRODUCERS = 3; //x
        public static final int N_CONSUMERS = 100;//y
        public static final int limQuSize = 30;

        public static void main(String[] args) {
                Buffer buffer = new Buffer(limQuSize);
                Thread threads[] = new Thread[N_CONSUMERS + N_PRODUCERS];

                for (int i = 0; i < N_PRODUCERS; i++)
                        threads[i] = new Thread(new Producer(buffer, i));
                for (int i = N_PRODUCERS; i < N_CONSUMERS + N_PRODUCERS; i++)
                        threads[i] = new Thread(new Consumer(buffer, i - N_PRODUCERS));

                for (int i = 0; i < N_CONSUMERS + N_PRODUCERS; i++)
                        threads[i].start();
                for (int i = 0; i < N_CONSUMERS + N_PRODUCERS; i++) {
                        try {
                                threads[i].join();
                        } catch (InterruptedException e) {
                                e.printStackTrace();
                        }
                }
    }
}
