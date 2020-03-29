package Test;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;

public class main {

	public static void main(String[] args) {
		String line1="// code";
		
		
		Process process;
		try { // change path to path exe
			process = new ProcessBuilder("F:\\bari3\\bari3\\bin\\Debug\\TEST.exe","√‘⁄· 13 «‰ Ÿ—  1 À«‰Ì… √ÿ›Ì¡ 13 «‰ Ÿ— 2 À«‰Ì… ").start();
			InputStream is = process.getInputStream();
			InputStreamReader isr = new InputStreamReader(is);
			BufferedReader br = new BufferedReader(isr);
			String line;

		//	System.out.printf("Output of running %s is:", Arrays.toString(args));

			while ((line = br.readLine()) != null) {
			line1=	line1.concat(line+"\n");
				
			}
		
		
		System.out.print(line1.toString());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		// TODO Auto-generated method stub

	}

}
