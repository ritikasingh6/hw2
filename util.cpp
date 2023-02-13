#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    int start = 0;
		int end = 0;
    set<string> keys;
		for (unsigned int i = 0; i < rawWords.length(); i++){
			if (i == rawWords.length()-1){
				end = i;
				if (end-start+1>=2){
        	keys.insert(rawWords.substr(start,end-start+1));
      	}	
			}
			else if (rawWords[i] < 65){
				end = i-1; 
				if (end-start+1>=2){
					keys.insert(rawWords.substr(start,end-start+1)); 
				}
				start = i+1; 
			}
			else if (rawWords[i] > 122){
				end = i-1; 
				if (end-start+1>=2){
					keys.insert(rawWords.substr(start,end-start+1)); 
				}
				start = i+1; 
			}
			else if((rawWords[i] > 90 && rawWords[i] < 97)){
				end = i-1; 
				if (end-start+1>=2){
					keys.insert(rawWords.substr(start,end-start+1));
				}
				start = i+1; 
			}
		}
		return keys;
		
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
