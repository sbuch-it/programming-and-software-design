/*
Implementare un piccolo motore di ricerca dei file
sul vostro computer (o una sua directory).
Realizzare una lista inversa
https://en.wikipedia.org/wiki/Inverted_index
che permetta di cercare i files che contengono certi termini.
Una lista inversa è una struttura dati che per ogni parola
memorizza l'insieme dei files che la contengono.
*/

#include <map>
#include <vector>
#include <string>
#include <sstream> // string stream
#include <fstream> // file stream
#include <iostream>
#include <filesystem> // filesystem library

const std::string path = "/Users/alessiobucciarelli/Desktop/SearchEngine";

class Position {
 private:
    // word position
    int line;
    int index;
    std::string filename;
    std::string directory;

 public:
    // default constructor
    Position(
    const int line_,
    const int index_,
    const std::string& filename_,
    const std::string& directory_) :
    line(line_), index(index_), filename(filename_), directory(directory_) { }

    // getters
    inline int GetLine() const {
        return line;
    }
    inline int GetIndex() const {
        return index;
    }
    inline const std::string& GetFileName() const {
        return filename;
    }
    inline const std::string& GetDirectory() const {
        return directory;
    }
};


class SearchEngine {
 private:
    // word -> position
    typedef std::map< std::string, std::vector<Position> > Word2Position;
    Word2Position word2position;

 public:
    // default constructor
    SearchEngine() { }

    void AddFile(const std::string& filepath, const std::string& filename);
    void SearchWord(const std::string& word);
};


void SearchEngine::AddFile(const std::string& filepath, const std::string& filename){

    // get the directory from filepath
    std::string directory = filepath;

    int pos_path = directory.find(path);
    if (pos_path != std::string::npos) {
        directory.replace(pos_path, path.length(), "");
    }

    int pos_filename = directory.find(filename);
    if (pos_filename != std::string::npos) {
        directory.replace(pos_filename, filename.length(), "");
    }

    // open file and check if it is good
    std::ifstream is(filepath);
    if (!is.good()) {
        std::cerr << "Can not load data from file" << std::endl;
        return;
    }
    
    int line_num = 0;
    int index_num = 0;

    std::string line;
    std::string word;

    // get a line
    while (getline(is, line)) {

        line_num++;
        index_num = 0;
        std::stringstream s(line);
        
        // get a single word of a line
        while (s >> word) {

            index_num++;
            Position p(line_num, index_num, filename, directory);
            word2position[word].push_back(p);

        }
    }
    is.close();
}


void SearchEngine::SearchWord(const std::string& word) {

    // check if word is present
    if (word2position.find(word) == word2position.end()) {
        std::cout << "The word is not present in any file \n\n";
        return;
    } else {
        std::cout << "The word has been found " 
        << word2position[word].size() << " times in the following files \n";
    }

    // if the word is present
    int line;
    int index;
    std::string filename;
    std::string directory;
    std::string filename_prev = "";
    std::string directory_prev = "";

    for(int i = 0; i < word2position[word].size() ; i++)  {

        line = word2position[word][i].GetLine();
        index = word2position[word][i].GetIndex();
        filename = word2position[word][i].GetFileName();
        directory = word2position[word][i].GetDirectory();

        if (filename != filename_prev || directory != directory_prev) {
            std::cout << "\n Path: "<< directory << "" << filename << std::endl;
            std::cout << "Position: line -> "<< line << " , index -> "<< index;
            std::cout << std::endl;
        } else {
            std::cout << "Position: line -> "<< line << " , index -> "<< index;
            std::cout << std::endl;
        }

        filename_prev = filename;
        directory_prev = directory;

    }
    
    std::cout << std::endl << std::endl;
}


int main() {

    SearchEngine se;

    for (const auto & file : std::__fs::filesystem::recursive_directory_iterator(path)) {
        if (file.path().extension() == ".txt") {
            se.AddFile(file.path(), file.path().filename());
        }
    }

    std::string s;
    while (true) {
        std::cout << "Enter one word to search for (press return to exit): ";
        std::getline(std::cin, s);
        if (!s.length())
            break;
        se.SearchWord(s);
    }
    return 0;
}