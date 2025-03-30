#include <iostream>
#include <memory>
#include <vector>
#include <ctime>

struct Question {
    int id;
    std::string text;
    
    Question(int qid, const std::string& qtext) : id(qid), text(qtext) {}
};

struct StudentAnswer {
    int studentId;
    int questionId;
    std::string answer;
    
    StudentAnswer(int sid, int qid, const std::string& ans) 
        : studentId(sid), questionId(qid), answer(ans) {}
};

// Standard Memory Allocation (Slow malloc/new)
void standardMemoryAllocation(int numQuestions, int numStudents) {
    std::vector<Question*> questions;
    std::vector<StudentAnswer*> answers;

    questions.reserve(numQuestions);
    answers.reserve(numQuestions * numStudents);

    clock_t start = clock();

    for (int i = 0; i < numQuestions; i++) {
        questions.push_back(new Question(i, "Sample Question " + std::to_string(i)));
    }

    for (int i = 0; i < numStudents; i++) {
        for (int j = 0; j < numQuestions; j++) {
            answers.push_back(new StudentAnswer(i, j, "Sample Answer"));
        }
    }

    for (auto q : questions) delete q;
    for (auto a : answers) delete a;

    clock_t end = clock();
    std::cout << "Standard Allocation Time: " << double(end - start) / CLOCKS_PER_SEC << "s\n";
}

// Optimized Memory Allocation (Object Pool + Slab Allocation)
class QuestionPool {
    std::unique_ptr<Question[]> pool;
    size_t index;
    size_t size;

public:
    QuestionPool(int maxQuestions) : pool(std::make_unique<Question[]>(maxQuestions)), index(0), size(maxQuestions) {
        for (int i = 0; i < maxQuestions; i++) {
            pool[i] = Question(i, "Sample Question " + std::to_string(i));
        }
    }

    Question* allocate() {
        return (index < size) ? &pool[index++] : nullptr;
    }
};

class AnswerSlab {
    std::unique_ptr<StudentAnswer[]> pool;
    size_t index;
    size_t size;

public:
    AnswerSlab(int maxAnswers) : pool(std::make_unique<StudentAnswer[]>(maxAnswers)), index(0), size(maxAnswers) {}

    StudentAnswer* allocate(int sid, int qid, const std::string& ans) {
        if (index < size) {
            pool[index] = StudentAnswer(sid, qid, ans);
            return &pool[index++];
        }
        return nullptr;
    }
};

void optimizedMemoryAllocation(int numQuestions, int numStudents) {
    QuestionPool qPool(numQuestions);
    AnswerSlab aSlab(numQuestions * numStudents);

    clock_t start = clock();

    for (int i = 0; i < numQuestions; i++) {
        qPool.allocate();
    }

    for (int i = 0; i < numStudents; i++) {
        for (int j = 0; j < numQuestions; j++) {
            aSlab.allocate(i, j, "Sample Answer");
        }
    }

    clock_t end = clock();
    std::cout << "Optimized Allocation Time: " << double(end - start) / CLOCKS_PER_SEC << "s\n";
}

int main() {
    int numQuestions = 10000;
    int numStudents = 1000;

    std::cout << "Starting Standard Memory Allocation Test...\n";
    standardMemoryAllocation(numQuestions, numStudents);

    std::cout << "Starting Optimized Memory Allocation Test...\n";
    optimizedMemoryAllocation(numQuestions, numStudents);

    return 0;
}

