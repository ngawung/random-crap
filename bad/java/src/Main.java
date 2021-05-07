import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;


public class Main {

	
	public static void main(String[] args) throws IOException {
		File file = new File("src/data");
		FileInputStream in = new FileInputStream(file);
		byte[] buffer = new byte[120*90];
		
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		GZIPOutputStream gzip = new GZIPOutputStream(out);
		DataOutputStream dos = new DataOutputStream(gzip);
		
		// convert byte to positive buffer[400] & 0xff
		
		int frame = 0;
		
		while (in.available() > 0) {
			in.read(buffer);
			
			dos.write(buffer);
			
			frame++;
			System.out.println(frame);
		}
		
		gzip.close();
		byte[] out_result = out.toByteArray();
		dos.close();
		out.close();
		System.out.println(out_result.length);
		
		try (FileOutputStream fos = new FileOutputStream("compress")) {
		   fos.write(out_result);
		   //fos.close(); There is no more need for this line since you had created the instance of "fos" inside the try. And this will automatically close the OutputStream
		}

		
		
		//////////////////////
		
//		frame = 0;
//		int pixel = 0;
//		char[] read_data = new char[5400]; 
//		
//		ByteArrayInputStream bin = new ByteArrayInputStream(out_result);
//		GZIPInputStream gzip2 = new GZIPInputStream(bin);
//		InputStreamReader dis = new InputStreamReader(gzip2, "UTF-8");
//		
//		while (true) {
//			if (dis.read(read_data, 0, read_data.length) == -1) break;
//			pixel++;
//			System.out.println("frame " + pixel);
////			if (pixel > 5400) {
////				frame++;
////				pixel = 0;
////			}
//		}

	}



}
