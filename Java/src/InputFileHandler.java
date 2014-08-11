import Models.*;

import javax.xml.parsers.ParserConfigurationException;
import java.io.*;

/**
 * This class is used for reading in both of the files and aligning and matching the file lines up.
 * @Author Ryan Gouldsmith
 * @version 0.3
 * @since  28/02/14.
 */
public class InputFileHandler {
    private String gpsFileOne;
    private String gpsFileTwo;
    private BufferedReader filereader;
    private BufferedReader fileReaderTwo;
    private GSV gsv;
    private GGA gga, ggaTwo;
    private OutputFileHandler outputHandler;
    private Model model;
    private SpeakParser parserValueOne;
    private SpeakParser parserValueTwo;
    private String lineTwo;
    private boolean fix;
    private String[] arrayOfGsv;
    private String lineTemp;

    /**
     * The constructor for the InputFileHandler will create two speak parsers and instantiate nnoth the filenames
     * It alos makes a reference call to the readFile method, to start parsing in the data.
     * @param filename1 is the first filename
     * @param filename2 is the second filename
     * @throws IOException if it can not find a file.
     * @throws ParserConfigurationException if it fails to parse the data correctly from either of the file.
     */
    public InputFileHandler(String filename1, String filename2) throws IOException, ParserConfigurationException {
        parserValueOne = new SpeakParser();
        parserValueTwo = new SpeakParser();
        this.gpsFileOne = filename1;
        this.gpsFileTwo = filename2;
        readFile();
    }

    /**
     * This file reads in the first file line by line, treating it as a stream.
     * This splits the sentence accordingly and create either a GSV or GGA object, depending on the sentence type.
     * @throws FileNotFoundException if the first file is not found.
     * @throws IOException if there was an error loading the file.
     * @throws ParserConfigurationException if it fails to parse the data correctly from either of the file.
     */
    private void readFile() throws FileNotFoundException, IOException, ParserConfigurationException{
        filereader = new BufferedReader(new FileReader(this.gpsFileOne));
        this.model = new Model();
        String line;
        //sets whether it is found or not
        boolean found = false;
        boolean isOnly;
        //creates a new outputHandler and passes the current model as a parameter
        outputHandler = new OutputFileHandler(this.model);
        while(!found){
            //reads a single line of the file and processes before execution.
            line = filereader.readLine();
            if (line == null){
                break;
            }
            //splits the sentence into a String array with the delimeter comma
            String[] file_one = line.split(",");
            //Matches the GPGGA sentence
            if (line.startsWith("$GPGGA")){
                //creates a new object and parses the data
                gga = new GGA(file_one);
                //if the return value is that it's found a match
                if(readFile2(gga)){
                    //if theres a fix then update the offset and then
                    if(fix){
                        //work out the offset
                        workOutOffSet();
                        //add the values to a linked list
                        model.getLatValues().add(gga.getLat());
                        model.getLngValues().add(gga.getLongnitude());
                        model.getTimeValue().add(gga.getTimeTaken());
                        //update the oututput handlers model
                        outputHandler.setModel(model);
                    }
                    //if there's not a fix work out the difference in the offset and update the model
                    else if (!fix){
                        double lat, lng;
                        workOutOffSet();
                        lat = getLastLatOffSet();
                        lng = getLastLngOffSet();
                        //work out the difference between the last offet and this longnitude
                        ggaTwo.setLongnitude(ggaTwo.getLongnitude() - lng);
                        ggaTwo.setLat(ggaTwo.getLat() - lat);
                        model.getLatValues().add(ggaTwo.getLat());
                        model.getLngValues().add(ggaTwo.getLongnitude());
                        model.getTimeValue().add(ggaTwo.getTimeTaken());
                        //update the model
                        outputHandler.setModel(model);
                    }
                }
            }
            //check to see if the line is a GPGSV sentence, if so process it.
            if (line.startsWith("$GPGSV")){
                //work out the number of sentences
                arrayOfGsv = new String[Integer.parseInt(file_one[1])];
                //shallow copy the line to temp line
                lineTemp = line;
                //loop over the number of sentences in the GSV sentence
                for (int i = 0; i < Integer.parseInt(file_one[1]); i++){

                    if(line.startsWith("$GPGSV")){
                        //add the line to an array
                        arrayOfGsv[i] = lineTemp;
                    }
                    //read the next line
                    lineTemp = filereader.readLine();
                }
                //create a new object and pass the array to it
                gsv = new GSV(arrayOfGsv);
                //update the fix result.
                fix = gsv.isItAGoodFix();
            }
        }
        //prepare to write the information to the gpx file
        outputHandler.write("Java.gpx");


    }
    /**
     * @return the double representation of the last latitude offset which was calculated.
     */
    private double getLastLatOffSet(){
        return model.getOffsetLatValue();
    }

    /**
     * @return the double representation of the last longitude offset which was calculated.
     */
    private double getLastLngOffSet(){
        return model.getOffsetLngValue();
    }

    /**
     * It checks the second file, trying to find a time stamp equalling the same value,
     * It also the second file for GSV sentences, and parses these sentences as they are received.
     * @param gga object created when the application read in the first file.
     * @return a boolean value of whether it has found the time stamp
     * @throws IOException if it cannot load the file.
     */
    private boolean readFile2(GGA gga) throws IOException {
        //creates a new Buffered Reader
        fileReaderTwo = new BufferedReader(new FileReader(this.gpsFileTwo));
        boolean found = false;
        //checks to see if the resultant value is found
        while (!found){
            //reads the next line in the file
            this.lineTwo = fileReaderTwo.readLine();
            //if there is no line in the file return false.
            if (lineTwo == null){
                return false;
            }else {
                //split the line into a string array
                String[] fileTwo = lineTwo.split(",");
                //checks to see if the line starts with GPGGA
                if (lineTwo.startsWith("$GPGGA")){
                    //create a new object passing the parsed line
                    ggaTwo = new GGA(fileTwo);
                    //update the parser references for the two GGA objects
                    addValuesToParser(gga, ggaTwo);
                    //checks to see if the times are the same, if so break out the loop and return true from the mehod
                    if ((int)gga.getTime() == (int) ggaTwo.getTime()){
                        found = true;
                    }
                }
                //checks to see if the line is a GSV sentence
                if (lineTwo.startsWith("$GPGSV")){
                    //work out the number of sentences
                    arrayOfGsv = new String[Integer.parseInt(fileTwo[1])];
                    lineTemp = lineTwo;
                    //loop over the number of sentences
                    for (int i = 0; i < Integer.parseInt(fileTwo[1]); i++){
                        //if there's another sentence parse that
                        if(lineTwo.startsWith("$GPGSV")){
                            arrayOfGsv[i] = lineTemp;
                        }
                        //read another line
                        lineTemp = filereader.readLine();
                    }
                    //create a new GSV object passing the string array to the GSV object
                    gsv = new GSV(arrayOfGsv);
                    //update the fix value
                    fix = gsv.isItAGoodFix();
                }
            }
        }
        //returning true or false to whether it's found a time or not
        return found;
    }
    /**
     * Sets the Time, lat and long values into the parser.
     * @param gga is file ones GGA obect
     * @param ggaTwo is file twos GGA object
     */
    private void addValuesToParser(GGA gga, GGA ggaTwo){
        parserValueOne.setTime(gga.getTimeTaken());
        parserValueTwo.setTime(ggaTwo.getTimeTaken());
        parserValueOne.setLat(gga.getLat());
        parserValueOne.setLng(gga.getLongnitude());
        parserValueTwo.setLat(ggaTwo.getLat());
        parserValueTwo.setLng(ggaTwo.getLongnitude());
    }
    /**
     * Both the latitude and longitude offset is calculated here.
     * The resultant is then stores in an updated value in the model.
     */
    private void workOutOffSet(){
        //checks to see if the first is less than the second, first being file one and second being file two.
        if (parserValueOne.getLat() <= parserValueTwo.getLat()){
            //subtract the second lat from the first lat
            model.setOffsetLatValue((parserValueTwo.getLat() - parserValueOne.getLat()));
        } else if(parserValueTwo.getLat() <= parserValueOne.getLat()){
            //subtract the first lat value from the second
            model.setOffsetLatValue((parserValueOne.getLat() - parserValueTwo.getLat()));
        }
        if (parserValueOne.getLng() <= parserValueTwo.getLng()){
            //subtract the second longitude value from the fist.
            model.setOffsetLngValue((parserValueTwo.getLng() - parserValueOne.getLng()));
        } else if (parserValueTwo.getLng() <= parserValueOne.getLng()){
            //subtract the first longitude from the second longitude.
            model.setOffsetLngValue((parserValueOne.getLng() - parserValueTwo.getLng()));
        }
    }

}
