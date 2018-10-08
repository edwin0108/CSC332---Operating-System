import java.awt.print.PrinterAbortException;
import java.io.*;
import java.net.*;
import java.io.IOException;


public class CPU_Emulator {

    /**run the server */
    public static void main(String[] args) throws IOException, ClassNotFoundException
    {
        ServerSocket listener = new ServerSocket(9000);
        listener.setSoTimeout(2000);
        Socket socket = null;
        try
        {
            System.out.println("\nExecution Results: \n" 
            +"###### Round-Robin @ 200 cycles/process: ######\n");
            listener.setSoTimeout(3000);
            while(true)
            {
                socket = listener.accept();
                ObjectOutputStream os = new ObjectOutputStream(socket.getOutputStream());
                ObjectInputStream is = new ObjectInputStream(socket.getInputStream());

                process m = (process) is.readObject();
                m.printprocess();

                /** subtract 200 cycles */
                m.cycle_subtract();

                /**return the update information to the client*/
                os.writeObject(m);
                socket.close();
            }
        }
        catch (SocketTimeoutException e)
        {
            System.out.println("Server is closing...");
            System.exit(-1);
        }
        finally
        {
            listener.close();
        }
    }
}


