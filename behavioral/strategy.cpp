/**
  * @purpose     Demonstrate strategy design pattern using pointers
  *
  * @description Encapsulate an algorithm in a class hierarchy
  *              The users of that algorithm will hold a pointer
  *              to the super class of that hierarchy and delegate 
  *              all requests for the algorithm to that 
  *              "anonymous" object.
  *
  * @note        This program uses only English ASCII characters - no unicode/wide char, yet
  *
  * @author      Ashish
  * @license     MIT license
  * @version     1.0, Doxygen compatible comments
  */
#include<iostream>
#include<sstream>
#include<string>
using namespace std;

/** \brief Trimming padding spaces
  */
inline string trim(string& given_string) {  /// non-constness is intentional
    given_string.erase(0, given_string.find_first_not_of(' '));  /// prefix
    given_string.erase(given_string.find_last_not_of(' ') + 1);  /// suffix
    return given_string;
}

/** \brief AlignText super class
  *        Delegates the text alignment algorithm to sub classes
  */
class TextAlignment {
 private:
    int width_;

 public:
    explicit TextAlignment(int width) : width_(width) {
    }

    int width(void) {
        return width_;
    }

    virtual string apply_to(const string &text) = 0;
};

/** \brief LeftAlign is a type of TextAlignment
  *        It implements Left Text Alignment algorithm
  *           by padding with spaces on right of text
  */
class LeftAlign : public TextAlignment {
 public:
    explicit LeftAlign(int width) : TextAlignment(width) {
    }

    string apply_to(const string &text) {
        string result = text;
        trim(result);
        if (result.length() < width() && !result.empty()) {
            int pad = width() - result.length();
            result.append(pad, ' ');
        }
        return result;
    }
};

/** \brief RightAlign is a type of TextAlignment
  *        It implements Right Text Alignment algorithm
  *           by padding with spaces on left of text
  */
class RightAlign : public TextAlignment {
 public:
    explicit RightAlign(int width) : TextAlignment(width) {
    }

    string apply_to(const string &text) {
        string result = text;
        trim(result);
        if (result.length() < width() && !result.empty()) {
            int pad = width() - result.length();
            result.insert(result.begin(), pad, ' ');
        }
        return result;
    }
};

/** \brief CenterAlign is a type of TextAlignment
  *        It implements Center Text Alignment algorithm
  *           by padding with spaces on both sides of text
  */
class CenterAlign : public TextAlignment {
 public:
    explicit CenterAlign(int width) : TextAlignment(width) {
    }

    string apply_to(const string &text) {
        string result = text;
        trim(result);
        if (result.length() < width() && !result.empty()) {
            int pad = (width() - result.length()) / 2;
            result.insert(result.begin(), pad, ' ');
            result.insert(result.end(), pad, ' ');
        }
        return result;
    }
};

/** \brief WordDocument is the user class
  *        It uses the TextAlignment class hierarchy by super class pointer
  *        to apply different types of text alignment to document_text_
  *        
  * \note  Does not have a default constructor - Any document must have a line_width.
  */
class WordDocument {
 private:
     int line_width_;
    string document_text_;
    TextAlignment *text_alignment_;  /// base class pointer to algorith strategy class - TextAlignment

 public:
     enum AlignType_t {
        ALIGN_LEFT, ALIGN_RIGHT, ALIGN_CENTER
    };

    explicit WordDocument(const int &line_width)
    : text_alignment_(NULL), line_width_(line_width) {
    }

    void set_line_width(int width) {
        line_width_ = width;
    }

    void do_align(int align_type) {
        if (text_alignment_)
            delete text_alignment_;

        switch (align_type) {
            case ALIGN_LEFT:    text_alignment_ = new LeftAlign(line_width_);
                                break;
            case ALIGN_RIGHT:   text_alignment_ = new RightAlign(line_width_);
                                break;
            case ALIGN_CENTER:  text_alignment_ = new CenterAlign(line_width_);
                                break;
            default:            text_alignment_ = new LeftAlign(line_width_);  /// Left alignment is the default
                                break;
        }

        document_text_ = text_alignment_->apply_to(document_text_);
    }

    void write(const string& given_text) {
        document_text_ = given_text;
    }

    string read(void) {
        return document_text_;
    }
};

int main() {
    const int LINE_WIDTH = 60;
    WordDocument new_document(LINE_WIDTH);

    new_document.write("The quick brown fox jumped over the lazy dog");

    new_document.do_align(WordDocument::ALIGN_LEFT);
    cout << new_document.read() << endl;

    new_document.do_align(WordDocument::ALIGN_RIGHT);
    cout << new_document.read() << endl;

    new_document.do_align(WordDocument::ALIGN_CENTER);
    cout << new_document.read() << endl;

    return 0;
}
