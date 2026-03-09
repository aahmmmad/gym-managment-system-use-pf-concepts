#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

int Count_members = 0;
 const char total_trainers = 100;
 const int size = 100;
void display_menu();
void Add_members(int total_members,int size);
void View_members();
int get_existing_members();
void update_members(char update_id[]);
void fee_submission(char member_id[]);
bool is_member_exist(char id[]);
bool is_fee_submitted(char id[]);
void search_member_by_ID(char search_id[]);
bool admin_login();
void view_trainers();
int load_trainers(char trainers[total_trainers][100]);
void hire_trainer(char trainer[total_trainers][100], int c);
void gender_stats();
void fee_stats();
void delete_member_by_ID(char del_Id[]) ;


void view_unpaid_members();
void clearscreen() {
	system("CLS");
}
int main() {

	
	Count_members = get_existing_members();
	
	int choice = 0;

	cout << " \033[1;30m+-------------------------------------------------------------------------------------------------------------------------+\033[0m " << endl;

	cout << " \033[1;30m+-------------------------------------------------------------------------------------------------------------------------+\033[0m " << endl;
	cout << " \033[1;30m|                                                                                                                         |\033[0m " << endl;
	cout << " \033[1;30m|                                                                                                                         |\033[0m " << endl;
	cout << " \033[1;30m|                                                                                                                         |" << endl;
    cout << " \033[1;36m                                                  GYM MEMBERSHIP SYSTEM                                         \033[0m   " << endl << endl;

	cout << " \033[1;30m|                                                                                                                         |\033[0m  " << endl;
	cout << " \033[1;30m|                                                                                                                         |\033[0m  " << endl;
	cout << " \033[1;30m+-------------------------------------------------------------------------------------------------------------------------+\033[0m " << endl ;
	cout << " \033[1;30m+-------------------------------------------------------------------------------------------------------------------------+\033[0m " << endl << endl;
		if (admin_login()) {
			cout << "Acces Granted:Welcome " << endl << endl;
			display_menu();

		}
		else {
			return 0;
		}
		
		do {
			
		
		cin >> choice;
		cin.ignore();
		
		if (choice == 1) {
			clearscreen();
			int Count_member;
			int Size_of_Field;

			cout << endl << "Enter how many members you want to add" << endl;
			cin >> Count_member;

			cout << "Enter size of each feild " << endl;
			cin >> Size_of_Field;
		
			Add_members(Count_member, Size_of_Field);
		
			
			display_menu();
		}
		else if (choice == 2) {
			clearscreen();
			View_members();
			cout << endl;
		
			display_menu();
		}
		else if(choice == 3) {
			clearscreen();
			char updated_id[100];
			
			cout << "Enter member ID you want to update " << endl;
			
				cin.getline(updated_id, 100);
			update_members(updated_id);
			
			display_menu();
		}
		else if (choice == 4) {
			clearscreen();
			char member_id[50];
			cout << "Enter member ID to submit fee " << endl;
			
				cout << "Enter member ID" << endl;
				cin.getline(member_id, 50);

				if (is_member_exist(member_id)) {
					fee_submission(member_id);

				}
				else {
					cout << "Entered ID not found:Please Try Again " << endl;
				}
				
				display_menu();
			}
		
		  else if (choice == 5) {
			clearscreen();
			char search_id[100];
			cout << "Enter search ID to seacrh member " << endl;
			cin.getline(search_id, 100);
			search_member_by_ID(search_id);
			 
				display_menu();
		   }
			


		  else if (choice == 6) {
			clearscreen();
			view_trainers();
			   
			display_menu();
		}

		  else if (choice == 7) {
			clearscreen();
			view_unpaid_members();
		
			display_menu();
		}

		  else if (choice == 8) {
			clearscreen();
		
			char trainers[total_trainers][100];
			int count = load_trainers(trainers);
			int i = 0, j = 0;
			if (count > 0) {
				view_trainers();
				cout << "Enter Trainer name to hire " << endl;
				hire_trainer(trainers, count);
				
			}
		
			display_menu();
		}
			else if (choice == 9) {
			clearscreen();
				gender_stats();
			
				display_menu();
				
			}
			else if (choice == 10) {
			clearscreen();
			fee_stats();
			
				display_menu();
				
		}
			else if (choice == 11) {
			clearscreen();
			char del_ID[100];
			cout << "Enter member ID you Want to delete " << endl;
			cin.getline(del_ID, 100);
			delete_member_by_ID(del_ID);

			display_menu();

		}
			else if(choice==12){
				cout << "Exiting The Progran:Thankyou " << endl;

		}
			else{
			cout << "Invalid Choice:PLease Enter number between 1 and 11 " << endl;
			
		}
		
		} while (choice != 12);

	} 

void display_menu() {
	cout << "\033[1;30m=====================================================Menu=============================================================\033[0m" << endl << endl;
	cout << "\033[1;31m1.\033[0m Add Members " << endl;
	cout << "\033[1;31m2.\033[0m View Members " << endl;
	cout << "\033[1;31m3.\033[0m Update Members " << endl;
	cout << "\033[1;31m4.\033[0m Fee Submission " << endl;
	cout << "\033[1;31m5.\033[0m Search Member by ID " << endl;
	cout << "\033[1;31m6.\033[0m View Available Trainers " << endl;
	cout << "\033[1;31m7.\033[0m View Unpaid Members " << endl;
	cout << "\033[1;31m8.\033[0m Hire A Trainer " << endl;
	cout << "\033[1;31m9.\033[0m Gender Statistics " << endl;
	cout <<"\033[1;31m10.\033[0mShow Fee Statistics " << endl;
	cout <<"\033[1;31m11.\033[0mDelete Member By ID " << endl;
	cout << "\033[1;31m12.\033[0mExit " << endl << endl;

	cout << "Enter your choice " << endl;

}
bool admin_login() {
	const int password = 1234;
	int pass_entered;
	int attempts = 3;
	while (attempts>0) {
		cout << "Enter the password to Grant access " << endl;
		cin >> pass_entered;
		if (pass_entered == password) {
			clearscreen();
			return true;
			
		}
		else {
			attempts--;
			cout << "Incorrect Password:Attempts left " << attempts << endl;
		}
	}
	cout << "Acces Denied : Too many failed attemptes"  << endl;
	return false;

}
      
void Add_members(int total_members,int size) {
	
	//dynamic memory 
	char* name = new char[size];        
	char* id = new char[size];
	char* age = new char[size];
	char* membership = new char[size];
	char* gender = new char[size];
    //Create File
	ofstream file("members.txt",ios::app);
	if (!file) {
		cout << "Error:Cannot opening a file " << endl;
	}

	cin. ignore();  
	 
	for (int i = 0;i < total_members;i++) {

		cout << "Member " << Count_members + 1 << endl;

		bool fee_paid = false;


		while(true){
		cout << "Enter Member ID " << endl;
		cin.getline(id, size);
		if (is_member_exist(id)) {
			cout << "This ID is already Exist:Please Enter Unique ID " << endl;
		}
		else {
			break;
		}
	}
			cout << "Do you want to submit the fee? (Y/N): ";
			char choice;
			cin >> choice;
			cin.ignore();

			if (choice != 'Y' && choice != 'y') {
				char admin_choice;
				cout << "You choose not to submit the fee " << endl;
				clearscreen();
				cout << "Do you still want to add this member?(Admin decision) (Y/N)  " << endl;
				cin >> admin_choice;
				cin.ignore();
				if (admin_choice != 'Y' && admin_choice != 'y') {
					cout << "Member not added ." << endl;
					i--;
					continue;  //code skip and exit
				}
				else {
					fee_paid = false;
				}
			}
			else {
				fee_submission(id);
				if (!is_fee_submitted(id)) {
					cout << "Fees are not submitted:Please submit the fee to continue " << endl;
					i--;
					continue;


				}
				fee_paid = true;
			}
		
		
		cout << "Enter Member Name " << endl;
		cin.getline(name, size);

		cout << "Enter Member Age " << endl;
		cin.getline(age, size);

		cout << "Enter your gender " << endl;
		cin.getline(gender, size);

		cout << "Enter Membership Type(Monthly(M)/Yearly(Y))  " << endl;
		cin.getline(membership, size);

		file<< "ID: " << id << ", Name: " << name << ", Age: " << age << ", Gender: "<<gender<<", Membership: " << membership;

		if (fee_paid) {
			file << ",Fee:Paid "<<endl;
		}
		else {
			file << ",Fee:UnPaid " << endl;
		}
		

		cout << "Members Added Successfully " << endl;

		Count_members++;
		
	}
	delete[] id;
	delete[] name;
	delete[] age;
	delete[] gender;
	delete[] membership;
	file.close();

}
//Function to Count how many members exist 
int get_existing_members() {
	ifstream fin("members.txt");
	const int size = 300;
	if (!fin) {
		cout << "Error:Cannot Opening a file " << endl;
	}
	int count = 0;
	char* line = new char[size];
	while (fin.getline(line, size)) {
		count++;
	}

	delete[] line;
	fin.close();
	return count;
}
//View Members 
void View_members() {

	
	ifstream fin("members.txt");
	const int size = 300;
	if (!fin) {
		cout << "Error:Cannot Opening a file " << endl;
	}
	char* line = new char[size];
	cout << "\033[1;30m==========================================================GYM MEMBERS LIST==============================================\033[0m " << endl << endl<<endl;
	cout << " ---------------------------------------------------------------------+" << endl;
	while (fin.getline(line, size)){
		
		
		cout << "|" << endl;
	    cout << "|" << endl;
		cout << "\033[1;36m"<<line<<"\033[0m" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		
		
	}
	cout << " --------------------------------------------------------------------+" << endl;



	delete[] line;
	fin.close();

}
void update_members(char update_id[]) {
	
	ifstream fin("members.txt");
	ofstream fout("Temp.txt");

	if (!fin || !fout) {
		cout << "File cannot open " << endl;
	}

	const int size = 100;
	char* new_id = new char[size];
	char* new_name = new char[size];
	char* new_age = new char[size];
	char* new_gend = new char[size];
	char* new_membership = new char[size];
	char* line = new char[size];
	
	bool updated = false;
	
	while (fin.getline(line, size)) {
		int i = 0;//check character in file
		bool match = false;
		//Search for "ID: " and compare woth updated id 
		while (line[i] != '\0') {
			if (line[i] == 'I' && line[i + 1] == 'D' && line[i+2] == ':') {
				i += 4;//move to start of actual id like 1234 after "ID" characters 

				int j = 0;  //check character for update_id

				//compare the entered id from file  
				while (update_id[j] != '\0' && line[i] == update_id[j]) {
					i++;
					j++;
				}
				//if line continues with comma space and end its match
				if (update_id[j] == '\0' && (line[i] == ',' || line[i] == ' ' || line[i] == '\0')) {
					match = true;
				}
				break;
			}
			i++;//keep scanning if ID not found
		}
		//if match than take input from user
		if (match) {
			cout << "The data of current member founded " << endl<<endl;
			cout << line << endl;

			cout << "Enter new name "<<endl;
			cin.getline(new_name, size);
			cout << "Enter new ID "<<endl;
			cin.getline(new_id, size);
			cout << "Enter new Age "<<endl;
			cin.getline(new_age, size);
			cout << "Enter gender "<<endl;
			cin.getline(new_gend, size);
			cout << "Enter new Membership type(Monthly(M)/Yearly(Y)) "<<endl;
			cin.getline(new_membership, size);
			
			cout << endl<< "Updated data of member is  " << endl;
			cout << "+------------------------------------------------------------------------------------------------------+" << endl;
			cout << "|                                                                                                      |" << endl;
			cout << "|                                                                                                      |" << endl;
			cout << "\033[1;36mID: " << new_id << ", Name: " << new_name << ", Age: " << new_age << ", Gender: " << new_gend <<", Membership: " << new_membership <<", Fee Paid "<<"\033[0m" << endl;
			cout << "|                                                                                                      |" << endl;
			cout << "|                                                                                                      |" << endl;
			cout << "+------------------------------------------------------------------------------------------------------+" << endl << endl << endl;
			fout << "ID: " << new_id << ", Name: " << new_name << ", Age: " << new_age <<", Gender: "<<new_gend<<", Membership: " << new_membership <<", Fee Paid "<< endl;
			updated = true;

		}
		else {
			fout << line << endl;
		}
	}
	delete[] line;
	delete[] new_id;
	delete[] new_name;
	delete[] new_age;
	
	delete[] new_membership;

	fin.close();
	fout.close();

	//overwrite the old data with new one
	ifstream temp_file_read("Temp.txt");
	ofstream write_in_main("members.txt");

	if(!temp_file_read || !write_in_main){
		cout << "Error in file overwritten " << endl;
  }
	char * line_copied = new char[size];
	while (temp_file_read.getline(line_copied, size)) {
		write_in_main << line_copied << endl;
	} 
	delete[] line_copied;
	temp_file_read.close();
	write_in_main.close();
	if (updated) {
		cout << "Member updated successfully." << endl;
	}
	else{
		cout << "Member with given ID not found." << endl;
}

	}

bool is_member_exist(char id[]) {
	ifstream fin("members.txt");
	if (!fin) {
		cout << "File cannot open " << endl;
	}
	const int size = 100;
	char* line = new char[size];

	bool found = false;

	while (fin.getline(line, size)) {	
		int i = 0;
		bool match = false;
		//Search for "ID: " and compare woth updated id 
		while (line[i] != '\0') {
			if (line[i] == 'I' && line[i + 1] == 'D' && line[i + 2] == ':') {
				i += 4;//move to start of actual id like 1234 after "ID" characters 
				int j = 0;
				//compare the entered id from file 
				while (id[j] != '\0' && line[i] == id[j]) {
					i++;
					j++;
				}
				//if line continues with comma space and end its match
				if (id[j] == '\0' && (line[i] == ',' || line[i] == ' ' || line[i] == '\0')) {
					found = true;
					break;
				}

			}
            i++;
		}
		if (found) {
			break;
		}
	}
	delete[] line;
		fin.close();
		return found;
	}
void search_member_by_ID(char search_id[]) {
	
	ifstream fin("members.txt");
	if (!fin) {
		cout << "File cannot open " << endl;
	}
	const int size = 100;
	char* line = new char[size];

	bool found = false;




	while (fin.getline(line, size)) {
		int i = 0;
		bool match = false;
		//Search for "ID: " and compare woth updated id 
		while (line[i] != '\0') {
			if (line[i] == 'I' && line[i + 1] == 'D' && line[i + 2] == ':') {
				i += 4;//move to start of actual id like 1234 after "ID" characters 
				int j = 0;
				//compare the entered id from file 
				while (search_id[j] != '\0' && line[i] == search_id[j]) {
					i++;
					j++;
				}
				//if line continues with comma space and end its match
				if (search_id[j] == '\0' && (line[i] == ',' || line[i] == ' ' || line[i] == '\0')) {
					found = true;
					cout << "Member found " << endl << line << endl;

					if (is_fee_submitted(search_id)) {
						cout << "Fee Status:Submitted " << endl;
					}
					else {
						cout << "Fee Status:Not Submitted " << endl;
					}
					break;
				}
			}

			i++;
		}
		if (found) {
			break;
		}

	}

	if (!found) {
		cout << "Member with ID " << search_id << " not found " << endl;
	}

	delete[] line;
	fin.close();

}
	


bool is_fee_submitted(char id[]) {
	ifstream fin("fees.txt");
	if (!fin) {
		cout << "File cannot open " << endl;
	}
	const int size = 100;
	char* line = new char[size];

	bool found = false;

	while (fin.getline(line, size)) {
		int i = 0;
		bool match = false;
		//Search for "ID: " and compare woth updated id 
		while (line[i] != '\0') {
			if (line[i] == 'I' && line[i + 1] == 'D' && line[i + 2] == ':') {
				i += 4;//move to start of actual id like 1234 after "ID" characters 
				int j = 0;
				//compare the entered id from file 
				while (id[j] != '\0' && line[i] == id[j]) {
					i++;
					j++;
				}
				//if line continues with comma space and end its match
				if (id[j] == '\0' && (line[i] == ',' || line[i] == ' ' || line[i] == '\0')) {
					found = true;
					break;
				}

			}

			i++;
		}
		if (found) {
			break;
		}
	}
	delete[] line;
	fin.close();

	return found;

}
void fee_submission(char member_id[]) {
	
	const int size = 100;
	int fees_of_gym = 2000;
	char choice[size];
	cout << "====================================================Fee Submission=====================================================" << endl<<endl<<endl;

	if (is_fee_submitted(member_id)) {
		cout << "Fee has already been submitted for this member ID." << endl;
		return;
	}
    
		
		cout << "Fee for this month is Rs: 2000. Do you want to Submit This fee(Yes/No) " << endl;
		cin.getline(choice, size);

		if ((choice[0] == 'Y' || choice[0] == 'y') && (choice[1] == 'E' || choice[1] == 'e') && (choice[2] == 'S' || choice[2] == 's') && choice[3] == '\0') {

			ofstream fout("fees.txt", ios::app);
			if (!fout) {
				cout << "Error:Cannot opened a File " << endl;
			}

			fout << "ID: " << member_id <<" ,Fee submitted:Yes"<< endl;
			fout.close();
			cout << "Thank you for submitting the fee. Welcome to the Gym!.Stay Healthy " << endl;

		}
		else if ((choice[0] == 'N' || choice[0] == 'n') && (choice[1] == 'O' || choice[1] == 'o') && (choice[2] == '\0')) {
			cout << "You choose not to submit fee. Have a great Day " << endl;


		}
		else {
			cout << "Invaliud Input: Please Type Yes or No " << endl;
		}
		
	}

void view_trainers() {
	
	ifstream trainer_file("trainers.txt");
	if (!trainer_file) {
		cout << "Trainer file not found " << endl;
	}
	char trainer_name[100];
	cout << "Available trainer are " << endl;
	cout << " -----------------------------------------------------------------+" << endl;
	cout << "|" << endl;
	cout << "|" << endl;
	while (trainer_file.getline(trainer_name, 100)) {
		cout <<"\033[1;36m" << trainer_name<<"\033[0m" << endl;
	}
	cout << "|" << endl;
	cout << "|" << endl;
	cout << " -----------------------------------------------------------------+" << endl;
	trainer_file.close();
	}

int load_trainers(char trainers[total_trainers][100]) {
	ifstream fin("trainers.txt");
	if (!fin) {
		cout << "Error:Cannot open trainers file " << endl;

	}

	int count = 0;
	while (fin.getline(trainers[count], 100)) {
		count++;
	}
	fin.close();
	return count;
 }
void hire_trainer(char trainers[total_trainers][100],int count){
                       
	char name[100];
	cin.getline(name, 100);
	int i = 0;
	bool found = false;

		int j = 0;
		for(int i=0;i<count;i++){
			int j = 0;
			while (trainers[i][j] != '\0') {
				if (trainers[i][j] == 'N' && trainers[i][j + 1] == 'a' && trainers[i][j + 2] == 'm' && trainers[i][j + 3] == 'e' && trainers[i][j + 4] == ':')
				{
					j += 5;
					while (trainers[i][j] == ' ') {
						j++;
					}
					break;
				}
				j++;
			}

			int k = 0;
		while (name[k] !='\0' && trainers[i][j] == name[k]  ) {
			k++;
			j++;
		}
		if ( name[k] == '\0' && (trainers[i][j]==',' || trainers[i][j]=='\0')) {
			found = true;
			break;
		}

	}
	if (found) {
		cout << endl << "Trainers " << name << " Hired Successfully:Best of Luck " << endl;
	}
	else {
		cout << "Trainer " << name << " not found " << endl;
	}

}

void view_unpaid_members() {
	ifstream file("members.txt");
	if (!file) {
		cout << "Error:Cannot open a file " << endl;
	}

	const int size = 100;
	char* line = new char[size];
	cout << "\033[1;30m====================================================UNPAID MEMBERS================================================\033[0m" << endl<<endl<<endl;
	while (file.getline(line, size)) {
		char id[50];
		int i = 0, j = 0;
		

		while (line[i] != '\0') {
			if (line[i] == 'I' && line[i + 1] == 'D' && line[i + 2] == ':') {
				i += 4;//ID Skip

				while (line[i] != ',' && line[i] != '\0') {
					id[j++] = line[i++];
					
				}
				id[j] = '\0';
				break;
			}
			i++;
		}
		if (!is_fee_submitted(id)) {
			cout << "+----------------------------------------------------------------------+" << endl;
			cout << "|                                                                      |" << endl;
			cout << "|                                                                      |" << endl;
			cout <<"\033[1;36m" << line<<"\033[0m" << endl;
			cout << "|                                                                      |" << endl;
			cout << "|                                                                      |" << endl;
			cout << "+----------------------------------------------------------------------+" << endl<<endl<<endl;
			
		}
	}

	delete[] line;
	file.close();

}
void gender_stats() {
	
	ifstream file("members.txt");
	if (!file) {
		cout << "Error:Cannot open a file " << endl;
	}

	char line[100];
	int male_count = 0;
	int female_count = 0;
	
	while (file.getline(line, 100)) {
		int pos = -1;
		for (int i = 0;line[i] != '\0';i++) {
			if (line[i] == 'G' && line[i + 1] == 'e' && line[i + 2] == 'n' && line[i + 3] == 'd' && line[i + 4] == 'e' && line[i + 5] == 'r' && line[i + 6] == ':' && line[i + 7] == ' ')
			{
				pos = i + 8;
				break;
			}
		}
		if (pos != -1) {
			char gender[50];
			int j = 0;
			while (line[pos] != ',' && line[pos] != '\0'  && j<9) {
				gender[j] = line[pos];
				j++;
				pos++;
				
			}
		
			gender[j] = '\0';


			bool is_male = true;
			char male[] = "male";
			int k = 0;
			for(int k=0;k<4;k++) {
				if (gender[k] != male[k]) {
					is_male = false;
					break;

				}

			}
			if (is_male && gender[4]=='\0') {
				male_count++;

			}
			else {
				female_count++;
			}
		}
	}
	cout << "\t\t\t\t" << "\033[1;36m+------------------------------------------------------------+\033[0m" << endl;
	cout << "\t\t\t\t" << "\033[1;36m|                    GENDER STATISTICS REPORT                |\033[0m" << endl;
	cout << "\t\t\t\t" << "\033[1;36m+------------------------------------------------------------+\033[0m" << endl;
	cout << "\t\t\t\t"<<  "\033[1;36m|                                                            |\033[0m" << endl;

	cout << "\t\t\t\t" << "Total Male Members are " << male_count << endl;
	cout << "\t\t\t\t" << "Total FeMale Members are " << female_count << endl;

	cout  <<"\t\t\t\t" << "\033[1;36m|                                                            |\033[0m" << endl;
	cout  <<"\t\t\t\t" << "\033[1;36m+------------------------------------------------------------+\033[m" << endl;
}

void fee_stats() {
	
	ifstream file("members.txt");
	if (!file) {
		cout << "Error:Cannot open a file " << endl;
	}

	char line[100];
	int paid_members = 0;
	int unpaid_members = 0;

	while (file.getline(line, 100)) {
		int pos = -1;
		for (int i = 0;line[i] != '\0';i++) {
			if (line[i] == 'F' && line[i + 1] == 'e' && line[i + 2] == 'e' && line[i + 3] == ':' )
			{
				pos = i + 4;
				break;
			}
		}
		if(pos!=-1){
		while (line[pos] == ' ') {
			pos++;

		}
		char status[50];
			int j = 0;
			while (line[pos] != ',' && line[pos] != '\0' && j < 9) {
				status[j] = line[pos];
				j++;
				pos++;

			}

			status[j] = '\0';


			bool is_paid = true;
			char word[] = "Paid";
			int k = 0;
			for (int k = 0;k < 4;k++) {
				if (status[k] != word[k]) {
					is_paid = false;
					break;

				}

			}
			if (is_paid && status[4] == '\0') {
				paid_members++;

			}
			else {
				unpaid_members++;
			}
		}
	}
   int total = paid_members + unpaid_members++;;
	cout << "\t\t\t\t" << "\033[1;36m+------------------------------------------------------------+\033[0m" << endl;
	cout << "\t\t\t\t" << "\033[1;36m|                    Fee Statistics Report                   |\033[0m " << endl;
	cout << "\t\t\t\t" << "\033[1;36m+------------------------------------------------------------+\033[0m" << endl;
	cout << "\t\t\t\t" << "\033[1;36m|                                                            |\033[0m" << endl;

	cout << "\t\t\t\t" << "Total Members are" << total << endl;
	cout << "\t\t\t\t" << "Total Paid Member are " << paid_members << endl;
	cout << "\t\t\t\t" << "Total UnPaid Member are " << unpaid_members << endl;

	cout << "\t\t\t\t" << "\033[1;36m|                                                            |\033[0m" << endl;
	cout << "\t\t\t\t" << "\033[1;36m+------------------------------------------------------------+\033[0m" << endl;
}
void delete_member_by_ID(char del_Id[]) {
	
	ifstream fin("members.txt");
	ofstream file("del_data.txt");
	if (!fin||!file) {
		cout << "Error:File cannot open " << endl;
	}

	const int size = 100;
	char* line = new char[size];

	bool del = false;

	while (fin.getline(line, size)) {
		int i = 0;
		bool match = false;
		//Search for "ID: " and compare woth updated id 
		while (line[i] != '\0') {
			if (line[i] == 'I' && line[i + 1] == 'D' && line[i + 2] == ':') {
				i += 4;//move to start of actual id like 1234 after "ID" characters 
				int j = 0;
				//compare the entered id from file 
				while (del_Id[j] != '\0' && line[i] == del_Id[j]) {
					i++;
					j++;
				}
				//if line continues with comma space and end its match
				if (del_Id[j] == '\0' && (line[i] == ',' || line[i] == ' ' || line[i] == '\0')) {
					match = true;
					del = true;
					
				}
				break;
			}

			i++;
		}
		if (!match){
			file << line << endl;
		}
		else {
			del = true;
		}
	}
	delete[] line;
	fin.close();
	file.close();

	ifstream from("del_data.txt");
	ofstream to("members.txt");

	if (!from|| !to) {
		cout << "Error:File cannot open " << endl;
	}
	char temp[size];
	while (from.getline(temp,size)) {
		to << temp << endl;
	}
	from.close();
	to.close();
	if (del) {
		cout << "Member Deleted Successfully " << endl;
		Count_members--;

	}
	else {
		cout << "Member ID not Found " << endl;
	}
}
