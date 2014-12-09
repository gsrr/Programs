import java.io.*;

public class DetectArrow {
	private static String ttyConfig;
	public static void main(String[] args) {

		try {
			int c0 = 0;
			int c1 = 0;
			int c2 = 0;
			setTerminalToCBreak();
			while (true) {
				if ( System.in.available() != 0 ) {
					c0 = System.in.read();
					System.out.println("input c:" + c0);
					if ( c0 == 0x71 ) 
					{
						break;
					}
					else
					{
						if( c0 == 0x41 && c1 == 0x5B && c2 == 0x1B)
						{
							System.out.println("up");
						}
						if( c0 == 0x42 && c1 == 0x5B && c2 == 0x1B)
						{
							System.out.println("down");
						}
						if( c0 == 0x43 && c1 == 0x5B && c2 == 0x1B)
						{
							System.out.println("right");
						}
						if( c0 == 0x44 && c1 == 0x5B && c2 == 0x1B)
						{
							System.out.println("left");
						}
					}
					c2 = c1;
					c1 = c0;
				}

			} // end while
		}
		catch (IOException e) {
			System.err.println("IOException");
		}
		catch (InterruptedException e) {
			System.err.println("InterruptedException");
		}
		finally {
			try {
				stty( ttyConfig.trim() );
			}
			catch (Exception e) {
				System.err.println("Exception restoring tty config");
			}
		}

	}

	private static void setTerminalToCBreak() throws IOException, InterruptedException {

		ttyConfig = stty("-g");

		// set the console to be character-buffered instead of line-buffered
		stty("-icanon min 1");

		// disable character echoing
		stty("-echo");
	}

	/**
	 *  Execute the stty command with the specified arguments
	 *  against the current active terminal.
	 */
	private static String stty(final String args)
		throws IOException, InterruptedException {
			String cmd = "stty " + args + " < /dev/tty";

			return exec(new String[] {
					"sh",
					"-c",
					cmd
					});
		}

	/**
	 *  Execute the specified command and return the output
	 *  (both stdout and stderr).
	 */
	private static String exec(final String[] cmd)
		throws IOException, InterruptedException {
			ByteArrayOutputStream bout = new ByteArrayOutputStream();

			Process p = Runtime.getRuntime().exec(cmd);
			int c;
			InputStream in = p.getInputStream();

			while ((c = in.read()) != -1) {
				bout.write(c);
			}

			in = p.getErrorStream();

			while ((c = in.read()) != -1) {
				bout.write(c);
			}

			p.waitFor();

			String result = new String(bout.toByteArray());
			return result;
		}

}
