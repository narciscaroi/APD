package task4;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class MyTask extends RecursiveTask<Void> {
     ArrayList<Integer>  partialPath;
     int destination;

    public MyTask(ArrayList<Integer>  partialPath, int destination) {
        this.partialPath = partialPath;
        this.destination = destination;
    }

    @Override
    protected Void compute() {
        if (partialPath.get(partialPath.size() - 1) == destination) {
            System.out.println(partialPath);
            return null;
        } else {
            ArrayList<MyTask> tasks = new ArrayList<>();
            for (int[] ints : Main.graph) {
                if (ints[0] == partialPath.get(partialPath.size() - 1)) {
                    if (partialPath.contains(ints[1]))
                        continue;
                    ArrayList<Integer> newPartialPath = new ArrayList<>(partialPath);
                    newPartialPath.add(ints[1]);
                    tasks.add(new MyTask(newPartialPath, destination));
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