package binarySearch;

public class MyThread extends Thread {
        int found = 0;
        int el;
        int position;
        int[] v;

        MyThread(int element, int position, int[] v){
                this.el = element;
                this.position = position;
                this.v = v;
        }

        public void run() {
                if(v[position] > el) {
                        found = -1;
                } else if(v[position] == el) {
                        found = 0;
                } else if(v[position] < el) {
                        found = -1;
                }
        }
}
