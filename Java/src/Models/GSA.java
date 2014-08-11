package Models;

/**
 * Created by ryan on 04/03/14.
 * @version 0.1
 */
public class GSA extends SpeakParser {
    private char selection;
    private int fix;
    private int prn;
    private double PDOP;
    private double horizontal;
    private double  vertical;
    // check sum beginnswith *
    private int checksum;

    public char getSelection() {
        return selection;
    }

    public void setSelection(char selection) {
        this.selection = selection;
    }

    public int getFix() {
        return fix;
    }

    public void setFix(int fix) {
        this.fix = fix;
    }

    public int getPrn() {
        return prn;
    }

    public void setPrn(int prn) {
        this.prn = prn;
    }

    public double getPDOP() {
        return PDOP;
    }

    public void setPDOP(double PDOP) {
        this.PDOP = PDOP;
    }

    public double getHorizontal() {
        return horizontal;
    }

    public void setHorizontal(double horizontal) {
        this.horizontal = horizontal;
    }

    public double getVertical() {
        return vertical;
    }

    public void setVertical(double vertical) {
        this.vertical = vertical;
    }

    public int getChecksum() {
        return checksum;
    }

    public void setChecksum(int checksum) {
        this.checksum = checksum;
    }
}
