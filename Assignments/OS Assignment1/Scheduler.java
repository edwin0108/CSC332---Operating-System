import java.io.*;
import java.net.Socket;
import java.util.Queue;
import java.util.LinkedList;

public class Scheduler {
    public static Socket socket = null;
    public static void main(String[] args) throws IOException, ClassNotFoundException
    {
        Queue<process> scheduler = new LinkedList<>();
        try
        {
            /**read process list line by line and add to queue*/
            String line = "";
            BufferedReader buffer = new BufferedReader(new FileReader("processes.txt"));
            while ((line = buffer.readLine()) != null)
            {
                scheduler.add(new process(line));
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }

        /**begin processing*/
        while (scheduler.peek() != null)
        {
            process input_process = scheduler.remove();
            process output_process = run(input_process);
            if(output_process.est_remain_time == 0)
            {
                System.out.println("\tScheduler: Process " + output_process.pid + ", "
                        + output_process.program_name + " Completed.");
            }
            else
                scheduler.add(output_process);

            /**added a delay to sees the result clearly */
            try
            {
                Thread.sleep(500);
            }
            catch(InterruptedException e)
            {
                e.printStackTrace();
            }
        }
    }

    public static process run(process proc)
    {
        process output_process = null;
        try
        {
            socket = new Socket("127.0.0.1", 9000);
            ObjectOutputStream os = new ObjectOutputStream((socket.getOutputStream()));
            ObjectInputStream is = new ObjectInputStream(socket.getInputStream());

            os.writeObject(proc);
            output_process = (process) is.readObject();
            socket.close();
        }

        catch(ClassNotFoundException e){
            e.printStackTrace();
            System.exit(-1);
        }

        catch (IOException e) {
            e.printStackTrace();
            System.exit(-1);
        }

        return output_process;
    }
}
