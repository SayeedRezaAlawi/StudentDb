/*
 * Address.h
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_
#include <string>

class Address
{
private:
	std::string street;
	unsigned short postalCode;
	std::string cityName;
	std::string additionalInfo;
public:
	Address(std::string street,	unsigned short postalCode,std::string cityName,std::string additionalInfo);
	virtual ~Address();
	const std::string& getAdditionalInfo() const;
	const std::string& getCityName() const;
	unsigned short getPostalCode() const;
	const std::string getStreet() const;
};

#endif /* ADDRESS_H_ */
