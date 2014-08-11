package Models;

/**
 * This class acts as a placeholder before putting into the model.  Used to compare the values from the two source files
 * @author  Ryan Gouldsmith (ryg1)
 * @since 06/03/14.
 * @version 0.2
 */
public class SpeakParser {
    //Private variables
    private double time;
    private double lat;
    private double lng;
    /**
     * @return the longitude instance of this class
     */
    public double getLng() {
        return lng;
    }
    /**
     * This sets the longitude for the class
     * @param lngnew is the new longitude.
     */
    public void setLng(double lngnew) {
        lng = lngnew;
    }
    /**
     * @return the latitude instance of the class
     */
    public double getLat() {
        return lat;
    }
    /**
     * sets the latitude for the instance of the class
     * @param latnew is the new latitude that is to be assigned to the private variable lat
     */
    public void setLat(double latnew) {
        lat = latnew;
    }
    /**
     * sets the time for the instance of the class
     * @param timenew is the new time which is going to be set to the variable time
     */
    public void setTime(double timenew){
        time = timenew;
    }
    /**
     * @return the time instance for this class
     */
    public double getTime(){
        return this.time;
    }


}
