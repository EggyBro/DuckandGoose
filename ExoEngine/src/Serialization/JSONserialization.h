/*
* Abstract Class for JSON serialization and deserialization
*/ 
#pragma once
//#include "empch.h"
#include "RapidJSON/rapidjson.h"
#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/stringbuffer.h"	// wrapper of C stream for prettywriter as output
#include "rapidjson/prettywriter.h"	// for stringify JSON
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