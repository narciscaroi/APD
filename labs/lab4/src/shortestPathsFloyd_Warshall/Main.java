package shortestPathsFloyd_Warshall;
/**
 * @author cristian.chilipirea
 *
 */
public class Main {

	public static void main(String[] args) {
		int M = 9;
		int graph[][] = { { 0, 1, M, M, M }, 
				          { 1, 0, 1, M, M }, 
				          { M, 1, 0, 1, 1 }, 
				          { M, M, 1, 0, M },
				          { M, M, 1, M, 0 } };
		
		// Parallelize me (You might want to keep the original code in order to compare)
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
				}
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(graph[i][j] + " ");
			}
			System.out.println();
		}

		int graph2[][] = { { 0, 1, M, M, M },
			{ 1, 0, 1, M, M },
			{ M, 1, 0, 1, 1 },
			{ M, M, 1, 0, M },
			{ M, M, 1, M, 0 } };
		int numThreads = Runtime.getRuntime().availableProcessors();
		int i;

		Thread[] threads = new Thread[numThreads];
		for (i = 0; i < numThreads; i++){
			threads[i] = new Thread(new Task(i, 5, numThreads, graph2));
			threads[i].start();
		}

		for(i = 0; i < numThreads; i++){
			try {
				threads[i].join();
			}
			catch (InterruptedException exception){
				exception.printStackTrace();
			}
		}
		System.out.print('\n');
		for (i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(graph2[i][j] + " ");
			}
			System.out.println();
		}
	}
}
