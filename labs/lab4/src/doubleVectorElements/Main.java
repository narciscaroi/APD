package doubleVectorElements;
/**
 * @author cristian.chilipirea
 *
 */
public class Main {

	public static void main(String[] args) {
		int N = 100000013;
		int v[] = new int[N];

		int numThreads = Runtime.getRuntime().availableProcessors();

		for(int i=0;i<N;i++)
			v[i]=i;

		Thread[] threads = new Thread[numThreads];
		// Parallelize me
		for(int i = 0; i < numThreads; i++){
			threads[i] = new Thread(new Task(i, N, numThreads, v));
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

		for (int i = 0; i < N; i++) {
			if(v[i] != i*2) {
				System.out.println("Wrong answer");
				System.exit(1);
			}
		}
		System.out.println("Correct");
	}

}
