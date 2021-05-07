
public class BitwiseTest {

	public static void main(String[] args) {
		
		
		char a = 0x0;
		char b = 0x1;
		
		System.out.println("bit shift");
		for (int i=0; i<8; i++) {			
			System.out.println(Integer.toBinaryString(a | b << i));
		}
		
		System.out.println("more bit shift");
		
		char c = (char)((a | b << 7) | b);
		
		System.out.println(Integer.toBinaryString(c));
		System.out.println(bitStatus(c, 7));

	}
	
	private static int bitStatus(char c, int bit) {
	    return (c >> bit) & 1;
	}


}
