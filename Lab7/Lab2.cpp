#include"DataBase.h"

int main()
{
	DataBase base;
	if (base.LoadFromFile("data_base.csv") == false) {
		cout << "WRONG FILE\n";
		getchar();
		return 0;
	}
	else {
		base.ArrangeSubordinates();
		cout << "DATA BASE WAS CREATED FROM FILE" << endl;
	}

	while (true) {
		cout << "1. DISPLAY ALL\n2. DISPLAY IT DEPARTMENT\n3. SQL REQUEST \nQ. QUIT\n"
			<< "CHOSE THE OPTION : ";
		char c;
		cin >> c;
		system("cls");
		switch (c)
		{
		case 'Q' :
			return 0;
		case '1' :
			base.DisplayAll();
			break;
		case '2' :
			base.DisplayDepartmentEmployees("IT");
			break;
		case '3' :
			base.ShowRecordSet(base.SQL("age", "lt", "36"));
			break;
		default :
			cin >> c;
			break;
		}
	}
    return 0;
}

