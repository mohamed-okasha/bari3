// bari3.cpp: Mohamed Okasha
//description: it's compiler source to source , convert code from bari3 commands to Arduino c style
// for more description e-mail Mohammmed.okasha.ps@gmail.com

#include <iostream>
#include <fstream>
#include <list>

#include <vector>


#include <stdio.h>  /* defines FILENAME_MAX */
#include <string>


#ifndef BXML_INCLUDED
#include "bXML.h"

#endif


#ifndef STRPRC_INCLUDED
#include "strprc.h"
 #endif

#ifndef TINYXML_INCLUDED
#include "tinyXML/tinyxml.h"
 #endif



// CONSTANTS
 extern const int MAX_TOKENS_PER_PAGE = 10000;
 extern const int MAX_VECTORS_PER_FILE = 10;
 extern const int MAX_CHARS_PER_TOKEN = 100;
 extern const char* const DELIMITER = " ";

// reserved symbols
std::string RESERVED_SYMPOLE = "{},";

// list of string  between "some text" in bari3 commands;
std::vector <std::string> _BARI3_STRINGS;

// list of variables  in  bari3 commands; [ beta ]
char _BARI3_VARIABLES [24][2][10]={{"ِA","0"},{"B","1"},{"C","-9"}};

typedef struct _BARI3_CONSTANTS{
char from[15];
char to[15];
};

//char * getVarType(const char *ch);
//Node * getCommand(std::string xx,std::list <char *> ss,std::vector string);

//{"واحد","1"},{"ثنتان","2"},{"ثلاث","3"},{"أربع","4"},{"خمس","5"},{"ستة","6"},{"سبع","7"},{"ثمان","8"},{"تسع","9"},{"عشرة","10"},{"ثلاثة","3"},{"ثلاثة","3"},{"ثلاثة","3"},{"واحدة","1"},{"اح","3"}
class Node
{



public:

    char name[MAX_CHARS_PER_TOKEN];
    char * arg[6]= {};
    char  type[6];
    int n_index=0;
    int CountOfArgument=1;// assumed number of argument == 1
    int current_arg=0;

    std::string command_file_name; // path contain name command
    std::string keywords;
    std::string Vectors;

    Node *next;
    Node():next(0) {}



    int isNew(Node *head,Node *current)
    {
        Node *train;
        train=head;
        while(train!=current)
        {





            if (!strcmp(train->name,current->name))
            {
                if( train->Vectors.compare(current->Vectors) ==0 && train->keywords.compare(current->keywords) ==0 ){

                if (train->arg[0]!=NULL && current->arg[0]!=NULL)
                {
                    if (strcmp(train->arg[0],current->arg[0])) // if different
                     {
                        return 1;  // similar name command and different argument
                     }

                        if (train->arg[1]!=NULL && current->arg[1]!=NULL)
                        {
                            if (strcmp(train->arg[1],current->arg[1])) // // if different
                            {
                                return 1;   // similar name command and different argument
                            }
                        }

                        if (train->arg[2]!=NULL && current->arg[2]!=NULL)
                        {
                            if (strcmp(train->arg[2],current->arg[2])) // // if different
                            {
                                return 1;   // similar name command and different argument
                            }
                        }

                        if (train->arg[3]!=NULL && current->arg[3]!=NULL)
                        {
                            if (strcmp(train->arg[3],current->arg[3])) // // if different
                            {
                                return 1;   // similar name command and different argument
                            }
                        }
                        if (train->arg[4]!=NULL && current->arg[4]!=NULL)
                        {
                            if (strcmp(train->arg[4],current->arg[4])) // // if different
                            {
                                return 1;   // similar name command and different argument
                            }
                        }

                        if (train->arg[5]!=NULL && current->arg[5]!=NULL)
                        {
                            if (strcmp(train->arg[5],current->arg[5])) // // if different
                            {
                                return 1;   // similar name command and different argument
                            }
                        }

                }


                    return 2;  // similar name command and argument
                }

            }


            train=train->next;
        }
        return 0; // different command




    }

    int add_argument(const char *ch ,char _type){

     arg[current_arg]=(char *)malloc(strlen(ch)+1);
     strcpy(arg[current_arg],ch);

     type[current_arg]=_type;
        current_arg++;
        return 0;
    }




};


class _Vector_
{



    public:

    int index_current_vector=0;
    int length_vector=0;
    bool end_vector=false;

    char current_sub_vector[MAX_CHARS_PER_TOKEN];
    char name[MAX_CHARS_PER_TOKEN];
    char sub_vector[MAX_VECTORS_PER_FILE][MAX_CHARS_PER_TOKEN];

    // vector<const char *> sub_vector;
   // vector<const char *>::iterator current_sub_vector;




    int next_sub_vector(){

       // cout<<"\n index_current_vector == "<<index_current_vector<<endl;

          //    0  & 1        <       1
    if (index_current_vector < length_vector-1 )
       strcpy(current_sub_vector,sub_vector[++index_current_vector]);

      end_sub_vector();

     //   std::cout<<" **next_sub_vector ::"<<index_current_vector<<"::"<<current_sub_vector<<endl;

      return 0;
    }



    _Vector_ *next;
    _Vector_():next(0) {}

  int getVectorTextDelimited( char *text,const char *delimiter){
    int Counter=0;
    const  char *buff;
    length_vector=0;
    // start splite code

    buff= strtok(text, delimiter);

    length_vector++;
    strcpy(sub_vector[index_current_vector],buff);
            strcpy(current_sub_vector,buff);
    //cout<<" \n sub vecotr1:"<<buff;
    // printf(" %s",buff);

    if (buff) // zero if line is blank
    {

        while (Counter++<MAX_TOKENS_PER_PAGE)
        {


            buff = strtok(0, delimiter); // subsequent tokens


            if (!buff) break; // no more tokens

            if (index_current_vector<MAX_CHARS_PER_TOKEN-1){
                strcpy(sub_vector[++index_current_vector],buff);
               length_vector++;
            }
            // sub_vector.push_back(buff);
           //  cout<<"  sub vecotr-N:"<<buff<<endl;
        }

    }



    return Counter; // number tokens

    }





    int add_sub_vectors( char * strVectors){

   // _Vector_  *new_ = new _Vector_;
//cout<<" getVectorTextDelimited"<<endl;
    getVectorTextDelimited(strVectors,";");

    index_current_vector=0;
   // end_sub_vector();

    return 0;
   // new_->next=0;
   //  next=new_;
  //  current= new_;
  //   cout<<" invoked! getVectorTextDelimited"<<endl;
    }


/*
int clear_vector(){

for (int i=length_vector-1;i>=0;i--){
        memset(sub_vector[i],MAX_CHARS_PER_TOKEN,'\0');
}
 memset(current_sub_vector,MAX_CHARS_PER_TOKEN,'\0');
length_vector=0;
index_current_vector=0;

    } */



   bool end_sub_vector(){
    if (index_current_vector==length_vector-1)
      return true;


    return false;


    }



};



// get tokens delimited by space
int getTokens(std::list <char *> *tokens ,char *code)
{
    int counter=0;
    char *buff;

    // start splite code
    buff= strtok(code, DELIMITER);
    (tokens)->push_back(buff);  // first token

    // printf(" %s",buff);

    if (buff) // zero if line is blank
    {

        while (counter++<MAX_TOKENS_PER_PAGE)
        {


            buff = strtok(0, DELIMITER); // subsequent tokens
            (tokens)->push_back(buff);

            if (!buff) break; // no more tokens
        }

    }



    return counter; // number tokens
}


char * rndNameVariable(){

char var[10]={"AAAAAAAAA"};

char *name= (char *)malloc(10);

var[0]=var[0]+rand() % 25 +1;
var[1]=var[1]+rand() % 25 +1;
var[2]= var[2]+rand() % 25 +1;
var[3]=var[3]+ rand() % 25 +1;
var[4]=var[4]+ rand() % 25 +1;
var[5]=var[5]+ rand() % 25 +1;
var[6]=var[6]+ rand() % 25 +1;
var[7]=var[7]+ rand() % 25 +1;
var[8]=var[8]+ rand() % 25 +1;
strcpy(name,var);

return name;

}

 char * getVarType(const char *ch){

//char *str=malloc(3);

if (ch==0)
return "int";


if (!strcmp(ch,"vf"))
        return "float";

        if (!strcmp(ch,"vi"))
        return "int";

        if (!strcmp(ch,"vc"))
        return "char";


 return "int";

}



Node *  getCommand(std::string exePath ,std::list <char *> *tokens,std::vector<std::string> files)
{

	//std::cout<<"step 6";
    std::string path= exePath.append("/CMD").c_str(); // get CMD (Commad) directory contine reserved word

   // cout<<"Path::"<<path;
    int num=0;
    int nnpos=path.length()+1; // number fetched current argument
    int index=0;

    
    std::vector<std::string>::iterator file;
    std::list<char *>::iterator token;

    std::list<_Vector_> vectors_;

    std::vector<std::string>::iterator str;
    std::list<std::string>::iterator exp;


   //GetFilesInDirectory(files,path); // exe file and CMD folder in debug folder
   
  //  std::cout<<"step 7";

    //--------------************--

    Node *current=new Node ;
        Node *last= new Node;
        Node *head;

        TiXmlDocument xml_file;
        TiXmlElement* root;

        std::string _file;
        char *_token;

        _Vector_ * current_vector = 0;
        _Vector_ *last_vector= new _Vector_;
        _Vector_ *head_vector=0;
        _Vector_ *train;


        std::string _string;
        std::string keywords;


      str=_BARI3_STRINGS.begin();
       // std::cout<<"step 8";

        for ( token = (tokens)->begin(); *token != NULL; ++token)
           {

             //  printf(" token [%s] ?\n",*token);

                _token=*token;

                   if ( !strcmp(_token,">") || !strcmp(_token,"<") ){
                       current->add_argument(_token,'sym');
                    //     cout<<"\n this sympole  ["<<current->current_arg<<"]"<<" = "<<_token<<endl;
                       continue;
                   }
                   if (!strcmp(_token,"=")){
                       current->add_argument("==",'sym');
                      //   cout<<"\n this sympole  ["<<current->current_arg<<"]"<<" = "<<_token<<endl;
                       continue;

                   }

                if(strlen(_token) ==1 && (int)*_token >-62 && (int)*_token <-18   ){
                   int iindex=index;

                   for(int iindex=index;iindex>=0;iindex--){
                       if (strcmp(_BARI3_VARIABLES[iindex][1],_token)==0 ){
                         current->add_argument(_BARI3_VARIABLES[iindex][0],'v');
                         goto jmp1;
                       }

                   }



                   strcpy(_BARI3_VARIABLES[index][0],rndNameVariable()); //  generate random identify for arduino c
                   strcpy(_BARI3_VARIABLES[index][1],_token);            //  copy variable
                   current->add_argument(_BARI3_VARIABLES[index][0],'v'); // set type v (variable)
                   index++;
           jmp1:        continue;


                }

     //   std::cout<<"step 9"<<endl;

//_==============================


        //






     //         if token is arabic character then
       //          define array 3 D with name varibale and name RND in code and inetial value
         //        add name this variable in code to arguments in last command
       /* file=files.begin();
        std::cout<<"step 99"<<endl;
        //file_xx.append();
        string file_xx;
        char xxxx[100];
        std::cout<<"step 100"<<endl;
        strcpy(xxxx,*file->c_str());
      // file_xx.append(*file);
        std::cout<<"step 101"<<endl;
        */
    // std::string::size_type pos = nnpos ; //file_xx.find_last_of( "/" )+1;

     //std::cout<<"step 10"<<endl;

             for ( file = files.begin(); file != files.end(); ++file)

             {

                //cout<< string(";").append(_file.substr(pos,_file.length()-pos-3).append(";"))<<endl;


                 if (_token==NULL) continue;

                 _file=*file;

     //cout<<endl<<" sub reserved word "<<_file.substr(pos,_file.length()-pos)<<endl;

                 // append ; or . in name to avoid conflict whit alphapitic


                 std::cout<<_file.find_first_of(".ب");
                 std::string g= std::string(" ;").append(_file.substr(  _file.find_first_of(".ب") , -1 ).append("; "))  ;
                 replaceAll(g,".ب","",0);
                 std::cout<<g;
                 if ( std::string(" ;").append(_file.substr(  _file.find_first_of(".ب") +2,_file.length()-nnpos-2).append("; ")).find(std::string(";").append(_token).append(";"))!=-1)
                 {
                	 std::cout<<"//first word --"<<std::string(";").append(_token).append(";--")<<"is Find in>>"<<std::endl;
                	 std::cout<<"//second word --"<<std::string(";").append(_file.substr(nnpos,_file.length()-nnpos-3).append(";--"))<<std::endl;

                     current = new Node;

                     current->command_file_name.append(_token);
                     const  char * fetch;
                     xml_file.LoadFile(_file.c_str());
                     root=xml_file.FirstChildElement();

                     keywords.erase(0);




                     keywords.append(";");
                     for(TiXmlElement* elem = root; elem != NULL; elem = elem->NextSiblingElement())
                     {
                         fetch=getAttribute(elem,"keywords");

                         if ( fetch != NULL)
                         {
                           //  cout<<"\n::"<<fetch<<"||"<<endl;
                             keywords.append(fetch).append(";");
                         }

                         fetch=getAttribute(elem,"vector");

                         if (fetch != NULL)
                         {
                             if (current_vector==0){
                             current_vector=new _Vector_;
                             head_vector=current_vector;
                          //   cout<<"__step 1&";
                             }else{
                              current_vector=new _Vector_;
                            //   cout<<"__step 2&";
                             }

                         // cout<<"__step 3&";


                             char ss[200];
                             strcpy(ss,fetch);
                          strcpy(current_vector->name,ss);

                           current_vector->add_sub_vectors(ss);



                          // current_vector->current_sub_vector= current_vector->sub_vector.begin();
                            current_vector->next=NULL;
                             last_vector->next=current_vector;

                             last_vector=current_vector;


                             //    current_vector->next_sub_vector();
                               //  cout<<" sub v2"<<*current_vector->current_sub_vector;

     /*
                            new_node_vector.add_vector(fetch);

                             node_vector.next=new_node_vector;
                           _vectors.push_back(fetch)  ;

                             __vector=_vectors.begin();
     */
                         }




                     }


                     strcpy((current)->name,_file.c_str());
                     current->n_index=num;
                   //  cout<<"\n this is Reserved word -- path XMl file " <<(current)->name<<endl;
                     current->next=NULL;

                     last->next=current;

                     if (++num==1)
                     {

                         head=current;
                     }
                 }



             }






     //for (int i=0;i<=train->length_vector-1;i++){




               //  if (!current->_vector.empty())
                 //break;

                // cout<<"\n----next vector ["<<train->name<<"]\n";
                   //  cout<<" ok!";
               //      train->current_sub_vector=train->sub_vector.begin();

             //    cout<<" :: ___end sub vector __ "<<*train->current_sub_vector<<"::";
                // if (train->current_sub_vector ==  train->sub_vector.end()){

         //            cout<<" :: ___current vector __ "<<train->name<<"::";
       //              current->_vector.append(train->name);

     //            }








             if (keywords.find(std::string(";").append(_token).append(";"))!=-1  ){
                 current->keywords.append(_token);
                // cout<<"\n ::"<<_token<<"::"<<endl<<current->keywords<<"::";

             }



             if(RESERVED_SYMPOLE.find(_token) !=-1)
                 {


                      if (*_token==','){

                         char *lastnode=(char *)malloc(strlen(current->name)+1);

                          strcpy(lastnode ,(current)->name);
                          current = new Node;
                          strcpy( current->name,lastnode);

                         last->next=current;

                         current->next=NULL;
                        // cout<<current->name<<"step 16";
                         // cout<<" _token == "<<_token << " ";
                          continue;
                     }

                     if (*_token==','){

                         char *lastnode=(char *)malloc(strlen(current->name)+1);

                          strcpy(lastnode ,(current)->name);
                          current = new Node;
                          strcpy( current->name,lastnode);

                         last->next=current;

                         current->next=NULL;
                        // cout<<current->name<<"step 16";
                         // cout<<" _token == "<<_token << " ";
                          continue;
                     }

                          current = new Node;
                          strcpy((current)->name,_token);

                  //   cout<<"\n this is symbol  " <<_token<<endl;
                     current->next=NULL;
                     last->next=current;
                     last=current;
                     continue;
                 }


             last=current;



             if (_token!=NULL && current !=NULL && isdigit(*_token))
             {
                 // int intval=atoi(cv);

               //  cout<<"\n this argument number ["<<current->current_arg<<"]"<<" = "<<_token<<endl;

                 current->add_argument(_token,'n');

                // current->arg[numarg++]=(char *)malloc(strlen(_token)+1);

               //  strcpy(current->arg[numarg-1],_token);

             }

             if (!strcmp(_token,"&@#!$"))
             {

     /*          _expression=*exp;
                 exp++;
                 cout<<" new expression  ["<<numarg<<"] =="<<_expression;
                 current->arg[numarg++]=(char *) malloc(_expression.length());
                 strcpy((current)->arg[numarg-1],_expression.c_str());
     */
             }


             if (!strcmp(_token,"&;?%"))
             {
                 //;
                 // string tmp; //last edit
                 // add string to arg;
                 //tmp.append(str);
                 _string.erase(0);
                 _string.append("\"");
                 _string.append(*str);
                 _string.append("\"");


               //  cout<<"// this string argument ["<<numarg<<"] =="<<_string;
                 current->add_argument(_string.c_str(),'s');

                 str++;

                 //current->arg[numarg++]=(char *) malloc(_string.length());
                // strcpy((current)->arg[numarg-1],_string.c_str());

             }

         if (!strcmp(_token,"HIGH") || !strcmp(_token,"LOW")  || !strcmp(_token,"INPUT") || !strcmp(_token,"OUTPUT"))
                  current->add_argument(_token,'c');



          /*   for(int _index=0;_index<=24;_index++){

                     std::cout<<"\n Check constant ::"<<*token<<" num==:"<<_index<<":with :"<<_constant[_index][0]<<endl;

                 if (strcmp(_constant[_index][0],*token)==0 ){
                     *token = _constant[_index][1];

                 std::cout<<" Constant:"<<_constant[_index][1]<< " rep with: "<<*token;
                 current->add_argument(*token,'c');
                 // std::cout<<" constant << "<<_token<<" *****";
                  break;
                 }


             } */



             // check vectors //



                 //vector<const char *>::iterator ___vector;
     //cout<<"\n loop train- vector-name:"<<train->name;
     //cout<<" current sub vector 1:"<<*train->current_sub_vector;
     //train->next_sub_vector();
     //cout<<" current sub vector2:"<<*train->current_sub_vector;

                 for(train=head_vector; train  ;train=train->next) {
                         if (!train)
                             break;

         //std::cout<<"\n// vector1 sub name:"<<train->name<<" current_sub_vector:"<<train->current_sub_vector<<"_token:"<<_token<<endl;

                    // cout<<" check current vector __ subvector"<<*train->current_sub_vector<<"current token::"<<_token<<endl;
                     if (strcmp(train->current_sub_vector,_token)){ // if deffirent
                         continue ;

                     }


                  //    cout<<"----ok::"<<train->name<<" length== ["<<train->length_vector<<"]";




                     if (train->end_sub_vector()){

                        // current->_vector.clear();
                         current->Vectors.append(train->name);

                      //   std::cout<<"\n// ok it's true vector ++:"<< current->_vector;

                         delete head_vector;
                         head_vector=0;
                          delete current_vector;
                          current_vector=0;
                          delete train;
                          train=0;
                         break;
                        // train->clear_vector();




                 }

                  train->next_sub_vector();




                     }

             //        ----------------------------- //










         }






    return head;
}









// make some processing to avoid confusion
char * preprocessing(char *code)
{

    std::string ccode;

    int offset=-1;
    int counter=0;

    ccode.assign(code);

    std::string to;
    int index=0;
    size_t start_pos = 0;
    while((start_pos = ccode.find("'", start_pos)) != std::string::npos)
    {
    counter++;

        if (counter%2 ==0 )
        {
            index++;

            _BARI3_STRINGS.push_back(ccode.substr(offset+1,start_pos-offset-1)); // copy string to new item in list
           // cout<<"// text ["<<index<<"]:"<<ccode.substr(offset+1,start_pos-offset-1);
            ccode.replace(offset, start_pos-offset+1, "&;?%");
            // In case 'to' contains 'from', like replacing 'x' with 'yx'
            start_pos=0;
            continue;
        }

        offset=start_pos;
        start_pos += 1;
    }
    ///////////////////////////////////////////////////////////
   // getExprestion(&ccode);

    //////////////////////////////////////////




    replaceAll(ccode,"\n"," ");




  int start_offset=  replaceAll(ccode,"}"," } ");
 replaceAll(ccode,"{"," { ");
    replaceAll(ccode,">"," > ");
    replaceAll(ccode,"<"," < ");
    replaceAll(ccode,"="," = ");
    replaceAll(ccode,","," , ");


    if (strlen(code)<ccode.length())
    {
        code=(char *)malloc(ccode.length()+1);
    }

    strcpy(code,ccode.c_str());

 //cout<<"\n ++++++++++++++++++"<<code<<"\n************************";





    return code;



}


int postprocessing(std::list <char *> *tokens, std::string constant_path)
{


      std::list<_BARI3_CONSTANTS> const_;
        _BARI3_CONSTANTS NEW_CONSTANT;
  
  char *buff1;
  char *buff2;
  char chunck[50];

  std::ifstream myfile (constant_path.append("Data/constant.data").c_str());


if (myfile.is_open())
  {


    while ( myfile.good() )
    {


      myfile>>chunck;

      buff1 = strtok(chunck, ":");
      buff2 = strtok(0, ":");

      strcpy(NEW_CONSTANT.from,buff1);
      strcpy(NEW_CONSTANT.to,buff2);
        const_.push_back(NEW_CONSTANT);
     // std::cout<<"_constant :"<<NEW_CONSTANT.from<<endl; ********************
   //  std::cout<<" buff1 ==["<<_constant[index][0]<<"] buff2 ==["<<_constant[index][1]<<"]"<<endl;

    }
    myfile.close();
  }else
  {


      return 0;
  }


    std::list<char *>::iterator token;
    std::list<_BARI3_CONSTANTS>::iterator iconstant;
    char *_token;
    std::string _string;
    std::cout<<"// postprocessing ..."<<std::endl<<std::endl;

    for ( token = (tokens)->begin(); *token != NULL; ++token)
    {

     //    std::cout<<"\n check Constant:"<<*token<<endl;
        _token=*token;

         for ( iconstant = (const_).begin(); iconstant != (const_).end(); ++iconstant)
    {

        NEW_CONSTANT=*iconstant;
            if (strcmp(NEW_CONSTANT.from,_token)==0 ){
                *token = (char *)malloc(strlen(NEW_CONSTANT.to));
                strcpy(*token,NEW_CONSTANT.to);

          //  std::cout<<"// Constant:"<<NEW_CONSTANT.from<< " rep with: "<<*token;
            // std::cout<<" constant << "<<_token<<" *****";
             break;
            }

    }
 //cout<<" constant << "<<_constant[index][0]<<"=="<<_token<<endl;






    }

    /*

    */



}


