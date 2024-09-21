#include "BloomFilter.h"

template <std::size_t N> 
BloomFilter<N>::BloomFilter(unsigned int num_hashes){
    this->bits.reset();
    this->num_hashes=num_hashes;
    this->seeds.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>distribution(0);
    for(int i=0;i<num_hashes;++i){
        this->seeds.push_back(distribution(gen));
    }
    this->server=new CDNServer();
}

template <std::size_t N> 
BloomFilter<N>::BloomFilter(const BloomFilter& other){
    this->bits=other.bits;
    this->num_hashes=other.num_hashes;
    this->seeds=other.seeds;
    this->server=new CDNServer();
    this->server->words=other.server->words;
    this->server->usage_count=other.server->usage_count;
}

template<std::size_t N>
BloomFilter<N>::BloomFilter(BloomFilter&& other) noexcept{
    bits=other.bits;
    num_hashes=other.num_hashes;
    seeds=std::move(other.seeds);
    server=other.server;
    other.server=nullptr;
}

template<std::size_t N>
BloomFilter<N>::~BloomFilter(){
    bits.reset();
    num_hashes=0;
    seeds.clear();
    delete server;
    server=nullptr;
}

template<std::size_t N>
void BloomFilter<N>::add(const std::string& item){
    for(auto &seed:seeds){
        size_t hash_value=this->hash(item,seed);
        bits.set(hash_value%N);
    }
}
template<std::size_t N>
void BloomFilter<N>::add(std::string&& file_name){
    std::ifstream file(file_name);
    if(!file.is_open()){
        throw std::runtime_error("no file.");
    }
    std::string line;
    while(std::getline(file,line)){
        std::stringstream ss(line);
        std::string item;
        while(std::getline(ss,item,',')){
            this->add(item);
        }
    }
}

template<size_t N>
bool BloomFilter<N>::possiblyContains(const std::string& item) const{
    for(auto &seed:seeds){
        size_t hash_value=this->hash(item,seed);
        if(bits[hash_value%N]==0)return false;
    }
    return true;
}

template<size_t N>
bool BloomFilter<N>::possiblyContains(std::string&& item) const{
    return this->possiblyContains(item);
}

template<size_t N>
bool BloomFilter<N>::certainlyContains(const std::string& item) const{
    if(!this->possiblyContains(item))return false;
    return this->server->checkWord(item);
}

template<size_t N>
bool BloomFilter<N>::certainlyContains(std::string&& item) const{
    return this->certainlyContains(item);
}

template<size_t N>
void BloomFilter<N>::reset(){
    bits.reset();
    delete this->server;
    this->server=new server;
}

template<size_t N>
BloomFilter<N>& BloomFilter<N>::operator&(const BloomFilter& other){
    BloomFilter<N> *new_b=new BloomFilter<N>(*this);
    new_b.bits.reset();
    new_b.num_hashes+=other.num_hashes;
    new_b->seeds
} 

template<size_t N>
BloomFilter<N>& BloomFilter<N>::operator|(const BloomFilter& other){

}

