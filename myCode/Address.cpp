/*
 * Address.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#include "Address.h"
#include <iostream>

Address::Address(std::string street,unsigned short postalCode,std::string cityName,
		std::string additionalInfo):street(street),postalCode(postalCode),cityName(cityName),
		additionalInfo(additionalInfo)
{}

Address::~Address()
{
	// TODO Auto-generated destructor stub
}

const std::string& Address::getAdditionalInfo() const
{
	return additionalInfo;
}

const std::string& Address::getCityName() const
{
	return cityName;
}

unsigned short Address::getPostalCode() const
{
	return postalCode;
}

const std::string Address::getStreet() const
{
	return (const std::string&) street;
}
