//
// Created by js on 22/05/22.
//

#ifndef __STATS_INFO_H__
#define __STATS_INFO_H__

#include "utils/common.h"
#include "utils/bfgp_utils.h"

class StatsInfo{
public:
    StatsInfo(){
        add_timer("start");
        _all_info = "";
    }

    void add_timer(const std::string &name){
        _timers[name] = utils::get_time();
    }

    void add_info_msg(const std::string &message){
        auto info_msg = "[INFO] " + message + "\n";
        std::cout << info_msg;
        _all_info += info_msg;
    }

    std::string get_all_info() const{
        return _all_info;
    }

    void timers_info(const std::string &message,
                     const std::string &start_timer_name = "",
                     const std::string &end_timer_name = ""){
        auto diff_time = get_seconds(start_timer_name, end_timer_name);
        auto out_line = "[INFO] " + message + " " + utils::print_time(diff_time) + "\n";
        std::cout << out_line;
        _all_info += out_line;
    }

    double get_seconds( const std::string &start_timer_name = "", const std::string &end_timer_name = ""){
        auto start_it = _timers.find(start_timer_name);
        auto end_it = _timers.find(end_timer_name);
        assert(start_it != _timers.end() and end_it != _timers.end());
        return utils::seconds_ellapsed(start_it->second, end_it->second);
    }

private:
    std::map<std::string, std::chrono::time_point<std::chrono::system_clock>> _timers;
    std::string _all_info;
};

#endif //__STATS_INFO_H__
