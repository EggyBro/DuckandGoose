/*!*************************************************************************
****
\file JSONserialization.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains the function definitions for the JSONSerializer
class which allows child classes of this class to define the data type they
serialize and deserialize using virtual functions.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "JSONserialization.h"
#include "ExoEngine/Audio/AudioEngine.h"

namespace EM
{
	/*!*************************************************************************
	Json Serializer for calling Derived class Serialize function
	****************************************************************************/
	std::string JSONSerializer::Serialize() const
	{
		rapidjson::StringBuffer ss;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(ss);
		if (Serialize(&writer)) 
		{ 
			return ss.GetString();
		}
		return "";
	}

	/*!*************************************************************************
	Json Deserializer for calling Derived class Deserialize function
	****************************************************************************/
	bool JSONSerializer::Deserialize(const std::string& stringbuffer)
	{
		rapidjson::Document doc;
		doc.Parse(stringbuffer.c_str());
		if (!InitDocument(stringbuffer, doc))
		{
			return false;
		}
		else
		{
			p_Audio->StopChannel(CAudioEngine::channel_groups::master);
			p_Audio->StopChannel(CAudioEngine::channel_groups::bgm);
			p_Audio->StopChannel(CAudioEngine::channel_groups::sfx);
			Deserialize(doc);
		}
		return true;
	}

	/*!*************************************************************************
	Funtion for Deserializing to JSON file
	****************************************************************************/
	bool JSONSerializer::DeserializeFromFile(const std::string& filePath)
	{
		std::ifstream ifs(filePath, std::ios::in);
		std::stringstream buffer;
		buffer << ifs.rdbuf();
		ifs.close();

		return Deserialize(buffer.str());
	}

	/*!*************************************************************************
	Funtion for Serializing to JSON file
	****************************************************************************/
	bool JSONSerializer::SerializeToFile(const std::string& filePath)
	{
		std::ofstream ofs(filePath);
		std::string str = Serialize();
		ofs << str;
		ofs.flush();
		ofs.close();

		return true;
	}

	/*!*************************************************************************
	Checks if Document can be Read
	****************************************************************************/
	bool JSONSerializer::InitDocument(const std::string& stringbuffer, rapidjson::Document& doc)
	{
		if (stringbuffer.empty())
			return false;

		std::string validJson(stringbuffer);

		return !doc.Parse(validJson.c_str()).HasParseError() ? true : false;
	}
}