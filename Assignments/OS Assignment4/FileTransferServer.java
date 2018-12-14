import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class FileTransferServer {
    
    public static void main(String[] args) throws Exception, FileNotFoundException {
        //Initialize Sockets
        ServerSocket listener = new ServerSocket(6000);

        //specific the old path here:
        String path = "/home/gor/Desktop/CSC332---Operating-System/Assignments/OS Assignment4/OldPath/pdftest.pdf";
        Socket socket = listener.accept();

        try
        {
            //Specify the file
            File file = new File(path);
            FileInputStream fis = new FileInputStream(file);
            BufferedInputStream bis = new BufferedInputStream(fis);

            //Get socket's output stream
            OutputStream os = socket.getOutputStream();

            //Read File Contents into contents array
            byte[] contents;
            long fileLength = file.length();
            long current = 0;
            
            while(current!=fileLength){
                int size = 10000;
                if(fileLength - current >= size)
                    current += size;
                else{
                    size = (int)(fileLength - current);
                    current = fileLength;
                }
                contents = new byte[size];
                bis.read(contents, 0, size);
                os.write(contents);
            }
        
        os.flush();
        //File transfer done. Close the socket connection!
        bis.close();
        socket.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("Error, Server is closing...");
            e.printStackTrace();
            System.exit(-1);
        }
        finally
        {
            listener.close();
            System.out.println("Server: File sent succesfully!");
        }
    }
}