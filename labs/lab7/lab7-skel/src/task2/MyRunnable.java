package task2;

import java.util.concurrent.ExecutorService;

class MyRunnable implements Runnable {

    ExecutorService tpe;
    int[] colors;
    int step;

    public MyRunnable(ExecutorService tpe, int[] colors, int step) {
        this.tpe = tpe;
        this.colors = colors;
        this.step = step;
    }


    @Override
    public void run() {
        if (step == Main.N) {
            Main.printColors(colors);
            tpe.shutdown();
        }

        for (int i = 0; i < Main.COLORS; i++) {
            int[] newColors = colors.clone();
            newColors[step] = i;
            if (Main.verifyColors(newColors, step))
                tpe.submit(new MyRunnable(tpe, newColors, step + 1));
        }
    }


}