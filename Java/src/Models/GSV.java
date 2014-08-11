package Models;

import java.util.LinkedList;

/**
 * This class represents the information relating to a single GSV object, each sentence will be parsed and created here.
 * @author Ryan Gouldsmith (ryg1)
 * Created by ryan on 05/03/14.
 * @version 0.1
 */
public class GSV  extends SpeakParser {
    private LinkedList<Integer> SNR = new LinkedList<Integer>();
    /**
     * This is the GSV constructor, it is used for passing in the array of sentences read in by the input file handler class.
     * It then parses the sentences and extracts the SNR numbers from each sentence accordingly.
     * @param sentence is the array of sentences parsed from a set of GSV sentences.
     */
    public GSV(String[] sentence){

            for (String sentences: sentence){
                getSNRNumber(sentences);
            }
    }
    /**
     * This extracts the SNR number from each of the sentences. The SNR is the fourth item in the information about a set of sentences.
     * It contains a loop which gors to the fourth element and extracts the value and adds it to a list of SNR values.
     * @param sentence is the sentence from the array of sentences.
     */
    public void getSNRNumber(String sentence){
        //create a temp LinkedList
        LinkedList<Integer> temp = new LinkedList<Integer>();
        //split the sentence at the delimeter ,
        String[] foo = sentence.split(",");
        if (!foo[3].isEmpty()){
            //REFERENCE : http://nmeaparser.googlecode.com/svn-history/r24/trunk/NMEAParser/SentenceHandlers/GPGSV.cs
            //goes to the fourth element each time
            for (int i = 4; i+3 < foo.length; i +=4){
                if (foo[i+3].contains("*")){
                    //substring the * from the sentence so it is easier to parse
                    foo[i+3] = foo[i+3].substring(0, foo[i+3].length() -3);
                }
                if (!foo[i+3].equals("")){
                    //adds the values to the linked list.
                    SNR.add(Integer.parseInt(foo[i+3]));
                }
            }
        }
    }
    /**
     * This checks to to see if the SNR values are good enough that we can accept that line.
     * It checks to see if the SNR is over 35, if it is, it increments a counter which if is greater than 3 returns true, else false.
     * @return whether the fix is good or not, via a boolean representation of True or False.
     */
    public boolean isItAGoodFix(){
        int accepted = 0;
        //loop over all the SNR values
        for (Integer snr: getSNR()){
            //checks the SNR
            if (snr > 35){
                //increment accepted
                accepted++;
            }
        }
        //checks accepted is > 3
        if (accepted >= 3){
            return true;
        } else {
            return false;
        }
    }

    /**
     * @return the SNR values, which have been parsed.
     */
    public LinkedList<Integer>getSNR() {
        return SNR;
    }
}
