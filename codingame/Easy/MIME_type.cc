/*Author: Randal Obringer
* Date Last Modified: 8/15/2016
* 
* Difficulty: Easy
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: MIME types are used in numerous internet protocols to associate a media type (html, image, video ...) 
*	with the content sent. The MIME type is generally inferred from the extension of the file to be sent. You have to write 
*	a program that makes it possible to detect the MIME type of a file based on its name. 
*
* Rules:
*	You are provided with a table which associates MIME types to file extensions. 
*	You are also given a list of names of files to be transferred and for each one of these files, you must find the MIME type to be used.
*	The extension of a file is defined as the substring which follows the last occurrence, if any, of the dot character within the file name.
*	If the extension for a given file can be found in the association table (case insensitive, e.g. TXT is treated the same way as txt), 
*		then print the corresponding MIME type. If it is not possible to find the MIME type corresponding to a file, or if the file doesn’t 
*		have an extension, print UNKNOWN.
*
* Game Input:
*	Line 1: Number N of elements which make up the association table.
*	Line 2: Number Q of file names to be analyzed.
*	N following lines: One file extension per line and the corresponding MIME type (separated by a blank space).
*	Q following lines: One file name per line.
*
* Output: For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.
*
* Constraints:
*	0 < N < 10000
*	0 < Q < 10000
*   File extensions are composed of a maximum of 10 alphanumerical ASCII characters.
*   MIME types are composed of a maximum 50 alphanumerical and punctuation ASCII characters.
*   File names are composed of a maximum of 256 alphanumerical ASCII characters and dots (full stops).
*   There are no spaces in the file names, extensions or MIME types.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main(){
    int N; // Number of elements which make up the association table.
    cin >> N; cin.ignore();
    int Q; // Number Q of file names to be analyzed.
    cin >> Q; cin.ignore();
    
    map<string,string> typeAssociations; //log extension to MIME types
    vector<string> fileExts; //hold the file extensions from the Q file names in order
    
    for (int i = 0; i < N; i++) {
        string EXT; // file extension
        string MT; // MIME type.
        cin >> EXT >> MT; cin.ignore();
        transform(EXT.begin(),EXT.end(),EXT.begin(),::tolower);
        //transform(MT.begin(),MT.end(),MT.begin(),::tolower);
        typeAssociations[EXT]=MT;
        //cout << "Extension is: " << EXT << endl;
        //cout << "MIME type is: " << MT << endl;
    }
	
    for (int i = 0; i < Q; i++) {
        string FNAME; // One file name per line.
        getline(cin, FNAME);
        transform(FNAME.begin(),FNAME.end(),FNAME.begin(),::tolower);
        int dotIndex=0; //keep track where the last '.' is in the file name.
        for(int j=0;j<FNAME.size();j++){
            if(FNAME[j]=='.'){
                dotIndex=j;
            }
        }
        
        string currentExt = FNAME.substr(dotIndex+1,FNAME.size()-1);
        //cout << currentExt << endl;
        fileExts.push_back(currentExt);
    }
    
    for(int i=0;i<fileExts.size();i++){
		// For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.
        if(typeAssociations.count(fileExts[i])==0){
            cout << "UNKNOWN" << endl;
        }else{
            cout << typeAssociations[ fileExts[i] ] << endl;
        }
    }
}