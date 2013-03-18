//find_concordance.cpp
//Author :Al-Akhali:Wael
/*
This program produces, and displays on the standard output or writes to a file,
a "concordance" for a file of text.

The Oxford American Dictionary
defines "concordance" like this:
"An index of the important words used in a book or an author's writings."

"A concordance is a list (in alphabetical order) of all words contained in a file,
with each word on a separate line and followed by a list (in increasing numerical order)
of all line numbers of the lines of the file in which the word appears."
Concordances are very useful to writers when they are preparing indexes for their books, for example.

a very particular meaning for the term "word" in this context.
A "word" will be any contiguous string of alphabetic characters, i.e.,
any contiguous string of upper case and/or lower case letters. Thus,
for example, what we would normally think of as the single word "can't" contains,
in this context, two "words", namely "can" and "t".
Among other things, this means that our concordance program views some sequences 
of letters as "words" that would not be considered words in the ordinary everyday sense of the term.

Also, all words are considered to be in lower case.
Thus, in our concordance, "John", "john" and "JOHN" 
would all be regarded as the same word, namely "john".
/*
program is complete and working according to the required
specifications.
*/
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include "utilities.h"
#include <iomanip>
#include <cctype>
#include <string>
using namespace std;
using Scobey::DisplayOpeningScreen;
using Scobey::Pause;
using Scobey::ReadString;
using Scobey::TextItems;

//constant decleration
const  TextItems TEXT("concordance.txt");

void getItem(ifstream& inFile,//in
    multimap<string,int> &map //in
    );
/**<
takes input  file from command line param.
callsgetItem function if files have no errors.
@param inFile The text input file.
@pre inFile and outFile have been initialized and are open.
@post The text in input File has been concordaned  has been
written out to stream. InputFile remain open.
*/
void printFile(ifstream& inFile,//in
    ofstream& outFile,//in out
    multimap<string,int> &map//in
    );
/**<
takes input  file from command line param.
callsgetItem function if files have no errors.
@param inFile The text input file.
@param outFile The output file.
@pre inFile and outFile have been initialized and are open.
@post The text in input File has been concordaned  has been
written out to outFile. Both files remain open.
*/

int main(int argc, char* argv[])
{
    //Variable Declerations
    multimap<string,int> box;
    ifstream inFile;
    ofstream outFile;

    vector<string> v1,v3;


    if(argc==1)
    {
        DisplayOpeningScreen("Al-Akhali:Wael",
            "Building concordance");
        TEXT.displayItem("ProgramDescription");
    }
    if(argc ==2)
    {
        inFile.open(argv[1]);
        getItem(inFile,box);
    }
    if(argc==3)
    {
        inFile.open(argv[1]);
        outFile.open(argv[2]);
        printFile(inFile,outFile,box);

    }
    if(argc==4)
    {
        string first;
        string second;  
        inFile.open(argv[1]);
        outFile.open(argv[2]);

        printFile(inFile,outFile,box);

        inFile.open(argv[2]);
        outFile.open(argv[3]);
        string command = "fc ";
        command += argv[2];
        command +=" ";
        command+= argv[3];
        command+= "> differences.txt";


        system(command.c_str());
        inFile.close();
        outFile.close();
    }
}
void getItem(ifstream& inFile,//in
    multimap<string,int> &map//in
    )
{

    string file,key,item,thing;
    int count = 1;
    int add = 0;
    while(!inFile.eof() && inFile.peek() != EOF)
    {
        //get word from file
        inFile>>key;
        if(inFile.peek() == '\n')
        {
            count++;
        }
        //convert all words to lower case & removes punctiation & digits
        for (int i=0; i<key.size();i++)
        {
            key[i] = tolower(key[i]);
            if(ispunct(key[i]) | isdigit(key[i]))
            {
                string::iterator p = key.begin()+i;
                string::iterator p2 =key.end();
                string::iterator p3 =p+1;
                thing.assign(p3,p2);

                for (int i=0; i<thing.size();i++)
                {
                    if(isdigit(thing[i]))thing.erase();
                }
                key.erase(p,p2);

                if(thing != "\0")
                {
                    count++;
                    map.insert(pair<string,int>(thing,count)); 
                }
            }
        }
        //insert word paired with line number
        map.insert(pair<string,int>(key,count));
    }
    multimap<string, int>::iterator p1 = map.begin();
    multimap<string, int>::iterator p2 = map.begin();

    while(p1!= map.end())
    {
        //initilizes iterators
        pair <multimap<string,int>::iterator,
            multimap<string,int>::iterator> ret;
        //points at range of values using equal range member function
        ret = map.equal_range(p1->first);
        auto position = distance( map.begin(), p1) ;
        //outputs the key with proper indentation

        cout <<setw(15)<<ret.first->first;

        p1++;
        //points iterator at second item in the multimap
        for (multimap<string,int>::iterator it=ret.first;
            it!=ret.second; ++it) 
        {
            //prints 15 numbers per line 
            if(add==15)
            {
                cout<<endl<<setw(18)<<it->second;

            }
            //outputs the corresponding key items
            if(add!=15)
            {
                cout <<" "<< it->second;
            }
            add++;
        }
        cout<<endl;
        p1=ret.second;
        add=0;
    }
}
void printFile(ifstream& inFile,//in
    ofstream& outFile,//in out
    multimap<string,int> &map//in 
    )
{
    string file,key,item,thing;
    int count = 1;
    int add = 0;
    while(!inFile.eof() && inFile.peek() != EOF)
    {
        //get word from file
        inFile>>key;
        //convert all words to lower case & removes punctiation & digits
        for (int i=0; i<key.size();i++)
        {
            key[i] = tolower(key[i]);
            if(ispunct(key[i]) | isdigit(key[i]))
            {

                string::iterator p = key.begin()+i;
                string::iterator p2 =key.end();
                string::iterator p3 =p+1;
                thing.assign(p3,p2);

                for (int i=0; i<thing.size();i++)
                {
                    if(isdigit(thing[i]))thing.erase();
                }
                key.erase(p,p2);

                if(thing != "\0")
                {
                    map.insert(pair<string,int>(thing,count)); 
                }

            }
        }

        //insert word paired with line number
        map.insert(pair<string,int>(key,count));
        if(inFile.peek() == '\n')
        {
            count++;
        }

    }
    multimap<string, int>::iterator p1 = map.begin();
    multimap<string, int>::iterator p2 = map.begin();

    while(p1!= map.end())
    {
        //initilizes iterators
        pair <multimap<string,int>::iterator,
            multimap<string,int>::iterator> ret;
        //points at range of values using equal range member function
        ret = map.equal_range(p1->first);
        auto position = distance( map.begin(), p1) ;
        //outputs the key with proper indentation

        outFile <<setw(15)<<ret.first->first;

        p1++;
        //points iterator at second item in the multimap
        for (multimap<string,int>::iterator it=ret.first;
            it!=ret.second; ++it) 
        {

            //prints 15 numbers per line 
            if(add==15)
            {
                outFile<<endl<<setw(18)<<it->second;

            }
            //outputs the corresponding key items
            if(add!=15)
            {
                outFile <<" "<<it->second;
            }
            add++;
        }
        outFile<<endl;
        p1=ret.second;
        add=0;
    }

}
