#ifndef EX5_UTILS_H

#include <iostream>
#include <cstring>

#define EXIT_ERROR -1
#define SYS_ERR_MSG_PREFIX "system error: "
#define SYS_ERR_MSG_SUFFIX " failed. "


/**
 * Checks the return value of the given function and if necessary, writes an error to stderr and exits the program.
 * @param return_val a return value from the system function {0: SUCCESS, 1: FAILURE, -1: ERROR}
 * @param func_name
 */
void err_exit(const int return_val, const std::string& func_name) {
    if (return_val == EXIT_ERROR || return_val == EXIT_FAILURE) {
        std::cerr << SYS_ERR_MSG_PREFIX <<
                  func_name << SYS_ERR_MSG_SUFFIX << strerror(errno) << std::endl;
        exit(EXIT_ERROR);
    }
}

#endif //EX5_UTILS_H
