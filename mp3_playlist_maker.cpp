/*Implementation of Mp3 Playlist maker using the Mp3finder 
Author->Vivek Singh Rathore
*/
#include<fstream>
#include<algorithm>
#include<iostream>
#include<dirent.h>     
#include<string>
#include<string.h>
#include<vector>    
using namespace std;
class mp3file{
    private:
    string f_name;
    public:
    string showFile(){
        return f_name;
    }
    mp3file(string filename){
        f_name=filename;       
    }   
};
vector<mp3file> list;
class dirfile{
    public:
    DIR *dir;           
    struct dirent *ent;
    dirfile(string s){
        dir=opendir(s.c_str());
    }
    bool isDir(){
        if(ent->d_type==4)
            return true;
        else 
            return false;
    }
    bool isMp3(){
        if(ent->d_type==8){
            string temp;
            for(int i=strlen(ent->d_name)-4;i<strlen(ent->d_name);i++)
                temp.push_back(ent->d_name[i]);
            if(temp==".mp3")
                return true;
            else
                return false;
        }
        else
            return false;                   
        }   
};
void mp3find(string s){
    dirfile d(s);
    if(d.dir!=NULL){
        while((d.ent=readdir(d.dir))!=NULL){
            
            //skips the entities names '.','..' and '.*'
            
            if(strcmp(d.ent->d_name,".")==0 || strcmp(d.ent->d_name,"..")==0 || d.ent->d_name[0]=='.')
                continue;
            
            //checks for directory
            
            if(d.isDir()){
                string temp(d.ent->d_name);
                temp=s+"/"+temp; 
                mp3find(temp);
            }
            
            //checks for mp3 file
            
            if(d.isMp3()){
                mp3file m((string)d.ent->d_name);          
                list.push_back(m);                                      
            }    
        }
        closedir(d.dir);
    }
    else
        cout<<"Couldn't open the directory "<<s<<endl;
}
class Playlist{
	public:
	     void makeList(vector<string> song_names){
	      ofstream obj;
              obj.open((song_names[0].substr(0,1)+"-list").c_str()); 
	      obj<<song_names[0]<<endl;
	      for(int i=0;i<song_names.size()-1;i++){
	       if( (song_names[i])[0] == (song_names[i+1])[0] ){
                 obj<<song_names[i+1]<<endl; 
	       }
	       else{
                 obj.close();
	 	 obj.open((song_names[i+1].substr(0,1)+"-list").c_str());
	         obj<<song_names[i+1]<<endl;
	       }
	      }
	     }
};

int main(){
    string inputPath;
    cout<<"Enter the path...."<<endl;
    cin>>inputPath;
    mp3find(inputPath);
    vector<string> song_names;
    for(int i=0;i<list.size();i++)
    song_names.push_back(list[i].showFile()); //extracting the song names
    sort(song_names.begin(),song_names.end());//sorting the filenames
    Playlist mylist;                           
    mylist.makeList(song_names);                   

}
