import java.util.*;

public class exp1 {

    public static long recursiveFibonacci(int n) {
        if (n <= 1) {
            return n;
        }

        return recursiveFibonacci(n - 1) + recursiveFibonacci(n - 2);
    }

    public static long iterativeFibonacci(int n) {

        if (n <= 1) {
            return n;
        }

        long a = 0, b = 1;
        for (int i = 2; i <= n; i++) {
            long c = a + b;
            a = b;
            b = c;

        }
        return b;

    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the value of n:");
        int n = sc.nextInt();

        if (n < 0) {
            System.out.println("Enter a valid positive number");
            sc.close();
            return;

        }
        System.out.println("The nth fibonacci number using recursion is :" + recursiveFibonacci(n));
        System.out.println("The nth fibonacci number using iterative function is: " + iterativeFibonacci(n));

    }

}