import java.util.ArrayList;
import java.util.HashMap;
import java.util.Objects;
import java.util.Scanner;

public class Main {
    static class Solver {
        int N = 29;
        int M = 3;

        int[] values = {7, 3, 2};

        int[][] mem;


        HashMap<String, Integer> indices;

        int[][] coords;

        double[][] dis;

        int P;


        double distance(int i, int j) {
            double sm = 0;
            for (int n = 0; n < 3; n ++) {
                sm += Math.pow(coords[i][n] - coords[j][n], 2);
            }
            return Math.sqrt(sm);
        }

        Solver() {
            Scanner sc = new Scanner(System.in);
            int T = sc.nextInt();
            for (int i_ = 0; i_ < T; i_ ++) {
                System.out.println(String.format("Case %d:", i_ + 1));
                indices = new HashMap<>();
                P = sc.nextInt();
                coords = new int[P][3];
                for (int i =0 ; i < P; i ++) {
                    String name = sc.next("\\w+");
                    indices.put(name, i);
                    for (int j = 0; j < 3; j ++) {
                        coords[i][j] = sc.nextInt();
                    }
                }

                dis = new double[P][P];

                for (int i = 0; i < P; i ++) {
                    for (int j = 0; j < P; j ++) {
                        if (i == j) {
                            dis[i][j] = 0;
                        } else {
                            dis[i][j] = distance(i, j);
                        }
                    }
                }

                int holes = sc.nextInt();
                for (int i = 0; i < holes; i ++) {
                    String f = sc.next("\\w+");
                    String g = sc.next("\\w+");
                    dis[indices.get(f)][indices.get(g)] = 0;
                }

                for (int k = 0; k < P; k ++) {
                    for (int i = 0; i < P; i ++) {
                        for (int j = 0; j < P; j ++) {
                            double r = dis[i][k] + dis[k][j];
                            if (r < dis[i][j]) {
                                dis[i][j] = r;
                            }
                        }
                    }
                }

                int qs = sc.nextInt();
                for (int i = 0; i <qs; i ++) {
                    String f = sc.next("\\w+");
                    String g = sc.next("\\w+");
                    double r = dis[indices.get(f)][indices.get(g)];
                    int r_ = (int) Math.round(r);
                    String s = String.format(
                            "The distance from %s to %s is %d parsecs.",
                            f, g, r_
                    );

                    System.out.println(s);
                }
            }
        }
    }

    public static void main(String[] args) {
        new Solver();
    }

}