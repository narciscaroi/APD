package task6;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class MyTask extends RecursiveTask<Void> {
    int[] graph;
    int step;

    public MyTask(int[] graph, int step) {
        this.graph = graph;
        this.step = step;
    }

    @Override
    protected Void compute() {
        if (Main.N == step) {
            Main.printQueens(graph);
            return null;
        } else {
            ArrayList<MyTask> tasks = new ArrayList<>();
            for (int i = 0; i < Main.N; ++i) {
                int[] newGraph = graph.clone();
                newGraph[step] = i;
                if (Main.check(newGraph, step)) {
                    tasks.add(new MyTask(newGraph, step + 1));
                    tasks.get(tasks.size() - 1).fork();
                }
            }

            for (MyTask task: tasks) {
                task.join();
            }
        }
        return null;
    }

}