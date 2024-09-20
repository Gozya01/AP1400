#include "Utils.h"
std::string get_random_string(int length){
    static std::unordered_set<std::string> numberset;
    const std::string char_set="0123456789";
    // "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                // "abcdefghijklmnopqrstuvwxyz"
                                
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0,char_set.length()-1);
    std::string ans="";
    do{
        ans="";
        for(int i=0;i<length;++i){
            ans+=char_set[distribution(generator)];
        } 
        if(!numberset.count(ans)){
            numberset.insert(ans);
            break;
        }
    }while(true);
    return ans;
}