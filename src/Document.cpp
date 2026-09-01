#include "Document.hpp"
#include <fstream>

Document::Document(std::string title, std::string contents) {
    title_ = title;
    contents_ = contents;

}

bool Document::operator==(const Document& other) const {
    return title_ == other.title_ &&
            sourcePath_ == other.sourcePath_ &&
            contents_ == other.contents_;

}

bool Document::operator!=(const Document& other) const {
    return !(*this == other);

}

bool Document::load(const std::string& path) {
    std::ifstream file(path);

    if (!file) {
        return false;
    }

    std::string newContents;
    char character;

    while (file.get(character)) {
        newContents += character;
    }

    if (file.bad()) {
        return false;
    }

    std::size_t position = path.find_last_of('/');
    std::string newTitle;

    if (position == std::string::npos) {
        newTitle = path;
    } else {
        newTitle = path.substr(position + 1);
    }

    sourcePath_ = path;
    title_ = newTitle;
    contents_ = newContents;

    return true;

}

const std::string& Document::title() const noexcept {
    return title_;

}

const std::string& Document::sourcePath() const noexcept {
    return sourcePath_;

}

const std::string& Document::contents() const noexcept {
    return contents_;
  
}

void Document::setTitle(std::string title) {
    title_ = title;
  
}

std::size_t Document::characterCount() const noexcept {
    return contents_.size();
    
}

bool Document::empty() const noexcept {
    return contents_.empty();
   
}
