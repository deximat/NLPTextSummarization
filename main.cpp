#include <iostream>
#include <map>

class Group {

    // 0 value means this is general word
    // otherwise this will be name of semantic category
public:
    char* ClassName = "0";

    Group(char* className) {
        ClassName = className;
    }
};


class Sentence {

    float m_TotalScore;
    float m_Trashold;

    std::map<Group*, float> m_FreqGroups;


public:

// ***** RESENJE ZADATKA POCETAK *****

    bool SentenceRelevant() {
        static const char* GeneralClassName = "0";

        float relevantScore = 0.0;

        std::map<Group*, float>::iterator iterator = m_FreqGroups.begin();

        while (iterator != m_FreqGroups.end()) {
            Group* group = iterator->first;
            bool groupRelevant = strcmp(group->ClassName, GeneralClassName) != 0;
            if (groupRelevant) {
                float groupScore = iterator->second;
                relevantScore += groupScore;
            }
            iterator++;
        }

        float relevantScoreRatio = relevantScore / m_TotalScore;
        return relevantScoreRatio > m_Trashold;
    };

// ***** RESENJE ZADATKA KRAJ *****


    void initAsRelevantForTest() {
        m_TotalScore = 5;
        m_Trashold = 0.1;

        Group* relevantGroup = new Group("Pravo");
        Group* irrelevantGroup = new Group("0");

        m_FreqGroups.insert(std::pair<Group*, float>(relevantGroup, 3.0f));
        m_FreqGroups.insert(std::pair<Group*, float>(irrelevantGroup, 2.0f));
    }

    void initAsIrrelevantForTest() {
        m_TotalScore = 5;
        m_Trashold = 0.1;

        Group* relevantGroup = new Group("Pravo");
        Group* irrelevantGroup = new Group("0");

        m_FreqGroups.insert(std::pair<Group*, float>(relevantGroup, 0.001f));
        m_FreqGroups.insert(std::pair<Group*, float>(irrelevantGroup, 4.999));
    }

};


int main() {
    std::cout << "Testing begins";
    std::cout << std::endl;

    std::cout << "Initialization of relevant sentence..";
    std::cout << std::endl;


    Sentence* relevantSentence = new Sentence();
    relevantSentence->initAsRelevantForTest();

    std::cout << "RelevantSentence is " << (relevantSentence->SentenceRelevant() ? "relevant" : "irrelevant");
    std::cout << std::endl;

    std::cout << "Initialization of irrelevant sentence..";
    std::cout << std::endl;


    Sentence* irrelevantSentence = new Sentence();
    irrelevantSentence->initAsIrrelevantForTest();

    std::cout << "IrrelevantSentence is " << (irrelevantSentence->SentenceRelevant() ? "relevant" : "irrelevant");
    std::cout << std::endl;


    return 0;
}

