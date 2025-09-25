#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <algorithm>

std::string appName;
std::string catogery;
std::string option;
std::string trigger;
std::map<std::string, int> appUsage;
int duration;
int totalTime = 0;

void quickLoadData(){
    std::ifstream file("system_usage_log.txt");
    std::string line;
    std::string appName;
    while(std::getline(file, line)){
        //std::cout << line << std::endl;
        //std::cout << line.find("stopped at") << std::endl;
        if(line.empty()){
            continue; // Skip empty lines
        }
        if(line.find("stopped at") != std::string::npos){
            appName = line.substr(0, line.find(" "));
        }

        size_t durPos = line.find("minutes:");
        //std::cout << durPos << std::endl;
        if(line.find("duration: ") != std::string::npos && durPos != std::string::npos){
            durPos += 8;
            //std::string numStr = line.substr(durPos, line.find("hours")-durPos);
            size_t secEnd = line.find("seconds", durPos);
            std::string secStr = line.substr(durPos, secEnd - durPos);
            secStr.erase(0, secStr.find_first_not_of(" ")); // remove leading spaces
            secStr.erase(secStr.find_last_not_of("0123456789"), std::string::npos); // remove trailing non-digit characters"))

            if(!secStr.empty()){
                int duration = std::stoi(secStr);
            //std::cout << "App: " << appName << ", Duration: " << duration << " seconds" << std::endl;
                appUsage[appName] += duration;
                totalTime += duration; 
                //std::cout << "Extracted seconds string: [" << secStr << "]" << std::endl;

            }
            
        }
        
    }
    file.close();

}

std::string formatTime(int seconds){
    int hrs = seconds/3600;
    int mins = seconds/60;
    int secs = seconds % 60;
    //std::cout << "Time Spent - " << hrs << " hours, " << mins << " minutes, " << secs << " seconds." << std::endl;
    std::string formattedTime = std::to_string(hrs) + " hours:" + std::to_string(mins) + " minutes:" + std::to_string(secs) + " seconds.";
    return formattedTime;

}

std::string formatTotalTime(int seconds){
    int hrs = seconds/3600;
    int mins = seconds/60;
    int secs = seconds % 60;
    //std::cout << "Time Spent - " << hrs << " hours, " << mins << " minutes, " << secs << " seconds." << std::endl;
    std::string formattedTime = std::to_string(hrs) + " hours:" + std::to_string(mins) + " minutes:" + std::to_string(secs) + " seconds.";
    return formattedTime;

}


void monitorApp(){
    std::cout << "\nHey what app are you going to use at this time: ";
    std::cin.ignore();
    //std::cin >> input;
    std::getline(std::cin, appName);
    //std::cout << "your input " << input << std::endl;
    std::cout<< "Enter Catogery of the app (work/ Gaming/ Social/ Learning/ Other): ";
    std::getline(std::cin, catogery);

    //std::cout << "Entered at current time phase: ";
    std::time_t currentTime = std::time(nullptr);
    std::cout << "\nmonitoring started for : " << appName << " at " << std::ctime(&currentTime) << std::endl;

    //std::cout << "writing to the file..."<<std::endl;
    std::ofstream outfile("system_usage_log.txt", std::ios::app);
    //std::cout << "file opened successfully..."<<std::endl;
    outfile <<std::endl << appName << "[" << catogery << "]" << " started at " << std::ctime(&currentTime);
    //std::cout << "written to the file successfully..."<<std::endl;

    std::cout<< "\npress ok to stop monitoring..." << std::endl;
    std:: cin >> trigger;
    if(trigger == "ok"){
        std::time_t stoppedTime = std::time(nullptr);
        duration = std::difftime(stoppedTime, currentTime);
        std::cout << "\nYou used " << appName << " for " << duration << "seconds." << std::endl;
        appUsage[appName] += duration;
        totalTime += duration; // input is the app name, duration is the usage time
        outfile << appName << "[" << catogery << "]" << " stopped at " << std::ctime(&stoppedTime) << "duration: " << formatTime(duration) << std::endl;
        std::cout << std::endl;
        outfile.close();
    }            

    // Your current monitoring code

}

void viewLogs(){
    std::ifstream infile("system_usage_log.txt");
    std::string line;

    while(std::getline(infile, line)){
        std::cout << line << std::endl;
    }

    infile.close();
    // Read and display file
}

void showSummary(){
    // Calculate and show stats
    std::cout << std::endl;
    std::cout << "\nAnalysing todays activities: loading" << std::endl;
    for(const auto& [key, value] : appUsage) {
        std::cout << key << ": " << formatTime(value) << std::endl;
    }

    std::cout << "\nQuick summary:\n";
    std::cout<< "All apps used today: " << appUsage.size() << std::endl;
    std::cout<< "Total time spent: " << formatTotalTime(totalTime) << std::endl;

}

int main(){
    quickLoadData();
    while(true){
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "\nMonitor new app: press 1" << std::endl << "View today's logs : Press 2" << std::endl << "View Summary : Press 3" << std::endl << "Exit: press 4" << std::endl;
        std::cout << "\nEnter your option: ";
        std::cin >> option;
        if(option == "1"){
            monitorApp();
            
        }else if(option == "2"){
            //viewLogs();
            viewLogs();
            
        }else if(option == "3"){    
            showSummary();

        }else if(option == "4"){
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            break;
        }else{
            std::cout << "Invalid option. Please try again." << std::endl;
            std::cout << "----------------------------------------"; 
            std::cout << "\nMonitor new app: press 1" << std::endl << "View today's logs : Press 2" << std::endl << "View Summary : Press 3" << std::endl << "Exit: press 4" << std::endl;
            std::cout << "Enter your option: ";
            std::cin >> option;
        }

    }
    
    return 0;
}

