package task5;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class MyTask extends RecursiveTask<Void> {
    int[] colors;
    int step;

    public MyTask(int[] colors, int step) {
        this.colors = colors;
        this.step = step;
    }

    @Override
    protected Void compute() {
        if (step == Main.N) {
            Main.printColors(colors);
            return null;
        } else {
            ArrayList<MyTask> tasks = new ArrayList<>();
            for (int i = 0; i < Main.COLORS; i++) {
                int[] newColors = colors.clone();
                newColors[step] = i;
                if (Main.verifyColors(newColors, step)) {
                    tasks.add(new MyTask(newColors, step + 1));
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