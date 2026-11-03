
import java.util.*;

public class exp5 {

    public static int partition(int a[], int low, int high) {
        int pivot = a[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {

            if (a[j] <= pivot) {
                i++;
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }

        }
        int temp = a[i + 1];
        a[i + 1] = a[high];
        a[high] = temp;

        return i + 1;

    }

    public static void quickSort(int a[], int low, int high) {

        if (low < high) {
            int p = partition(a, low, high);
            quickSort(a, low, p - 1);
            quickSort(a, p + 1, high);

        }

    }

    public static int randomPartition(int a[], int low, int high) {
        int r = low + new Random().nextInt(high - low + 1);

        int temp = a[r];
        a[r] = a[high];
        a[high] = temp;

        return partition(a, low, high);

    }

    public static void randomQuickSort(int a[], int low, int high) {

        if (low < high) {
            int p = randomPartition(a, low, high);
            randomQuickSort(a, low, p - 1);
            randomQuickSort(a, p + 1, high);

        }

    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the size of the array: ");
        int n = sc.nextInt();
        int a[] = new int[n];

        System.out.println("Enter the elements of Array: ");

        for (int i = 0; i < n; i++) {

            a[i] = sc.nextInt();
        }
        int b[] = a.clone();
        long start = System.nanoTime();
        quickSort(a, 0, n - 1);
        long end = System.nanoTime();
        System.out.println(Arrays.toString(a));
        System.out.println("Time: " + (end - start) / 1000 + " microseconds");

        start = System.nanoTime();
        randomQuickSort(b, 0, n - 1);
        end = System.nanoTime();
        System.out.println(Arrays.toString(b));
        System.out.println("Time: " + (end - start) / 1000 + " microseconds");

    }
}
