WhereHaveIGone version 1.0 28/03/2014

General Information 
-----------------------------------------------------------------------------------------------------------------------------------
- The application is to run two text files which must be CSV
  and it will work out which route the user has taken depending
  on the users latitude, longitude and the time. It will work out the 
  best route out of the two, taking into consideration the offset value
  from both the files. It will then output a gps file, which will be 
  a valid GPSX formatted file, and will be able to view on a visual 
  GPSX viewer online.

- The format must be that of the NMEA standard. Where each sentence 
  adheres to the format at http://www.gpsinformation.org/dale/nmea.htm


Compilation of the program
------------------------------------------------------------------------------------------------------------------------------------
- To compile the C program use the GCC compiler:
	-  cd to c/WhereAmI/ inside the directory, type: gcc -o <an output filename> main.c
           eg: gcc -o  WhereAmI main.c will produce a executable file called  WhereAmI. To 
           run this executable file run as a shell script: ./<outputFilename> and it will run the application.
	   Additionally there's already an executable file in the directory: cd c/WhereAmI/bin/Debug
	   this will take you to the executable section. ./WhereAmI will run the pre compiled version of when I 
	   did the screencasts.

- To compile the C++ program use the GCC compiler:
	- cd to C++/GPS/ inside the directory, type: gcc -0 <output filename> main.cpp.
	  eg: gcc -o WhereAmIC++ main.cpp will produce an executable files called WhereAmIC++. To run 
	  this executable file as a shell script use: ./<outputFilename> this will then run the application. 
	  Additionally there's already an executable file in the directory: cd C++/GPS/bin/Debug where there's 
	  an executable file, to run use the command above: ./GPS and it will run theh compiled version of when I
          I did the screencasts.

- To compile and run the Java application you will have to use the Javac compiler:
	- cd to Java/src. Type in javac *.java, this will compile all the java source code. To run the application 
	you will have to type java runner, this will run the main method in the Java application. Additionally you will
	need to to have jdk installed, versoin jdk 1.7 is used for the assignment.
   

Libraries and Packages needed:
------------------------------------------------------------------------------------------------------------------------------------
Below is a list of packages and libraries needed for each application that you need to include, or have imported:
- Java: 
	- Java.util.LinkedList, Java.util.List, java.io., org.w3c.dom, javax.xml.parsers, javax.xml.transform.
	- Note: The Java exporter was based on a tutorial website, references have been included in the JavaDoc class description 
	of where I used the code/ based my implementation on.

- C: 	
	- stdio.h, string.h, stdlib.h, math.h

- C++: - iostream, string, stdio.h, sstream, Markup.h (external library included and referenced to export the file),
       - vector, stdlib.h, fstream, Markup.cpp (The external libraray's implementation. Referenced accordingly)

Files Included
------------------------------------------------------------------------------------------------------------------------------------
- Included in the Java directory are all the the .java and .class files
  under the directory src. Additionally included within the Java directory
  is all the .dat test files that I used to test my application. Aswell as
  a file called java.gpx which outputs the correct positions for the Java 
  application. 
  Names of files in the Java Directory: 
	- java.gpx, gps_1.dat, gps_2.dat,InputFileHandler.class,InputFileHandler.java
	  OutputFileHandler.class, OutputFileHandler.java, Runner.class, Runner.java
          GGA.class, GGA.java, GSA.java, GSV.class, GSV.java, Model.class, Model.java
	  Speak.class, SpeakParser.java, Runner.class, Runner.java

- Included in the C++ directory are all the .cpp and .h files used in the 
  application. There is also the test files used to help generate the results, 
  and the exported version in the c++.gpx which outputs the correct positions 
  for the C++ application. Additionally, there are generated doxygen included.
  As well as a runnible executable file, which is located in bin/debug and is 
  called GPS (see compilation of program to run this).
  Names of the main Files in C++ Directory: 
	 - C++.gpx, Doxyfile, Exporter.cpp, Exporter.h, GGA.cpp, GGA.h, gps_1.dat
	   gps_2.dat, GPS.h, GPSParser.cpp, GPSParser.h, GSV.cpp, GSV.h, InputReader.cpp
	   InputReader.h, main.cpp, Markup.cpp, Markup.h, index.html (viewing the doxygenonline)
	   GPS.exe

- Included in the C directory are all the .c and .h files. There is also the test 
  files I used to help test my application. There are generated doxygen included within
  this directory also. There is a runnable executable file, which is located in bin/debug
  and is called WhereAmI (see compilation of program to run this)
  Names of main Files in C directory
	- Doxyfile, exporter.c, GGA.h, gps_1.dat, gps_2.dat, GSV.h, inputhandler.c
	  InputHandler.h, main.c, model.c, model.h, parser.c, Parser.h, WhereAmI.exe

- Within the screencast section there are all the the screencasts for the three different
  applications at run time, showing the running process, any errors and the output. The screencasts are in .ogv format as this is 
  the file extention given by the screen casting software I used for Linux. This should be able to be opened in VLC or any good 
  video software.

- All GPX files are in the individual langauge directory. I.e the Java GPX is in the directory Java, C++ GPX in C++ directory etc.

- Inside the documentation directory there is the documentation writeup called:
  ryg1_writeup.pdf which is a short write up containing my assumptions and interpretations
=======================================================================================================================================
Contact Details:
---------------------------------------------------------------------------------------------------------------------------------------
Author: Ryan Gouldsmith
Email: ryg1@aber.ac.uk
=======================================================================================================================================
