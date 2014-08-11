package Models;

import java.util.LinkedList;
import java.util.List;
/**
 * A Models.Model class where all lists of information is stored.
 * Inside this class there are lists of Latitude, longitude and time values,
 * Additionally, with the current latitude and longitude offset values
 * @Author Ryan Gouldsmith
 * @version 0.3
 * @since  28/02/14.
 */
public class Model {
    // private variables
    private List<Double> latValues = new LinkedList<Double>();
    private List<Double> lngValues = new LinkedList<Double>();
    private List<Double> timeValue = new LinkedList<Double>();
    private double offsetLatValue;
    private double offsetLngValue;
    /**
     * Constructor
     */
    public Model(){
    }
    /**
     * @return the time value list.
     */
    public List<Double> getTimeValue() {
        return timeValue;
    }
    /**
     * Sets this classes instance of the longitude offset.
     * @param offset is the longitude offset which is worked out by the subtraction of the Latitude and Longitude values.
     */
    public void setOffsetLngValue(double offset){
        this.offsetLngValue = offset;
    }
    /**
     * @return the Longitude offset
     */
    public double getOffsetLngValue(){
        return this.offsetLngValue;
    }
    /**
     * @return The list of latitude values used for outputting to the file
     */
    public List<Double> getLatValues() {
        return latValues;
    }
    /**
     * @return the list of longitude values use for outputting to the file
     */
    public List<Double> getLngValues() {
        return lngValues;
    }
    /**
     * This sets the latitude offset Value
     * @param value is the offset calculated from the difference between the two latitude points.
     */
    public void setOffsetLatValue(double value){
        this.offsetLatValue = value;
    }
    /**
     * @return the latitude offset value.
     */
    public double getOffsetLatValue(){
        return this.offsetLatValue;
    }


}
