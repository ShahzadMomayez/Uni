import java.util.Scanner;

public class Main {
    public static final int N = 720;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();
        int[][] A = new int[N][N];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = scanner.nextInt();
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    A[i][j] = Math.min(A[i][j], A[i][k] + A[k][j]);
                }
            }
        }

        int m = scanner.nextInt();
        while (m-- > 0) {
            int f = scanner.nextInt();
            int r = scanner.nextInt();
            int u = scanner.nextInt();

            int res1 = A[f][r] + A[r][u];
            int res2 = res1 - A[f][u];
            System.out.println(res1 + " " + res2);
        }
    }
}
