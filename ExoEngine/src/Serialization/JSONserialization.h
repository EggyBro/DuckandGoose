/*!*************************************************************************
****
\file JSONserialization.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains the function declarations for the JSONSerializer
class which allows child classes of this class to define the data type they
serialize and deserialize using virtual functions.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/

#pragma once
#include "JSONincludes.h"
#include "empch.h"
#include "ExoEngine/Core.h"

namespace EM
{

	class EM_API JSONSerializer
	{
		public:
			/*!*************************************************************************
			Funtion for Deserializing to JSON file
			****************************************************************************/
			bool DeserializeFromFile(const std::string& filePath);
			/*!*************************************************************************
			Funtion for Serializing to JSON file
			****************************************************************************/
			bool SerializeToFile(const std::string& filePath);

			/*!*************************************************************************
			Json Serializer for calling Derived class Serialize function
			****************************************************************************/
			virtual std::string Serialize() const;
			/*!*************************************************************************
			Json Deserializer for calling Derived class Deserialize function
			****************************************************************************/
			virtual bool Deserialize(const std::string& s);

			/*!*************************************************************************
			Virtual deserialize function for derived classes to overload
			****************************************************************************/
			virtual bool Deserialize(const rapidjson::Value& obj) = 0;
			/*!*************************************************************************
			Virtual serialize function for derived classes to overload
			****************************************************************************/
			virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const = 0;

			virtual ~JSONSerializer() = default;

		protected:
			/*!*************************************************************************
			Checks if Document can be Read
			****************************************************************************/
			bool InitDocument(const std::string& s, rapidjson::Document& doc);
	};
}