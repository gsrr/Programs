import java.io.*;
import java.net.*;

public class socketClient
{
	public static void main(String[] args)
	{
		try
		{
			Socket skt = new Socket("127.0.0.1", 8888); 

			System.out.println("連線成功！嘗試傳送檔案....");

			PrintStream printStream = new PrintStream(skt.getOutputStream()); 
			printStream.println("fileCommand" + " " + "filePath"); 
			BufferedReader in = new BufferedReader(new InputStreamReader(skt.getInputStream()));
			System.out.println(in.readLine());
			System.out.print("OK! 傳送檔案...."); 
		}
		catch(IOException e)
		{
			System.out.println(e);
		}
	}
}
