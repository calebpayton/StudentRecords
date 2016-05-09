/**
 *	Author: Caleb A. Payton
 *
 *	Implementation of a singly linked list to store a collection of student records.
 *	studentRecord class stores three pieces of data (grade, ID, and name).
 *	studentCollection places student records into a singly linked list.
 *	Methods to add students, remove students, find students, and copy records can be found
 *	in the studentCollection class.
 *
 */

#include <iostream>

using namespace std;

class studentRecord
{
	public:
		studentRecord()
		{
			setGrade(0);
			setID(-1);
			setName("");
		}
		studentRecord(int newGrade, int newID, string newName)
		{
			setGrade(newGrade);
			setID(newID);
			setName(newName);
		}
		int getGrade()
		{
			return grade;
		}
		void setGrade(int newGrade)
		{
			if (isValidGrade(newGrade))
				grade = newGrade;
		}
		int getID()
		{
			return studentID;
		}
		void setID(int newID)
		{
			studentID = newID;
		}
		string getName()
		{
			return name;
		}
		void setName(string newName)
		{
			name = newName;
		}
	
	private:
		int grade;
		int studentID;
		string name;
		string letterGrade()
		{
			if (!isValidGrade(grade))
				return "ERROR";
			const int NUMBER_CATEGORIES = 11;
			const string GRADE_LETTER[] = {"F", "D", "D+", "C-", "C", "C+", "B-", "B", "B+", "A-", "A"};
			const int LOWEST_GRADE_SCORE[] = {0, 60, 67, 70, 73, 77, 80, 83, 87, 90, 93};
			int category = 0;
			while ((category < NUMBER_CATEGORIES) && (LOWEST_GRADE_SCORE[category] <= grade))
			{
				category++;
			}
			return GRADE_LETTER[category - 1];
		}
		bool isValidGrade(int grade)
		{
			if ((grade >= 0) && (grade <= 100))
				return true;
			else
				return false;
		}
};

class studentCollection
{
	private:
		struct studentNode
		{
			studentRecord studentData;
			studentNode * next;
		};
	
	public:
		studentCollection()
		{
			listHead = NULL;
		}
		~studentCollection()
		{
			deleteList(listHead);
		}
		studentCollection(const studentCollection &original)
		{
			listHead = copiedList(original.listHead);
		}
		studentCollection& operator=(const studentCollection &rhs)
		{
			if (this != &rhs)
			{
				deleteList(listHead);
				listHead = copiedList(rhs.listHead);
			}
			return *this;
		}
		void addRecord(studentRecord newStudent)
		{
			studentNode * newNode = new studentNode;
			newNode->studentData = newStudent;
			newNode->next = listHead;
			listHead = newNode;
		}
		studentRecord recordWithNumber(int idNum)
		{
			studentNode * loopPtr = listHead;
			while ((loopPtr != NULL) && (loopPtr->studentData.getID() != idNum))
			{
				loopPtr = loopPtr->next;
			}
			if (loopPtr == NULL)
			{
				studentRecord dummyRecord(-1, -1, "");
				return dummyRecord;
			}
			else
			{
				return loopPtr->studentData;
			}
		}
		void removeRecord(int idNum)
		{
			studentNode * loopPtr = listHead;
			studentNode * trailing = NULL;
			while ((loopPtr != NULL) && (loopPtr->studentData.getID() != idNum))
			{
				trailing = loopPtr;
				loopPtr = loopPtr->next;
			}
			if (loopPtr == NULL)
			{
				return;
			}
			if (trailing == NULL)
			{
				listHead = listHead->next;
			}
			else
			{
				trailing->next = loopPtr->next;
			}
			delete loopPtr;
		}
		void printStudentCollection()
		{
			studentNode * loopPtr = listHead;
			cout << "Student Records:\n";
			if (loopPtr == NULL)
			{
				cout << "No student records found" << endl;	
			}
			while (loopPtr != NULL)
			{
				cout << loopPtr->studentData.getID() << "\t" << loopPtr->studentData.getName() 
							<< "\t" << loopPtr->studentData.getGrade() << endl;
				loopPtr = loopPtr->next;
			}
		}		
	
	private:
		typedef studentNode * studentList;
		studentList listHead;
		void deleteList(studentList &listPtr)
		{
			while (listPtr != NULL)
			{
				studentNode * temp = listPtr;
				listPtr = listPtr->next;
				delete temp;
			}
		}
		studentList copiedList(const studentList original)
		{
			if (original == NULL)
			{
				return NULL;
			}
			studentList newList = new studentNode;
			newList->studentData = original->studentData;
			studentNode * oldLoopPtr = original->next;
			studentNode * newLoopPtr = newList;
			while (oldLoopPtr != NULL)
			{
				newLoopPtr->next = new studentNode;
				newLoopPtr = newLoopPtr->next;
				newLoopPtr->studentData = oldLoopPtr->studentData;
				oldLoopPtr = oldLoopPtr->next;
			}
			newLoopPtr->next = NULL;
			return newList;
		}
};

int main ()
{
	studentCollection sc;
	studentRecord sr1(87, 1001, "Caleb");
	sc.addRecord(sr1);
	studentRecord sr2(65, 1002, "Jeff");
	sc.addRecord(sr2);
	studentRecord sr3(94, 1003, "John");
	sc.addRecord(sr3);
	
	sc.printStudentCollection();
	
	sc.removeRecord(1002);
	
	sc.printStudentCollection();	
}
