package doubleVectorElements;

import static java.lang.StrictMath.min;

public class Task implements Runnable {
        private int threadId;
        private int N;
        private int P;
        private int[] v;

        public Task(final int id, final int N, final int P, int[] v) {
                this.threadId = id;
                this.N = N;
                this.P = P;
                this.v = v;
        };

        @Override
        public void run() {
                int start = threadId * N/P;
                int end = min((threadId+1) * N/P,N);
                for(int i = start; i < end; i++){
                        v[i] = v[i] * 2;
                }
        }

}