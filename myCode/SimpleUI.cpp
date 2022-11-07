/*
 * SimpleUI.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#include "SimpleUI.h"
#include <iostream>
#include <fstream>

SimpleUI::SimpleUI(StudentDb& db):db(&db)
{
	// TODO Auto-generated constructor stub

}

void SimpleUI::run()
{
	int choice=-1;
	while(choice)
	{
		std::cout<<std::endl<<"Commands for Database:"<<std::endl;
	    std::cout << "1. Add New Course" << std::endl
	    		  << "2. List Courses" << std::endl
				  << "3. Add New Student" << std::endl
				  << "4. Add Enrollment" << std::endl
				  << "5. Print Student" << std::endl
				  << "6. Search Student" << std::endl
				  << "7. Update Student" << std::endl
				  << "8. Write Db to file" << std::endl
				  << "9. Read from file to DB" << std::endl
				  << "10. Get Student Data from Server"<<std::endl
				  << "0. Enter Choice of Command (0 to terminate)"<<std::endl;
	    std::cin >> choice;
	    switch(choice)
	    {
	    case 1:db->addNewCourse();break;
	    case 2:db->listCourse();break;
	    case 3:db->addNewStudent();break;
		case 4:db->addNewEnrollment();break;
		case 5:db->printStudent();break;
		case 6:db->searchStudent();break;
		case 7:db->updateStudent();break;
		case 8:{
			std::string fileName;
			std::ofstream file;
			std::cout<<std::endl<<"Enter File Name"<<std::endl;
			std::cin>>fileName;
			file.open(fileName);
			db->write(file);
			file.close();
			break;}
		case 9:{
			std::string fileName;
			std::ifstream file;
			std::cout<<std::endl<<"Enter File Name"<<std::endl;
			std::cin>>fileName;
			file.open(fileName);
			db->read(file);
			file.close();
			break;}
		case 10:
			db->getServerData();
			break;
	    }
	}
}

SimpleUI::~SimpleUI()
{
	// TODO Auto-generated destructor stub
}

