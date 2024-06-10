//
// Created by clemens on 6/8/24.
//

#ifndef SKIBIDICOMPILER_CONSOLECOLORS_H
#define SKIBIDICOMPILER_CONSOLECOLORS_H

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define COLOR_RESET   std::string("\033[0m")
#define COLOR_BLACK   std::string("\033[30m")      /* Black */
#define COLOR_RED     std::string("\033[31m")      /* Red */
#define COLOR_GREEN   std::string("\033[32m")      /* Green */
#define COLOR_YELLOW  std::string("\033[33m")      /* Yellow */
#define COLOR_BLUE    std::string("\033[34m")      /* Blue */
#define COLOR_MAGENTA std::string("\033[35m")      /* Magenta */
#define COLOR_CYAN    std::string("\033[36m")      /* Cyan */
#define COLOR_WHITE   std::string("\033[37m")      /* White */
#define COLOR_BOLDBLACK   std::string("\033[1m\033[30m")      /* Bold Black */
#define COLOR_BOLDRED     std::string("\033[1m\033[31m")      /* Bold Red */
#define COLOR_BOLDGREEN   std::string("\033[1m\033[32m")      /* Bold Green */
#define COLOR_BOLDYELLOW  std::string("\033[1m\033[33m")      /* Bold Yellow */
#define COLOR_BOLDBLUE    std::string("\033[1m\033[34m")      /* Bold Blue */
#define COLOR_BOLDMAGENTA std::string("\033[1m\033[35m")      /* Bold Magenta */
#define COLOR_BOLDCYAN    std::string("\033[1m\033[36m")      /* Bold Cyan */
#define COLOR_BOLDWHITE   std::string("\033[1m\033[37m")      /* Bold White */

#endif //SKIBIDICOMPILER_CONSOLECOLORS_H
