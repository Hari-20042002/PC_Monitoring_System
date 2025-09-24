#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

int main(){
    std::string input;
    std::string trigger;
    int duration;

    std::cout << "Hey what app are you going to use at this time: ";
    std::getline(std::cin, input);

    std::time_t currentTime = std::time(nullptr);
    std::cout << "monitoring started for : " << input << " at " << std::ctime(&currentTime) << std::endl;

    std::ofstream outfile("system_usage_log.txt", std::ios::app);
    outfile << input << " started at " << std::ctime(&currentTime) << std::endl;

    std::cout<< "press ok to stop monitoring..." << std::endl;
    std:: cin >> trigger;
    if(trigger == "ok"){
        std::time_t stoppedTime = std::time(nullptr);
        duration = std::difftime(stoppedTime, currentTime);
        std::cout << "You used " << input << " for " << duration << "seconds." << std::endl;
        outfile << input << " stopped at " << std::ctime(&stoppedTime) << "duration: " << duration << "seconds." << std::endl;
        outfile.close();
        
    }

    return 0;

}