#ifndef Q4_H
#define Q4_H

#endif //Q4_H

namespace q4{
    struct Vector2D
    {
        double x{};
        double y{}; 
    };

    struct Sensor
    {
        Vector2D pos;
        double accuracy;    
    };

    Vector2D kalman_filter(std::vector<Sensor> sensors){
        Vector2D ans;ans.x=0;ans.y=0;
        double tot_acc=0;
        for(auto s:sensors){
            tot_acc+=s.accuracy;
            ans.x+=s.pos.x*s.accuracy;
            ans.y+=s.pos.y*s.accuracy;
        }
        ans.x/=tot_acc;
        ans.y/=tot_acc;
        return ans;
    }
}