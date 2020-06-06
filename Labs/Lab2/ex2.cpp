
#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct {
    //string Name="stringwentwrong";
    char Name[16];
    int ChineseScore;
    int MathScore;
    int EnglishScore;
} Student;

int compare(const void* p1, const void* p2) {
    // TODO: complete compare function for qsort()
    Student *student1,*student2;
    student1=(Student*)p1;
    student2=(Student*)p2;
    int total_score1,total_score2;
    total_score1=(*student1).ChineseScore+(*student1).MathScore+(*student1).EnglishScore;
    total_score2=(*student2).ChineseScore+(*student2).MathScore+(*student2).EnglishScore;
    return total_score2-total_score1;
}

int main() {
    // TODO: read input
    int student_num;
    cin >> student_num;
    Student test_students[student_num];
    for(int i = 0;i < student_num;++ i) {
        cin >> test_students[i].Name >> test_students[i].ChineseScore >>
        test_students[i].MathScore >> test_students[i].EnglishScore;
    }

    /*for(int i = 0;i < student_num;++ i) {
        cout << test_students[i].Name << " " << test_students[i].ChineseScore << " " <<
             test_students[i].MathScore <<  " " << test_students[i].EnglishScore << endl;
    }*/
    // TODO: sort array with qsort()
    qsort(test_students,student_num,sizeof(Student),compare);
    // TODO: print result
    for(int i = 0;i < student_num;++ i) {
        cout << test_students[i].Name << " " << test_students[i].ChineseScore << " " <<
        test_students[i].MathScore <<  " " << test_students[i].EnglishScore << endl;
    }
    return 0;
}
