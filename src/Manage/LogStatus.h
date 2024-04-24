#pragma once

#ifndef _LOGSTATUS_H
#define _LOGSTATUS_H

#include <stdio.h>
#include <string>
#include <iostream>

class LogStatus
{
    private:
        std::string area = "";
    public:
        // LogStatus(){

        // }

        LogStatus(std::string area){
            this -> area = area;
        }

        void Status(const std::string stat){
            std::cout << area << "'s status: " << stat << '\n';
        }
};

#endif