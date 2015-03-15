
#include<stdio.h>

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <malloc.h>
#include <string.h>
#include <cstring>
#include "tinyxml.h"
#include <windows.h>

#define TIXML_USE_STL

using std::ifstream;
using std::cout;
using std::endl;

using namespace std;



const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const int MAX_CHARS_PER_TOKEN = 15;
const int MAX_TOKENS_PER_PAGE = 1000;

const char* const DELIMITER = " ";

int n = 0; //  number of tokens

class Node
{
public:
    char name[150];

    char * arg[4]= {};
    Node *next;
    Node():next(0) {}
    Node(char *nm,char **arg2, Node *n = 0)
    {
        memset(name,'\0',15);
        strcpy(name,nm);

        arg[0] = arg2[0];
        arg[1] = arg2[1];
        next = n;
    }
};


char * new_str(int Size)
{

    char * tmp = (char *) malloc(Size+1)  ;
    memset(tmp, '\0', Size+1);

    return tmp;

}

int gettokens(list <char *> *tokens ,char *code)
{
    int counter=0;
    char *buff;

    buff= strtok(code, DELIMITER);
    (tokens)->push_back(buff);  // first token

    // printf(" %s",buff);
    // read each line of the file

    if (buff) // zero if line is blank
    {

        while (counter++<MAX_TOKENS_PER_PAGE)
        {


            buff = strtok(0, DELIMITER); // subsequent tokens
            (tokens)->push_back(buff);

            if (!buff) break; // no more tokens
        }

    }
    else
    {

        return 0;

    }


    return counter;
}


/*
to get text between tags XML for Example

<ar_setup>
pinMode(_val_01, OUTPUT);
</ar_setup>

return pinMode(_val_01, OUTPUT);



*/
const char * getText(TiXmlElement *elem)
{

    for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        if(text == NULL)
            continue;
        // int size =strlen(text->ToText()->Value());
        // string str;

        // str.assign(text->ToText()->Value());
        return text->ToText()->Value();
    }
    return NULL;
}

/*

 to get attributes from tag

    for example XML DATA <variable var1="_val_01"/>
    str = getAttribute(elem,"var1")
    return _val_01

  where
   ::elem node this tag variable

*/

const char * getAttribute(TiXmlElement *elem,char *nAtrr)
{
    const char *attr;


    attr = elem->Attribute(nAtrr);
    if(attr != NULL)
    {
        return attr;
    }

    return NULL;
}

/*

this function gets all ˙XML FIle for Commands in linked list(Nodes) and get text then
banding together for  forming complete complete arduino C


*/
string * parse_code(Node *head,char *path_save_file)

{

    string ar_include;
    string ar_initial;
    string ar_setup;
    string ar_loop;
    string ar_extra;
    string full_code;


    Node *current =head;
    TiXmlDocument xml_file;
    TiXmlElement* root;

    const char* var1;
    const char* var2;


    while(current!=NULL)
    {

        xml_file.LoadFile(current->name);
        root=xml_file.FirstChildElement();

//(file_xml)->FirstChildElement();
        if(root == NULL)
        {
            cerr << "Failed to load file: No root element." << endl;
        }



        for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
        {
            string elemName = elem->Value();
            TiXmlText* text ;


            if (elemName=="variable" )
            {
                var1=   getAttribute(elem,"var1");
                var2=   getAttribute(elem,"var2");
            }
            if(elemName == "ar_include")
            {

                if (getText(elem) != NULL)
                {

                    ar_include.append(getText(elem));
                    ar_include.append("\n");
                }

            }
            else if(elemName == "ar_initial")
            {
                if (getText(elem) != NULL)
                {

                    full_code.append(getText(elem));
                    full_code.append("\n");
                }

            }
            else if(elemName == "ar_setup")
            {
                if (getText(elem) != NULL)
                {
                    // ar_setup.append("void setup() {\n");
                    ar_setup.append(getText(elem));
                    ar_setup.append("\n");
                }
            }
            else if(elemName == "ar_loop")
            {
                if (getText(elem) != NULL)
                {
                    //full_code.append("void loop() {\n");
                    ar_loop.append(getText(elem));
                    ar_loop.append("\n");

                }

            }
            else if(elemName == "ar_extra")
            {


                if (getText(elem) != NULL)
                {
                    ar_extra.append(getText(elem));
                    ar_extra.append("\n");
                }



            }

        }

 /* this part specific for replace name attributes (var1 & var2) by corresponding names
            for example √‘⁄· 1
              gets name=√‘⁄·
              gets arg[0]=1

         √‘⁄·.» file cointain XML data

          <variable var1="_var_01"/>  <ar_setup> pinMode(_val_01, OUTPUT); </ar_setup>

           gets var1= _var_01
           gets  ar_setup= pinMode(_val_01, OUTPUT);

           then replace value arg[0] by _var_01 in ar_setup then output
                 pinMode(1, OUTPUT);

                if (attr1 != NULL){
                    ar_setup.replace(var1,current->arg[0]);
                    ar_loop.replace(var2,current->arg[1]);
                }
            */

        current=current->next;

    }


    full_code.append(ar_include);
    full_code.append("\n");
    full_code.append("void setup() {\n");
    full_code.append(ar_setup);
    full_code.append("\n}\n");
    full_code.append("void loop() {\n");
    full_code.append(ar_loop);
    full_code.append("\n}\n");
    full_code.append(ar_extra);
    full_code.append("\n");


    // cout <<full_code.c_str();
    return &full_code;
}

// function gets files in certain folder @StackOverFlow.com
void GetFilesInDirectory(vector<string> &out, const string &directory)
{

    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        return; /* No files found */

    do
    {
        const string file_name = file_data.cFileName;
        const string full_file_name = directory + "/" + file_name;
        const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (file_name[0] == '.')
            continue;

        if (is_directory)
            continue;

        out.push_back(full_file_name);
    }
    while (FindNextFile(dir, &file_data));


} // GetFilesInDirectory




// get project directory @StackOverFlow.com
string ExePath()
{
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return  string( buffer ).substr( 0, pos).c_str();
}



/*

this function take tokens and generate liked list (Nodes)
each node contain name command and 4 parmeters but 2 parameter only use in and saved them

*/

// #issue there are sum defects when there is multi line in code
Node * getCommand(list <char *> *tokens)
{


    const  char *path= ExePath().append("\\CMD").c_str(); // get CMD (Commad) directory contine reserved word


    int num=0;
    int numarg=0;

    vector<string> files;
    vector<string>::iterator file;
    list<char *>::iterator token;

    GetFilesInDirectory(files,path); // exe file and Command folder in debug folder


    Node *current=new Node ;
    Node *last= new Node;
    Node *head;


    string _file;
    char *_token;


    for ( token = (tokens)->begin(); token != (tokens)->end(); ++token)
    {

        printf(" token [%s] ?\n",*token);
        for ( file = files.begin(); file != files.end(); ++file)

        {
            _file=*file;
            _token=*token;


            if (_token==NULL) continue;


            if (_file.find(_token)!=-1)
            {

                numarg=0;
                current = new Node;

                strcpy((current)->name,_file.c_str());

                cout<<"\n this is Reserved word -- path XMl file " <<(current)->name<<endl;
                current->next=NULL;

                last->next=current;

                if (++num==1)
                {
                    head=current;
                }
            }

        }
        last=current;

        if (_token!=NULL && current !=NULL && isdigit(*_token))
        {
            // int intval=atoi(cv);
            current->arg[numarg++]=(char *)malloc(strlen(_token)+1);

            cout<<"***"<<_token<<"\n";
            strcpy(current->arg[numarg-1],_token);

        }



    }



    return head;
}





// function for show all linked list (Nodes) just for check
int show_all(Node *head)
{

    Node *current =head;

    while(current!=NULL)
    {
        std::cout<<current->name<<"*";
        if (current->arg[0])
            std::cout <<" arg[0] == " <<current->arg[0];
        if (current->arg[1])
        {

            std::cout<< " arg[1] == " <<current->arg[1]<<std::endl;
        }

        std::cout<<endl;
        //  printf(" arg[0] == %s  arg[1] == %s\n",current->arg[0],current->arg[1]);

        current=current->next;

    }



    return 0;

}


// #issue_02 return full code by executable file
int main()
{
// this path pass to executable file Bari3

    char *path="f:/text.txt";
    string *full_code;
    fstream File(path,ios::out | ios::in | ios::binary);
    File.seekg (1, ios::end);
    int Size = File.tellg();

    char *code;
    list <char *> tokens;

    code = (char *) malloc(Size+1)  ;
    if (!code)
    {
        printf("error in allocate block memory");
    }
    memset(code, '\0', Size+1);
    File.seekg(0, ios::beg);
    File.read(code,Size);
    File.close();



    //  list<char *>::iterator i;

    // cout<<"ok----"<<code;

    // format(&ccode);



    int num=gettokens(&tokens, code);
    printf("number token %d\n",num);

    if(num)
    {
        Node *head= getCommand(&tokens);

        cout<<"\n---- Command ------\n";
        show_all(head);

        full_code=parse_code(head,"F:/bari3.ino");

    }




//     cout<<"\n " << strcmp(token[n],"okasha");

    cout<< full_code->c_str();



}







int add(Node * head,string name)
{

    Node *current=head;
    Node *newNode;


    newNode=( Node * ) malloc(sizeof(Node));

    for(; current->next != NULL;)
    {



// √ﬂ„·
        current=current->next;

    }

    current->next=newNode;
    newNode->next=NULL;

/////////////////////

    strcpy(newNode->name,name.c_str());
    //random (500+);


    return 1;
}




