package task1;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;

public class MyRunnable implements Runnable{

    ExecutorService tpe;
    ArrayList<Integer> partialPath;
    AtomicInteger inQueue;
    int destination;

    MyRunnable(ExecutorService tpe, ArrayList<Integer> partialPath, int destination, AtomicInteger inQueue) {
        this.tpe = tpe;
        this.destination = destination;
        this.partialPath = partialPath;
        this.inQueue = inQueue;
    }

    @Override
    public void run() {
        if (partialPath.get(partialPath.size() - 1) == destination) {
            System.out.println(partialPath);
            tpe.shutdown();
        }

        for (int[] ints : Main.graph) {
            if (ints[0] == partialPath.get(partialPath.size() - 1)) {
                if (partialPath.contains(ints[1]))
                    continue;
                ArrayList<Integer> newPartialPath = new ArrayList<>(partialPath);
                newPartialPath.add(ints[1]);
                tpe.submit(new MyRunnable(tpe, newPartialPath, destination, inQueue));
            }
        }
        int left = inQueue.decrementAndGet();
        if (left == 0) {
            tpe.shutdown();
        }
    }

}
