import java.io.*;
import java.util.*;
import java.util.concurrent.Semaphore;

public class multiThread extends Thread {

    //array for merging both file's content and perform sorting
    private List<Integer> array = new ArrayList<Integer>();

    //limiting the # key to be 1
    static Semaphore lock = new Semaphore(1);

    File file1;
    File file2;

    //multiThread class contain two file, where file1 is the mainfile and file2 is the file getting merge.
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
                //scan the mainfile to the array
                Scanner scanner = new Scanner(file1);
                while(scanner.hasNextInt()){
                    array.add(scanner.nextInt());
                }
                scanner.close();

                //scan the second file to the array
                Scanner scanner1 = new Scanner(file2);
                while(scanner1.hasNextInt()){
                    array.add(scanner1.nextInt());
                }
                scanner1.close();

                //sort the entire array
                Collections.sort(array);

                //write the array contents back to the mainfile
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
            //release the lock after sorting and file writing
            //so the next thread can access
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

        //calling threads
        multiThread thread1 = new multiThread(mainFile, file1);
        thread1.start();
        multiThread thread2 = new multiThread(mainFile, file2);
        thread2.start();
        multiThread thread3 = new multiThread(mainFile, file3);
        thread3.start();
    }
}