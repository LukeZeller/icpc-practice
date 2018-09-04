import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;

public class Main {
    static class Solver {
        int N = 29;
        int M = 3;

        int[] values = {7, 3, 2};

        int[][] mem;
        int solve(int s, int p) {


            if (p > N) return -100000;

            if (p == N) return 0;
            if (mem[s][p] != -1) return mem[s][p];
            int v = -1000000;

            for (int i = 0; i < M; i ++) {
                v = Math.max(v, values[i] + solve(s + values[i], p + s + values[i]));
            }

            mem[s][p] = v;

            return v;
        }

        Solver() {
            Scanner sc = new Scanner(System.in);
            int cases = sc.nextInt();
            for (int i = 0; i < cases; i ++) {
                N = sc.nextInt();
                M = sc.nextInt();
                values = new int[M];
                for (int j = 0; j < M; j ++) {
                    values[j] = sc.nextInt();
                }
                mem = new int[N + 1][N + 1];
                clearMem();
                int r = solve(0, 0);
                if (r < -10) {
                    r = -1;
                }
                System.out.println(r);
            }
        }

        void clearMem() {
            for (int i = 0; i < N + 1; i ++) {
                for (int j = 0; j < N + 1; j ++) {
                    mem[i][j] = -1;
                }
            }
        }
    }

    public static void main(String[] args) {
        new Solver();
    }

}