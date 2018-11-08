import java.io.*;
import java.util.*;
import java.util.concurrent.Semaphore;

public class multiThread extends Thread {

    private List<Integer> array = new ArrayList<Integer>();
    static Semaphore lock = new Semaphore(1);

    File file1;
    File file2;

    public multiThread(File file1, File file2) {
        this.file1 = file1;
        this.file2 = file2;
    }

    public void run() {

        try {
            System.out.println(file2 + " Acquiring lock...");
            lock.acquire();
            System.out.println(file2 + " Got the permit!");
            System.out.println(file2 + " Available Semaphore permits now: " 
                + lock.availablePermits());
        
            try {
                Scanner scanner = new Scanner(file1);
                while(scanner.hasNextInt()){
                    array.add(scanner.nextInt());
                }
                scanner.close();

                Scanner scanner1 = new Scanner(file2);
                while(scanner1.hasNextInt()){
                    array.add(scanner1.nextInt());
                }
                scanner1.close();

                Collections.sort(array);

                FileWriter write = null;
                try {
                    write = new FileWriter("datafile.txt");
                } 
                catch (IOException e) {
                    e.printStackTrace();
                }
                BufferedWriter bw = new BufferedWriter(write);
        
                for(int i: array){
                    bw.write(i + "\n");
                }
                bw.close();
            }
            catch (IOException e) {
                e.printStackTrace();
            }
        
        finally {
            System.out.println(file2 + " Releasing lock...");
            lock.release();
            System.out.println("Available Semaphore permits now: " 
                + lock.availablePermits() + System.getProperty("line.separator"));
            } 
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {

        File mainFile = new File("datafile.txt");
        File file1 = new File("new1.txt");
        File file2 = new File("new2.txt");
        File file3 = new File("new3.txt");

        //Semaphore key = new Semaphore(1,true);

        multiThread thread1 = new multiThread(mainFile, file1);
        thread1.start();
        multiThread thread2 = new multiThread(mainFile, file2);
        thread2.start();
        multiThread thread3 = new multiThread(mainFile, file3);
        thread3.start();
    }
}