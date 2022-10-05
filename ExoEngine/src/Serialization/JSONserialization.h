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
****************************************************************************
***/

#pragma once
#include "JSONincludes.h"
#include "ExoEngine/Core.h"

namespace EM
{

	class EM_API JSONSerializer
	{
		public:
			bool DeserializeFromFile(const std::string& filePath);
			bool SerializeToFile(const std::string& filePath);

			virtual std::string Serialize() const;
			virtual bool Deserialize(const std::string& s);

			virtual bool Deserialize(const rapidjson::Value& obj) = 0;
			virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const = 0;

			virtual ~JSONSerializer() = default;

		protected:
			bool InitDocument(const std::string& s, rapidjson::Document& doc);
	};
}