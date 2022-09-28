#include "empch.h"
#include "JSONserialization.h"

namespace EM
{
	std::string JSONSerializer::Serialize() const
	{
		rapidjson::StringBuffer ss;
		rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
		if (Serialize(&writer)) 
		{ 
			return ss.GetString();
		}
		return "";
	}

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
			Deserialize(doc);
		}
		return true;
	}

	bool JSONSerializer::DeserializeFromFile(const std::string& filePath)
	{
		std::ifstream ifs(filePath);
		std::stringstream buffer;
		buffer << ifs.rdbuf();
		ifs.close();

		return Deserialize(buffer.str());
	}

	bool JSONSerializer::SerializeToFile(const std::string& filePath)
	{
		std::ofstream ofs(filePath);
		std::string str = Serialize();
		ofs << str;
		ofs.flush();
		ofs.close();

		return true;
	}

	bool JSONSerializer::InitDocument(const std::string& stringbuffer, rapidjson::Document& doc)
	{
		if (stringbuffer.empty())
			return false;

		std::string validJson(stringbuffer);

		return !doc.Parse(validJson.c_str()).HasParseError() ? true : false;
	}
}