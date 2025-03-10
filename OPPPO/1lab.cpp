#include "1lab.h"

// ���������� ������������ Movie
Movie::Movie(const std::string& t) : title(t) {}

std::string Movie::getTitle() const {
    return title;
}

// ���������� FeatureFilm
FeatureFilm::FeatureFilm(const std::string& t, const std::string& d) : Movie(t), director(d) {
    if (t.empty() || d.empty()) {
        throw std::invalid_argument("�������� ������ � ��� ��������� �� ����� ���� �������.");
    }
}


void FeatureFilm::print() const {
    std::cout << "������� �����: " << title << ", ��������: " << director << '\n';
}

bool FeatureFilm::matchesCondition(const std::string& condition) const {
    return director == condition;
}

std::string FeatureFilm::getDirector() const {
    return director;
}

// ���������� Cartoon
Cartoon::Cartoon(const std::string& t, const std::string& type) : Movie(t), animationType(type) {}

void Cartoon::print() const {
    std::cout << "����������: " << title << ", ���: " << animationType << '\n';
}

bool Cartoon::matchesCondition(const std::string& condition) const {
    return animationType == condition;
}

// ���������� TVSeries
TVSeries::TVSeries(const std::string& t, const std::string& d, int e) : Movie(t), director(d), episodes(e) {
    if (t.empty() || d.empty()) {
        throw std::invalid_argument("�������� ������� � ��� ��������� �� ����� ���� �������.");
    }
}


void TVSeries::print() const {
    std::cout << "������: " << title << ", ��������: " << director << ", �����: " << episodes << '\n';
}

bool TVSeries::matchesCondition(const std::string& condition) const {
    return director == condition;
}

// ��������� �������
std::vector<std::unique_ptr<Movie>> movies;

// ��������� ������� ADD
void addMovie(const std::string& type, const std::vector<std::string>& args) {
    if (type == "FeatureFilm" && args.size() == 2) {
        movies.push_back(std::make_unique<FeatureFilm>(args[0], args[1]));
    }
    else if (type == "Cartoon" && args.size() == 2) {
        movies.push_back(std::make_unique<Cartoon>(args[0], args[1]));
    }
    else if (type == "TVSeries" && args.size() == 3) {
        movies.push_back(std::make_unique<TVSeries>(args[0], args[1], std::stoi(args[2])));
    }
}

// ��������� ������� REM
void removeMovie(std::string condition) {
    if (!condition.empty() && condition.front() == '"' && condition.back() == '"') {
        condition = condition.substr(1, condition.size() - 2);
    }

    movies.erase(std::remove_if(movies.begin(), movies.end(), [&](const std::unique_ptr<Movie>& movie) {
        return movie->matchesCondition(condition);
        }), movies.end());
}




// ��������� ������� PRINT
void printMovies() {
    for (const auto& movie : movies) {
        movie->print();
    }
}

// ������ ����� � ��������� ������
void processFile(const std::string& filename) {
    setlocale(LC_ALL, "ru");
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "������: �� ������� ������� ���� " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string command, type;
        iss >> command;
        if (command == "ADD") {
            iss >> type;
            std::vector<std::string> args;
            std::string arg;
            while (iss >> std::ws >> std::quoted(arg)) {
                args.push_back(arg);
            }
            addMovie(type, args);
        }
        else if (command == "REM") {
            std::string condition;
            std::getline(iss >> std::ws, condition);
            removeMovie(condition);
        }
        else if (command == "PRINT") {
            printMovies();
        }
    }
}

// ������� �������
//int main() {
//    processFile("movies.txt");
//    return 0;
//}




/*
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

// ������� ����� "�����"
class Movie {
protected:
    std::string title;  // �������� ������
public:
    Movie(const std::string& t) : title(t) {}
    virtual ~Movie() = default;
    virtual void print() const = 0;
    virtual bool matchesCondition(const std::string& condition) const = 0;

    // ��������� ������ ��� ������
    std::string getTitle() const { return title; }
};

// ������� �����
class FeatureFilm : public Movie {
    std::string director;
public:
    FeatureFilm(const std::string& t, const std::string& d) : Movie(t), director(d) {}
    void print() const override {
        std::cout << "������� �����: " << title << ", ��������: " << director << '\n';
    }
    bool matchesCondition(const std::string& condition) const override {
        return director == condition;
    }

    // ��������� ����� ��� ��������� ��������
    std::string getDirector() const { return director; }
};

// ����������
class Cartoon : public Movie {
    std::string animationType;
public:
    Cartoon(const std::string& t, const std::string& type) : Movie(t), animationType(type) {}
    void print() const override {
        std::cout << "����������: " << title << ", ���: " << animationType << '\n';
    }
    bool matchesCondition(const std::string& condition) const override {
        return animationType == condition;
    }
};

// ������
class TVSeries : public Movie {
    std::string director;
    int episodes;
public:
    TVSeries(const std::string& t, const std::string& d, int e) : Movie(t), director(d), episodes(e) {}
    void print() const override {
        std::cout << "������: " << title << ", ��������: " << director << ", �����: " << episodes << '\n';
    }
    bool matchesCondition(const std::string& condition) const override {
        return director == condition;
    }
};

// ��������� �������
std::vector<std::unique_ptr<Movie>> movies;

// ��������� ������� ADD
void addMovie(const std::string& type, const std::vector<std::string>& args) {
    if (type == "FeatureFilm" && args.size() == 2) {
        movies.push_back(std::make_unique<FeatureFilm>(args[0], args[1]));
    }
    else if (type == "Cartoon" && args.size() == 2) {
        movies.push_back(std::make_unique<Cartoon>(args[0], args[1]));
    }
    else if (type == "TVSeries" && args.size() == 3) {
        movies.push_back(std::make_unique<TVSeries>(args[0], args[1], std::stoi(args[2])));
    }
}

// ��������� ������� REM
void removeMovie(const std::string& condition) {
    movies.erase(std::remove_if(movies.begin(), movies.end(), [&](const std::unique_ptr<Movie>& movie) {
        return movie->matchesCondition(condition);
        }), movies.end());
}

// ��������� ������� PRINT
void printMovies() {
    for (const auto& movie : movies) {
        movie->print();
    }
}

// ������ ����� � ��������� ������
void processFile(const std::string& filename) {
    setlocale(LC_ALL, "ru");
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "������: �� ������� ������� ���� " << filename << std::endl;
        std::ofstream errorFile("error.txt");
        if (errorFile.is_open()) {
            errorFile << "������: ���� " << filename << " �� ������." << std::endl;
            std::cerr << "������ ���� error.txt � ��������� ������." << std::endl;
        }
        else {
            std::cerr << "�� ������� ������� error.txt" << std::endl;
        }
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string command, type;
        iss >> command;
        if (command == "ADD") {
            iss >> type;
            std::vector<std::string> args;
            std::string arg;
            while (iss >> std::quoted(arg)) {
                args.push_back(arg);
            }
            addMovie(type, args);
        }
        else if (command == "REM") {
            std::string condition;
            std::getline(iss >> std::ws, condition);

            // ������� �������, ���� ��� ����
            if (!condition.empty() && condition.front() == '"' && condition.back() == '"') {
                condition = condition.substr(1, condition.size() - 2);
            }
            removeMovie(condition);
        }
        else if (command == "PRINT") {
            printMovies();
        }
    }
}

int main() {
    processFile("movies.txt");
    return 0;
}

*/