/*
* Probably not the most elegant way...
* but gets accepted anyway
*
* Rectangle Fit (csacademy)
*/

import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Main {
    static class Solver {
        class Pt {
            long x, y;

            Pt(int x, int y) {
                this.x = x;
                this.y = y;
            }

            long area() {
                return x * y;
            }

            @Override
            public String toString() {
                return "Pt{" +
                        "x=" + x +
                        ", y=" + y +
                        '}';
            }
        }

        PriorityQueue<Pt> xqueue;
        PriorityQueue<Pt> yqueue;
        Scanner sc = new Scanner(System.in);

        int N, A;
        Solver() {
            N = sc.nextInt();
            A = sc.nextInt();
            ArrayList<Pt> pts = new ArrayList<>(N);
            for (int i = 0 ; i < N; i ++) {
                Pt np = new Pt(sc.nextInt(), sc.nextInt());
                pts.add(np);
            }

            xqueue = new PriorityQueue<>(N, Comparator.comparingLong(l -> l.x));
            yqueue = new PriorityQueue<>(N, Comparator.comparingLong(l -> -l.y));

            xqueue.addAll(pts);

            int cnt = 0;
            int mcnt = 0;
            while (!xqueue.isEmpty()) {
                Pt cur = xqueue.poll();
                yqueue.add(cur);
                cnt++;
                while(yqueue.peek() != null && yqueue.peek().y > (A / cur.x)) {
                    yqueue.poll();
                    cnt--;
                }
                mcnt = Math.max(cnt, mcnt);
            }

            System.out.println(mcnt);
        }
    }

    public static void main(String[] args) {
        new Solver();
    }
}
