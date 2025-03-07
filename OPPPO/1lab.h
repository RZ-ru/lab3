#ifndef LAB1_H
#define LAB1_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

// Базовый класс "Фильм"
class Movie {
protected:
    std::string title;
public:
    Movie(const std::string& t);
    virtual ~Movie() = default;

    virtual void print() const = 0;
    virtual bool matchesCondition(const std::string& condition) const = 0;

    std::string getTitle() const;
};

// Игровой фильм
class FeatureFilm : public Movie {
    std::string director;
public:
    FeatureFilm(const std::string& t, const std::string& d);
    void print() const override;
    bool matchesCondition(const std::string& condition) const override;
    std::string getDirector() const;
};

// Мультфильм
class Cartoon : public Movie {
    std::string animationType;
public:
    Cartoon(const std::string& t, const std::string& type);
    void print() const override;
    bool matchesCondition(const std::string& condition) const override;
};

// Сериал
class TVSeries : public Movie {
    std::string director;
    int episodes;
public:
    TVSeries(const std::string& t, const std::string& d, int e);
    void print() const override;
    bool matchesCondition(const std::string& condition) const override;
};

// Функции для работы с фильмами
void addMovie(const std::string& type, const std::vector<std::string>& args);
void removeMovie(std::string condition);
void printMovies();
void processFile(const std::string& filename);

#endif  // LAB1_H

