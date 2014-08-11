import Models.Model;
import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
/**
 * A Output file handler class, dealing with exporting the data to a .gps file
 * It uses the Model class and all relevant datato export it to the document.
 * Based on and some code from http://www.mkyong.com/java/how-to-create-xml-file-in-java-dom/
 * @Author Ryan Gouldsmith
 * @version 0.4
 * @since  28/02/14.
 */

public class OutputFileHandler {
    /*private instance variables */
        private Model model;
        private DocumentBuilderFactory fact;
        private DocumentBuilder document;
        private Document xmlFile;
        private Element root;
        private Element wayPoint;
        private Attr attribute;
        private Transformer transformer;
    /**
     * The Constructor takes a model reference which it copies over so that the private model has an instantiation.
     * It also creates a new Documents and new xmlFile
     * @param model is the model from the inputFileHandler class
     * @throws ParserConfigurationException if it can not parse the information
     */
    public OutputFileHandler(Model model) throws ParserConfigurationException {
        this.model = model;
        this.fact = DocumentBuilderFactory.newInstance();
        this.document  = fact.newDocumentBuilder();
        this.xmlFile = document.newDocument();
    }
    /**
     * This creates different elements and all the information inside the gps file.
     * It creates the GPX node, the WPT not and all the attributes that go with both
     * Help from: http://www.topografix.com/gpx_manual.asp#gpx_req
     * @param filename is the filename of the saved .gps file.
     */
    public void write(String filename){
        /*
         * sets the root element, and all the attributes associated with that
         */
        this.setRootElement("gpx");
        this.createAttribute("version");
        this.getAttribute().setValue("1.0");
        this.getRoot().setAttributeNode(this.getAttribute());
        this.createAttribute("creator");
        this.getAttribute().setValue("GPSFix - Ryan Gouldsmith (ryg1@aber.ac.uk)");
        this.getRoot().setAttributeNode(this.getAttribute());
        this.createAttribute("xmlns:xsi");
        this.getAttribute().setValue("http://www.w3.org/2001/XMLSchema-instance");
        this.getRoot().setAttributeNode(this.getAttribute());
        this.createAttribute("xmlns");
        this.getAttribute().setValue("http://www.topografix.com/GPX/1/0");
        this.getRoot().setAttributeNode(this.getAttribute());
        this.createAttribute("xsi:schemaLocation");
        this.getAttribute().setValue("http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd");
        this.getRoot().setAttributeNode(this.getAttribute());

        //loops over the array and gets the values and creates a new way point element
        for(int i = 0; i <model.getLatValues().size(); i++){
            this.setWayPointElemt("wpt", model.getLatValues().get(i), model.getLngValues().get(i));
        }

        TransformerFactory transformerFactory = TransformerFactory.newInstance();
        try {
            transformer = transformerFactory.newTransformer();
        } catch (TransformerConfigurationException e) {
            e.printStackTrace();
        }
        //creates the Dom and outputs it to the file.
        DOMSource source = new DOMSource(this.getXmlFile());
        StreamResult result = new StreamResult(new File(filename));

        try {
            transformer.transform(source, result);
        } catch (TransformerException e) {
            e.printStackTrace();
        }
    }
    /**
     * This appends the root element to be the root element
     * @param name is the name of the element that is to be appeneded to the root
     */
    private void setRootElement(String name){
        root = this.getXmlFile().createElement(name);
        this.getXmlFile().appendChild(root);
    }
    /**
     * This sets the way point element with all the attributes to the root node.
     * @param name of the element
     * @param lat of the current way point
     * @param longitude of the current way point
     */
    private void setWayPointElemt(String name, double lat, double longitude){
        wayPoint = this.getXmlFile().createElement(name);
        this.createAttribute("lat");
        this.getAttribute().setValue(String.valueOf(lat));
        wayPoint.setAttributeNode(this.getAttribute());
        this.createAttribute("lon");
        this.getAttribute().setValue(String.valueOf(longitude));
        wayPoint.setAttributeNode(this.getAttribute());
        root.appendChild(wayPoint);
    }
    /**
     * This sets the model instance variable
     * @param model is the model that is to be assigned over.
     */
    public void setModel(Model model) {
        this.model = model;
    }
    /**
     * @return  the XML file's instance variable
     */
    public Document getXmlFile() {
        return xmlFile;
    }
    /**
     * @return the root elements instance variable
     */
    public Element getRoot() {
        return root;
    }
    /**
     * @return the attribute instance variable
     */
    public Attr getAttribute(){
        return this.attribute;
    }
    /**
     * assigned the attribute instance to a newly created Attribute.
     * @param name is the name of the instance variable that is to be created.
     */
    public void createAttribute(String name){
        this.attribute = this.getXmlFile().createAttribute(name);
    }
}
