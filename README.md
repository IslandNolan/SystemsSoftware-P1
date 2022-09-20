# SystemsSoftware-P1 - Fall 2022

## Chained Hash Table: 
Organizes Student Records, and inserts them into a Chained Hash Table. 


### Project Description:
This project verifies, and inserts students in a datastructure called a Chained Hashtable,
A unique signature for a particular student record is generated. Using this signature, we can bind it to the table
size and place it into the Table.  </br>

The records can be inserted in two ways:
 - A Root Element, or-
 - A Chained Element

A root element is an element that is first in any particular table location. It does not rely on a link for its location.
A Chained Element relies on a separate element. The Chained Element is linked to a root element. An example of this is a LinkedList.

There are multiple internal changes done to this project. They are listed below:

- Text Formatting
- Removal of several unused #defines
- Inclusion of new methods/tweaks to exiting structures.
- Inclusion of a Pre-Processor Directive to identify the operating env.
- Removal of several #includes, they are no longer needed.
- Removal of the initializeTable method. This is accomplished with calloc instead.
- Changes to several pre-defined methods including their return types, and parameters.
- Additional Changes that facilitate a better/more efficient experience.

<br/>

## Extra Credit:

The Search Functionality outlined in the project description has been 100% implemented, and is functioning as intended.
Simply pass the filename as an argument if you wish to use this feature. Several cLion Run Configurations are 
included which utilize this feature.

<br/>

## Experiences:
I did not have any issues completing this project in the 25 hours expected. The majority of the time used was spent on formatting, and improving efficiency.
Using C++ Made this far easier than I originall expected. I was able to complete the entire project in <10 Hours as I am extremely familiar with C++.

<br>
One issue I had was dealing with the Windows Style Line break. This was a problem that not only, but many students faced.
As a result, my program disallows the use of files containing Carriage returns, and will exit if it encounters one.
It is important to note that the program only disallows these characters on a Unix based system, as Windows can parse these characters as normal.
It is highly encouraged to convert the file with dos2unix on the course server before grading. 

<br/>

## Shortcomings:

The Project has one Major Shortcoming. This is the aforementioned Carriage Returns on a Unix System.
When running in any Combination of files/OS arch, the program functions exactly as intended. 
The Program does not have any other shortcomings.


## Improvements:

The only improvement I can suggest is that the createStudent method should return a pointer to a student instead of a raw student object. 
This encourages the use of malloc in the correct context.

Another (Potentially) Useful idea to implement would be to pre-convert the file to a unix-format. Another issue I disovered was that the #defines were off by one.



## Compile Instructions:

You can either use GCC, or Cmake for compilation. Either of these will work. 

For Cmake: Navigate to the directory and run "make" from the CLI.

Required Dependencies:

- Cmake
- G++


To Compile:

- Navigate to the root of the project, and run:
- ```sudo cmake . && make```


**You may need to clear the Cache for the previous build in order for this to successfully compile.**

