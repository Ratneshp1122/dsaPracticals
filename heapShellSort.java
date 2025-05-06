import java.util.Scanner;

class heapShellSort {

    public void heapSort(int[] arr){
        int n = arr.length;

        // Build Max Heap
        for(int i = n / 2 - 1; i >= 0; i--){
            heapify(arr, n, i);
        }

        // Extract elements from heap one by one
        for(int i = n - 1; i > 0; i--){
            // Move current root to end
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

    public void heapify(int[] arr, int n, int i){
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if(left < n && arr[left] > arr[largest]){
            largest = left;
        }
        if(right < n && arr[right] > arr[largest]){
            largest = right;
        }

        if(largest != i){
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;

            heapify(arr, n, largest);
        }
    }

    public void display(int[] arr){
        for(int num : arr){
            System.out.print(num + " ");
        }
        System.out.println();
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();
        int[] arr = new int[n];

        System.out.println("Enter the elements:");
        for(int i = 0; i < n; i++){
            arr[i] = sc.nextInt();
        }

        heapShellSort sorter = new heapShellSort();

        System.out.println("Before Heap Sort:");
        sorter.display(arr);

        sorter.heapSort(arr);

        System.out.println("After Heap Sort:");
        sorter.display(arr);

        sc.close();
    }
}
