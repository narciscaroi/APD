package task3;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.RecursiveTask;

public class MyRunnable implements Runnable {
    int[] graph;
    int step;
    ExecutorService tpe;

    public MyRunnable(int[] graph, ExecutorService tpe, int step) {
        this.graph = graph;
        this.step = step;
        this.tpe = tpe;
    }


    @Override
    public void run() {
        if (Main.N == step) {
            Main.printQueens(graph);
            tpe.shutdown();
        } else {
            for (int i = 0; i < Main.N; i++) {
                int[] newGraph = graph.clone();
                newGraph[step] = i;

                if (Main.check(newGraph, step)) {
                    tpe.submit(new MyRunnable(newGraph, tpe, step + 1));
                }
            }

        }
    }
}