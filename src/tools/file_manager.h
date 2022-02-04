/*
 * CPW Woodpecker Server
 * Copyright (C) 2021 CPW Online support@cpwonline.org
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CPW_TOOLS_FILEMANAGER_H
#define CPW_TOOLS_FILEMANAGER_H


#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <memory>

#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/DateTime.h"
#include "Poco/Random.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/CountingStream.h"
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/JSONException.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>

#include "extras/file_properties.h"


namespace CPW
{
	namespace Tools
	{
		enum class OperationType;
		enum class FileType;
		class FileManager;
	}
}

using namespace Poco;
using namespace Poco::Net;


enum class CPW::Tools::OperationType
{
	kDownload
	,kUpload
	,kReplace
	,kDelete
};

enum class CPW::Tools::FileType
{
	kBinary
	,kTextPlain
};


class CPW::Tools::FileManager: public Net::PartHandler
{
	public:
		FileManager();
		~FileManager();

		std::shared_ptr<Path> get_requested_path() const{return requested_path_;}
		std::map<std::string, Extras::FileProperties>& get_supported_files()
		{
			auto& var = supported_files_;
			return var;
		}
		std::shared_ptr<File>& get_requested_file()
		{
			auto& var = requested_file_;
			return var;
		}
		OperationType get_operation_type() const{return operation_type_;}
		FileType get_file_type() const{return file_type_;}
		std::string get_directory_base() const{return directory_base_;}
		std::string get_directory_for_uploaded_files() const{return directory_for_uploaded_files_;}
		std::string get_directory_for_temp_files() const{return directory_for_temp_files_;}
		std::size_t get_content_length() const{return content_length_;}
		std::string get_content_type() const{return content_type_;}
		std::string get_name() const {return name_;}
		std::string get_filename() const {return filename_;}
		JSON::Array::Ptr get_result() const {return result_;}

		void set_operation_type(OperationType operation_type){operation_type_ = operation_type;}
		void set_filename(std::string filename) {filename_ = filename;}

		void handlePart(const MessageHeader& header, std::istream& stream) override;
		bool CheckFile_(Path path);
		bool IsSupported_();
		void ProcessContentType_();
		void ManageFile_(std::ostream& out_response);

	protected:
		void ManageBinaryFile_(std::ostream& out_response);
		void ManageTextPlainFile_(std::ostream& out_response);

	private:
		void AddSupportedFiles_();

		std::shared_ptr<Path> requested_path_;
		std::shared_ptr<File> requested_file_;
		std::map<std::string, Extras::FileProperties> supported_files_;
		OperationType operation_type_;
		FileType file_type_;
		std::string directory_base_;
		std::string directory_for_uploaded_files_;
		std::string directory_for_temp_files_;
		std::size_t content_length_;
		std::string content_type_;
		std::string name_;
		std::string filename_;
		Extras::FileProperties* file_properties_;
		JSON::Array::Ptr result_;
};

#endif // CPW_TOOLS_FILEMANAGER_H
