#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <thread>
#include <fstream>
#include <stdexcept> // Include for exception handling
using namespace std;
using namespace chrono;

class TypingTutor {
private:
    string originalSentence;
    int difficultyLevel;

public:
    TypingTutor() : difficultyLevel(1) {}

    void displayWelcomeMessage() {
        cout << "........................" << endl;
        cout << " Welcome to Typing Tutor " << endl;
        cout << "........................" << endl << endl;
    }

    void setDifficultyLevel(int level) {
        difficultyLevel = level;
    }

    int getDifficultyLevel() const {
        return difficultyLevel;
    }

    // Virtual function for getting a random sentence
    virtual string getRandomSentence() = 0; // Abstract method
    string getOriginalSentence() const {
        return originalSentence;
    }

    void setOriginalSentence(const string &sentence) {
        originalSentence = sentence;
    }

    void savePerformanceData(double wpm, double accuracy) {
        ofstream outFile("performance.txt", ios::app);
        outFile << "WPM: " << wpm << ", Accuracy: " << accuracy << "%" << endl;
        outFile.close();
    }

    void classifyErrors(const vector<string> &originalWords, const vector<string> &inputWords, vector<int> &mistakeIndices) {
        int totalWords = originalWords.size();
        for (int i = 0; i < totalWords; i++) {
            if (i >= inputWords.size() || originalWords[i] != inputWords[i]) {
                mistakeIndices.push_back(i);
            }
        }
    }

    double calculateWPM(int correctWords, double timeUsed, int totalMistakes) {
        double penalty = totalMistakes * 0.01;
        double wpm = (correctWords / timeUsed) * 60;
        return wpm * (1 - penalty);
    }

    void displayAnalytics(int correctWords, int totalWords, double timeUsed, const string &input) {
        int totalMistakes = totalWords - correctWords;
        double correctWPM = calculateWPM(correctWords, timeUsed, totalMistakes);
        double accuracy = ((double)correctWords / totalWords) * 100;

        cout << fixed << setprecision(2);
        cout << "Time elapsed: " << timeUsed << " seconds" << endl;
        cout << "Your typing speed: " << correctWPM << " WPM (with error penalties)" << endl;
        cout << "Correct words: " << correctWords << " out of " << totalWords << endl;
        cout << "Accuracy: " << accuracy << "%" << endl;

        if (totalMistakes > 0) {
            cout << "\nFeedback: You made mistakes on the following words:" << endl;
            vector<string> originalWords = splitIntoWords(originalSentence);
            vector<int> mistakeIndices;
            classifyErrors(originalWords, splitIntoWords(input), mistakeIndices);
            for (int index : mistakeIndices) {
                cout << "Word " << index + 1 << ": '" << originalWords[index] << "'" << endl;
            }
        } else {
            cout << "Perfect! You typed the sentence correctly." << endl;
        }

        savePerformanceData(correctWPM, accuracy);
    }

    // Function to split a string into words
    vector<string> splitIntoWords(const string &str) {
        istringstream stream(str);
        vector<string> words;
        string word;
        while (stream >> word) {
            words.push_back(word);
        }
        return words;
    }
};


class EasyTypingTutor : public TypingTutor {
public:
    string getRandomSentence() override {
        vector<string> sentences;
        ifstream file("easy_sentences.txt");
        string line;

        while (getline(file, line)) {
            if (!line.empty()) {
                sentences.push_back(line);
            }
        }

        file.close();

        // Backup sentences in case file is missing or empty
        if (sentences.empty()) {
            sentences = {
                "Practice makes perfect",
                "Typing is a useful skill",
                "Keep your fingers on home row",
                "Accuracy is better than speed",
                "Try again until you succeed"
            };
        }

        int randomIndex = rand() % sentences.size();
        setOriginalSentence(sentences[randomIndex]);
        return sentences[randomIndex];
    }
};

class MediumTypingTutor : public TypingTutor {
public:
    string getRandomSentence() override {
        vector<string> sentences;
        ifstream file("medium_sentences.txt");
        string line;

        while (getline(file, line)) {
            if (!line.empty()) {
                sentences.push_back(line);
            }
        }

        file.close();

        // Backup sentences in case file is missing or empty
        if (sentences.empty()) {
            sentences = {
                "Programming is fun and challenging",
                "Practice makes perfect",
                "Coding improves problem-solving skills",
                "Typing without looking is a skill to master",
                "Learning never exhausts the mind"
            };
        }

        int randomIndex = rand() % sentences.size();
        setOriginalSentence(sentences[randomIndex]);
        return sentences[randomIndex];
    }
};

// Derived class for Hard Typing Tutor
class HardTypingTutor : public TypingTutor {
public:
    string getRandomSentence() override {
        vector<string> sentences;
        ifstream file("hard_sentences.txt");
        string line;

        while (getline(file, line)) {
            if (!line.empty()) {
                sentences.push_back(line);
            }
        }
        file.close();

        // Backup hard sentences if file is missing or empty
        if (sentences.empty()) {
            sentences = {
                "Artificial intelligence is transforming industries across the globe",
                "Memory management in C++ requires careful use of pointers",
                "Consistency is key to mastering complex programming concepts",
                "Data structures like trees and graphs are fundamental in computer science",
                "Machine learning algorithms optimize processes and predict outcomes",
                "To be or not to be, that is the question: Whether 'tis nobler in the mind to suffer",
                "She had been struggling with her programming assignment for hours, trying to debug the stubborn code",
                "The philosopher's nuanced argument required careful consideration of each premise and conclusion",
                "Complex algorithms require an in-depth understanding of both the problem and the data structures used",
                "A curious paradox emerges when one considers Schrödinger's cat, a quantum mechanics thought experiment"
            };
        }

        int randomIndex = rand() % sentences.size();
        setOriginalSentence(sentences[randomIndex]);
        return sentences[randomIndex];
    }
};

// Derived class for Long Lines Tutor
class LongTypingTutor : public TypingTutor {
public:
    string getRandomSentence() override {
        vector<string> sentences;
        ifstream file("long_sentences.txt");
        string line;

        while (getline(file, line)) {
            if (!line.empty()) {
                sentences.push_back(line);
            }
        }
        file.close();

        // Backup sentences if file is missing or empty
        if (sentences.empty()) {
            sentences = {
                "In the midst of chaos, there is also opportunity—a valuable lesson for strategists in times of crisis.",
                "The intricate dance between light and shadow paints a vivid picture of the delicate balance of nature.",
                "To understand the workings of the universe, one must first grasp the fundamental principles that govern it.",
                "When we try to pick out anything by itself, we find it hitched to everything else in the universe.",
                "Time flies like an arrow; fruit flies like a banana, as the wise philosopher once quipped."
            };
        }

        int randomIndex = rand() % sentences.size();
        setOriginalSentence(sentences[randomIndex]);
        return sentences[randomIndex];
    }
};

// Derived class for Paragraphs Tutor
class ParaTypingTutor : public TypingTutor {
public:
    string getRandomSentence() override {
        vector<string> paragraphs;
        ifstream file("paragraphs.txt");
        string line;

        while (getline(file, line)) {
            if (!line.empty()) {
                paragraphs.push_back(line);
            }
        }
        file.close();

        // Backup paragraphs if file is missing or empty
        if (paragraphs.empty()) {
            paragraphs = {
                "The history of human progress is a narrative of resilience and innovation. Through centuries of struggle and triumph, humanity has demonstrated an unwavering spirit, constantly pushing the boundaries of what is possible. From the early days of discovery and exploration to the rapid advancements in technology and medicine, our journey is a testament to the power of knowledge and the relentless pursuit of improvement.",
                "The rain fell steadily, each drop a tiny silver thread stitching the sky to the earth. It was the kind of day that invited reflection, a time for considering the passage of days, the accumulation of small moments that make up a life. As the water pooled on the ground, it mirrored the greyness above, creating an illusion of an endless world where the heavens and the earth met seamlessly.",
                "With the advancement of modern technology, the boundaries of human capability are constantly being redefined. Today, artificial intelligence and machine learning play an integral role in various industries, from healthcare to finance, offering unprecedented opportunities for growth and efficiency. As we navigate this technological landscape, we must also address the ethical considerations that accompany such rapid innovation.",
                "In the quiet of the night, the world seemed to breathe with a subtle rhythm, each sound blending into a symphony of serenity. The rustle of leaves, the distant call of a night bird, and the soft whisper of the wind formed a backdrop for contemplation. It was in these moments that one could feel truly connected to the essence of life itself, appreciating the beauty in stillness.",
                "As civilizations rose and fell, they left behind a rich tapestry of culture and knowledge. These remnants of the past offer a glimpse into the minds of those who came before us, their thoughts, aspirations, and struggles. By studying history, we can draw lessons and insights that help us navigate the complexities of the present and future."
            };
        }

        int randomIndex = rand() % paragraphs.size();
        setOriginalSentence(paragraphs[randomIndex]);
        return paragraphs[randomIndex];
    }
};

// Main function
int main() {
    srand(static_cast<unsigned>(time(NULL)));

    TypingTutor *tutor = nullptr;
    int sentenceType;

    while (true) {
        try {
            cout << "Choose sentence type (1 - Easy, 2 - Medium, 3 - Hard, 4 - Long, 5 - Paragraph): ";
            cin >> sentenceType;

            if (sentenceType < 1 || sentenceType > 5) {
                throw invalid_argument("Invalid choice! Please enter a valid type (1, 2, 3, 4, or 5).");
            }

            // Assigning the tutor based on sentence type
            if (sentenceType == 1) {
                tutor = new EasyTypingTutor();
            } else if (sentenceType == 2) {
                tutor = new MediumTypingTutor();
            } else if (sentenceType == 3) {
                tutor = new HardTypingTutor();
            } else if (sentenceType == 4) {
                tutor = new LongTypingTutor();
            } else if (sentenceType == 5) {
                tutor = new ParaTypingTutor();
            }

            cin.ignore(); // Clear the input buffer
            break; // Exit the loop if valid input
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }

    tutor->displayWelcomeMessage();
    string originalSentence = tutor->getRandomSentence();
    cout << "\nType the following sentence:" << endl;
    cout << originalSentence << endl;

    auto start = high_resolution_clock::now();
    string userInput;
    getline(cin, userInput);
    auto end = high_resolution_clock::now();
    double timeUsed = duration_cast<duration<double>>(end - start).count();

    vector<string> originalWords = tutor->splitIntoWords(originalSentence);
    vector<string> inputWords = tutor->splitIntoWords(userInput);
    int correctWords = 0;

    // Calculate the number of correct words
    for (size_t i = 0; i < min(originalWords.size(), inputWords.size()); i++) {
        if (originalWords[i] == inputWords[i]) {
            correctWords++;
        }
    }

    tutor->displayAnalytics(correctWords, originalWords.size(), timeUsed, userInput);

    delete tutor; // Clean up dynamically allocated memory
    return 0;
}