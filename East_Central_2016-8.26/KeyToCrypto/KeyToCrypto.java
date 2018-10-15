import java.util.Scanner;

public class Main {
    static class Solver {
        public Solver() {
            Scanner sc = new Scanner(System.in);
            while (sc.hasNextLine()) {
                String en = sc.nextLine();
                String k = sc.nextLine();
                System.out.println(solve(en,k));
            }
        }

        StringBuilder sb = new StringBuilder();

        void solve_(String encrypted, String word) {
            if (encrypted.isEmpty()) return;
            int k = toRot(word.charAt(0));
            int q = toRot(encrypted.charAt(0));
            char r = (char) ((q + 26 - k) % 26 + 'A');
            sb.append(r);
            String nw = word.substring(1) + r;
            solve_(encrypted.substring(1), nw);
        }

        String solve(String encrypted, String word) {
            sb = new StringBuilder();
            solve_(encrypted, word);
            return sb.toString();
        }

        int toRot(char x) {
            return x - 'A';
        }
    }

    public static void main(String[] args) {
        new Solver();
    }

}
