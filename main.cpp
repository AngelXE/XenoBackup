/*
MIT License

Copyright (c) 2026 AngelXE

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <chrono>
#include <climits>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <thread>

std::string spaceprint =
    "+-----------------------------------------------------+";

std::string dir;
long long seconds;

const long long MAX_SECONDS = 999999999;

bool isDirectory(const std::string& path) {
    struct stat info;

    if (stat(path.c_str(), &info) != 0) {
        return false;
    }

    return S_ISDIR(info.st_mode);
}

bool exists(const std::string& path) {
    struct stat info;

    return stat(path.c_str(), &info) == 0;
}

bool createDirectory(const std::string& path) {
    if (exists(path)) {
        return isDirectory(path);
    }

    return mkdir(path.c_str(), 0755) == 0;
}

bool copyFile(
    const std::string& source,
    const std::string& destination
) {
    std::ifstream input(
        source.c_str(),
        std::ios::binary
    );

    std::ofstream output(
        destination.c_str(),
        std::ios::binary
    );

    if (!input.is_open() || !output.is_open()) {
        return false;
    }

    output << input.rdbuf();

    return output.good();
}

bool cloneDirectory(
    const std::string& source,
    const std::string& destination
) {
    if (!isDirectory(source)) {
        return false;
    }

    if (!createDirectory(destination)) {
        return false;
    }

    DIR* directory = opendir(source.c_str());

    if (directory == NULL) {
        return false;
    }

    struct dirent* entry;

    while ((entry = readdir(directory)) != NULL) {
        std::string name = entry->d_name;

        if (name == "." || name == "..") {
            continue;
        }

        std::string sourcePath =
            source + "/" + name;

        std::string destinationPath =
            destination + "/" + name;

        if (isDirectory(sourcePath)) {
            if (!cloneDirectory(
                    sourcePath,
                    destinationPath
                )) {

                closedir(directory);
                return false;
            }
        }
        else {
            if (!copyFile(
                    sourcePath,
                    destinationPath
                )) {

                std::cout
                    << "[!] Failed to copy: "
                    << sourcePath
                    << std::endl;

                closedir(directory);
                return false;
            }
        }
    }

    closedir(directory);

    return true;
}

void createBackup(long long backupNumber) {
    if (!exists(dir)) {
        std::cout
            << "[!] Directory does not exist: "
            << dir
            << std::endl;

        return;
    }

    if (!isDirectory(dir)) {
        std::cout
            << "[!] Source is not a directory."
            << std::endl;

        return;
    }

    std::string folderName = dir;

    std::size_t slash =
        folderName.find_last_of("/");

    if (slash != std::string::npos) {
        folderName =
            folderName.substr(slash + 1);
    }

    if (folderName.empty()) {
        folderName = "backup";
    }

    std::stringstream backupName;

    backupName
        << folderName
        << "_backup_"
        << backupNumber;

    std::string backupPath =
        backupName.str();

    if (exists(backupPath)) {
        std::cout
            << "[!] Backup already exists: "
            << backupPath
            << std::endl;

        return;
    }

    std::cout
        << "[*] Creating backup..."
        << std::endl;

    if (cloneDirectory(dir, backupPath)) {
        std::cout
            << "[+] Backup created: "
            << backupPath
            << std::endl;
    }
    else {
        std::cout
            << "[!] Backup failed."
            << std::endl;
    }
}

void countLoop() {
    long long backupNumber = 1;

    while (true) {
        std::this_thread::sleep_for(
            std::chrono::seconds(seconds)
        );

        createBackup(backupNumber);

        if (backupNumber >= LLONG_MAX) {
            std::cout
                << "[!] Backup number limit reached."
                << std::endl;

            break;
        }

        backupNumber++;
    }
}

void menu() {
    std::cout
        << "   _  __              ___           __           "
        << std::endl;

    std::cout
        << "  | |/_/__ ___  ___  / _ )___ _____/ /____ _____ "
        << std::endl;

    std::cout
        << " _>  </ -_) _ \\/ _ \\/ _  / _ `/ __/  '_/ // / _ \\"
        << std::endl;

    std::cout
        << "/_/|_|\\__/_//_/\\___/____/\\_,_/\\__/_/\\_\\\\_,_/ .__/"
        << std::endl;

    std::cout
        << "                                          /_/     "
        << std::endl;

    std::cout
        << spaceprint
        << std::endl;
}

int main() {
    menu();

    std::cout << "dir> ";
    std::getline(std::cin, dir);

    if (dir.empty()) {
        std::cout
            << "[!] Directory cannot be empty."
            << std::endl;

        return 1;
    }

    std::string secondsInput;

    std::cout << "seconds> ";
    std::cin >> secondsInput;

    std::stringstream ss(secondsInput);

    ss >> seconds;

    if (ss.fail()) {
        bool digits = true;

        for (std::size_t i = 0;
             i < secondsInput.length();
             i++) {

            if (i == 0 && secondsInput[i] == '-') {
                continue;
            }

            if (
                secondsInput[i] < '0' ||
                secondsInput[i] > '9'
            ) {
                digits = false;
                break;
            }
        }

        if (digits) {
            std::cout
                << "That number is too big!"
                << std::endl;
        }
        else {
            std::cout
                << "Invalid number."
                << std::endl;
        }

        return 1;
    }

    char extra;

    if (ss >> extra) {
        std::cout
            << "Invalid number."
            << std::endl;

        return 1;
    }

    if (seconds <= 0) {
        std::cout
            << "Number must be greater than 0."
            << std::endl;

        return 1;
    }

    if (seconds > MAX_SECONDS) {
        std::cout
            << "That number is too big!"
            << std::endl;

        return 1;
    }

    std::cout
        << spaceprint
        << std::endl;

    std::cout
        << "dir: "
        << dir
        << std::endl;

    std::cout
        << "seconds: "
        << seconds
        << std::endl;

    std::cout
        << spaceprint
        << std::endl;

    std::cout
        << "[*] XenoBackup started."
        << std::endl;

    std::cout
        << "[*] Next backup in "
        << seconds
        << " seconds."
        << std::endl;

    countLoop();

    return 0;
}
