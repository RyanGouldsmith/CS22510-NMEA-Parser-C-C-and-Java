import javax.xml.parsers.ParserConfigurationException;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * This is a runner class, this is where the application will run from.
 * @Author Ryan Gouldsmith
 * @version 0.1
 * @since  28/02/14.
 */
public class Runner {
    public static void main (String[] args)throws IOException, FileNotFoundException, ParserConfigurationException{
        //starts the application.
        System.out.println("Reading in the Files");
        InputFileHandler file = new InputFileHandler("gps_1.dat", "gps_2.dat");
        System.out.println("All values have been exported correctly!");
    }

}
