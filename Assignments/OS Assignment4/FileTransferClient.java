import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.InetAddress;
import java.net.Socket;


public class FileTransferClient {
    
    public static void main(String[] args) throws Exception{
        //Initialize socket
        Socket socket = new Socket("127.0.0.1", 6000);

        //specific the new path here:
        String path = "/home/gor/Desktop/CSC332---Operating-System/Assignments/OS Assignment4/NewPath/pdftest.pdf";
        byte[] contents = new byte[10000];
        
        //Initialize the FileOutputStream to the output file's full path.
        FileOutputStream fos = new FileOutputStream(path);
        BufferedOutputStream bos = new BufferedOutputStream(fos);
        InputStream is = socket.getInputStream();
        
        //No of bytes read in one read() call
        int bytesRead = 0;
        
        while((bytesRead=is.read(contents))!=-1)
            bos.write(contents, 0, bytesRead);

        bos.flush();
        bos.close();
        socket.close();
        
        System.out.println("Client: File saved successfully!");
    }
}