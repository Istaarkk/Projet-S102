#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

void loadPicture(const std::string &picture, std::vector<std::vector<int>> &red,
                 std::vector<std::vector<int>> &green,
                 std::vector<std::vector<int>> &blue);

std::string getFileNameFromUser();

#endif // UTILS_H
