#pragma once

#ifndef _LOGSTATUS_H
#define _LOGSTATUS_H

#include <stdio.h>
#include <string>

class LogStat 
{
    public:
        LogStatus(){}

        LogStatus(std::string area){
            this -> area = area;
        }

        void Status(const std::string stat){
            std::cout << area << "'s status: " << stat << '\n';
        }
}   