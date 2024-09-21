#ifndef Q3_H
#define Q3_H

#endif //Q3_H

#include<strstream>
#include<queue>
#include<fstream>
namespace q3{
    size_t str2time(std::string word){
        size_t ans=0;
        std::string word1=word.substr(0,word.find('h'));
        
        ans=std::stoi(word1)*60;
        if(word.find('m')!=-1){
            std::string word2=word.substr(word.find('h')+1,word.find('m')-word.find('h')-1);
            
            ans+=std::stoi(word2);
            // std::cout<<word2<<std::endl;
        }
        return ans;
    }
    struct Flight{
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
        Flight(std::string s){
            std::stringstream ss(s);
            std::string word;
            int i=0;
            while(getline(ss,word,'-')){
                i++;
                //  flight_number:QR492 
                if(i==1)continue;
                else if(i==2){
                    word=word.substr(1);
                    word=word.substr(14,word.find_first_of(' ')-14);
                    flight_number=word;
                    // std::cout<<flight_number<<std::endl;
                }
                else if(i==3){
                    //  duration:11h30m 
                    word=word.substr(10);
                    // std::cout<<word<< std::endl;
                    duration=str2time(word);
                }
                else if(i==4){
                    //  connections:3
                    word=word.substr(13);
                    
                    connections=std::stoi(word);
                    // std::cout<<word<<std::endl;
                }
                else if(i==5){
                    // connection_times:2h,1h30m,4h15m
                    word=word.substr(18);
                    // std::cout<<word<<std::endl;
                    connection_times=0;
                    for(int j=0;j<connections;++j){
                        std::string word1=word.substr(0,word.find(','));
                        connection_times+=str2time(word1);
                        word=word.substr(word.find(',')+1);
                    }
                }
                else if(i==6){
                    //  price:250
                    word=word.substr(7);
                    price=std::stoi(word);
                }
            }
            // std::cout<<flight_number<<" "<<connection_times<<std::endl;
        }
        size_t get_val() const{
            return duration + connection_times + 3*price;
        }
        bool operator <(const Flight &other)const{
            return this->get_val()>other.get_val();
        }
    };
    std::priority_queue<Flight> gather_flights(std::string filename){
        std::ifstream file(filename);
        if(!file.is_open()){
            throw std::runtime_error("no file.");
        }
        std::priority_queue<Flight>ans;
        std::string line;
        while(getline(file,line)){
            Flight a(line);
            // std::cout<<a.flight_number<<std::endl;
            ans.push(a);
        }
        return ans;
    }
};