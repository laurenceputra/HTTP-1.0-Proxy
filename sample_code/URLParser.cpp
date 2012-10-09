/**
   @file
   @brief  URL Parser code
  
   @details  This program provides a helper method to parse
     http URLs into server-name, port-number and resource-path.

     <pre>
      Compile:
       $ g++ -o URLParser URLParser.cpp
      Run:
       $ ./URLParser

      Sample Output:
      
       URL: http://www.google.com
       Server Name: www.google.com
       Port Number: 80
       Resource path: /

       URL: http://www.google.com:23
       Server Name: www.google.com
       Port Number: 23
       Resource path: /

       URL: http://www.google.com:54/
       Server Name: www.google.com
       Port Number: 54
       Resource path: /

       URL: http://www.google.com:12/this/is/a/resource/path.html
       Server Name: www.google.com
       Port Number: 12
       Resource path: /this/is/a/resource/path.html

       URL: http://www.google.com:59/index.html?q=networking
       Server Name: www.google.com
       Port Number: 59
       Resource path: /index.html?q=networking

       URL: http://:59/index.html
       Invalid HTTP URL!!

       URL: http://www.google.com:345asc/index.html
       Invalid HTTP URL!!

       URL: http://
       Invalid HTTP URL!!

       URL: ftp://www.google.com/
       Invalid HTTP URL!!
     </pre>
 */

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>

/**
   @brief   Helper method that parses http URLs.

   @details  This method takes a http URL and parses it into
     server-name, port-number, and resource-path. By default,
     port-number is 80.
     <br>
     This method is *not* strictly conformant to RFC 2396. It
     is *not* industrial strength code. But its functionality
     is enough for doing this assignment.

   @param   url        HTTP URL to be parsed
   @param   server     Server-name gets stored here
   @param   port       Port-number gets stored here
   @param   resource   Resource path gets stored here

   @returns   0 on success, other values indicate failure
 */
int parseURL ( const std :: string  &url ,
               std :: string        &server ,
               int                  &port ,
               std :: string        &resource ) {

    // Initialise
    server = "";
    port = 80;
    resource = "/";
    
    // Check for the prefix 'http://'
    if ( url.substr ( 0 , 7 ) != "http://" )
        return -1;

    // Get the server-name
    int i;
    std :: string portNumber = "";
    std :: string *portion = &server;
    for ( i = 7 ; i < url.length() ; ++i ) {

        // Check for '/', the end of the server name (or port number)
        if ( url[i] == '/' ) {
            break;
        }

        // Check for ':', indicating port number is specified
        else if ( url[i] == ':' ) {
            // Start reading port number now
            portion = &portNumber;
        }

        // Otherwise, just append the char
        else {
            *portion += url[i];
        }
    }

    // Server name must have been specified
    if ( server.length() == 0 )
        return -1;

    // If port number was specified, then convert to integer
    if ( portNumber.length() > 0 ) {
        char *invalidChar;
        port = (int) strtol ( portNumber.c_str() , &invalidChar , 10 );
        if ( *invalidChar != '\0' )
            return -1;
    }

    // Rest of the URL is resource path (including possible query strings)
    for ( i += 1 ; i < url.length() ; ++i ) {
        resource += url[i];
    }

    // Return success
    return 0;
}

/// @brief   Analyses a URL.
void analyseURL ( const std :: string &url ) {

    std :: string server , resource;
    int port;

    std :: cout << "URL: " << url << std :: endl;
    if ( parseURL ( url , server , port , resource ) != 0 ) {
        std :: cout << "Invalid HTTP URL!!\n\n";
        return;
    }

    std :: cout << "Server Name: " << server << std :: endl;
    std :: cout << "Port Number: " << port << std :: endl;
    std :: cout << "Resource path: " << resource << std :: endl;
    std :: cout << std :: endl;
}

/// @brief  Just to demonstrate some examples of parsing http URLs
int
main ( int argc , char **argv ) {

    // Parse some URLs
    analyseURL ( "http://www.google.com" );
    analyseURL ( "http://www.google.com:23" );
    analyseURL ( "http://www.google.com:54/" );
    analyseURL ( "http://www.google.com:12/this/is/a/resource/path.html" );
    analyseURL ( "http://www.google.com:59/index.html?q=networking" );

    // Some invalid ones
    analyseURL ( "http://:59/index.html" );
    analyseURL ( "http://www.google.com:345asc/index.html" );
    analyseURL ( "http://" );
    analyseURL ( "ftp://www.google.com/" );
    
    return 0;
}
