
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
    char name[15];

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


int  check_and_corect_format(char *code)
{

}

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
    const char* attr1;
    const char* attr2;


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
                attr1=   getAttribute(elem,"var1");
                attr2=   getAttribute(elem,"var2");
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
        /*
                if (attr1 != NULL)
                    full_code.replace(attr1,current->arg[0]);

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

/*
 char fc;
 char lc;
 int offset;
 char tmp[20];

 for ( i = (tokens)->begin(); i != (tokens)->end(); ++i)
{
    if (*i==NULL)
     continue;

     fc=*(*i);
     offset=0;

     while(*(*i + ++offset)!='\0'){}

     lc=*(*i+--offset);

    // cout <<"last char " <<lc<<endl;

switch(fc){
case '[':
case '{':
case '(':
    //////////
//case ']':
//case '}':
//case ')':


(ntokens)->remove()
(ntokens)->push_front(*i + 1);
(ntokens)->push_front(*i + 1);

// (tokens)->push_back(*i);

   //  *(ntoken[i+shift])=fc;

//printf("old address %d num %d",ntoken[i+ ++shift],i);

    // ntoken[i+ ++shift]=new_str(strlen(dtoken[i])) ;

// printf(" new address %d",ntoken[i+ shift]);


  //   printf(" new word %s",ntoken[i+shift]);

// return 0;
//  printf("\n * token = %s \n" ,ntoken[i+shift]);

break;

}
switch(lc){
case '[':
case '{':
case '(':
    //////////
case ']':
case '}':
case ')':

memset((dtoken[i]+offset), '\0', 1);
*ntoken[i+shift]=*dtoken[i];
*(ntoken[i+ ++shift])=lc;



break;


}

 // if (!ntoken[i]) break; // no more tokens
}
*/
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

// #issue do not working well in multy line
Node * getCommand(list <char *> *tokens)
{

    list<char *>::iterator token;
    vector<string> files;


    GetFilesInDirectory(files,"f:/CMD");

    vector<string>::iterator file;
    string as;
    char *cv;

    int num=0;
    int numarg=0;
    Node *current=new Node ;
    Node *last= new Node;
    Node *head;


    for ( token = (tokens)->begin(); token != (tokens)->end(); ++token)
    {

        printf("--------------- \n token [%s]? \n----------------",*token);
        for ( file = files.begin(); file != files.end(); ++file)

        {
            as=*file;
            cv=*token;

            //  strcat(cv,".Ø¨");
            if (cv==NULL) continue;


            if (as.find(cv)!=-1)
            {
                printf("--%s--",cv);

                numarg=0;
                current = new Node;

                strcpy((current)->name,as.c_str());
                current->next=NULL;

                last->next=current;

                if (++num==1)
                {
                    head=current;
                }
            }

        }
        last=current;

        if (cv!=NULL && current !=NULL && isdigit(*cv))
        {
            // int intval=atoi(cv);
            current->arg[numarg++]=(char *)malloc(strlen(cv)+1);
            cout<<"***"<<cv<<"\n";
            strcpy(current->arg[numarg-1],cv);


        }


        //   if (current->name != NULL){


//
        // }


    }






    return head;
}






int show_all(Node *head)
{

    Node *current =head;

    while(current!=NULL)
    {
        cout<<current->name<<"*";

        printf(" arg[0] == %s  arg[1] == %s\n",current->arg[0],current->arg[1]);
        current=current->next;

    }



    return 0;

}
// #issue_02 return full code by executable file
int main()
{
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



    //  list<char *>::iterator i;

    // cout<<"ok----"<<code;

    // format(&ccode);



    int num=gettokens(&tokens, code);
    printf("number token %d\n ",num);

    if(num)
    {
        Node *head= getCommand(&tokens);
        cout<<"\n---------new Node-----------------\n";
        show_all(head);

        full_code=parse_code(head,"F:/bari3.ino");

    }




//     cout<<"\n " << strcmp(token[n],"okasha");

return full_code->c_str();



}







int add(Node * head,string name)
{

    Node *current=head;
    Node *newNode;


    newNode=( Node * ) malloc(sizeof(Node));

    for(; current->next != NULL;)
    {



// Ãßãá
        current=current->next;

    }

    current->next=newNode;
    newNode->next=NULL;

/////////////////////

    strcpy(newNode->name,name.c_str());
    //random (500+);


    return 1;
}




