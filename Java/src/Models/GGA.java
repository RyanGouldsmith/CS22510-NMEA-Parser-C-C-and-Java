package Models;

/**
 * This class stores all attributes relating to the GGA sentence type.
 * @Created 05/03/14.
 * @author Ryan Gouldsmith (ryg1)
 * @version 0.4
 */
public class GGA extends SpeakParser {
    private double timeTaken;
    private double lat;
    private double longnitude;
    private int fixQuality;
    private int numSatellites;
    private double horizontal;
    private double altitude;
    private double height;
    private int checksum;
    /**
     * The default constructor parses the data from the GGA sentence and splits it into the appropriate attribbutes
     * @param sentence is the String array passed in from the Input File Handler, contains a GGA sentence
     */
    public GGA(String sentence[]){
        //parses the time at the second element in the array
        this.timeTaken = Double.parseDouble(sentence[1]);
        //parses the third element to the converLatToDecimal function, and the return value is assigned to the lat variable
        this.lat = convertLatToDecimal(sentence[2]);
        //parses the fifth and sixth elements to the convert Long to Decimal and the resultant is assigned to the longitude attribute
        this.longnitude = convertLongToDecimal(sentence[4], sentence[5]);
    }
    /**
     * This method is based on https://gist.github.com/javisantana/1326141
     * It converts the NMEA version of the Latitude to actual decimal value latitude so it can be exported correctly.
     * @param value is the String representation of the NMEA speak from the sentence being parsed
     * @return the latitude version represented as a decimal value.
     */
    private double convertLatToDecimal(String value){
        double lat = Double.parseDouble(value.substring(2))/60.0f;
        lat +=  Double.parseDouble(value.substring(0, 2));
        return lat;
    }
    /**
     * This method is based on https://gist.github.com/javisantana/1326141
     * It converts the NMEA sentence speak to the Longitude values.
     * @param value is the parsed String from the sentence, which will be converted to the decimal value
     * @param direction is the parsed String value, describing whether it's W OR E
     * @return the longitude version of the NMEA parsed value
     */
    private double convertLongToDecimal(String value, String direction){
        double lng = Double.parseDouble(value.substring(3))/60.0f;
        lng += Double.parseDouble(value.substring(0, 3));
        if(direction.startsWith("W")) {
            lng = -lng;
        }
        return lng;
    }
    /**
     * @return the time taken
     */
    public double getTimeTaken() {
        return this.timeTaken;
    }
    /**
     * @return the latitude for this instance of the Class
     */
    public double getLat() {
        return this.lat;
    }
    /**
     * Sets the latitude for this instance of the class
     * @param lat is the parsed double value of the latitude.
     */
    public void setLat(double lat) {
        this.lat = lat;
    }
    /**
     * @return the longitude of the current instance of the class.
     */
    public double getLongnitude() {
        return this.longnitude;
    }
    /**
     * Sets the longitude of the current GGA instance
     * @param longnitude is the parsed double representation of the NMEA time speak.
     */
    public void setLongnitude(double longnitude) {
        this.longnitude = longnitude;
    }
}

