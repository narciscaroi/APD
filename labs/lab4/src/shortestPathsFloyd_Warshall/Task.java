package shortestPathsFloyd_Warshall;

import static java.lang.StrictMath.min;

public class Task implements Runnable {
        private int threadId;
        private int N;
        private int P;
        private int[][] graph;

        public Task(final int id, final int N, final int P, int[][] graph) {
                this.threadId = id;
                this.N = N;
                this.P = P;
                this.graph = graph;
        };

        @Override
        public void run() {
                int start = threadId * N/P;
                int end = min((threadId+1) * N/P,N);
                for (int k = start; k < end; k++) {
                        for (int i = 0; i < 5; i++) {
                                for (int j = 0; j < 5; j++) {
                                        graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
                                }
                        }
                }
        }

}
